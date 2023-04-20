
/*************功能说明**************
未实现居中，与左对齐。实现了透明效果与
非透明效果。
****************************************/
#include "TimeLabel.h"
#include "Page.h"
#include "Screen.h"
#include "api.h"
#include "Stdlib.h"

const struct TimeLabelVarType code TimeGroup[TimeCount]={
{0x0024,Print,{Trans,(480+52),(272+140),200,Font24x24,0x0000F0,0x0000FF}},
{0x0024,PrintPause,{Trans,(480+52),(272+140),200,Font24x24,0x0000F0,0x0000FF}},
{0x0027,Version,{Untrans,387,37,160,Font16x16,0X0166FF,0X000000}}
};	


//============================================
// 函数: TimeLabelFlush()
// 描述: 时间刷新
// 参数:当前页面
// 返回: 无
// 版本: V1.0, 2021-6-11
//============================================
void TimeLabelFlush(u8 PageName)
{	
	u8 StrTime[12];
	u8 index;
	u16 x,y;
	u16 length,width;
	u32 color;
	u32 Bcolor;
	u8 *DataPointer=0;
	for(index=0;index<TimeCount;index++)
	{
		if(PageName==TimeGroup[index].PageName)
		{
			x=TimeGroup[index].VarInfo.x;
			y=TimeGroup[index].VarInfo.y;
			width=TimeGroup[index].VarInfo.Width;
			length=TimeGroup[index].VarInfo.Length;
			color=TimeGroup[index].VarInfo.Color;
			Bcolor=TimeGroup[index].VarInfo.Bcolor;
			if(VaddrtoPaddrVar(TimeGroup[index].Addr)!=NULL) DataPointer=VaddrtoPaddrVar(TimeGroup[index].Addr);//数据指针
			else return;		
			
			if(PageName==Version)
			{
				StrTime[0]=(DataPointer[0]/16)+48;
				StrTime[1]=(DataPointer[0]%16)+48;
				StrTime[2]=':';
				StrTime[3]=(DataPointer[1]/16)+48;
				StrTime[4]=(DataPointer[1]%16)+48;//Hour
				StrTime[5]=':';
				StrTime[6]=(DataPointer[2]/16)+48;
				StrTime[7]=(DataPointer[2]%16)+48;//Minite
				StrTime[8]=':';
				StrTime[9]=(DataPointer[3]/16)+48;
				StrTime[10]=(DataPointer[3]%16)+48;//Second
				StrTime[11]=0;//End

			}
			else
			{
				StrTime[0]=(DataPointer[1]/16)+48;
				StrTime[1]=(DataPointer[2]/16)+48;
				StrTime[2]=(DataPointer[2]%16)+48;//Hour
				StrTime[3]=':';
				StrTime[4]=(DataPointer[3]/16)+48;
				StrTime[5]=(DataPointer[3]%16)+48;//Minite
				StrTime[6]=':';
				StrTime[7]=(DataPointer[4]/16)+48;
				StrTime[8]=(DataPointer[4]%16)+48;//Second
				StrTime[9]=0;//End
			}
		
			
	
			Select_Font_Height_WxN_HxN_ChromaKey_Alignment(length,1,1,TimeGroup[index].VarInfo.TransFlag,0);
			Print_GB2312String(3,0,0,x,y,width,length,color,Bcolor,StrTime);		
		}			
	}	
}

