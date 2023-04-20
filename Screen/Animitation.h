#ifndef		__ANIMITATION_H
#define		__ANIMITATION_H
#include "STC15Fxxxx.H"

#define AnimitationCount 2
struct AnimitationType //±‡º≠µØ¥∞¿‡–Õ
{
	u8 PageName;
	u8 Bgin;
	u8  Circle;
	u8 End;
	u8 Intervel;
};



void AnimitationFlush(u8 PageName);
#endif