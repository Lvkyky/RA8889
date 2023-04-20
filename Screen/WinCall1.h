#ifndef		__WINCALL1_H
#define		__WINCALL1_H
#include "STC15Fxxxx.H"

#define WinScanCallCount  23
struct WinScanCall //弹窗的回调函数
{
	u8  Name;//窗口名字	
	void (*FuncScan)(u16 x,u16 y,u8 WinName);
};


extern const struct WinScanCall code WinScanCallGroup[WinScanCallCount];
#endif