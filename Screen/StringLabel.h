#ifndef __STRIMGLABEL_H
#define __STRINGLABEL_H	 
#include "STC15Fxxxx.H"

#define StringLabelVarCount 9
#define Trans 1
#define Untrans 0

#define CenterAlign 0
#define LeftAlign 1

struct StringInfoType//字符变量信息结构
{  
	u8 Align;
	u8 TransFlag;//透明否   1：透明   0：不透明
	u16 x;
	u16 y;//位置
	u16 Width;//长度
	u16 Length;//高度
	u32 Color;//颜色
	u32 Bcolor;
};	


struct StringLabelVarType
{
	u16 Addr;//变量地址
	u8 PageName;//变量所属页面
	struct StringInfoType VarInfo;//变量附加信息
}; //变量



void StringLabelFlush(u8 PageName);
void StringInit();
void StringSingleInit(u8 *mem,u8 *p);
#endif