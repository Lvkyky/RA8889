#include "Animitation.h"
#include "timer.h"
#include "api.h"
#include "Page.h"
#include "All_8889_Pic_NOR.h"
#include "UserDef.h"


u8 AnimationIndex=0;
struct AnimitationType AnimitationGroup[AnimitationCount]={
{PowerOn,0,25,40,100}		
};


//============================================
// 函数: AnimationFlush()
// 描述: 实现开机动画的播放
// 参数:无
// 返回: 无
// 版本: V1.0, 2021-7-2
//============================================
void AnimitationFlush(u8 PageName)
{
	u8 Index;
	for(Index=0;Index<AnimitationCount;Index++)
	{
		if(AnimitationGroup[Index].PageName==PageName) break;
	}
	if(Index==AnimitationCount||Index>AnimitationCount)
	{
		AnimitationTimer.swit=0;
		AnimationIndex=0;
		return;
	}
	else//有动画
	{	
		AnimitationTimer.swit=1;	
		if(AnimitationTimer.update==1)
		{
			AnimitationTimer.update=0;
			AnimitationTimer.count=0;
			
			if(AnimationIndex<AnimitationGroup[Index].End)
			{
				JPG_NOR(BINARY_INFO[AnimationIndex].start_addr,BINARY_INFO[AnimationIndex].img_size,canvas_image_width,0,0);
				AnimationIndex++;
			}
			else
			{
				AnimationIndex=AnimitationGroup[Index].Circle;
			}
		}
	}
}

