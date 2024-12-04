#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "SmartCar.h"             // Component selection
#include "PWM.h"   
#include "OLED.h"               
#include "Encodec.h"                  // Device header
#include "Key.h"  
#include "timer.h"
#include "Serial.h"
int8_t Speed;
int8_t KeyNum;
uint8_t RxData;
int main(void)
{
	int8_t Speed2=0;
	/*模块初始化*/
   SmartCar_Init();
	OLED_Init();
  Encoder_Init();
	//Key_Init();
	Timer_Init();
	Serial_Init();
	
	OLED_ShowString(1,3,"Speed:");
	OLED_ShowString(2, 1, "RxData:");
	OLED_ShowString(4,3,"Speed2:");
	while (1) 
	{
	OLED_ShowSignedNum(1, 9, Speed, 5); //显示速度
	
	/*蓝牙模块处*/
	 while(Speed2<=100&&Speed>=-100)
	{
	//获取串口接收标志位 --串口接收标志位，范围：0~1，接收到数据后，标志位置1，读取后标志位自动清零
	if(Serial_GetRxFlag()==1)
	{
	RxData=Serial_GetRxData();//获取串口接收的数据
				OLED_ShowString(3, 1, "R");
	}
		if(RxData==0x0)//0 停止
			{
				Speed2=0;
				Move_ward(Speed2);
			}
		
		if(RxData==0x1) //1 向前20
		{
			Speed2=20;
				Move_ward(Speed2);//大于0 前进 小于0 后退 等于0 停止
		}
		
		 if(RxData==0x2)//2 向后20
		{
			Speed2=-20;
			Move_ward(Speed2);
		}
		
		 if(RxData==0x3)//3 向前30
		{
			Speed2=30;
			Move_ward(Speed2);
		}
		if(RxData==0x4)//4 向后30
		{
			Speed2=-30;
			Move_ward(Speed2);
		}
		 if(RxData==0x5)//5  向前50
		{
			Speed2=50;
			Move_ward(Speed2);
		}
		 if(RxData==0x6)//6 向后50
		{
			Speed2=-50;
			Move_ward(Speed2);
		}
			
		if(RxData==0x7)// 7直接按照原来速度前进方向变反
		{
			Speed2=-Speed2;
				Move_ward(Speed2);
			
		}
		if(RxData==0x8)//8 向前80
		{
			Speed2=80;
			Move_ward(Speed2);
		}
		 if(RxData==0x9)//9 向后80
		{
			Speed2=-80;
			Move_ward(Speed2);
		}
		 if(RxData==0x10)//
		{
			Turn_Left();
		}
		 if(RxData==0x11)//
		{
			Turn_Right();
		}
		 if(RxData==0x12)//
		{
			Clockwise_Rotation();
		}
		 if(RxData==0x13)//
		{
			CounterClockwise_Rotation();
		}
		 if(RxData==0x14)//
		{
			Slide_to_Left();
		}
		 if(RxData==0x15)//
		{
			Slide_to_Right();
		}
		 		
            OLED_ShowSignedNum(1, 9, Speed, 5); //显示速度
			OLED_ShowHexNum(2, 8, RxData, 2);	 
			OLED_ShowSignedNum(4, 9, Speed2, 3);
     }
	}

}
	












/**
  * 函    数：TIM2中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)		//判断是否是TIM4的更新事件触发的中断
	{
		Speed = Encoder_Get();								//每隔固定时间段读取一次编码器计数增量值，即为速度值
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			//清除TIM2更新事件的中断标志位
															//中断标志位必须清除														//否则中断将连续不断地触发，导致主程序卡死
	}
}


