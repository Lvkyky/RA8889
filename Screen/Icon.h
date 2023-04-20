#ifndef		__ICON_H
#define		__ICON_H
#include	"STC15Fxxxx.H"
#include	"Button.h"
typedef void (*IconFun)(void);
#define IconVarCount 2
struct IconButtonType
{
	u16 x;
	u16 y;
	u8 width;
	u8 length;
};


struct IconCheckType
{	u8 Count;	
	u16 VarAddress;//图标变量地址
	u8 PageName;//变量所属页面
	struct IconButtonType ButtonGroup[4];
	IconFun	FlushGroup[4];
	IconFun	ButtonCallGroup[4];
};


struct IconFileType
{
	u16 VarAddress;//图标变量地址
	u8 PageName;//变量所属页面
	IconFun Flush1;
	IconFun Flush2;
	IconFun Flush3;
};
extern const struct IconFileType code FileIconGroup[7];





void IconMaterialInit();
u8 IsPushIconButton(struct IconButtonType Button,u16 x,u16 y);
void IconPressEffect(u8 PageName,u16 x,u16 y);
void IconCall(u8 PageName,u16 x,u16 y);
void IconFlush(u8 PageName);
void FileIconFlush(u8 PageName);



void Icon1Button1Flush();
void Icon1Button2Flush();
void Icon1Button3Flush();
void Icon1Button4Flush();
void Icon1Button1Call();
void Icon1Button2Call();
void Icon1Button3Call();
void Icon1Button4Call();

void Icon2Button1Flush();
void Icon2Button2Flush();
void Icon2Button1Call();
void Icon2Button2Call();


void FileIcon1Flush1();
void FileIcon1Flush2();
void FileIcon1Flush3();
void FileIcon2Flush1();
void FileIcon2Flush2();
void FileIcon2Flush3();
void FileIcon3Flush1();
void FileIcon3Flush2();
void FileIcon3Flush3();
void FileIcon4Flush1();
void FileIcon4Flush2();
void FileIcon4Flush3();
void FileIcon5Flush1();
void FileIcon5Flush2();
void FileIcon5Flush3();
void FileIcon6Flush1();
void FileIcon6Flush2();
void FileIcon6Flush3();
void FileIcon7Flush1();
void FileIcon7Flush2();
void FileIcon7Flush3();
#endif