#ifndef		__SCALER_H
#define		__SCALER_H
#include	"STC15Fxxxx.H"



#define ScalerCount 2
struct ScalerType //编辑弹窗类型
{	u16 Addr;
	u8 PageName;
	u16 x;//起点
	u16 y;
	u16 width;//长
	u16 length;//宽
	u32 Color;
	u32 Bcolor;
	u8 First;
};

extern struct ScalerType Scaler;
	

void ScalerFlush(u8 PageName);
#endif