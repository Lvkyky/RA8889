
#include "config.h"
#include "USART.h"
#include "delay.h"
#include "screen.h"
#include "timer.h"
#include "ads7843.h"
#include "Exti.h"
#include "api.h"
#include "RA8889.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include "Win.h"
#include "Page.h"
#include "String.h"
#include "Icon.h"
#include "Scaler.h"
#include "NumLabel.h"
#include "StringLabel.h"
#include "TimeLabel.h"
#include "Fifo.h"
#include "Stdlib.h"
#include "Input.h"
#include "Animitation.h"


void main(void)
{  
u8 AddrTemp;
u8 i;
u8 *DataPointer;
u8 str[4];

QueueInit();
	
UART1_config();
UART2_config();  

Ads7843_Init();    
EXTI_config();    
Timer_config_t0();  
EA = 1;

RA8889_Initial();  
BTE_Solid_Fill(0,canvas_image_width,0,0,0x000000,480*4,272*3);
SPI_NOR_initial_JPG_AVI (1,0,1,2,1);
IconMaterialInit();
res_03[0]==0x00;
res_03[1]==0x00;
while (1)
{
/**********************定时任务************************/
	UpdatePageName();
	AnimitationFlush(Page_Name);
	
	
	if(PageTimer.update==1)//周期返回pageId
	{ 
		PageTimer.update=0;
		PageTimer.count=0;	
		Send_Mesg_res(3,2);
	}

		
	if(InfoWinTimer.update==1)//信息弹窗
	{
		InfoWinTimer.update=0;
		InfoWinTimer.swit=0;  
		InfoWinTimer.count=0; 
		PrintString1("弹窗消失\r\n");
		WindowOff(CurentWin);
	}


	if(CursorFluTimer.update==1)//光标刷新
	{
		CursorFluTimer.update=0;
		CursorFluTimer.count=0;
		CursorRever=!CursorRever;
	}

			
	if(ButtonDecreTimer.update==1)//按键消抖
	{
		ButtonDecreTimer.update=0;
		ButtonDecreTimer.count=0;
		ButtonDecreTimer.swit=0;
		if(INTT_0==0) 
		{
			TouchStatus=Pressed;
			ButtonReleaTimer.swit=1;
			INT_CLKO &= ~(1 << 4);//屏蔽按压中断
		}
	}
	
	
	
	
/**********************触控释放************************/
	if(ButtonReleaTimer.update==1)//按键释放
	{	
		ButtonReleaTimer.update=0;
		ButtonReleaTimer.count=0;
		ButtonReleaTimer.swit=0;
		
		TouchDetectSwit=1;
		TouchStatus=Rlease;
	
		if(CurentWin!=0XFF)//弹窗
		{
			if(GetWinClass(CurentWin)==Info)
			{				   
			
			}
			else if(GetWinClass(CurentWin)==Select)
			{
				PrintString1("选择按钮回调函数\r\n");
				SelectButtonCall(CurentWin,x,y);       						                      						
			}
			else if(GetWinClass(CurentWin)==SingleSelect)
			{
				SingleSelectButtonCall(CurentWin,x,y);
				PrintString1("单选择按钮回调函数\r\n");
			}

		}
		else if(CurrentInput!=0xFF)
		{
			NumButtonReleaEffect(CurrentInput,x,y);
			NumButtonCall(CurrentInput,x,y);
		}
		else 
		{
			 ButtonRealeEffect(Page_Id,x,y);
			 ButtonCall(Page_Id,x,y);
			 IconCall(Page_Name,x,y);
		}
		res_05[0]=0x00;
		Send_Mesg_res(0x05,1);
		INT_CLKO |= (1 << 4);//允许按压中断		
	}

/********************定时刷新************************/	
	UpdatePageName();
	if(tempFluTimer.update==1)//变量定时刷新
	{
		tempFluTimer.update=0;
		tempFluTimer.count=0;
		if(CurentWin!=0xFF)//窗口
		{	
			if(GetWinClass(CurentWin)==Info)
			{
				//空操作							
			}
			else
			{
				//空操作
			}
		}
		else if(CurrentInput!=0xFF)
		{
			InputStrFlush();
		}
		else
		{	
			 if(FlushExchange==0)
			 {
				 FlushExchange=1;
				 ScalerFlush(Page_Name);
			 }
			 else if(FlushExchange==1)
			 {
				 FlushExchange=2;
				 NumLabelFlush(Page_Name);
				 TimeLabelFlush(Page_Name);
			 }
			 else if(FlushExchange==2)
			 {
				 FlushExchange=0;
				 StringLabelFlush(Page_Name);
			 }			      
			IconFlush(Page_Name); 
		}
	}
/********************触控按下***********************/	
	if(TouchDetectSwit==1)//按键未释放之前不再进行坐标更新           
	{
		if(TouchStatus==Pressed)
		{	
			Cord_read();	
			TouchDetectSwit=0;
			res_05[0]=0x5A;
			Send_Mesg_res(0x05,1); 
			if(CurentWin!=0XFF)
			{
				if(GetWinClass(CurentWin)==Info)//信息弹窗
				{
					//空操作		    			 
				}
				else if(GetWinClass(CurentWin)==Select||GetWinClass(CurentWin)==SingleSelect)//选择弹窗
				{
					SeletButtonPressEffect(CurentWin,x,y);
				}
			}
			else if(CurrentInput!=0xFF) //编辑
			{
				NumButtonPressEffect(x,y);
			}	
			else//普通按钮
			{	
				 ButtonPressEffect(Page_Id,x,y);
				 IconPressEffect(Page_Name,x,y);
			}
		}
	}
/**********************指令************************/	
	UpdateCmd();
    if(CmdUpdateFlag==1)
	{
		#ifdef Debug
		PrintString1("Cmd:");
		PrintString1(u8_to_str_hex(CurentCmd.Cmd,str));
		PrintString1(" ");
		PrintString1(" Addr:");


		AddrTemp=0x00FF&(CurentCmd.Addr>>8);
		PrintString1(u8_to_str_hex(AddrTemp,str));

		AddrTemp=CurentCmd.Addr&0X00FF;
		PrintString1(u8_to_str_hex(AddrTemp,str));
		PrintString1(" ");  //debug	
		
		
		if(CurentCmd.Cmd==0x80||CurentCmd.Cmd==0x82)
		{   
			PrintString1("Data:");
			for(i=0;i<CurentCmd.ByteSize;i++)
			{   
				PrintString1(u8_to_str_hex(CurentCmd.Data[i],str));
				PrintString1(" ");
			}	
		}
		else if(CurentCmd.Cmd==0x81||CurentCmd.Cmd==0x83)
		{
			PrintString1("Read Data: ");
			if(CurentCmd.Cmd==0x81)
			{
				DataPointer=VaddrtoPaddrRes(CurentCmd.Addr);
				for(i=0;i<CurentCmd.ByteSize;i++)
				{
					PrintString1(u8_to_str_hex(DataPointer[i],str));
				}
			}
			else if(CurentCmd.Cmd==0x83)
			{
				DataPointer=VaddrtoPaddrVar(CurentCmd.Addr);
				if(DataPointer==NULL)
				{
					PrintString1("无效的地址，不进行Debug显示\r\n");
				}
				else
				{
					for(i=0;i<(CurentCmd.ByteSize*2);i++)
					{
						PrintString1(u8_to_str_hex(DataPointer[i],str));
					}					
				}
			}		
			PrintString1("\r\n");	
		}
		PrintString1("\r\n");  //debug		
		#endif	
		
		if(CurentCmd.Cmd==0x80||CurentCmd.Cmd==0x82)
		{
			Update_var_res();//更新变量和寄存器
			UpdatePageName();
			ImediaFlushScreen(Page_Name);//刷新屏幕(解释切换ID命令)
		}	
		else if(CurentCmd.Cmd==0x81||CurentCmd.Cmd==0x83)
		{
		    Return_var_res();//返回要读取的寄存器和变量
		}		
		CmdUpdateFlag=0;
	}
}
}





