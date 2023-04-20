#ifndef __NUMLABEL_H
#define __NUMLABEL_H	 
#include "STC15Fxxxx.H"

#define NumLabelVarCount 73


struct FormatType
{
	u8 Left;
	u8 Right;
};


struct UnitType
{
	u8 Pre;  //1：前缀  0：后缀
	u8 Count; //个数
	u8 *p; //单位字符串指针
};



struct NumInfoType//字符变量信息结构
{  
	u8 Align;
	u8 TransFlag;//透明否   1：透明   2：不透明
	u16 x;
	u16 y;//位置
	u16 Width;//长度
	u16 Length;//高度
	u32 Color;//颜色
	u32 Bcolor;
	struct FormatType Format;//格式
	struct UnitType Unit;//单位
};	


struct NumLabelVarType
{
	u16 Addr;//变量地址
	u8 PageName;//变量所属页面
	struct NumInfoType VarInfo;//变量附加信息
	u8 DataLength;//变量数据长度
}; //变量






void NumLabelFlush(u8 PageName);
#endif