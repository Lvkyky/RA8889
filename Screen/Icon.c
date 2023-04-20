#include "Icon.h"
#include "Page.h"
#include "USART.h"
#include "api.h"
#include "RA8889.h"
#include  "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include "screen.h"
#include "Button.h"
#include "Stdlib.h"

const struct IconCheckType code IconCheckGroup[IconVarCount]={
{4,
0x0020,
Move,
{{415,16,53,30},{415,62,53,30},{415,108,53,30},{415,156,53,30}},
{Icon1Button1Flush,Icon1Button2Flush,Icon1Button3Flush,Icon1Button4Flush},
{Icon1Button1Call,Icon1Button2Call,Icon1Button3Call,Icon1Button4Call}
},

{2,
0x0021,
Failment,
{{175,90,50,50},{275,90,50,50}},
{Icon2Button1Flush,Icon2Button2Flush},
{Icon2Button1Call,Icon2Button2Call}}
};//单选框图标变量



const struct IconFileType code FileIconGroup[7]={
{0x030F,UdiskNext,FileIcon1Flush1,FileIcon1Flush2,FileIcon1Flush3},
{0x031F,UdiskNext,FileIcon2Flush1,FileIcon2Flush2,FileIcon2Flush3},
{0x032F,UdiskNext,FileIcon3Flush1,FileIcon3Flush2,FileIcon3Flush3},
{0x033F,UdiskNext,FileIcon4Flush1,FileIcon4Flush2,FileIcon4Flush3},
{0x034F,UdiskNext,FileIcon5Flush1,FileIcon5Flush2,FileIcon5Flush3},
{0x035F,UdiskNext,FileIcon6Flush1,FileIcon6Flush2,FileIcon6Flush3},
{0x036F,UdiskNext,FileIcon7Flush1,FileIcon7Flush2,FileIcon7Flush3}
};//文件图标变量




//========================================================================
// 函数: IsPushIconButton
// 功能: 检测某个图标按钮是否被按下
//返回值：1：按下，0：没按下
// 版本: V1.0, 2021-06-15
//========================================================================	
u8 IsPushIconButton(struct IconButtonType Button,u16 x,u16 y)
{
	if(x>Button.x&&x<(Button.x+Button.width)&&y>Button.y&&y<(Button.y+Button.length))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
	
	
	
//========================================================================
// 函数: IconPressEffect
// 功能: 实现图标变量的按压效果
//返回值：无
// 版本: V1.0, 2021-06-29
//========================================================================	
void IconPressEffect(u8 PageName,u16 x,u16 y)
{	
	u8 IconIndex;
	u8 ButtonIndex;
	u8 BCount;
	for(IconIndex=0;IconIndex<IconVarCount;IconIndex++)
	{
		if(IconCheckGroup[IconIndex].PageName==PageName)
		{	
			BCount=IconCheckGroup[IconIndex].Count;
			for(ButtonIndex=0;ButtonIndex<BCount;ButtonIndex++)
			{
				if(IsPushIconButton(IconCheckGroup[IconIndex].ButtonGroup[ButtonIndex],x,y))
				{
					IconCheckGroup[IconIndex].FlushGroup[ButtonIndex]();//执行按压效果
					IconCheckGroup[IconIndex].ButtonCallGroup[ButtonIndex]();
				}					
			}		
		}
	}
}	
	
	
	
		
		
//========================================================================
// 函数: IconCall
// 功能: 实现图标按钮的回调函数
//返回值：无
// 版本: V1.0, 2021-06-29
//========================================================================	
void IconCall(u8 PageName,u16 x,u16 y)
{	
	u8 IconIndex;
	u8 ButtonIndex;
	u8 BCount;
	for(IconIndex=0;IconIndex<IconVarCount;IconIndex++)
	{
		if(IconCheckGroup[IconIndex].PageName==PageName)
		{
			BCount=IconCheckGroup[IconIndex].Count;
			for(ButtonIndex=0;ButtonIndex<BCount;ButtonIndex++)
			{
				if(IsPushIconButton(IconCheckGroup[IconIndex].ButtonGroup[ButtonIndex],x,y))
				{
					IconCheckGroup[IconIndex].ButtonCallGroup[ButtonIndex]();//执行按压效果
				}					
			}
					
		}
	}
}	
	
	


//========================================================================
// 函数: IconFlush
// 功能: 实现图标变量的刷新
//返回值：无
// 版本: V1.0, 2021-06-29
//========================================================================	
void IconFlush(u8 PageName)
{	
	u8 IconIndex;
	u8 *DataPointer;
	u16 FlushCallIndex=0;
	for(IconIndex=0;IconIndex<IconVarCount;IconIndex++)
	{
		if(IconCheckGroup[IconIndex].PageName==PageName)
		{
			DataPointer=VaddrtoPaddrVar(IconCheckGroup[IconIndex].VarAddress);
			FlushCallIndex=DataPointer[0];
			FlushCallIndex=FlushCallIndex<<8;
			FlushCallIndex|=DataPointer[1];
			FlushCallIndex=FlushCallIndex-1;
			if(PageName==Failment)
			{
				FlushCallIndex--;
				IconCheckGroup[IconIndex].FlushGroup[FlushCallIndex]();			
			}
			else
			{
				IconCheckGroup[IconIndex].FlushGroup[FlushCallIndex]();		
			}
		}
	}
}	
	




//========================================================================
// 函数: FileIconFlush
// 功能: 实现文件图标刷新
//返回值：无
// 版本: V1.0, 2021-06-15
//========================================================================	
void FileIconFlush(u8 PageName)
{	
	u8 Index;
	u16 IconVar;
	u16 IconAddres;
	u8 *DataPointer;
	if(PageName==UdiskOne||PageName==UdiskNext||PageName==UdiskBoth||PageName==UdiskLast||
		PageName==UdiskOneUp||PageName==UdiskNextUp||PageName==UdiskBothUp||PageName==UdiskLastUp)
	{
		for(Index=0;Index<7;Index++)
		{
			IconAddres=FileIconGroup[Index].VarAddress;
			DataPointer=VaddrtoPaddrVar(IconAddres);
			IconVar=DataPointer[0];
			IconVar=IconVar<<8;
			IconVar=IconVar|DataPointer[1];
			switch(IconVar)
			{
				case 0x0000:
				{
					FileIconGroup[Index].Flush1();//刷空
					break;
				}
				case 0x0001:
				{
					
					FileIconGroup[Index].Flush2();//刷文件夹
					break;
				}
				case 0x0002:
				{
					FileIconGroup[Index].Flush3();//刷文件
					break;
				}
			}
		}	
	}	
}
	


//========================================================================
// 函数: IconMaterialInit
// 功能:准备好图标的素材，加载到右3
//返回值：无
// 版本: V1.0, 2021-06-23
//========================================================================	
void IconMaterialInit()
{	
	JPG_NOR(BINARY_INFO[160].start_addr,BINARY_INFO[160].img_size,canvas_image_width,960,0);
	JPG_NOR(BINARY_INFO[159].start_addr,BINARY_INFO[159].img_size,canvas_image_width,960,28);
	BTE_Solid_Fill(0,canvas_image_width,960,56,0x000000,28,28);//无
	
	JPG_NOR(BINARY_INFO[155].start_addr,BINARY_INFO[155].img_size,canvas_image_width,960,84);
	JPG_NOR(BINARY_INFO[156].start_addr,BINARY_INFO[156].img_size,canvas_image_width,960,(84+75));
}
	



//////////////////////////图标变量按键回调与刷新函数////////////////////
void Icon1Button1Flush()
{
	BTE_Solid_Fill(0,canvas_image_width,480,272,0x000000,480,272);
	BTE_Memory_Copy(0,canvas_image_width,408,(272+0),0,canvas_image_width,408,(272+0),0,canvas_image_width,480+408,272,12,70,190);
	Active_Window_XY(480,272);							 
	Active_Window_WH(480,272);
	Draw_Square(0x0000FF,(480+414),(272+16),(480+414+53),(272+16+28));
	BTE_Memory_Copy(0,canvas_image_width,480+408,(272+0),0,canvas_image_width,480+408,(272+0),0,canvas_image_width,408,0,12,70,190);
}

void Icon1Button2Flush()
{	BTE_Solid_Fill(0,canvas_image_width,480,272,0x000000,480,272);
	BTE_Memory_Copy(0,canvas_image_width,408,(272+0),0,canvas_image_width,408,(272+0),0,canvas_image_width,480+408,272,12,70,190);
	Active_Window_XY(480,272);							 
	Active_Window_WH(480,272);
	Draw_Square(0x0000FF,(480+414),(272+64),(480+414+53),(272+64+28));
	BTE_Memory_Copy(0,canvas_image_width,480+408,(272+0),0,canvas_image_width,480+408,(272+0),0,canvas_image_width,408,0,12,70,190);
}

void Icon1Button3Flush()
{	BTE_Solid_Fill(0,canvas_image_width,480,272,0x000000,480,272);
	BTE_Memory_Copy(0,canvas_image_width,408,(272+0),0,canvas_image_width,408,(272+0),0,canvas_image_width,480+408,272,12,70,190);
	Active_Window_XY(480,272);							 
	Active_Window_WH(480,272);
	Draw_Square(0x0000FF,(480+414),(272+111),(480+414+53),(272+111+28));
	BTE_Memory_Copy(0,canvas_image_width,480+408,(272+0),0,canvas_image_width,480+408,(272+0),0,canvas_image_width,408,0,12,70,190);
}

void Icon1Button4Flush()
{	BTE_Solid_Fill(0,canvas_image_width,480,272,0x000000,480,272);
	BTE_Memory_Copy(0,canvas_image_width,408,(272+0),0,canvas_image_width,408,(272+0),0,canvas_image_width,480+408,272,12,70,190);
	Active_Window_XY(480,272);							 
	Active_Window_WH(480,272);
	Draw_Square(0x0000FF,(480+414),(272+161),(480+414+53),(272+161+28));
	BTE_Memory_Copy(0,canvas_image_width,480+408,(272+0),0,canvas_image_width,480+408,(272+0),0,canvas_image_width,408,0,12,70,190);	
}


void Icon1Button1Call()
{
	mem_0020[0]=0x00;
	mem_0020[1]=0x01;    				
	Send_Mesg_var(0x0020,1);
}


void Icon1Button2Call()
{
	mem_0020[0]=0x00;
	mem_0020[1]=0x02;    				
	Send_Mesg_var(0x0020,1);
}

void Icon1Button3Call()
{
	mem_0020[0]=0x00;
	mem_0020[1]=0x03;    				
	Send_Mesg_var(0x0020,1);
}

void Icon1Button4Call()
{
	mem_0020[0]=0x00;
	mem_0020[1]=0x04;    				
	Send_Mesg_var(0x0020,1);
}



////////////////////////文件图标变量刷新函数////////////////////
void FileIcon1Flush1()//空    0
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,0,12,28,28);
}
void FileIcon1Flush2()//文件  1
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,0,12,28,28);
}
void FileIcon1Flush3()//文件夹  2
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,0,12,28,28);
}


void FileIcon2Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40,12,28,28);
}
void FileIcon2Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40,12,28,28);
}
void FileIcon2Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40,12,28,28);
}


void FileIcon3Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40*2,12,28,28);
}
void FileIcon3Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40*2,12,28,28);
}
void FileIcon3Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40*2,12,28,28);
}


void FileIcon4Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40*3,12,28,28);
}
void FileIcon4Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40*3,12,28,28);
}
void FileIcon4Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40*3,12,28,28);
}


void FileIcon5Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40*4,12,28,28);
}
void FileIcon5Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40*4,12,28,28);
}
void FileIcon5Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40*4,12,28,28);
}


void FileIcon6Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40*5,12,28,28);
}
void FileIcon6Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40*5,12,28,28);
}
void FileIcon6Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40*5,12,28,28);
}


void FileIcon7Flush1()
{
	BTE_Memory_Copy(0,canvas_image_width,960,56,0,canvas_image_width,960,56,0,canvas_image_width,0,40*6,12,28,28);
}
void FileIcon7Flush2()
{
	BTE_Memory_Copy(0,canvas_image_width,960,28,0,canvas_image_width,960,28,0,canvas_image_width,0,40*6,12,28,28);
}
void FileIcon7Flush3()
{
	BTE_Memory_Copy(0,canvas_image_width,960,0,0,canvas_image_width,960,0,0,canvas_image_width,0,40*6,12,28,28);
}






///////////////////Failment/////////////
void Icon2Button1Flush()
{
	
	BTE_Memory_Copy(0,canvas_image_width,960,84,0,canvas_image_width,960,84,0,canvas_image_width,175,105,12,162,75);
}
void Icon2Button2Flush()
{
	BTE_Memory_Copy(0,canvas_image_width,960,84+75,0,canvas_image_width,960,84+75,0,canvas_image_width,175,105,12,162,75);
}

void Icon2Button1Call()
{
	mem_0021[0]=0x00;
	mem_0021[1]=0x02;    				
	Send_Mesg_var(0x0021,1);
}
void Icon2Button2Call()
{
	mem_0021[0]=0x00;
	mem_0021[1]=0x03;    				
	Send_Mesg_var(0x0021,1);
}






