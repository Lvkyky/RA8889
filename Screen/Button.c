#include "USART.h"
#include "screen.h"
#include "Button.h"
#include "Win.h"
#include "timer.h"
#include "api.h"
#include "RA8889.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include "Page.h"
#include "Input.h"
const struct ButtonType code ButtonGroup[ButtonCount] = {
///////////////////////////Main界面///////////////////////
{MainPreheatButton,Main,8,180,92,92,1,MainPreheatButtonCall},
{MainFailmentButton,Main,101,180,92,92,1,MainFailmentButtonCall},
{MainMoveButton,Main,287,180,92,92,1,MainMoveButtonCall},
{MainSettingButton,Main,380,180,92,92,1,MainSettingCall},
{MainEditt1Button,Main,198,50,40,40,0,MainEditt1ButtonCall},
{MainEditt2Button,Main,272,52,40,40,0,MainEditt2ButtonCall},
{MainEditt3Button,Main,343,52,40,40,0,MainEditt3ButtonCall},
{MainEditt4Button,Main,409,53,40,40,0,MainEditt4ButtonCall},
{MainVersionButton,Main,27,35,132,48,0,MainVersionButtonCall},
///////////////////////////MainPreheat界面///////////////////////
{MainPreheatCoolButton,MainPreheat,8,180,92,92,1,MainPreheatCoolButtonCall},
{MainFailmentButton,MainPreheat,101,180,92,92,1,MainFailmentButtonCall},
{MainPreheatMoveButton,MainPreheat,287,180,92,92,1,MainMoveButtonCall},
{MainPreheatSettingButton,MainPreheat,380,180,92,92,1,MainSettingCall},
{MainPreheatEditt1Button,MainPreheat,198,50,40,40,0,MainEditt1ButtonCall},
{MainPreheatEditt2Button,MainPreheat,272,52,40,40,0,MainEditt2ButtonCall},
{MainPreheatEditt3Button,MainPreheat,343,52,40,40,0,MainEditt3ButtonCall},
{MainPreheatEditt4Button,MainPreheat,409,53,40,40,0,MainEditt4ButtonCall},
{MainPreheatVersionButton,MainPreheat,27,35,132,48,0,MainVersionButtonCall},
//////////////////////////MainUdisk界面//////////////////////
{MainUdiskPreheatButton,MainUdisk,8,180,92,92,1,MainPreheatButtonCall},
{MainUdiskFailmentButton,MainUdisk,101,180,92,92,1,MainFailmentButtonCall},
{MainUdiskUsbButton,MainUdisk,194,180,92,92,1,MainUdiskUsbButtonCall},
{MainUdiskMoveButton,MainUdisk,287,180,92,92,1,MainMoveButtonCall},
{MainUdiskSettingButton,MainUdisk,380,180,92,92,1,MainSettingCall},
{MainUdiskEditt1Button,MainUdisk,198,50,40,40,0,MainEditt1ButtonCall},
{MainUdiskEditt2Button,MainUdisk,272,52,40,40,0,MainEditt2ButtonCall},
{MainUdiskEditt3Button,MainUdisk,343,52,40,40,0,MainEditt3ButtonCall},
{MainUdiskEditt4Button,MainUdisk,409,53,40,40,0,MainEditt4ButtonCall},
{MainUdiskVersionButton,MainUdisk,27,35,132,48,0,MainVersionButtonCall},
////////////////////////MainUdiskPreheat界面//////////////
{MainUdiskPreheatCoolButton,MainUdiskPreheat,8,180,92,92,1,MainPreheatCoolButtonCall},
{MainUdiskPreheatFailmentButton,MainUdiskPreheat,101,180,92,92,1,MainFailmentButtonCall},
{MainUdiskPreheatUsbButton,MainUdiskPreheat,194,180,92,92,1,MainUdiskUsbButtonCall},
{MainUdiskPreheatMoveButton,MainUdiskPreheat,287,180,92,92,1,MainMoveButtonCall},
{MainUdiskPreheatSettingButton,MainUdiskPreheat,380,180,92,92,1,MainSettingCall},
{MainUdiskPreheatEditt1Button,MainUdiskPreheat,198,50,40,40,0,MainEditt1ButtonCall},
{MainUdiskPreheatEditt2Button,MainUdiskPreheat,272,52,40,40,0,MainEditt2ButtonCall},
{MainUdiskPreheatEditt3Button,MainUdiskPreheat,343,52,40,40,0,MainEditt3ButtonCall},
{MainUdiskPreheatEditt4Button,MainUdiskPreheat,409,53,40,40,0,MainEditt4ButtonCall},
{MainUdiskPreheatVersionButton,MainUdiskPreheat,27,35,132,48,0,MainVersionButtonCall},
///////////////////////////Setting界面////////////////////
{SettingMotionButton,Setting,68,62,180,30,0,SettingMotionButtonCall},
{SettingFansButton,Setting,288,67,124,22,0,SettingFansButtonCall},
{SettingPreheatButton,Setting,63,109,167,31,0,SettingPreheatButtonCall},
{SettingBackButton,Setting,241,212,240,60,1,SettingBackCall},
{SettingFactButton,Setting,0,212,240,60,1,SettingFactButtonCall},
{SettingAutoLevelButton,Setting,286,107,151,31,0,SettingAutoLevelButtonCall},
///////////////////////////Version界面////////////////////
{VersionBackButton,Version,380,202,110,70,1,VersionBackButtonCall},
///////////////////////////Motion界面////////////////////
{MotionEditxButton,Motor,137,86,110,30,0,MotionEditxButtonCall},
{MotionEdityButton,Motor,368,85,110,30,0,MotionEdityButtonCall},
{MotionEditzButton,Motor,137,134,110,30,0,MotionEditzButtonCall},
{MotionEditeButton,Motor,371,139,110,30,0,MotionEditeButtonCall},
{MotionSaveButton,Motor,0,212,240,60,1,MotionSaveButtonCall},
{MotionBackButton,Motor,241,212,240,60,1,MotionBackButtonCall},
///////////////////////////Fans界面////////////////////
{FansSaveButton,Fansped,0,212,240,60,1,FansSaveButtonCall},
{FansBackButton,Fansped,241,212,240,60,1,FansBackButtonCall},
{FansEditf1Button,Fansped,247,65,98,27,0,FansEditf1ButtonCall},
{FansEditf2Button,Fansped,249,113,98,27,0,FansEditf2ButtonCall},
{FansEditf3Button,Fansped,244,159,98,27,0,FansEditf3ButtonCall},
///////////////////////////Preheat界面////////////////////
{PreheatSaveButton,Preheat,0,212,240,60,1,PreheatSaveButtonCall},
{PreheatBackButton,Preheat,241,212,240,60,1,PreheatBackButtonCall},
{PreheatEditt1Button,Preheat,247,65,98,27,0,PreheatEditt1ButtonCall},
{PreheatEditt2Button,Preheat,249,113,98,27,0,PreheatEditt2ButtonCall},
{PreheatEditt3Button,Preheat,244,159,98,27,0,PreheatEditt3ButtonCall},
///////////////////////////Move界面////////////////////
{MoveXhomeButton,Move,0,0,94,67,1,MoveXhomeButtonCall},
{MoveYhomeButton,Move,0,68,94,67,1,MoveYhomeButtonCall},
{MoveZhomeButton,Move,0,136,94,67,1,MoveZhomeButtonCall},
{MoveAhomeButton,Move,0,204,94,67,1,MoveAhomeButtonCall},
{MoveBackButton,Move,416,208,64,64,1,MoveBackButtonCall},
{MoveSubXButton,Move,119,99,62,32,1,MoveSubXButtonCall},
{MoveAddXButton,Move,259,99,62,32,1,MoveAddXButtonCall},
{MoveSubYButton,Move,189,164,62,32,1,MoveSubYButtonCall},
{MoveAddYButton,Move,189,34,62,32,1,MoveAddYButtonCall},
{MoveSubZButton,Move,332,34,62,32,1,MoveSubZButtonCall},
{MoveAddZButton,Move,332,164,62,32,1,MoveAddZButtonCall},
///////////////////////////AoutoLeve1界面////////////////////
{AutoLevel1OffButton,AoutoLeve1,54,103,254,29,0,AutoLevel1OnButtonCall},
{AutoLevel1SaveButton,AoutoLeve1,0,212,240,60,1,AutoLevel1SaveButtonCall},
{AutoLevel1BackButton,AoutoLeve1,241,212,240,60,1,AutoLevel1BackButtonCall},
{AutoLeve1EditAl1Button,AoutoLeve1,163,59,103,40,1,AutoLeve1EditAl1ButtonCall},
{AutoLeve1EditAl2Button,AoutoLeve1,349,153,88,26,1,AutoLeve1EditAl2ButtonCall},
///////////////////////////AoutoLeve2界面////////////////////
{AutoLeve2EditAl1Button,AoutoLeve2,344,146,97,36,1,AutoLeve2EditAl1ButtonCall},
{AutoLeve2EditAl2Button,AoutoLeve2,349,153,88,26,1,AutoLeve2EditAl2ButtonCall},
{AutoLevel2OnButton,AoutoLeve2,54,103,254,29,0,AutoLevel2OnButtonCall}, 
{AutoLevel2SaveButton,AoutoLeve2,0,212,240,60,1,AutoLevel1SaveButtonCall},
{AutoLevel2BackButton,AoutoLeve2,241,212,240,60,1,AutoLevel1BackButtonCall},
{AutoLevel2CalibrationButton,AoutoLeve2,43,145,139,38,1,AutoLevel2CalibrationButtonCall},
///////////////////////////Failment界面////////////////////
{Failment10Button,Failment,23,68,78,40,1,Failment10ButtonCall},
{Failment20Button,Failment,23,124,78,40,1,Failment20ButtonCall},
{Failment30Button,Failment,23,172,78,40,1,Failment30ButtonCall},
{Failment50Button,Failment,23,218,78,40,1,Failment50ButtonCall},
{FailmentUnloadButton,Failment,204,184,92,32,1,FailmentUnloadButtonCall},
{FailmentRxButton,Failment,401,0,79,90,1,FailmentRxButtonCall},
{FailmentExButton,Failment,401,91,79,90,1,FailmentExButtonCall},
{FailmentBackButton,Failment,401,182,78,87,1,FailmentBackButtonCall},
//////////////////////////文件界面///////////////////////////////////////

{UdiskOneBackButton,UdiskOne,418,208,58,70,1,FileBackButtonCall},

{UdiskNextBackButton,UdiskNext,418,208,58,70,1,FileBackButtonCall},
{UdiskNextNextButton,UdiskNext,419,141,58,56,1,FileNextButtonCall},

{UdiskBothBackButton,UdiskBoth,418,207,58,70,1,FileBackButtonCall},
{UdiskBothNextButton,UdiskBoth,419,141,58,56,1,FileNextButtonCall},
{UdiskBothLastButton,UdiskBoth,419,0,58,56,1,FileLastButtonCall},

{UdiskLastBackButton,UdiskLast,418,207,58,70,1,FileBackButtonCall},
{UdiskLastLastButton,UdiskLast,419,0,58,56,1,FileLastButtonCall}, //翻滚

{FileSelect0Button,UdiskOne,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskOne,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskOne,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskOne,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskOne,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskOne,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskOne,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskLast,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskLast,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskLast,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskLast,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskLast,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskLast,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskLast,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskNext,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskNext,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskNext,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskNext,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskNext,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskNext,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskNext,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskBoth,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskBoth,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskBoth,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskBoth,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskBoth,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskBoth,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskBoth,0,(40*6),480,30,1,FileSelect6ButtonCall},//选择



{UdiskOneUpBackButton,UdiskOneUp,418,208,58,70,1,FileBackButtonCall},
{UdiskOneUppButton,UdiskOneUp,420,73,56,60,1,FileUppButtonCall},

{UdiskNextUpBackButton,UdiskNextUp,418,208,58,70,1,FileBackButtonCall},
{UdiskNextUpNextButton,UdiskNextUp,419,141,58,56,1,FileNextButtonCall},

{UdiskBothUpBackButton,UdiskBothUp,418,207,58,70,1,FileBackButtonCall},
{UdiskBothUpNextButton,UdiskBothUp,419,141,58,56,1,FileNextButtonCall},
{UdiskBothUpLastButton,UdiskBothUp,419,0,58,56,1,FileLastButtonCall},

{UdiskLastUpBackButton,UdiskLastUp,418,207,58,70,1,FileBackButtonCall},
{UdiskLastUpLastButton,UdiskLastUp,419,0,58,56,1,FileLastButtonCall},  

{UdiskLastUppButton,UdiskLastUp,420,73,56,60,1,FileUppButtonCall},
{UdiskBothUppButton,UdiskBothUp,420,73,56,60,1,FileUppButtonCall},
{UdiskNextUppButton,UdiskNextUp,420,73,56,60,1,FileUppButtonCall},//翻滚

{FileSelect0Button,UdiskOneUp,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskOneUp,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskOneUp,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskOneUp,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskOneUp,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskOneUp,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskOneUp,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskLastUp,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskLastUp,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskLastUp,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskLastUp,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskLastUp,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskLastUp,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskLastUp,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskNextUp,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskNextUp,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskNextUp,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskNextUp,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskNextUp,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskNextUp,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskNextUp,0,(40*6),480,30,1,FileSelect6ButtonCall},
{FileSelect0Button,UdiskBothUp,0,(40*0),480,30,1,FileSelect0ButtonCall},
{FileSelect1Button,UdiskBothUp,0,(40*1),480,30,1,FileSelect1ButtonCall},
{FileSelect2Button,UdiskBothUp,0,(40*2),480,30,1,FileSelect2ButtonCall},
{FileSelect3Button,UdiskBothUp,0,(40*3),480,30,1,FileSelect3ButtonCall},
{FileSelect4Button,UdiskBothUp,0,(40*4),480,30,1,FileSelect4ButtonCall},
{FileSelect5Button,UdiskBothUp,0,(40*5),480,30,1,FileSelect5ButtonCall},
{FileSelect6Button,UdiskBothUp,0,(40*6),480,30,1,FileSelect6ButtonCall},    //选择

/////////////////////PrintConfirm界面////////////////////////////////
{PrintConfirmYesButton,PrintConfirm,0,200,230,73,1,PrintConfirmYesButtonCall}, 
{PrintConfirmCanButton,PrintConfirm,245,200,230,73,1,PrintConfirmCanButtonCall},
/////////////////////////Print界面//////////////////////////////////
{PrintVersionButton,Print,0,0,165,66,1,PrintVersionButtonCall},
{PrintEditt1Button,Print,198,50,40,60,0,PrintEditt1ButtonCall},
{PrintEditt2Button,Print,272,52,40,60,0,PrintEditt2ButtonCall},
{PrintEditt3Button,Print,343,52,40,60,0,PrintEditt3ButtonCall},
{PrintEditt4Button,Print,409,53,40,60,0,PrintEditt4ButtonCall},

{PrintStopButton,Print,287,180,92,92,1,PrintStopButtonCall},
{PrintChangeButton,Print,101,180,92,92,1,PrintChangeButtonCall},
{PrintAdjustButton,Print,318,0,114,28,1,PrintAdjustButtonCall},
{PrintPauseButton,Print,194,180,92,92,1,PrintPauseButtonButtonCall},
/////////////////////////PrintPause界面//////////////////////////////////
{PrintPauseVersionButton,PrintPause,0,0,165,66,1,PrintPauseVersionButtonCall},
{PrintPauseAdjustButton,PrintPause,321,5,108,28,1,PrintPauseAdjustButtonCall},
{PrintPauseBedUpButton,PrintPause,8,180,92,92,1,PrintPauseBedUpButtonCall},
{PrintPauseChangeButton,PrintPause,101,180,92,92,1,PrintPauseChangeButtonCall},
{PrintPauseResumButton,PrintPause,194,180,92,92,1,PrintPauseResumButtonCall},
{PrintPauseStopButton,PrintPause,287,180,92,92,1,PrintPauseStopButtonCall},
{PrintPauseBedDownButton,PrintPause,380,180,92,92,1,PrintPauseBedDownButtonCall},
///////////////////////////Adjust界面//////////////////////////////////
{AdjustSettingButton,Adjust,8,218,225,48,1,MainSettingCall},
{AdjustBackButton,Adjust,245,216,225,48,1,SettingBackCall},

{AdjustEditAd1Button,Adjust,246,60,101,35,1,AdjustEditAd1ButtonCall},
{AdjustEditAd2Button,Adjust,246,110,101,35,1,AdjustEditAd2ButtonCall},
{AdjustEditAd3Button,Adjust,246,160,101,35,1,AdjustEditAd3ButtonCall}
};//普通按钮



/******************************按钮核心函数*******************************/

//========================================================================
// 函数: IsPush
// 功能: 检测某个按钮是否被按下
//返回值：1：按下，0：没按下
// 版本: V1.0, 2021-06-5
//========================================================================	
u8 IsPush(struct ButtonType button,u16 x,u16 y)
{
	if(x>button.x&&x<(button.x+button.width)&&y>button.y&&y<(button.y+button.length))
	{
	 return 1;
	}
	else
	{
	 return 0;
	}
}



//========================================================================
// 函数: ButtonCall
// 功能: 执行按钮的回调函数
//参数：所有按钮，当前页面ID，当前触摸坐标
// 版本: V1.0, 2021-06-5
//========================================================================	
void ButtonCall(u16 PageId,u16 x,u16 y)
{
	u8 Index;
	for(Index=0;Index<ButtonCount;Index++)
	{
		if(ButtonGroup[Index].PageName==PageIdtoPageName(PageId)&&(IsPush(ButtonGroup[Index],x,y))) break;		
	}
	if(Index==ButtonCount||Index>ButtonCount)
	{
		PrintString1("There is no buttton to do call function\r\n");
		return;
	}
	ButtonGroup[Index].func();//按键回调函数	
}



//========================================================================	
// 函数: ButtonPressEffect
// 功能: 实现普通按钮的按键效果
//参数：所有按钮，当前页面ID，当前触摸坐标
// 版本: V1.0, 2021-06-5
//========================================================================	
void ButtonPressEffect(u16 PageId,u16 x,u16 y)
{
	u8 i;
	u16 xx,yy;
	u8 width,length;
	for(i=0;i<ButtonCount;i++)
	{
		if(ButtonGroup[i].PageName==PageIdtoPageName(PageId)&&(IsPush(ButtonGroup[i],x,y)&&ButtonGroup[i].Effect==1))break;		
	}
	if(i==ButtonCount||i>ButtonCount)
	{
		PrintString1("There is no buttton to do effect\r\n");
		return;
	}	
	width=ButtonGroup[i].width;
	length=ButtonGroup[i].length;
	xx=ButtonGroup[i].x;
	yy=ButtonGroup[i].y;			
	BTE_Memory_Copy(0,canvas_image_width,xx,(272+yy),0,canvas_image_width,xx,(272+yy),0,canvas_image_width,xx,yy,12,width,length);	
}





//========================================================================	
// 函数: ButtonRealeEffect()
// 描述: 用切回原图的方式实现普通按键释放效果
//参数：所有按钮，当前页面ID，当前触摸坐标
// 版本: V1.0, 2021-6-8
//========================================================================	
void ButtonRealeEffect(u16 PageId,u16 x,u16 y)
{
	u8 PageIndex;
	u8 PicIndex;
	u8 ButtonIndex;
	u16 xx,yy;
	u8 width,length;
	for(PageIndex=0;PageIndex<PageCount;PageIndex++)
	{
		if(PageGroup[PageIndex].Id==PageId) break;
	}
	if(PageIndex==PageCount||PageIndex>PageCount)
	{
		PrintString1("Invalide PageId\r\n");
		return;
	}
	PicIndex=PageGroup[PageIndex].PicIndex;		
	JPG_NOR(BINARY_INFO[PicIndex].start_addr,BINARY_INFO[PicIndex].img_size,canvas_image_width,480,0);//加载到右1	
	for(ButtonIndex=0;ButtonIndex<ButtonCount;ButtonIndex++)
	{
		if(ButtonGroup[ButtonIndex].PageName==PageIdtoPageName(PageId)&&IsPush(ButtonGroup[ButtonIndex],x,y)) break;
	}
	if(ButtonIndex==ButtonCount||ButtonIndex>ButtonCount)
	{
		PrintString1("There is no buttton to release\r\n");
		return;
	}		
	width=ButtonGroup[ButtonIndex].width;
	length=ButtonGroup[ButtonIndex].length;
	xx=ButtonGroup[ButtonIndex].x;
	yy=ButtonGroup[ButtonIndex].y;
	BTE_Memory_Copy(0,canvas_image_width,(xx+480),yy,0,canvas_image_width,(xx+480),yy,0,canvas_image_width,xx,yy,12,width,length);	
}

/*******************按钮核心函数************************/

//////////////////////Main 界面////////////////
void  MainVersionButtonCall()
{
	res_03[0]=0X00;    
	res_03[1]=0X62; 
	PageShift(Version); 
	Send_Mesg_res(0x03,2);  
}

void MainSettingCall(void)
{ 
	mem_0700[0]=0x07;
	mem_0700[1]=0x0c;    				
	Send_Mesg_var(0x0700,1); 						 						 
}
 
void MainMoveButtonCall()
{
	res_03[0]=0X00;    
	res_03[1]=0X42; 
	PageShift(Move);
}

 
 
//////////////////////Setting界面///////////////////////
void VersionBackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x01;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR（切换回主界面）	
}


void SettingBackCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x01;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到主界面）		
}

void SettingFactButtonCall()
{
	mem_0062[0]=0xFF;
	mem_0062[0]=0x09;
	WindowOn(SettingSelectFact);		
}

void SettingMotionButtonCall()
{
	res_03[0]=0X00;
	res_03[1]=0X58;
	PageShift(Motor);//主动切换
	Send_Mesg_res(3,2);//告诉master切换结果						
}


void SettingFansButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x35;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到FANspeed）	
}

void SettingPreheatButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x36;    //初始化CMD_ADDR
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到Preheat）	
}
	
void SettingAutoLevelButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x38;    //初始化CMD_ADDR
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到Preheat）
}


void MainEditt1ButtonCall()
{
	InputOn(MainEditt1);	
}

void MainEditt2ButtonCall()
{
	InputOn(MainEditt2);		
}

void MainEditt3ButtonCall()
{
	InputOn(MainEditt3);		
}

void MainEditt4ButtonCall()
{
	InputOn(MainEditt4);		
}

////////////////////////Motion界面///////////////
void MotionEditxButtonCall()
{
	InputOn(MoveEditx);			
}

void MotionEdityButtonCall()
{
	InputOn(MoveEdity);	
}

void MotionEditzButtonCall()
{
	InputOn(MoveEditz);	
}

void MotionEditeButtonCall()
{
	InputOn(MoveEdite);
}

void MotionSaveButtonCall()
{
	 mem_0700[0]=0x07;
	 mem_0700[1]=0x30;    //初始化CMD_ADDR						
	 Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（save motor parameter）	
}

void MotionBackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0c;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到主界面）	
}

/////////////////////Fans界面////////////////////
void FansSaveButtonCall()
{
	 mem_0700[0]=0x07;
	 mem_0700[1]=0x30;    //初始化CMD_ADDR						
	 Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（启动弹窗）
}


void FansBackButtonCall()
{
	 mem_0700[0]=0x07;
	 mem_0700[1]=0x0C;    //初始化CMD_ADDR						
	 Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR	（切换到设置界面）
}


	
void FansEditf1ButtonCall()
{
	InputOn(FansEditF1);//进入F1编辑窗口
}

void FansEditf2ButtonCall()
{
	InputOn(FansEditF2);//进入F1编辑窗口
}

void FansEditf3ButtonCall()
{
	InputOn(FansEditF3);//进入F1编辑窗口
}

///////////////Preheat界面/////////////////////	
void PreheatSaveButtonCall()
{
    mem_0700[0]=0x07;
	mem_0700[1]=0x30;    				
	Send_Mesg_var(0x0700,1); 
}

void PreheatBackButtonCall()
{
	 mem_0700[0]=0x07;
	 mem_0700[1]=0x0C;    				
	 Send_Mesg_var(0x0700,1); 
}

void PreheatEditt1ButtonCall()
{
	InputOn(PreheatEditP1);
}

void PreheatEditt2ButtonCall()
{
	InputOn(PreheatEditP2);
}

void PreheatEditt3ButtonCall()
{
	InputOn(PreheatEditP3);
}


//////////////////////Move界面//////////////////////
void MoveXhomeButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x11;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR（切换到主界面）
}


void MoveYhomeButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x12;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR（切换到主界面）
}

void MoveZhomeButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x13;    //初始化CMD_ADDR						
	Send_Mesg_var(0x0700,1); //发给主控 CMD_ADDR（切换到主界面）
}


void MoveAhomeButtonCall()
{	
	mem_0700[0]=0x07;
	mem_0700[1]=0x10;    					
	Send_Mesg_var(0x0700,1); 
}


void MoveBackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x01;    						
	Send_Mesg_var(0x0700,1); 
}

void MoveSubXButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x17;    					
	Send_Mesg_var(0x0700,1); 
}
void MoveAddXButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x14;    						
	Send_Mesg_var(0x0700,1); 
}
void MoveSubYButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x18;    					
	Send_Mesg_var(0x0700,1); 
}
void MoveAddYButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x15;   					
	Send_Mesg_var(0x0700,1); 
}
void MoveSubZButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x19;   					
	Send_Mesg_var(0x0700,1); 
}
void MoveAddZButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x16;    						
	Send_Mesg_var(0x0700,1); 
}

/////////////////Auto Level/////////////////////
void AutoLevel1OnButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x6F;    					
	Send_Mesg_var(0x0700,1); 
}

void AutoLevel1SaveButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x30;    						
	Send_Mesg_var(0x0700,1); 
}


void AutoLevel1BackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0C;   					
	Send_Mesg_var(0x0700,1);
}


void AutoLevel2OnButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x6F;   					
	Send_Mesg_var(0x0700,1);
}

void AutoLevel2CalibrationButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x60;   					
	Send_Mesg_var(0x0700,1);
}
void AutoLeve1EditAl1ButtonCall()
{
	InputOn(Auto1EditAl1);
}

void AutoLeve1EditAl2ButtonCall()
{
	InputOn(Auto1EditAl2);
}

void AutoLeve2EditAl1ButtonCall()
{
	InputOn(Auto2EditAl1);
}
void AutoLeve2EditAl2ButtonCall()
{
	InputOn(Auto2EditAl2);
}

///////////////////Main/////////////////////////
void MainFailmentButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x08;   					
	Send_Mesg_var(0x0700,1); 
}


void MainPreheatButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x05;   					
	Send_Mesg_var(0x0700,1); 
}
////////////////MainPreheat///////////////////
void MainPreheatCoolButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x06;   					
	Send_Mesg_var(0x0700,1); 
}

///////////////Failment///////////////////
void Failment10ButtonCall()
{
	mem_0022[0]=0x00;
	mem_0022[1]=0x0A;   					
	Send_Mesg_var(0x0022,1); 
}

void Failment20ButtonCall()
{
	mem_0022[0]=0x00;
	mem_0022[1]=0x14;   					
	Send_Mesg_var(0x0022,1);
}

void Failment30ButtonCall()
{
	mem_0022[0]=0x00;
	mem_0022[1]=0x1E;   					
	Send_Mesg_var(0x0022,1);
}

void Failment50ButtonCall()
{
	mem_0022[0]=0x00;
	mem_0022[1]=0x32;   					
	Send_Mesg_var(0x0022,1);
}

void FailmentUnloadButtonCall()
{	
	mem_0700[0]=0x07;
	mem_0700[1]=0x22;   					
	Send_Mesg_var(0x0700,1); 
}

void FailmentRxButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x21;   					
	Send_Mesg_var(0x0700,1); 
}

void FailmentExButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x20;   					
	Send_Mesg_var(0x0700,1); 
}

void FailmentBackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x01;   					
	Send_Mesg_var(0x0700,1); 
}


///////////////////MainUdisk///////////////////////////
void MainUdiskUsbButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x07;   					
	Send_Mesg_var(0x0700,1); 
}
/////////////////文件界面（Next,Last,Both）/////////////////
void FileBackButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x01;   					
	Send_Mesg_var(0x0700,1); 
}

void FileNextButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x40;   					
	Send_Mesg_var(0x0700,1); 
}


void FileLastButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x41;   					
	Send_Mesg_var(0x0700,1); 
}
void FileUppButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x42;   					
	Send_Mesg_var(0x0700,1); 
}

void FileSelect0ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA0;   					
	Send_Mesg_var(0x0700,1); 
	FileSelect=0;
}
void FileSelect1ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA1;   					
	Send_Mesg_var(0x0700,1); 
	FileSelect=1;
}
void FileSelect2ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA2;   					
	Send_Mesg_var(0x0700,1);
	FileSelect=2;	
}
void FileSelect3ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA3;   					
	Send_Mesg_var(0x0700,1);
	FileSelect=3;
}
void FileSelect4ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA4;   					
	Send_Mesg_var(0x0700,1);
	FileSelect=4;
}
void FileSelect5ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA5;   					
	Send_Mesg_var(0x0700,1);
	FileSelect=5;
}
void FileSelect6ButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0xA6;   					
	Send_Mesg_var(0x0700,1);
	FileSelect=6;
}




////////////////////////PrintConfirm///////////////
void PrintConfirmYesButtonCall()
{
	mem_0700[0]=0x00;
	mem_0700[1]=0xB1;   					
	Send_Mesg_var(0x0700,1);
}

void PrintConfirmCanButtonCall()
{
	mem_0700[0]=0x00;
	mem_0700[1]=0xB2;   					
	Send_Mesg_var(0x0700,1);
}

/////////////////////Print界面//////////////////
void PrintVersionButtonCall()
{
	res_03[0]=0X00;    
	res_03[1]=0X62; 
	PageShift(Version); 
	Send_Mesg_res(0x03,2); 
}

void PrintEditt1ButtonCall()
{
	InputOn(PrintEditt1);	
}
void PrintEditt2ButtonCall()
{
	InputOn(PrintEditt2);	
}
void PrintEditt3ButtonCall()
{
	InputOn(PrintEditt3);	
}
void PrintEditt4ButtonCall()
{
	InputOn(PrintEditt4);	
}

void PrintStopButtonCall()
{
	WindowOn(PrintSelectCancelPrint);	
}
void PrintChangeButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x09;   					
	Send_Mesg_var(0x0700,1);
}
void PrintAdjustButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0D;   					
	Send_Mesg_var(0x0700,1);
}

void PrintPauseButtonButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x02;   					
	Send_Mesg_var(0x0700,1);
}

/////////////////PrintPause界面///////////////
void PrintPauseAdjustButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0D;   					
	Send_Mesg_var(0x0700,1);
}
void PrintPauseBedUpButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0A;   					
	Send_Mesg_var(0x0700,1);
}
void PrintPauseChangeButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x09;   					
	Send_Mesg_var(0x0700,1);
}
void PrintPauseResumButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x03;   					
	Send_Mesg_var(0x0700,1);
}

void PrintPauseStopButtonCall()
{
	WindowOn(PrintSelectCancelPrint);	
}
void PrintPauseBedDownButtonCall()
{
	mem_0700[0]=0x07;
	mem_0700[1]=0x0B;   					
	Send_Mesg_var(0x0700,1);
}

void PrintPauseVersionButtonCall()
{
	res_03[0]=0X00;    
	res_03[1]=0X62; 
	PageShift(Version); 
	Send_Mesg_res(0x03,2); 
}
/////////////////////////Adjust界面///////////////
void AdjustEditAd1ButtonCall()
{
	InputOn(AdjustEditAd1);
}

void AdjustEditAd2ButtonCall()
{
	InputOn(AdjustEditAd2);
}

void AdjustEditAd3ButtonCall()
{
	InputOn(AdjustEditAd3);
}




























