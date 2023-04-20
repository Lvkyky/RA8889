
/*************功能说明**************
实现了居中，与左对齐。未实现透明显示，
透明效果通过设置背景色相同达到。
************************************/
#include "StringLabel.h"
#include "Page.h"
#include "screen.h"
#include "api.h"
#include "UserDef.h"
#include "String.h"
#include "USART.h"
const struct StringLabelVarType code StringLabelGroup[StringLabelVarCount]={
{0x0140,0XFF       ,{CenterAlign,Untrans,10,142,460,Font24x24,0x000000,0X0166FF}},
{0x0140,Main       ,{CenterAlign,Untrans,10,142,460,Font24x24,0x000000,0X0166FF}},
{0x0140,MainPreheat,{CenterAlign,Untrans,10,142,460,Font24x24,0x000000,0X0166FF}},
{0x0140,MainUdisk  ,{CenterAlign,Untrans,10,142,460,Font24x24,0x000000,0X0166FF}},
{0x0140,MainUdiskPreheat,{CenterAlign,0,10,142,460,Font24x24,0x000000,0X0166FF}},
{0x0140,Print,{LeftAlign,Untrans,20,80,160,Font24x24,0xD2691E,0x000000}},
{0x0140,PrintPause,{LeftAlign,Untrans,20,80,160,Font24x24,0xD2691E,0x000000}},
{0x0030,Version,{LeftAlign,Untrans,389,102,80,Font16x16,0X0166FF,0x1A1A1A}},
{0x0038,Version,{LeftAlign,Untrans,409,167,40,Font16x16,0X0166FF,0x1A1A1A}}
};




//============================================
// 函数: StringLabelFlush()
// 描述: 字符串标签刷新
// 参数:当前页面
// 返回: 无
// 版本: V1.0, 2021-6-11
//============================================
void StringLabelFlush(u8 PageName)
{
	u8 index;
	u16 Absolutex,Absolutey;
	u16 length,width;
	u32 color;
	u32 Bcolor;
	u8 *DataPointer=0;
	u8 Reletivex;
	u8 CharCount=0;
	u8 i;
	u8 str[4];
	for(index=0;index<StringLabelVarCount;index++)
	{
		if(PageName==StringLabelGroup[index].PageName)  
		{
			Absolutex=StringLabelGroup[index].VarInfo.x;
			Absolutey=StringLabelGroup[index].VarInfo.y;
			width=StringLabelGroup[index].VarInfo.Width;
			length=StringLabelGroup[index].VarInfo.Length;
			color=StringLabelGroup[index].VarInfo.Color;
			Bcolor=StringLabelGroup[index].VarInfo.Bcolor;
			DataPointer=VaddrtoPaddrVar(StringLabelGroup[index].Addr);//数据指针			
			
			Select_Font_Height_WxN_HxN_ChromaKey_Alignment(length,1,1,1,0);
			BTE_Solid_Fill(0,canvas_image_width,(480+Absolutex),(272+Absolutey),Bcolor,width,length);
			
			if(Bcolor=StringLabelGroup[index].VarInfo.Align==CenterAlign)//对齐
			{   
				i=0;
				while(DataPointer[i]!=0) 
				{
					if(DataPointer[i]>64&&DataPointer[i]<91) CharCount=CharCount+1;
					else CharCount++;
					i++;
				}
//				PrintString1("---------------------------->\r\n");
//				PrintString1(u8_to_str_3(i,str));
//				PrintString1("\r\n");
				Reletivex=width/2-(CharCount*length/2)/2;
				Print_GB2312String(3,0,0,(480+Absolutex+Reletivex),(272+Absolutey),width,length,color,Bcolor,DataPointer);
			}
			else
			{
				Print_GB2312String(3,0,0,(480+Absolutex),(272+Absolutey),width,length,color,Bcolor,DataPointer);
			}
			BTE_Memory_Copy(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,Absolutex,Absolutey,12,width,length);
		}
	}
} 






//============================================
// 函数: StringInit()
// 描述: 字符串初始化
// 参数: 无
// 返回: 无
// 版本: V1.0, 2021-7-3
//============================================
void StringInit()
{
	 u8 *p;
	 p="6.0.101010";
	 StringSingleInit(mem_0030,p);
	 
	 p="5.0.0";
	 StringSingleInit(mem_0038,p);
}




void StringSingleInit(u8 *mem,u8 *p)
{
	u8 i;
	for(i=0;p[i]!=0;i++)
	 {
		 mem[i]=p[i];
	 }
	 mem[i]=p[i];
}
