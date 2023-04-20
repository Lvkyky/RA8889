#ifndef		__PAGE_H
#define		__PAGE_H
#include "STC15Fxxxx.H"

#define PageCount 27
struct PageType 
	{
		u16 Id;
		u8  Name;
		u8  PicIndex;
		u8  PicIndex1;
	};
	
enum Page{
PowerOn=0x00,Main,Version,Setting, Motor,Fansped,Preheat,Move,AoutoLeve1,AoutoLeve2,MainPreheat,Failment,
MainUdisk,
UdiskNext,UdiskBoth,UdiskLast,UdiskOne,
UdiskNextUp,UdiskBothUp,UdiskLastUp,UdiskOneUp,
PrintConfirm,
Print,
MainUdiskPreheat,
PrintPause,
Adjust
};//页面类型的枚举


extern const struct PageType code PageGroup[PageCount];//页面组
extern u16 Page_Id;
extern u8 Page_Name;

void PageShift(u8 PageName);
u8 PageIdtoPageName(u16 PageId);
void UpdatePageName();
#endif