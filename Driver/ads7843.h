#ifndef	__ADS7843_H
#define	__ADS7843_H
#include	"STC15Fxxxx.H"

#define  DCLK  P04
#define  CS    P03
#define  DIN   P02 
#define  BUSY  P01 
#define  DOUT  P00
#define  INTT_0  P36 


void Ads7843_Init(void);
void Ads_start(void);
void Ads_w(u8 dat);
int Ads_r(void);
void Cord_read();
#endif