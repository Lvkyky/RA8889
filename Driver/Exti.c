
/*************	功能说明	**************
本文件实现了中断配置以及对触摸事件的处理，
是状态转换的内部触发。
******************************************/
#include "Exti.h"
#include "USART.h"
#include "ads7843.h"
#include "delay.h"
#include "timer.h"

#include "screen.h"
#include "api.h"
#include "All_8889_Pic_NOR.h"
#include  "RA8889.h"
#include  "UserDef.h"
#include  "Button.h"
#include  "Win.h"

/********************* INT0中断函数 *************************/
//========================================================================
// 函数: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断2处理函数.
// 功能: 获取触摸坐标（单位：像素）
// 版本: V1.0, 2021-05-21
//========================================================================
void Ext_INT2 (void) interrupt INT2_VECTOR
{
	ButtonDecreTimer.swit=1;//消抖计时开关	
	PrintString1("EXT\r\n");
}



	
//========================================================================
// 函数: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断初始化程序.
// 参数: INTx: 结构参数,请参考Exti.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{ PrintString1("开始中断初始化\r\n");  
	if(EXT >  EXT_INT4)
	{
	 PrintString1("空操作\r\n");
	 return 1;	//空操作
	}		
	
	if(EXT == EXT_INT0)	//外中断0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//允许中断
		else									EX0 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//高优先级中断
		else									PX0 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//下降沿中断
		else									IT0 = 0;	//上升,下降沿中断
	  PrintString1(" 中断初始化成功\r\n");      
		return	0;		//成功
	}
	
	if(EXT == EXT_INT2)		//外中断2, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//允许中断	
		else								INT_CLKO &= ~(1 << 4);	//禁止中断
		return	0;		//成功
	}

	PrintString1("中断初始化失败\r\n");
	return 2;	//失败
}


void	EXTI_config(void)                          //外部中断2 初始化
{ 
	EXTI_InitTypeDef	EXTI_InitStructure;					//结构定义
	PrintString1("开始中断2初始化\r\n");
	EXTI_InitStructure.EXTI_Mode      = EXT_MODE_Fall;	//中断模式,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	EXTI_InitStructure.EXTI_Polity    = PolityLow;			//中断优先级,   PolityLow,PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//中断允许,     ENABLE或DISABLE
	Ext_Inilize(EXT_INT2,&EXTI_InitStructure);				//初始化INT0	EXT_INT0,EXT_INT1,EXT_INT2,EXT_INT3,EXT_INT4
}













