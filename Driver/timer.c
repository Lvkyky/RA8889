
/*************	功能说明	**************
本文件实现了对定时器的初始化和配置，
在此基础上实现了周期返回PAGE_ID，
并且还实现了命令帧超时判定。
******************************************/
#include "timer.h"
#include "USART.h"
#include "screen.h"
#include "delay.h"
#include "api.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include "RA8889.h"
#include "ads7843.h"

struct Timer  PageTimer;  //周期返回page_id计数
struct Timer  InfoWinTimer;
struct Timer  tempFluTimer;
struct Timer  CursorFluTimer;
struct Timer  ButtonReleaTimer;
struct Timer  ButtonDecreTimer;
struct Timer  AnimitationTimer;

u32 CurentInfoWinTime=0X00FF;//当前信息弹窗的时间
//======================================================================
// 函数: u8	timer0_int()
// 描述: 定时器0中断函数
// 参数: 无
// 返回: 无
// 版本: V1.0, 2021-05-26
//======================================================================
void timer0_int (void) interrupt TIMER0_VECTOR   //1s<---->200  
{
	
	PageTimer.count=(PageTimer.count+1)%1000;
	if(PageTimer.count==250)  PageTimer.update=1;//周期返回Page_ID（500ms）
		
	if(InfoWinTimer.swit==1)	
	{
		InfoWinTimer.count=(InfoWinTimer.count+1)%(65530);//信息弹窗计时(500ms)
		if(InfoWinTimer.count==CurentInfoWinTime) InfoWinTimer.update=1;
	}
		
	tempFluTimer.count=(tempFluTimer.count+1)%1000;//屏幕刷新(500ms)
	if(tempFluTimer.count==80) tempFluTimer.update=1;
		
	if(CursorFluTimer.swit==1) 
	{
		CursorFluTimer.count=(CursorFluTimer.count+1)%1000;//光标闪烁（500ms）
		if(CursorFluTimer.count==250) CursorFluTimer.update=1;
	}
	
	if(ButtonReleaTimer.swit==1)
	{
		ButtonReleaTimer.count=(ButtonReleaTimer.count+1)%1000;//按键释放检测计时器（50ms）
		if (ButtonReleaTimer.count==25) ButtonReleaTimer.update=1;
	}
	if (INTT_0==0)
	{
		ButtonReleaTimer.count=0;
	}

	
	if(ButtonDecreTimer.swit==1)   
	{
		ButtonDecreTimer.count=(ButtonDecreTimer.count+1)%1000;//触控消抖（50ms）
		if (ButtonDecreTimer.count==25)  ButtonDecreTimer.update=1;
	}
	
	if(AnimitationTimer.swit==1)	
	{
		AnimitationTimer.count=(AnimitationTimer.count+1)%(65530);//信息弹窗计时(100ms)
		if(AnimitationTimer.count==50) AnimitationTimer.update=1;
	}
}




//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//空操作

	if(TIM == Timer0)
	{
		TR0 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		else									ET0 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		else									PT0 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		else										TMOD &= ~0x04;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		else							INT_CLKO &= ~0x01;	//不输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		else									ET1 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//输出时钟
		else							INT_CLKO &= ~0x02;	//不输出时钟
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1<<4);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//允许中断
		else										IE2  &= ~(1<<2);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		else										AUXR &= ~(1<<3);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//输出时钟
		else							INT_CLKO &= ~0x04;	//不输出时钟

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	return 2;	//错误
}




//=======================================================================
// 函数: u8	Timer_config()
// 描述: 定时器初始化程序.
// 参数: 无
// 返回: 无
// 版本: V1.0, 2012-10-22
//========================================================================
void Timer_config_t0(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - 44236UL;	//初值,2ms中断一次
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2
	
	TimerInit(&PageTimer);
	TimerInit(&InfoWinTimer);
	TimerInit(&tempFluTimer);
	TimerInit(&CursorFluTimer);
	TimerInit(&ButtonReleaTimer); 
	TimerInit(&ButtonDecreTimer);
	TimerInit(&AnimitationTimer); 														
}




//=======================================================================
// 函数: u8	TimerInit()
// 描述: 定时器变量初始化
// 参数: 定时器变量
// 返回: 无
// 版本: V1.0, 2021-06-09
//========================================================================
void TimerInit(struct Timer *timer)
{
	(*timer).update=0;
	(*timer).count=0;
	(*timer).swit=0;
}



