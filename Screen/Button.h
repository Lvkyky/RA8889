#ifndef		__BUTTON_H
#define		__BUTTON_H
#include "STC15Fxxxx.H"

#define ButtonCount 190
typedef void (*Fun)(void);

struct ButtonType
{   u8 Name;
	u8 PageName;//页面名字
	u16 x;//起始坐标
	u16 y;
	u8 width;//长宽
	u8 length;
	u8 Effect;//有无按键效果
	Fun func;//按下的回调函数
}; 


struct WinEditType //编辑弹窗类型
{
u16 PageId;//窗口所属页面
u8  name;//窗口名字	
u8  PicIndex;//窗口所对应的图片索引
u8  PicIndex1;
};

enum Button{
///////////////////////Main////////////////////////////
MainSettingButton=0x00,MainVersionButton,MainMoveButton,MainFailmentButton,MainEditt1Button,MainEditt2Button,MainEditt3Button,MainEditt4Button,MainPreheatButton,
//////////////////////MainPreheat/////////////////////
MainPreheatCoolButton,MainPreheatMoveButton,MainPreheatSettingButton,MainPreheatEditt1Button,
MainPreheatEditt2Button,MainPreheatEditt3Button,MainPreheatEditt4Button,MainPreheatVersionButton,	
//////////////////////MainUdisk///////////////////////	
MainUdiskPreheatButton,MainUdiskFailmentButton,MainUdiskUsbButton,MainUdiskMoveButton,MainUdiskSettingButton,MainUdiskEditt1Button,
MainUdiskEditt2Button,MainUdiskEditt3Button,MainUdiskEditt4Button,MainUdiskVersionButton,
//////////////////////MainUdiskPreheat///////////////		
MainUdiskPreheatCoolButton,MainUdiskPreheatFailmentButton,MainUdiskPreheatUsbButton,MainUdiskPreheatMoveButton,MainUdiskPreheatSettingButton,
MainUdiskPreheatEditt1Button,MainUdiskPreheatEditt2Button,MainUdiskPreheatEditt3Button,MainUdiskPreheatEditt4Button,MainUdiskPreheatVersionButton,	
/////////////////////////////Setting///////////////////////////////////	
SettingMotionButton,SettingFansButton,SettingPreheatButton,SettingBackButton,SettingFactButton,SettingAutoLevelButton,
/////////////////////////////Version///////////////////////////////////	
VersionBackButton,
/////////////////////////////Motion///////////////////////////////////	
MotionEditxButton,MotionEdityButton,MotionEditzButton,MotionEditeButton,MotionSaveButton,MotionBackButton,
/////////////////////////////Fans///////////////////////////////////	
FansEditf1Button,FansEditf2Button,FansEditf3Button,FansBackButton,FansSaveButton,
/////////////////////////////Preheat///////////////////////////////////	
PreheatSaveButton,PreheatBackButton,PreheatEditt1Button,PreheatEditt2Button,PreheatEditt3Button,
/////////////////////////////Move///////////////////////////////////	
MoveXhomeButton,MoveYhomeButton,MoveZhomeButton,MoveAhomeButton,MoveBackButton,MoveSubXButton,MoveAddXButton,MoveSubYButton,
MoveAddYButton,MoveSubZButton,MoveAddZButton,MoveUnit1Button,MoveUnit2Button,MoveUnit3Button,MoveUnit4Button,
/////////////////////////////AutoLevel1///////////////////////////////////
AutoLevel1OffButton,AutoLevel1SaveButton,AutoLevel1BackButton,AutoLeve1EditAl1Button,AutoLeve1EditAl2Button,
/////////////////////////////AutoLevel2///////////////////////////////////
AutoLevel2SaveButton,AutoLevel2CalibrationButton,AutoLevel2OnButton,AutoLevel2BackButton,AutoLeve2EditAl1Button,AutoLeve2EditAl2Button,
/////////////////////////////Failment///////////////////////////////////
Failment10Button,Failment20Button,Failment30Button,Failment50Button,FailmentUnloadButton,FailmentRxButton,FailmentExButton,FailmentBackButton,
/////////////////////////////UdiskNext///////////////////////////////////
UdiskNextBackButton,UdiskNextNextButton,
/////////////////////////////UdiskBoth///////////////////////////////////
UdiskBothBackButton,UdiskBothNextButton,UdiskBothLastButton,
/////////////////////////////UdiskLast///////////////////////////////////
UdiskLastBackButton,UdiskLastLastButton,
/////////////////////////////UdiskOne///////////////////////////////////
UdiskOneBackButton,
/////////////////////////////UdiskOneUp///////////////////////////////////
UdiskOneUpBackButton,UdiskOneUppButton,
/////////////////////////////UdiskNextUp///////////////////////////////////
UdiskNextUpBackButton,UdiskNextUpNextButton,
/////////////////////////////UdiskBothUp///////////////////////////////////
UdiskBothUpBackButton,UdiskBothUpNextButton,UdiskBothUpLastButton,
/////////////////////////////UdiskLastUp///////////////////////////////////
UdiskLastUpBackButton,UdiskLastUpLastButton,
/////////////////////////////FileSelect///////////////////////////////////
FileSelect0Button,FileSelect1Button,FileSelect2Button,FileSelect3Button,FileSelect4Button,FileSelect5Button,FileSelect6Button,UdiskLastUppButton,UdiskBothUppButton,UdiskNextUppButton,
/////////////////////////////PrintConfirm///////////////////////////////////
PrintConfirmYesButton,PrintConfirmCanButton,
/////////////////////////////Print///////////////////////////////////
PrintVersionButton,PrintEditt1Button,PrintEditt2Button,PrintEditt3Button,PrintEditt4Button,PrintStopButton,PrintChangeButton,PrintAdjustButton,PrintPauseButton,
/////////////////////////////Adjust///////////////////////////////////
AdjustSettingButton,AdjustBackButton,AdjustEditAd1Button,AdjustEditAd2Button,AdjustEditAd3Button,
///////////////////////PrintPause界面/////////////////
PrintPauseAdjustButton,PrintPauseBedUpButton,PrintPauseChangeButton,PrintPauseResumButton,PrintPauseStopButton,PrintPauseBedDownButton,PrintPauseVersionButton
};//普通按钮枚举	

extern const struct ButtonType code ButtonGroup[];//普通按钮组

void SettingBackCall();
void SettingFactButtonCall();
void VersionBackButtonCall();
void SettingMotionButtonCall();
void SettingFansButtonCall();
void SettingPreheatButtonCall();
void SettingAutoLevelButtonCall();

void MainSettingCall();
void MainMoveButtonCall();
void MainVersionButtonCall();
void MainPreheatButtonCall();
void MainFailmentButtonCall();
void MainEditt1ButtonCall();
void MainEditt2ButtonCall();
void MainEditt3ButtonCall();
void MainEditt4ButtonCall();
void MotionEditxButtonCall();
void MotionEdityButtonCall();
void MotionEditzButtonCall();
void MotionEditeButtonCall();
void MotionSaveButtonCall();
void MotionBackButtonCall();
void FansSaveButtonCall();
void FansBackButtonCall();
void FansEditf1ButtonCall();
void FansEditf2ButtonCall();
void FansEditf3ButtonCall();

void PreheatSaveButtonCall();
void PreheatBackButtonCall();
void PreheatEditt1ButtonCall();
void PreheatEditt2ButtonCall();
void PreheatEditt3ButtonCall();

void MoveXhomeButtonCall();
void MoveYhomeButtonCall();
void MoveZhomeButtonCall();
void MoveAhomeButtonCall();
void MoveBackButtonCall();

void MoveSubXButtonCall();
void MoveAddXButtonCall();
void MoveSubYButtonCall();
void MoveAddYButtonCall();
void MoveSubZButtonCall();
void MoveAddZButtonCall();

void MoveUnit1ButtonCall();
void MoveUnit2ButtonCall();
void MoveUnit3ButtonCall();
void MoveUnit4ButtonCall();

void AutoLevel1OnButtonCall();
void AutoLevel1SaveButtonCall();
void AutoLevel1BackButtonCall();
void AutoLevel2OnButtonCall();
void AutoLevel2CalibrationButtonCall();
void AutoLeve1EditAl1ButtonCall();
void AutoLeve1EditAl2ButtonCall();
void AutoLeve2EditAl1ButtonCall();   
void AutoLeve2EditAl2ButtonCall();

void MainPreheatCoolButtonCall();

void Failment10ButtonCall();
void Failment20ButtonCall();
void Failment30ButtonCall();
void Failment50ButtonCall();
void FailmentUnloadButtonCall();
void FailmentRxButtonCall();
void FailmentExButtonCall();
void FailmentBackButtonCall();


void MainUdiskUsbButtonCall();
void FileBackButtonCall();
void FileNextButtonCall();
void FileLastButtonCall();
void FileUppButtonCall();

void FileSelect0ButtonCall();
void FileSelect1ButtonCall();
void FileSelect2ButtonCall();
void FileSelect3ButtonCall();
void FileSelect4ButtonCall();
void FileSelect5ButtonCall();
void FileSelect6ButtonCall();

void PrintConfirmYesButtonCall();
void PrintConfirmCanButtonCall();

void PrintVersionButtonCall();
void PrintEditt1ButtonCall();
void PrintEditt2ButtonCall();
void PrintEditt3ButtonCall();
void PrintEditt4ButtonCall();
void PrintStopButtonCall();
void PrintChangeButtonCall();
void PrintPauseButtonButtonCall();
void PrintAdjustButtonCall();


void PrintPauseAdjustButtonCall();
void PrintPauseBedUpButtonCall();
void PrintPauseChangeButtonCall();
void PrintPauseResumButtonCall();
void PrintPauseStopButtonCall();
void PrintPauseBedDownButtonCall();
void PrintPauseVersionButtonCall();


void AdjustEditAd1ButtonCall();
void AdjustEditAd2ButtonCall();
void AdjustEditAd3ButtonCall();
//回调函数


u8 IsPush(struct ButtonType button,u16 x,u16 y);//按钮按下判断
void ButtonCall(u16 PageId,u16 x,u16 y);//按键回调函数
void ButtonPressEffect(u16 PageId,u16 x,u16 y);//按下效果的实现
void ButtonRealeEffect(u16 PageId,u16 x,u16 y);
void Button_release(u8 ButtonName);//释放按键效果
#endif