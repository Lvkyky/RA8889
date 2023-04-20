#include "Scaler.h"
#include "Page.h"
#include "api.h"
#include "screen.h"
#include "RA8889.h"
#include "UserDef.h"
#include "NumLabel.h"
#include "TimeLabel.h"
#include "USART.h"
#include "delay.h"
struct ScalerType ScalerGroup[ScalerCount]={
{0x0023,Print,0,134,480,40,0XF4A460,0X808080,1},	
{0x0023,PrintPause,0,134,480,40,0XF4A460,0X808080,1}	
};


void ScalerFlush(u8 PageName)
{    
	u16 Per;
	float c;
	u16 CurentW;
	u8 *DataPointer;
	u8 Index;
	u16 x,y;
	u16 Width;
	u16 Length;
	for(Index=0;Index<ScalerCount;Index++)
	{
	if(PageName==ScalerGroup[Index].PageName)
	{
		BTE_Solid_Fill(0,canvas_image_width,480,272,0x000000,480,272);//Ìî³äºÚÉ«
		Active_Window_XY(480,272);							 
		Active_Window_WH(480,272);
		x=ScalerGroup[Index].x;
		y=ScalerGroup[Index].y;
		Width=ScalerGroup[Index].width;
		Length=ScalerGroup[Index].length;
		Draw_Square_Fill(ScalerGroup[Index].Bcolor,(x+480),(y+272),(x+480+Width),(y+272+Length));	
	
		DataPointer=VaddrtoPaddrVar(ScalerGroup[Index].Addr);
			
		Per=DataPointer[0];
		Per=Per<<8;
		Per=Per|DataPointer[1];	
		c=Per/1000.0;
		CurentW=c*(480);
	
		Active_Window_XY(480,272);							 
		Active_Window_WH(480,272);
		Draw_Square_Fill(ScalerGroup[Index].Color,(x+480),(y+272),(x+480+CurentW),(y+272+Length));
		NumLabelFlush(PageName);	
		TimeLabelFlush(PageName);	 
		BTE_Memory_Copy(0,canvas_image_width,(x+480),(y+272),0,canvas_image_width,(x+480),(y+272),0,canvas_image_width,x,y,12,Width,Length);
	}
	}		
}