#ifndef		__WIN_H
#define		__WIN_H
#include "screen.h"
#include "Button.h"

#define Wincount 16
#define NumButtonCount 17

typedef void (*WinFun0)(u16 x,u16 y,u8 WinName);
typedef void (*WinFun1)(void);

struct WinType //±‡º≠µØ¥∞¿‡–Õ
{
	u8 WinClass;
	u8 PageName;
	u8  Name;
	u16 Addr;
	u8 PicIndex;
	u8 PicIndex1;
	u8 Position;
};



enum WinClas{Select=0x00,SingleSelect,Info};
enum Win{
SettingSelectFact=0X00,SettingInfoFac,
MotorSave,
FansSave,
PreheSave,	
MoveHoming,MovemovingAsix,
AoutoLeve1CalibrationProbe,AoutoLeve1CalibrationMes,AoutoLeve1Save,Aoutolevel1SelectCalibrate,
AoutoLeve2CalibrationProbe,
FailmentLow,
PrintSelectCancelPrint,
PrintPauseChangeDone,
PrintPauseChangeMes
};


extern const struct WinType code WinGroup[Wincount];
extern const struct NumButtonType code NumButtonGroup[NumButtonCount];   
extern u8 CurentWin;


void WinDebug(u8 *String);
void WindowOn(u8 WinName);
void WindowOff(u8 WinName);
void WinGraph(struct WinType Win);
u8 GetWinClass(u8 WinName);


void SeletButtonPressEffect(u8 WinName,u16 x,u16 y);
void SingleSelectButtonCall(u8 WinName,u16 x,u16 y);
void SelectButtonCall(u8 WinName,u16 x,u16 y);
void WinExecuteOkCall(u8 WinName);
void WinExecuteCanCall(u8 WinName);


void SelectFacOkCall();
void SelectFacCanCall();
void SkipCall();
void AgainCall();

void PrintSelectCancelPrintOkCall();
void PrintSelectCancelPrintCanCall();
void ChangeDoneOkCall();
#endif