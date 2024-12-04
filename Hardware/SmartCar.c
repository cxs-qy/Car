#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "PWM.h"
#include "OLED.h"                  // Device header

void SmartCar_Init(void)
{
	Motor_Init();
}
void Move_ward(int8_t Speed2) //前后移动
{
	BLMotor_Speed(Speed2);//后左轮
	BRMotor_Speed(Speed2);//后右轮
	FLMotor_Speed(Speed2);//前左轮
	FRMotor_Speed(Speed2);//前右轮
}
 
void Turn_Left(void)//左转
{
	BLMotor_Speed(10);
	BRMotor_Speed(50);
	FLMotor_Speed(10);
	FRMotor_Speed(50);
}
void Turn_Right(void)//右转
{
	BLMotor_Speed(50);
	BRMotor_Speed(10);
	FLMotor_Speed(50);
	FRMotor_Speed(10);
}
void Clockwise_Rotation(void)//顺时针旋转
{
	BLMotor_Speed(50);
	BRMotor_Speed(-50);
	FLMotor_Speed(50);
	FRMotor_Speed(-50);
}
void CounterClockwise_Rotation(void)//逆时针旋转
{
	BLMotor_Speed(-50);
	BRMotor_Speed(50);
	FLMotor_Speed(-50);
	FRMotor_Speed(50);
}
void Slide_to_Left(void)//水平向左-- 顺时针旋转
{
	BLMotor_Speed(50);
	BRMotor_Speed(-50);
	FLMotor_Speed(-50);
	FRMotor_Speed(50);
}
void Slide_to_Right(void)//水平向右 --逆时针旋转
{
	BLMotor_Speed(-50);
	BRMotor_Speed(50);
	FLMotor_Speed(50);
	FRMotor_Speed(-50);
}
void FL_45(void)//左前45
{
	BLMotor_Speed(0);
	BRMotor_Speed(50);
	FLMotor_Speed(50);
	FRMotor_Speed(0);
}	
void BR_45(void)//右后45
{
	BLMotor_Speed(0);
	BRMotor_Speed(-50);
	FLMotor_Speed(-50);
	FRMotor_Speed(0);
}
void FR_45(void)//右前45
{
	BLMotor_Speed(50);
	BRMotor_Speed(0);
	FLMotor_Speed(0);
	FRMotor_Speed(50);
}	
void BL_45(void)//左后45
{
	BLMotor_Speed(-50);
	BRMotor_Speed(0);
	FLMotor_Speed(0);
	FRMotor_Speed(-50);
}	


