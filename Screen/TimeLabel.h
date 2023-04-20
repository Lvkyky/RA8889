#ifndef __TIMELABEL_H
#define __TIMELABEL_H	 
#include "STC15Fxxxx.H"

#define TimeCount 5

#define Trans 1
#define Untrans 0

struct TimeInfoType//字符变量信息结构
{  
	u8 TransFlag;//透明否   1：透明   2：不透明
	u16 x;
	u16 y;
	u8 Width;
	u8 Length;
	u32 Color;
	u32 Bcolor;
};	


struct TimeLabelVarType
{
	u16 Addr;
	u8 PageName;
	struct TimeInfoType VarInfo;
}; 




void TimeLabelFlush(u8 PageName);
#endif