#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"                  // Device header

/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	/*驱动电机上三对GPIOA口的初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//此时不用复用推挽输出，因为只用设置两个口的高低电平即可	
																//而PWM中的GPIO口要输出PWM的方波 所以复用推挽
/*驱动电机上一对GPIOB口的初始化*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);							//将PA2引脚初始化为复用推挽输出	
																	//受外设控制的引脚，均需要配置为复用模式

	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100  GPIO控制正转反转
  * 返 回 值：无
  */
//左后轮 通道TIM_CH1 compare1 PA4 5
void BLMotor_Speed(int8_t Speed) 
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);	//PA4置高电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	//PA5置低电平，设置方向为正转
		PWM_SetCompare1(Speed);				//PWM设置为速度值
	}

	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);	
		PWM_SetCompare1(-Speed);				//CRR的值为正，所以speed前面加负号
	}
	
}
//右后轮 通道TIM_CH2 compare2 PA0  1
void BRMotor_Speed(int8_t Speed) 
{
	if (Speed >= 0)							
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);	
		PWM_SetCompare2(Speed);				
	}

	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	
		PWM_SetCompare2(-Speed);				
	}
	
}
//右前轮 通道TIM1_CH3 compare3 PA12 15
void FLMotor_Speed(int8_t Speed) 
{
	if (Speed >= 0)							
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);
		PWM_SetCompare3(Speed);			
	}

	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_10);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);	
		PWM_SetCompare3(-Speed);		
	}
	
}
//左前轮 通道TIM1_CH4 compare4 PB10 11
void FRMotor_Speed(int8_t Speed) 
{
	if (Speed >= 0)							
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_11);	
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);	
		PWM_SetCompare4(Speed);				
	}

	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_10);	
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);	
		PWM_SetCompare4(-Speed);				
	}
	
}
