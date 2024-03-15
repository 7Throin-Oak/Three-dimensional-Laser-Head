#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "math.h"
void Servo_Init(void)
{
	initPWM();
}

void Servo_SetAngle_UP(float Angle)
{
	PWM_SetCompare3(Angle / 180 * 2000 + 500);
	
}

void Servo_SetAngle_DOWN(float Angle)
{
	PWM_SetCompare4(Angle / 180 * 2000 + 500);
	
}
void setServoAngle_UP(float Angle) {
    // 将角度转换为对应的脉冲宽度
    uint16_t pulse_width = 500 + (uint16_t)(Angle / 180.0 * 2000);

    // 设置TIM2和TIM3的通道1和通道2的脉冲宽度
    TIM2->CCR1 = pulse_width;
    
}
void setServoAngle_DOWN(float Angle) {
    // 将角度转换为对应的脉冲宽度
    uint16_t pulse_width = 500 + (uint16_t)(Angle / 180.0 * 2000);

    // 设置TIM2和TIM3的通道1和通道2的脉冲宽度
    TIM3->CCR2 = pulse_width;
	
	
	
}


void circle(){
	
        setServoAngle_UP(2.6);
		setServoAngle_DOWN(90);
        Delay_ms(1000);
	
		setServoAngle_UP(1.4);
		setServoAngle_DOWN(117.5);
		Delay_ms(1000);
	
		setServoAngle_UP(22);
		setServoAngle_DOWN(118);
		Delay_ms(1000);
	
		setServoAngle_UP(38);
		setServoAngle_DOWN(118);
		Delay_ms(1000);
	
	
		setServoAngle_UP(42);
		setServoAngle_DOWN(90);
		Delay_ms(1000);
		
		
		setServoAngle_UP(39);
		setServoAngle_DOWN(66);
		Delay_ms(1000);
		
		setServoAngle_UP(26);
		setServoAngle_DOWN(64.5);
		Delay_ms(1000);
		
		setServoAngle_UP(3);
		setServoAngle_DOWN(63.5);
		Delay_ms(1000);
		
		
}


void restoration(void){//复位函数
	
	setServoAngle_DOWN(90);
	setServoAngle_UP(2.6);
	Delay_ms(1000);
	setServoAngle_DOWN(90);
	setServoAngle_UP(26);
	Delay_ms(1000);


}

float TransformX(float X)
{
    float Angle_X;
    float Rad_X;
    Rad_X = atan(fabs(X) / sqrt(2504.8)); // X取值为-25~25
    if (X >= 0)
    {
        Angle_X = (180 * Rad_X) / 3.14;
        Angle_X = 90 + Angle_X;
    }
    else
    {
        Angle_X = (180 * Rad_X) / 3.14;
        Angle_X = 90 - Angle_X;
    }
    return Angle_X;
}

float TransformY(float Y, float X)
{
    float Angle_Y;
    float Rad_Y;
    if (X >= 0)
    {
        Rad_Y = atan((Y) / 50) - 0.001 * X; // Y取值为0~50
    }
    else
    {
        Rad_Y = atan((Y) / 50); // Y取值为0~50
    }
    Angle_Y = (180 * Rad_Y) / 3.14;
    return Angle_Y;
}

float Transform(float y)
{
    float y2;
    y2 = y * 0.81 + 2.2;
    return y2;
}

void FindLocation(float x,float y){//所以我只要输入正常坐标即可
	
	float Angle_x = TransformX(x);//将坐标下的x（0-25和-25-0）输入并转换为舵机角度坐标
    float transformed_y_2 = Transform(y);//先将y（0-50）范围下的转换为（2.2-42.7）范围下的y
    float Angle_y = TransformY(transformed_y_2, x);//再将真正的角度坐标y换算出来
    setServoAngle_UP(Angle_y);
    setServoAngle_DOWN(Angle_x);
	
	
}

float zhuanhuan(uint8_t RxData)
{
	float Angle = 90;
	if (RxData ==0x3A)
		Angle=58;
	if (RxData ==0x3B)
		Angle=59;
	if(RxData == 0x3C)
		Angle=60;
	if(RxData == 0x3D)
		Angle=61;
	if(RxData == 0x3E)
		Angle=62;
	if(RxData == 0x3F)
		Angle=63;
	if(RxData == 0x40)
		Angle=64;
	if(RxData == 0x41)
		Angle=65;
	if(RxData == 0x42)
		Angle=66;
	if(RxData == 0x43)
		Angle=67;
	if(RxData == 0x44)
		Angle=68;
	if(RxData == 0x45)
		Angle=69;
	if(RxData == 0x46)
		Angle=70;
	if(RxData == 0x47)
		Angle=71;
	if(RxData == 0x48)
		Angle=72;
	if(RxData == 0x49)
		Angle=73;
	if(RxData == 0x4A)
		Angle=74;
	if(RxData == 0x4B)
		Angle=75;
	if(RxData == 0x4C)
		Angle=76;
	if(RxData == 0x4D)
		Angle=77;
	if(RxData == 0x4E)
		Angle=78;
	if(RxData == 0x4F)
		Angle=79;
	if(RxData == 0x50)
		Angle=80;
	if(RxData == 0x51)
		Angle=81;
	if(RxData == 0x52)
		Angle=82;
	if(RxData == 0x53)
		Angle=83;
	if(RxData == 0x54)
		Angle=84;
	if(RxData == 0x55)
		Angle=85;
	if(RxData == 0x56)
		Angle=86;
	if(RxData == 0x57)
		Angle=87;
	if(RxData == 0x58)
		Angle=88;
	if(RxData == 0x59)
		Angle=89;
	if(RxData == 0x5A)
		Angle=90;
	if(RxData == 0x5B)
		Angle=91;
	if(RxData == 0x5C)
		Angle=92;
	if(RxData == 0x5D)
		Angle=93;
	if(RxData == 0x5E)
		Angle=94;
	if(RxData == 0x5F)
		Angle=95;
	if(RxData == 0x60)
		Angle=96;
	if(RxData == 0x61)
		Angle=97;
	if(RxData == 0x62)
		Angle=98;
	if(RxData == 0x63)
		Angle=99;
	if(RxData == 0x64)
		Angle=100;
	if(RxData == 0x65)
		Angle=101;
	if(RxData == 0x66)
		Angle=102;
	if(RxData == 0x67)
		Angle=103;
	if(RxData == 0x68)
		Angle=104;
	if(RxData == 0x69)
		Angle=105;
	if(RxData == 0x6A)
		Angle=106;
	if(RxData == 0x6B)
		Angle=107;
	if(RxData == 0x6C)
		Angle=108;
	if(RxData == 0x6D)
		Angle=109;
	if(RxData == 0x6E)
		Angle=110;
	if(RxData == 0x6F)
		Angle=111;
	if(RxData == 0x70)
		Angle=112;
	if(RxData == 0x71)
		Angle=113;
	if(RxData == 0x72)
		Angle=114;
	if(RxData == 0x73)
		Angle=115;
	if(RxData == 0x74)
		Angle=116;
	if(RxData == 0x75)
		Angle=117;
	if(RxData == 0x76)
		Angle=118;
	if(RxData == 0x77)
		Angle=119;
	if(RxData == 0x78)
		Angle=120;
	if(RxData == 0x79)
		Angle=121;
	if(RxData == 0x7A)
		Angle=122;
	
	
	return Angle;
}

