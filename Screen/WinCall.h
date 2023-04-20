#ifndef		__WINCALL_H
#define		__WINCALL_H
#include "STC15Fxxxx.H"

#define WinOkCallCount  27
#define WinCanCallCount  26


struct WinOkCall //弹窗的回调函数
{
	u8  Name;//窗口名字	
	void (*FuncOk)(void);
};

struct WinCanCall //弹窗的回调函数
{
	u8  Name;//窗口名字	
	void (*FuncCan)(void);
};



extern const struct WinOkCall code WinOkCallGroup[WinOkCallCount];
extern const struct WinCanCall code WinCanCallGroup[WinCanCallCount];
#endif