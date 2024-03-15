#ifndef __SERVO_H
#define __SERVO_H

void Servo_Init(void);
void Servo_SetAngle_UP(float Angle1);
void Servo_SetAngle_DOWN(float Angle2);
void circle(void);
void setServoAngle_UP(float Angle);
void setServoAngle_DOWN(float Angle);
void restoration(void);
float TransformY(float Y, float X);
float TransformX(float X);
void FindLocation(float x,float y);
float Transform(float y);
float zhuanhuan(uint8_t RxData);

#endif
