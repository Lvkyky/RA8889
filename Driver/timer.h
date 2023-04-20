
#ifndef	__TIMER_H
#define	__TIMER_H

#include	"config.h"

#define	Timer0						0
#define	Timer1						1
#define	Timer2						2
#define	Timer3						3
#define	Timer4						4

#define	TIM_16BitAutoReload			0
#define	TIM_16Bit					1
#define	TIM_8BitAutoReload			2
#define	TIM_16BitAutoReloadNoMask	3

#define	TIM_CLOCK_1T				0
#define	TIM_CLOCK_12T				1
#define	TIM_CLOCK_Ext				2

/*********************************************************************************/
extern struct Timer PageTimer;
extern struct Timer  InfoWinTimer;
extern struct Timer  tempFluTimer;
extern struct Timer  CursorFluTimer;
extern struct Timer  ButtonReleaTimer;
extern struct Timer  ButtonDecreTimer;
extern struct Timer  AnimitationTimer;
extern u32 CurentInfoWinTime;//当前信息弹窗的时间


struct Timer
{
	u16	count;	//当前计数值
	u8	swit;	//计数开关
	u8	update;	//时间是否到达
};


typedef struct
{
	u8	TIM_Mode;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	u8	TIM_Polity;		//优先级设置	PolityHigh,PolityLow
	u8	TIM_Interrupt;	//中断允许		ENABLE,DISABLE
	u8	TIM_ClkSource;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	u8	TIM_ClkOut;		//可编程时钟输出,	ENABLE,DISABLE
	u16	TIM_Value;		//装载初值
	u8	TIM_Run;		//是否运行		ENABLE,DISABLE
} TIM_InitTypeDef;


u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx);
void	Timer_config_t0(void);
void TimerInit(struct Timer *timer);
#endif
