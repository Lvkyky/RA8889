/*************	功能说明	**************
本文件实现了串口配置以及对命令帧的解析
******************************************/
#include "USART.h"
#include "timer.h"
#include "screen.h"
#include "api.h"
#include "String.h"

COMx_Define	COM1;
u8  TX1_Buffer[COM_TX1_Lenth];	//TX1发送缓冲
u8 	RX1_Buffer[COM_RX1_Lenth];	//TX1接收缓冲

COMx_Define	COM2;
u8 TX2_Buffer[COM_TX2_Lenth];	//TX2发送缓冲

//======================================================================
// 函数: u8	USART_Configuration()
// 描述: 串口配置函数，并且实现了接收缓冲队列的初始化
// 参数: 串口序号，串口结构体
// 返回: 无
// 版本: V1.0, 2012-10-22
//======================================================================
u8 USART_Configuration(u8 UARTx, COMx_InitDefine *COMx)
{
	u8	i;
	u32	j;
	
	if(UARTx == USART1)
	{
		COM1.id = 1;
		COM1.TX_read    = 0;
		COM1.TX_write   = 0;
		COM1.B_TX_busy  = 0;
		COM1.RX_Cnt     = 0;
		COM1.RX_TimeOut = 0;
		COM1.B_RX_OK    = 0;
		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		if(COMx->UART_Mode > UART_9bit_BRTx)	return 1;	//模式错误
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//高优先级中断
		else									PS = 0;	//低优先级中断
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (u8)(j>>8);
				TL1 = (u8)j;
				ET1 = 0;	//禁止中断
				TMOD &= ~0x40;	//定时
				INT_CLKO &= ~0x02;	//不输出时钟
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				TH2 = (u8)(j>>8);
				TL2 = (u8)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR &= ~(1<<3);	//定时
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//错误
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//固定波特率SysClk/2
			else								AUXR &= ~(1<<5);	//固定波特率SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//固定波特率SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//固定波特率SysClk/32
			else								PCON &= ~(1<<7);	//固定波特率SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//允许中断
		else								ES = 0;	//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//允许接收
		else								REN = 0;	//禁止接收
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//切换IO
		if(COMx->UART_RXD_TXD_Short == ENABLE)	PCON2 |=  (1<<4);	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
		else									PCON2 &= ~(1<<4);
		return	0;
	}
	
	
	if(UARTx == USART2)
	{
		COM2.id = 2;
		COM2.TX_read    = 0;
		COM2.TX_write   = 0;
		COM2.B_TX_busy  = 0;
		COM2.RX_Cnt     = 0;
		COM2.RX_TimeOut = 0;
		COM2.B_RX_OK    = 0;
		for(i=0; i<COM_TX2_Lenth; i++)	
		{
			TX2_Buffer[i] = 0;
		}  //发送缓冲区清零
		
		
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//高优先级中断
			else									IP2 &= ~1;	//低优先级中断
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			TH2 = (u8)(j>>8);
			TL2 = (u8)j;
			IE2  &= ~(1<<2);	//禁止中断
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//模式错误
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//允许中断
		else								IE2   &= ~1;		//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//允许接收
		else								S2CON &= ~(1<<4);	//禁止接收
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//切换IO
	}
	return 3;	//其它错误
}






void TX1_write2buff(u8 dat)	//写入发送缓冲，指针+1
{
	TX1_Buffer[COM1.TX_write] = dat;	//装发送缓冲
	if(++COM1.TX_write >= COM_TX1_Lenth)	COM1.TX_write = 0;

	if(COM1.B_TX_busy == 0)		//空闲
	{  
		COM1.B_TX_busy = 1;		//标志忙
		TI = 1;					//触发发送中断
	}
}


void TX2_write2buff(u8 dat)	//写入发送缓冲，指针+1
{
	TX2_Buffer[COM2.TX_write] = dat;	//装发送缓冲
	if(++COM2.TX_write >= COM_TX2_Lenth)	COM2.TX_write = 0;

	if(COM2.B_TX_busy == 0)		//空闲
	{  
		COM2.B_TX_busy = 1;		//标志忙
		SET_TI2();				//触发发送中断
	}
}



void PrintString1(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX1_write2buff(*puts); 	//遇到停止符0结束
		//Print_Internal_Font_String(0,300,800,100,0xffffff,0x000000, puts);

}


void PrintString2(u8 *puts)
{
    for (; *puts != 0;	puts++)  TX2_write2buff(*puts); 	//遇到停止符0结束
}




/********************* UART中断函数************************/
void UART1_int (void) interrupt UART1_VECTOR
{
u8 buf;
 if(RI)
	{ 
		RI=0;
		if(COM1.B_RX_OK == 0)
		{
		  buf=SBUF;	
		  CmdReceive1(buf);	
		}
	}

	if(TI)
	{
		TI = 0;
		if(COM1.TX_read != COM1.TX_write)
		{
		 	SBUF = TX1_Buffer[COM1.TX_read];
			if(++COM1.TX_read >= COM_TX1_Lenth)		COM1.TX_read = 0;
		}
		else	COM1.B_TX_busy = 0;
	}
}





void UART2_int (void) interrupt UART2_VECTOR
{
	u8 buf;
	if(RI2)
	{   
		CLR_RI2();
		if(COM2.B_RX_OK == 0)
		{
			buf=S2BUF;	
			CmdReceive1(buf);
		}
	}
	
	if(TI2)
	{
		CLR_TI2();
		if(COM2.TX_read != COM2.TX_write)
		{
		 	S2BUF = TX2_Buffer[COM2.TX_read];
			if(++COM2.TX_read >= COM_TX2_Lenth)		COM2.TX_read = 0;
		}
		else	COM2.B_TX_busy = 0;
	}

}


/********************* UART配置函数************************/
void	UART1_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 460800ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
	COMx_InitStructure.UART_Polity    = PolityLow;			//中断优先级, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//初始化串口1 USART1,USART2

	PrintString1("STC15F2K60S2 UART1 Test Prgramme!\r\n");	//SUART1发送一个字符串
}

void UART2_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
	COMx_InitStructure.UART_Polity    = PolityHigh;			//中断优先级, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
	USART_Configuration(USART2, &COMx_InitStructure);		//初始化串口2 USART1,USART2
	
	PrintString1("STC15F2K60S2 UART2 Test Prgramme!\r\n");	//SUART2发送一个字符串
}









