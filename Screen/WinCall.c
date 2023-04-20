#include "WinCall.h"
#include "Win.h"
const struct WinOkCall code WinOkCallGroup[WinOkCallCount]={
{Aoutolevel1SelectCalibrate,SkipCall},  
{SettingSelectFact,SelectFacOkCall},
///////////////////Print界面////////////////////////
{PrintSelectCancelPrint,PrintSelectCancelPrintOkCall},             
{PrintPauseChangeDone,ChangeDoneOkCall}
};



const struct WinCanCall code WinCanCallGroup[WinCanCallCount]={

{Aoutolevel1SelectCalibrate,AgainCall},  
{SettingSelectFact,SelectFacCanCall},
//////////////////////Print界面///////////////////
{PrintSelectCancelPrint,PrintSelectCancelPrintCanCall}
};





