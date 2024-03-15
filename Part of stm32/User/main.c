#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <stdint.h>
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <stdarg.h>
#include "Serial.h"


// 函数声明
void initUSART1(void);
void sendStringUSART1(const char *str);
void receiveStringUSART1(char *buffer, int bufferSize);
float Angle_UP;
float Angle_DOWN;
float Angle_Y; // 角度值转动角
float Angle_X; // 角度值转动角
float X;       // 对应的纸面坐标X
float Y;       // 对应的纸面坐标Y
float Rad_X;   // 弧度制转动角
float Rad_Y;   // 弧度制转动角
uint8_t RxData;
uint8_t RyData;

void initPWM(void);
void circle(void);
void FindLocation(float x,float y);
void restoration(void);
void setServoAngle_DOWN(float Angle);
void setServoAngle_UP(float Angle);



#include "stm32f10x.h"

void USART1_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 启动GPIOA和USART1的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // 配置USART1 TX (PA.09) 为复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART1 RX (PA.10) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART1
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    // 启动USART1
    USART_Cmd(USART1, ENABLE);
}

float hexto(char c)
{
	float ret = 0;
	if(c >= '0' && c <= '9')
	{
		ret = c - '0';
	}
	else if(c >= 'a' && c <= 'f')
	{
		ret = c - 'a';
		ret += 10;
	}
	return ret;
}
//void test05()
//{
//	//Serial_Init();
//    while (1)
//    {
//        // 从串口接收数据

//        char received_data[4];
//        USART1_Init();

//        while (1)
//        {
//            /* Wait until the USART1 receive data register is not empty */
//            while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//            {
//                OLED_ShowString(1, 1, "NoFound1111");
//            }
//                
//           
//            /* Read the received data */
//            received_data[0] = USART_ReceiveData(USART1);
//		    received_data[1] = USART_ReceiveData(USART1);
//			received_data[2] = USART_ReceiveData(USART1);
//		    received_data[3] = USART_ReceiveData(USART1);
//		
//			float data0 = hexto(received_data[0]);
//			float data1 = hexto(received_data[1]);
//			float temp_x = data0 * 16 + data1;
//			int test_x = (int)temp_x;

//            /* Wait until the USART1 receive data register is not empty */
////            while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
////            {
////                OLED_ShowString(2, 1, "NoFound2222");
////            }

//            /* Read the received data */
//			
//			float data2 = hexto(received_data[2]);
//			float data3 = hexto(received_data[3]);
//			float temp_y = data2 * 16 + data3;
//			int test_y = (int)temp_y;
//			Serial_SendNumber(test_x-50, 2);
//			Serial_SendNumber(test_y, 2);
//			Delay_ms(500);
//		
//            /* Do something with the received data */
//            // ...

//            float x = TransformX(temp_x-50);
//    
//            float y_2 = Transform(temp_y);
//            float y = TransformY(y_2, temp_x-50);

//            OLED_ShowString(2, 1, "RxData:");
//            OLED_ShowNum(3, 1, x, 3);
//            OLED_ShowNum(4, 1, y, 5);

//            setServoAngle_UP(y);
//            setServoAngle_DOWN(x);
//           
//			
//           // circle(); // 绕圈函数
//        }
//    }
//}

void test05() 
{
	OLED_ShowString(2,1,"WORKING");
	Serial_Init();
	Servo_Init();
	
	
	
    setServoAngle_DOWN(90);
	setServoAngle_UP(2.6);
	while(1){
		if (Serial_GetRxFlag() == 1)
		{
			static uint8_t rx_count=0;
			static uint8_t rx_data[2];
			OLED_ShowString(1,1,"WORKING");
			if(rx_count<2)
			{
				rx_data[rx_count++]=Serial_GetRxData();
				
			}
			
			if(rx_count == 2)
			{
				float Anglex = zhuanhuan(rx_data[0]);
				float Angley = zhuanhuan(rx_data[1]);
				Angley -= 60;
				
				
				OLED_ShowNum(3,1,Anglex,3);
				OLED_ShowNum(4,1,Angley,3);
				OLED_ShowHexNum(3,7,rx_data[0],4);
				OLED_ShowHexNum(4,7,rx_data[1],4);
				

				setServoAngle_DOWN(Anglex);
				setServoAngle_UP(Angley);
				
				rx_count = 0;
				//Delay_ms(500);
			}
		}
}
}
int main(void)
{

    OLED_Init();
	Servo_Init();
    //restoration();//复位函数 要求二
	
	//FindLocation(20,20);//只需输入正常坐标即可 （要求四 到达指定点函数）
	test05();
	
      while (1)
    {
 //circle();
		
   
}
}
