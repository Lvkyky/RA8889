
  /*************** RAIO Technology Inc. ***************
  * product		: RA8889
  * file		: RA8889.c
  * author		: Henry 
  * version		: ver 0.0 
  * date		: 2020/12/23 
  RAIO Technology Inc. copyright all rights reserved.
  ****************************************************/	


#include "delay.h"

#include "UserDef.h"
#include "spi.h"
#include "RA8889.h"
#include <gpio.h>
#include <USART.h>

//----------------------------//

//==============================================================================

/******************************************************************************
RA8889 Subroutine		  													 
******************************************************************************/




//==============================================================================


void RA8889_Initial(void)
{
	
PrintString1("spi初始化开始\r\n");	
delay_ms(200);
delay_ms(200);
SPI3_Init();
PrintString1("spi初始化完成\r\n");	
delay_ms(200);
delay_ms(200);

	
PrintString1("硬件复位开始\r\n");	
delay_ms(200);
delay_ms(200);

//------------------------------------
RA8889_HW_Reset();
Check_IC_ready();
//	System_Check_Temp();  

PrintString1("硬件复位完成\r\n");
delay_ms(200);
delay_ms(200);

	
	
PrintString1("软件复位开始\r\n");	
delay_ms(200);
delay_ms(200);
RA8889_SW_Reset();
Check_IC_ready();
PrintString1("软件复位完成\r\n");
delay_ms(200);
delay_ms(200);


//------------------------------------
	RA8889_PLL(DRAM_FREQ, CORE_FREQ, SCAN_FREQ);

//------------------------------------	
	RA8889_SDRAM_initial();// set the SDRAM parameter.  
//------------------------------------

//**[01h]**//
	TFT_24bit();
//	TFT_18bit();
//	TFT_16bit();
//	Without_TFT();

//**[01h]**//
#if defined (MCU_8bit_ColorDepth_8bpp) || defined (MCU_8bit_ColorDepth_16bpp) || defined (MCU_8bit_ColorDepth_24bpp)	
	Host_Bus_8bit();
#endif

#if defined (MCU_16bit_ColorDepth_16bpp) || defined (MCU_16bit_ColorDepth_24bpp_Mode_1) || defined (MCU_16bit_ColorDepth_24bpp_Mode_2)	
	Host_Bus_16bit();
#endif


//------------------------------------
//**[02h]**//
	#ifdef MCU_8bit_ColorDepth_8bpp	
	Data_Format_8b_8bpp();
	#endif
	#ifdef MCU_8bit_ColorDepth_16bpp	
	Data_Format_8b_16bpp();
	#endif
	#ifdef MCU_8bit_ColorDepth_24bpp	
	Data_Format_8b_24bpp();
	#endif

	#ifdef MCU_16bit_ColorDepth_16bpp	
	Data_Format_16b_16bpp();
	#endif
	#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
	Data_Format_16b_24bpp_mode1();
	#endif
	#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
	Data_Format_16b_24bpp_mode2();
	#endif

	
	MemWrite_Left_Right_Top_Down();//(Default) Memory Write: Left to Right, Top to Down.

//------------------------------------
//**[03h]**//

	Graphic_Mode();
//	Text_Mode();

	Memory_Select_SDRAM();

//------------------------------------
//** Set color depth, define in [UserDef.h] **//

	#ifdef MCU_8bit_ColorDepth_8bpp	
		Select_Main_Window_8bpp();		//[10h] Set main window color depth
		Memory_8bpp_Mode();				//[5Eh] Set active memory color depth

		Select_PIP1_Window_8bpp();		//[11h] PIP 1 Window Color Depth
		Select_PIP2_Window_8bpp();		//[11h] PIP 2 Window Color Depth

		BTE_S0_Color_8bpp();			//[92h] Source_0 Color Depth
		BTE_S1_Color_8bpp();			//[92h] Source_1 Color Depth
		BTE_Destination_Color_8bpp();	//[92h] Destination Color Depth	
		
		IDEC_Destination_Color_8bpp();//
	#endif

	#if defined (MCU_8bit_ColorDepth_16bpp) || defined (MCU_16bit_ColorDepth_16bpp)
		Select_Main_Window_16bpp();		//[10h]Set main window color depth
		Memory_16bpp_Mode();			//[5Eh]Set active memory color depth

		Select_PIP1_Window_16bpp();		//[11h] PIP 1 Window Color Depth
		Select_PIP2_Window_16bpp();		//[11h] PIP 2 Window Color Depth

		BTE_S0_Color_16bpp();			//[92h] Source_0 Color Depth
		BTE_S1_Color_16bpp();			//[92h] Source_1 Color Depth
		BTE_Destination_Color_16bpp();	//[92h] Destination Color Depth	 
		
		IDEC_Destination_Color_16bpp();//
	#endif

	#if defined (MCU_8bit_ColorDepth_24bpp) || defined (MCU_16bit_ColorDepth_24bpp_Mode_1) || defined (MCU_16bit_ColorDepth_24bpp_Mode_2)	
		Select_Main_Window_24bpp();		//[10h]Set main window color depth
		Memory_24bpp_Mode();			//[5Eh]Set active memory color depth

		Select_PIP1_Window_24bpp();		//[11h] PIP 1 Window Color Depth
		Select_PIP2_Window_24bpp();		//[11h] PIP 2 Window Color Depth

		BTE_S0_Color_24bpp();			//[92h] Source_0 Color Depth
		BTE_S1_Color_24bpp();			//[92h] Source_1 Color Depth
		BTE_Destination_Color_24bpp();	//[92h] Destination Color Depth	   
		
		IDEC_Destination_Color_24bpp();//
	#endif

//------------------------------------
//**[12h]~[1Fh]]**//
	Set_LCD_Panel(); // define in [UserDef.h]

//------------------------------------
//**[20h][21h][22h][23h]**//
	Main_Image_Start_Address(0);
//**[24h][25h]**//					
	Main_Image_Width(main_image_width);							
//**[26h][27h][28h][29h]**//
	Main_Window_Start_XY(0,0);	
//**[50h][51h][52h][53h]**//
	Canvas_Image_Start_address(0);
//**[54h][55h]**//
	Canvas_image_width(canvas_image_width);
//**[56h][57h][58h][59h]**//
	Active_Window_XY(0,0);
//**[5Ah][5Bh][5Ch][5Dh]**//
	Active_Window_WH(LCD_width,LCD_legth);

//------------------------------------
//**[5E]**//
	Memory_XY_Mode();
//	Memory_Linear_Mode();


//------------------------------------
	Set_Serial_Flash_IF();

//------------------------------------
//**[5Fh][60h][61h][62h]**//
	Goto_Pixel_XY(0,0);	   

//------------------------------------  

	//---------------------//
	Display_ON();
	//---------------------//
	Color_Bar_ON();
	delay_seconds(1);
	Color_Bar_OFF();

}


//==============================================================================
//==============================================================================

/******************************************************************************/
/*Sub-Program area		  													  */
/******************************************************************************/

//==============================================================================


#define GPIO_SetBits(GPIOE, GPIO_Pin_1 )  P40=1;
#define GPIO_ResetBits(GPIOE, GPIO_Pin_1)  P40=0;
void RA8889_HW_Reset(void)
{

	/**************************************************************************************************/
	GPIO_InitTypeDef  IOP40;
  IOP40.	Pin=GPIO_Pin_0;
  IOP40.	Mode=GPIO_OUT_PP;                    //设置p30为复用推挽输出
	GPIO_Inilize(GPIO_P4,&IOP40);	
	/************************************************************************************************/
	
	
	GPIO_SetBits(GPIOE, GPIO_Pin_1 );
	delay_ms(1);

	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	delay_ms(1); // XnRST have to keep low at least 256 OSC clocks. 1
	//delay_seconds(2);

	GPIO_SetBits(GPIOE, GPIO_Pin_1 );	
	delay_ms(1);
	
}

//==============================================================================

void Check_IC_ready(void)
{
/*	[Status Register] bit1
Operation mode status
0: Normal operation state
1: Inhibit operation state
Inhibit operation state means internal reset event keep running or
initial display still running or chip enter power saving state.		
*/	
	unsigned short i;
	// Please according to your usage to modify delay(check) time. // ???????????????
	for(i=0;i<1000;i++)
	{
		if( (LCD_StatusRead()&0x02)==0x00 ){break;}
	}

#ifdef Check_While_Busy		
	while(LCD_StatusRead() & 0x02);
#endif
}


void RA8889_SW_Reset(void)
{/*
Software Reset
0: Normal operation.
1: Software Reset.
Software Reset only reset internal state machine. Configuration
Registers value won be reset. So all read-only flag in the
register will return to its initial value. User should have proper
action to make sure flag is in desired state.
Note: The bit will auto clear after reset.
*/	
	unsigned short i;
	unsigned char temp;

	LCD_CmdWrite(0x00);
	temp = LCD_DataRead();
	temp |= 0x01;
	LCD_DataWrite(temp);
	delay_us(100);			// it must wait 100us after Software_Reset.

	// Please according to your usage to modify delay(check) time. // ???????????????
//	for(i=0;i<100;i++)
//	{
//		if( (LCD_RegisterRead(0x00)&0x01)==0x00 )
//		{break;}
//	}
	
#ifdef Check_While_Busy
	while( LCD_RegisterRead(0x00)&0x01 );
#endif
}




void RA8889_PLL(unsigned short DRAM_clock, unsigned short CORE_clock, unsigned short SCAN_clock) 
{
/*
[A]
DRAM_clock maximum 166 MHz
CORE_clock maximum 133 MHz
SCAN_clock maximum 100 MHz

[B]
(1) 10MHz <= OSC_FREQ <= 15MHz
(2) 10MHz <= (OSC_FREQ/PLLDIVM) <= 40MHz
(3) 250MHz <= [OSC_FREQ/(PLLDIVM+1)]x(PLLDIVN+1) <= 500MHz
(4) In addition, please pay special attention to:
	[DRAM_clock] >= [CORE_clock],
	[CORE_clock] >= 2x[SCAN_clock].
PLLDIVM:0
PLLDIVN:1~63
PLLDIVK:CPLL & MPLL = 1/2/4/8.SPLL = 1/2/4/8/16/32/64/128.
ex:
 OSC_FREQ = 10MHz
 Set X_DIVK=2
 Set X_DIVM=0
 => (X_DIVN+1)=(XPLLx4)/10
*/


unsigned short x_Divide,PLLC1,PLLC2;
unsigned short pll_m_lo, pll_m_hi;
unsigned char temp;

		// Set DRAM clock
		if((DRAM_clock>=125)&&(DRAM_clock<=166))
		{
			LCD_RegisterWrite(0x07,0x02);				//PLL Divided by 2
			LCD_RegisterWrite(0x08,(DRAM_clock*2/OSC_FREQ)-1);
		}
		else if((DRAM_clock>=63)&&(DRAM_clock<=124))
		{
			LCD_RegisterWrite(0x07,0x04);				//PLL Divided by 4
			LCD_RegisterWrite(0x08,(DRAM_clock*4/OSC_FREQ)-1);
		}
		else if((DRAM_clock>=32)&&(DRAM_clock<=62))
		{								  	
			LCD_RegisterWrite(0x07,0x06);				//PLL Divided by 8
			LCD_RegisterWrite(0x08,(DRAM_clock*8/OSC_FREQ)-1);
		}
		else //if(DRAM_clock<32)
		{
			LCD_RegisterWrite(0x07,0x06);				//PLL Divided by 8
			LCD_RegisterWrite(0x08,(32*8/OSC_FREQ)-1);	//
		}


		// Set Core clock
		if((CORE_clock>=125)&&(CORE_clock<=133))
		{
			LCD_RegisterWrite(0x09,0x02);				//PLL Divided by 2
			LCD_RegisterWrite(0x0A,(CORE_clock*2/OSC_FREQ)-1);
		}
		else if((CORE_clock>=63)&&(CORE_clock<=124))					
		{
			LCD_RegisterWrite(0x09,0x04);				//PLL Divided by 4
			LCD_RegisterWrite(0x0A,(CORE_clock*4/OSC_FREQ)-1);
		}
		else if((CORE_clock>=32)&&(CORE_clock<=62))
		{								  	
			LCD_RegisterWrite(0x09,0x06);				//PLL Divided by 8
			LCD_RegisterWrite(0x0A,(CORE_clock*8/OSC_FREQ)-1);
		}
		else //if(CORE_clock<32)
		{
			LCD_RegisterWrite(0x09,0x06);				//PLL Divided by 8
			LCD_RegisterWrite(0x0A,(32*8/OSC_FREQ)-1);	//	
		}
		

		// Set pixel clock
  		if((SCAN_clock>=63)&&(SCAN_clock<=100))
		{
			LCD_RegisterWrite(0x05,0x04);				//PLL Divided by 4
			LCD_RegisterWrite(0x06,(SCAN_clock*4/OSC_FREQ)-1);
		}
		else if((SCAN_clock>=32)&&(SCAN_clock<=62))
		{								  	
			LCD_RegisterWrite(0x05,0x06);				//PLL Divided by 8
			LCD_RegisterWrite(0x06,(SCAN_clock*8/OSC_FREQ)-1);
		}
		else if((SCAN_clock>=16)&&(SCAN_clock<=31))
		{								  	
			LCD_RegisterWrite(0x05,0x16);				//PLL Divided by 16
			LCD_RegisterWrite(0x06,(SCAN_clock*16/OSC_FREQ)-1);
		}
		else if((SCAN_clock>=8)&&(SCAN_clock<=15))
		{
			LCD_RegisterWrite(0x05,0x26);				//PLL Divided by 32
			LCD_RegisterWrite(0x06,(SCAN_clock*32/OSC_FREQ)-1);
		}
		else if((SCAN_clock>0)&&(SCAN_clock<=7))
		{
			LCD_RegisterWrite(0x05,0x36);				//PLL Divided by 64
			LCD_RegisterWrite(0x06,(SCAN_clock*64/OSC_FREQ)-1);
		}	
		else // if out of range, set 32MHz for debug. 
		{
			LCD_RegisterWrite(0x05,0x06);				
			LCD_RegisterWrite(0x06,(32*8/OSC_FREQ)-1);
		}

		Enable_PLL();
		delay_ms(100);
}




void RA8889_SDRAM_initial(void)
{
unsigned char	CAS_Latency;
unsigned short	Auto_Refresh;
//
//Auto_Refresh=(64*DRAM_FREQ*1000)/(8192);


	CAS_Latency=3;
	Auto_Refresh=(64*DRAM_FREQ*1000)/(4096);
	Auto_Refresh=Auto_Refresh-2;//????refresh,???????????// Start [refresh] in advance to avoid just reaching the limits.
	
	LCD_RegisterWrite(0xe0,0x29);      
	LCD_RegisterWrite(0xe1,CAS_Latency);      //CAS:2=0x02,CAS:3=0x03
	LCD_RegisterWrite(0xe2,Auto_Refresh);
	LCD_RegisterWrite(0xe3,Auto_Refresh>>8);
	LCD_RegisterWrite(0xe4,0x01);

	Check_SDRAM_Ready();

}




void TFT_24bit(void)//
{
/*  TFT Panel I/F Output pin Setting
00b: 24-bits TFT output.
01b: 18-bits TFT output.
10b: 16-bits TFT output.
11b: w/o TFT output.
Other unused TFT output pins are set as GPIO or Key function.*/
	unsigned char temp;
	LCD_CmdWrite(0x01);
	temp = LCD_DataRead();
	temp &= cClrb4;
    temp &= cClrb3;
	LCD_DataWrite(temp);    
}




void Host_Bus_8bit(void)
{
/*  Parallel Host Data Bus Width Selection
    0: 8-bit Parallel Host Data Bus.
    1: 16-bit Parallel Host Data Bus.*/
	unsigned char temp;
	LCD_CmdWrite(0x01);
	temp = LCD_DataRead();
	temp &= cClrb0;
	LCD_DataWrite(temp);
}



void Data_Format_8b_24bpp(void)
{
/* MPU read/write data format when access memory data port.
0xb: Direct write for 
	all 8 bits MPU I/F,
	16 bits MPU I/F with 8bpp data mode 2, 
	16 bits MPU I/F with 16bpp, 
	16 bits MPU I/F with 24bpp data mode 1, 
	and serial host interface.				 				*/
	unsigned char temp;
	LCD_CmdWrite(0x02);
	temp = LCD_DataRead();
	temp &= cClrb7;
	LCD_DataWrite(temp);
}




void MemWrite_Left_Right_Top_Down(void)
{
/* Host Write Memory Direction (Only for Graphic Mode)
00b: Left .. Right then Top ..Bottom.
Ignored if canvas in linear addressing mode.		*/
	unsigned char temp;
	LCD_CmdWrite(0x02);
	temp = LCD_DataRead();
	temp &= cClrb2;
	temp &= cClrb1;
	LCD_DataWrite(temp);
}




void Graphic_Mode(void)
{
	unsigned char temp;
	LCD_CmdWrite(0x03);
	temp = LCD_DataRead();
    temp &= cClrb2;
	LCD_DataWrite(temp);
}


void Memory_Select_SDRAM(void)
{
	unsigned char temp;

	LCD_CmdWrite(0x03);
	temp = LCD_DataRead();
    temp &= cClrb1;
    temp &= cClrb0;
	LCD_DataWrite(temp);
}


void Select_Main_Window_24bpp(void)
{
/*
Main Window Color Depth Setting
00b: 8-bpp generic TFT, i.e. 256 colors.
01b: 16-bpp generic TFT, i.e. 65K colors.
1xb: 24-bpp generic TFT, i.e. 1.67M colors.
*/
	unsigned char temp;
	LCD_CmdWrite(0x10);
	temp = LCD_DataRead();
    temp |= cSetb3;
	LCD_DataWrite(temp);
}



void Memory_24bpp_Mode(void)	
{
/*
Canvas image color depth & memory R/W data width
In Block Mode:
00: 8bpp
01: 16bpp
1x: 24bpp
In Linear Mode:
x0: 8-bits memory data read/write.
x1: 16-bits memory data read/write
*/
	unsigned char temp;

	LCD_CmdWrite(0x5E);
	temp = LCD_DataRead();
	temp |= cSetb1;
//	temp |= cSetb0;
	LCD_DataWrite(temp);
}



void Select_PIP1_Window_24bpp(void)
{
/*
PIP 1 Window Color Depth Setting
00b: 8-bpp generic TFT, i.e. 256 colors.
01b: 16-bpp generic TFT, i.e. 65K colors.
1xb: 24-bpp generic TFT, i.e. 1.67M colors.
*/
	unsigned char temp;
	LCD_CmdWrite(0x11);
	temp = LCD_DataRead();
    temp |= cSetb3;
//    temp &= cClrb2;
	LCD_DataWrite(temp);
}




void Select_PIP2_Window_24bpp(void)
{
/*
PIP 2 Window Color Depth Setting
00b: 8-bpp generic TFT, i.e. 256 colors.
01b: 16-bpp generic TFT, i.e. 65K colors.
1xb: 24-bpp generic TFT, i.e. 1.67M colors.
*/
	unsigned char temp;
	LCD_CmdWrite(0x11);
	temp = LCD_DataRead();
    temp |= cSetb1;
//    temp &= cClrb0;
	LCD_DataWrite(temp);
}



void BTE_S0_Color_24bpp(void)
{	
/*
S0 Color Depth
00 : 256 Color
01 : 64k Color
1x : 16M Color
*/	
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
	temp |= cSetb6 ;
	//temp |= cSetb5 ;
	LCD_DataWrite(temp);
}




void BTE_S1_Color_24bpp(void)
{	
/*
S1 Color Depth
000 : 256 Color
001 : 64k Color
010 : 16M Color
011 : Constant Color
100 : 8 bit pixel alpha blending
101 : 16 bit pixel alpha blending
110 : 32bit ARGB mode
*/	
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
	temp &= cClrb4 ;
	temp |= cSetb3 ;
	temp &= cClrb2 ;
	LCD_DataWrite(temp);
}



void BTE_Destination_Color_24bpp(void)
{	
/*
Destination Color Depth
00 : 256 Color
10 : 64k Color
1x : 16M Color
*/	
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp |= cSetb1 ;
		//temp |= cSetb0 ;
	  LCD_DataWrite(temp);
}




void IDEC_Destination_Color_24bpp(void)
{
/*[REG PAGE 1], REG[B6h], 
[bit2-1] 
IDEC destination Color depth:
00: 8bit
01: 16 bit
10: 24bit
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0xF8;			//if bit0=1, IDEC will start .
	temp |= 0x04;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}




void Set_LCD_Panel(void)
{
	    #ifdef EJ080NA_04B	//##INNOLUX_1024x768_EJ080NA-04B
		//**[03h]**//
		//	LVDS_Format1();//(VESA format)//only for RA8877
		//	LVDS_Format2();//(JEIDA format) //only for RA8877
		//**[10h]**//
		Select_LCD_Sync_Mode();	// Enable XVSYNC, XHSYNC, XDE.
		//	Select_LCD_DE_Mode();	// XVSYNC & XHSYNC in idle state.
		//**[12h]**//
		//	PCLK_Rising();
		PCLK_Falling();
		VSCAN_T_to_B();
		//VSCAN_B_to_T();
		HSCAN_L_to_R();
		PDATA_Set_RGB();
		//	PDATA_Set_RBG();
		//	PDATA_Set_GRB();
		//	PDATA_Set_GBR();
		//	PDATA_Set_BRG();
		//	PDATA_Set_BGR();
		//	PDATA_Set_Gray();
		//	PDATA_IDLE_STATE();

		//**[13h]**//
			HSYNC_Low_Active();
		//	HSYNC_High_Active();

			VSYNC_Low_Active();
		//	VSYNC_High_Active();
			
		//	DE_Low_Active();
			DE_High_Active();
	
			//**[14h][15h][1Ah][1Bh]**//
			LCD_HorizontalWidth_VerticalHeight(1024,600);// INNOLUX 1024x768?
		
		/*	[16h][17h] : Figure 19-3 [HND]	Non Display or Back porch (pixels)		= (HNDR + 1) * 8 + HNDFTR  
			[18h] :		 Figure 19-3 [HST]	Start Position or Front porch (pixels)	= (HSTR + 1)x8
			[19h] :		 Figure 19-3 [HPW]	Pulse Width(pixels)						= (HPW + 1)x8
		*/
			LCD_Horizontal_Non_Display(48);	//Blank=90~376, TYP.=320?
			LCD_HSYNC_Start_Position(48);		//Start Position or Front-Porch
			LCD_HSYNC_Pulse_Width(112);			//Pulse Width 

		/*	[1Ch][1Dh] : Figure 19-3 [VND]	Non-Display Period(Line)	= (VNDR + 1)
			[1Eh] :		 Figure 19-3 [VST]	Start Position(Line)		= (VSTR + 1)
			[1Fh] :		 Figure 19-3 [VPW]	Pulse Width(Line)			= (VPWR + 1)
		*/
			LCD_Vertical_Non_Display(8);		//Non Display or Back-Porch  //Blank=10~77, TYP.=38?
			LCD_VSYNC_Start_Position(8);		//Start Position or Front-Porch
			LCD_VSYNC_Pulse_Width(15);			//Pulse Width
	#endif


	#ifdef AT043TN25 

		//**[10h]**//
		//	Select_LCD_Sync_Mode();	// Enable XVSYNC, XHSYNC, XDE.
			Select_LCD_DE_Mode();	// XVSYNC & XHSYNC in idle state.
		
		   //PCLK_Rising();							
			PCLK_Falling();
			//VSCAN_T_to_B();
			HSCAN_R_to_L();
			VSCAN_B_to_T();
			PDATA_Set_RGB();
			//**[13h]**//
			HSYNC_Low_Active();
			VSYNC_Low_Active();
			DE_High_Active();
			//	DE_Low_Active();
			//------------------------------------
			//**[14h][15h][1Ah][1Bh]**//
			LCD_HorizontalWidth_VerticalHeight(480,272); //LCD Resolution 480x272。
			//**[16h][17h]**//
			LCD_Horizontal_Non_Display(48);//480x272，HSYNC Back Porch=38。
			//**[18h]**//
			LCD_HSYNC_Start_Position(48);//480x272 HSYNC Front Porch = 20。
			//**[19h]**//
			LCD_HSYNC_Pulse_Width(112);//480x272，HSYNC Pulse Width=5~30,set 20。
			//**[1Ch][1Dh]**//
			LCD_Vertical_Non_Display(8);//480x272，VSYNC Back Porch =4。
			//**[1Eh]**//
			LCD_VSYNC_Start_Position(15);//480x272，VSYNC Front Porch =15。
			//**[1Fh]**//
			LCD_VSYNC_Pulse_Width(8);//480x272，VSYNC Pulse Width =3。
	  #endif

}



void Main_Image_Start_Address(unsigned long Addr)	
{
/*
[20h] Main Image Start Address[7:2]
[21h] Main Image Start Address[15:8]
[22h] Main Image Start Address [23:16]
[23h] Main Image Start Address [31:24]
*/
	LCD_CmdWrite(0x20);	LCD_DataWrite(Addr);
	LCD_CmdWrite(0x21);	LCD_DataWrite(Addr>>8);
	LCD_CmdWrite(0x22);	LCD_DataWrite(Addr>>16);
	LCD_CmdWrite(0x23);	LCD_DataWrite(Addr>>24);
}



void Main_Image_Width(unsigned short WX)	
{
/*
[24h] Main Image Width [7:0]
[25h] Main Image Width [12:8]
Unit: Pixel.
It must be divisible by 4. MIW Bit [1:0] tie to ??internally.
The value is physical pixel number. Maximum value is 8188 pixels
*/
	LCD_CmdWrite(0x24);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x25);	LCD_DataWrite(WX>>8);
}


void Main_Window_Start_XY(unsigned short WX,unsigned short HY)	
{
/*
[26h] Main Window Upper-Left corner X-coordinate [7:0]
[27h] Main Window Upper-Left corner X-coordinate [12:8]
Reference Main Image coordinate.
Unit: Pixel
It must be divisible by 4. MWULX Bit [1:0] tie to ??internally.
X-axis coordinate plus Horizontal display width cannot large than 8188.

[28h] Main Window Upper-Left corner Y-coordinate [7:0]
[29h] Main Window Upper-Left corner Y-coordinate [12:8]
Reference Main Image coordinate.
Unit: Pixel
Range is between 0 and 8191.
*/
	LCD_CmdWrite(0x26);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x27);	LCD_DataWrite(WX>>8);
	LCD_CmdWrite(0x28);	LCD_DataWrite(HY);
	LCD_CmdWrite(0x29);	LCD_DataWrite(HY>>8);
}


void Canvas_Image_Start_address(unsigned long Addr)	
{
/*
[50h] Start address of Canvas [7:0]
[51h] Start address of Canvas [15:8]
[52h] Start address of Canvas [23:16]
[53h] Start address of Canvas [31:24]
*/
	LCD_CmdWrite(0x50);	LCD_DataWrite(Addr);
	LCD_CmdWrite(0x51);	LCD_DataWrite(Addr>>8);
	LCD_CmdWrite(0x52);	LCD_DataWrite(Addr>>16);
	LCD_CmdWrite(0x53);	LCD_DataWrite(Addr>>24);
}



void Canvas_image_width(unsigned short WX)	
{
/*
[54h] Canvas image width [7:2]
[55h] Canvas image width [12:8]
*/
	LCD_CmdWrite(0x54);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x55);	LCD_DataWrite(WX>>8);
}



void Active_Window_XY(unsigned short WX,unsigned short HY)	
{
/*
[56h] Active Window Upper-Left corner X-coordinate [7:0]
[57h] Active Window Upper-Left corner X-coordinate [12:8]
[58h] Active Window Upper-Left corner Y-coordinate [7:0]
[59h] Active Window Upper-Left corner Y-coordinate [12:8]
*/
	LCD_CmdWrite(0x56);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x57);	LCD_DataWrite(WX>>8);
	LCD_CmdWrite(0x58);	LCD_DataWrite(HY);
	LCD_CmdWrite(0x59);	LCD_DataWrite(HY>>8);

}


void Active_Window_WH(unsigned short WX,unsigned short HY)	
{
/*
[5Ah] Width of Active Window [7:0]
[5Bh] Width of Active Window [12:8]
[5Ch] Height of Active Window [7:0]
[5Dh] Height of Active Window [12:8]
*/
	LCD_CmdWrite(0x5A);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x5B);	LCD_DataWrite(WX>>8);
	LCD_CmdWrite(0x5C);	LCD_DataWrite(HY);
	LCD_CmdWrite(0x5D);	LCD_DataWrite(HY>>8);
}




void Goto_Pixel_XY(unsigned short WX,unsigned short HY)	
{
/*
Set Graphic Read/Write position

REG[5Eh] bit3, Select to read back Graphic Read/Write position.
When DPRAM Linear mode:Graphic Read/Write Position [31:24][23:16][15:8][7:0]
When DPRAM Active window mode:Graphic Read/Write 
Horizontal Position [12:8][7:0], 
Vertical Position [12:8][7:0].
Reference Canvas image coordinate. Unit: Pixel
*/
	LCD_CmdWrite(0x5F);
	LCD_DataWrite(WX);
	LCD_CmdWrite(0x60);
	LCD_DataWrite(WX>>8);
	LCD_CmdWrite(0x61);
	LCD_DataWrite(HY);
	LCD_CmdWrite(0x62);
	LCD_DataWrite(HY>>8);
}



unsigned char LCD_RegisterRead(unsigned char Cmd)
{
	unsigned char temp;
//	Check_2D_Busy();
	LCD_CmdWrite(Cmd);
	temp=LCD_DataRead();

	return temp;
}


void LCD_RegisterWrite(unsigned char Cmd,unsigned char Data)
{
	Check_2D_Busy();
//delay_us(1);
	LCD_CmdWrite(Cmd);
	LCD_DataWrite(Data);
}  



void Memory_XY_Mode(void)	
{
/*
Canvas addressing mode
0: Block mode (X-Y coordinate addressing)
1: linear mode
*/
	unsigned char temp;

	LCD_CmdWrite(0x5E);
	temp = LCD_DataRead();
	temp &= cClrb2;
	LCD_DataWrite(temp);
}



void Set_Serial_Flash_IF(void)
{

//(*) Using Serial Flash
	#ifdef MX25L25635E
		Enable_SFlash_SPI();
	#endif
	#ifdef W25Q256FV
		Enable_SFlash_SPI();
	#endif
//(*) Using GT_ROM
	#ifdef GT21L16T1W
		GTFont_Select_GT21L16T1W();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT30L16U2W
		GTFont_Select_GT30L16U2W();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT30L24T3Y
		GTFont_Select_GT30L24T3Y();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT30L24M1Z	
		GTFont_Select_GT30L24M1Z();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT30L32S4W
		GTFont_Select_GT30L32S4W();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT20L24F6Y
		GTFont_Select_GT20L24F6Y();
		Enable_SFlash_SPI();
	#endif
	#ifdef GT21L24S1W
		GTFont_Select_GT21L24S1W();
		Enable_SFlash_SPI();
	#endif

//(*) 
	Select_SFI_24bit_Address();
//	Select_SFI_32bit_Address();
	
//(*)
	Select_standard_SPI_Mode0_or_Mode3();
	//Select_RA8875_SPI_Mode0_and_Mode3();
	
//(*)
	Select_SFI_Single_Mode_Dummy_0T_03h();
//	Select_SFI_Single_Mode_Dummy_8T_0Bh();
//	Select_SFI_Single_Mode_Dummy_16T_1Bh();
//	Select_SFI_Dual_Mode_Dummy_8T_3Bh();
//	Select_SFI_Dual_Mode_Dummy_4T_BBh();
//	Select_SFI_Quad_Mode_Dummy_8T_6Bh();
//	Select_SFI_Quad_Mode_Dummy_4T_EBh();



//(*)

	Set_CPOL();
	Set_CPHA();

	Reset_CPOL();
	Reset_CPHA();



//(*) clock speed
	SPI_Clock_Period(3);

/******************************/

}



void Display_ON(void)
{
/*	
Display ON/OFF
0b: Display Off.
1b: Display On.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp |= cSetb6;
	LCD_DataWrite(temp);
}



void Color_Bar_ON(void)
{
/*	
Display Test Color Bar
0b: Disable.
1b: Enable.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp |= cSetb5;
	LCD_DataWrite(temp);
}



void Color_Bar_OFF(void)
{
/*	
Display Test Color Bar
0b: Disable.
1b: Enable.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp &= cClrb5;
	LCD_DataWrite(temp);
}



void Enable_PLL(void)
{
/* 1: PLL enable; cannot change PLL parameter.*/
	unsigned char temp;
	unsigned short i;

	LCD_CmdWrite(0x01);
	temp = LCD_DataRead();
	temp |= cSetb7;
	LCD_DataWrite(temp);

	delay_us(100);// PLL lock time = 1024 T OSC clocks, if OSC=10MHz, PLL lock time = 100 us.  

	/*check PLL was ready ( Please according to your usage to modify. // 請依據您的使用情況修改)	 */
	for(i=0;i<1000;i++)
	{
		LCD_CmdWrite(0x01);
		temp=LCD_DataRead();
		if( (temp&0x80)==0x80 ){break;}
	}

#ifdef Check_While_Busy
	while((LCD_RegisterRead(0x01)&0x80)!=0x80);//check PLL was ready.
#endif
}



void Check_SDRAM_Ready(void)
{
/*	[Status Register] bit2
SDRAM ready for access
0: SDRAM is not ready for access
1: SDRAM is ready for access		
*/	
	unsigned short i;
	// Please according to your usage to modify delay(check) time. // 請依據您的使用情況修改執行時間
	for(i=0;i<1000;i++)
	{
		if( (LCD_StatusRead()&0x04)==0x04 ){break;}
	}

#ifdef Check_While_Busy	
	while( (LCD_StatusRead()&0x04) == 0x00 );
#endif
}



void REG_Switch_to_REG1(void)//
{
/*
REG[46h] [bit0] Page switch, and SPIM bus switch.
0: page 0, SPIM bus 0.
1: page 1, SPIM bus 1.
*/
	unsigned char temp;
	LCD_CmdWrite(0x46);
	temp=LCD_DataRead();
	temp |= cSetb0;
	LCD_DataWrite(temp);

	delay_us(1);		//for test
}



void REG_Switch_to_REG0(void)//(default)
{
/*
REG[46h] [bit0] Page switch, and SPIM bus switch.
0: page 0, SPIM bus 0.
1: page 1, SPIM bus 1.
*/
	unsigned char temp;
	LCD_CmdWrite(0x46);
	temp=LCD_DataRead();
	temp &= cClrb0;
	LCD_DataWrite(temp);

	delay_us(1);		//for test
}



void Check_2D_Busy(void)
{
/*	[Status Register] bit3
Core task is busy
Following task is running:
BTE, Geometry engine, Serial flash DMA, Text write or Graphic write
0: task is done or idle.
1: task is busy.													
*/
	unsigned short i,temp;
	// Please according to your usage to modify delay(check) time. // 請依據您的使用情況修改執行時間


#ifdef Check_While_Busy

	//case1: using status register 	
	do{
		temp=LCD_StatusRead();
	}while(temp&0x08);


#else
	for(i=0;i<1000;i++)
	{
		if( (LCD_StatusRead()&0x08)==0x00 ){break;}
	}
#endif
}



void Enable_SFlash_SPI(void)
{
/*	Serial Flash or SPI Interface Enable/Disable
		0: Disable (GPIO function)
		1: Enable (SPI master function)
		When SDR SDRAM 32bits bus function enable, this bit is ignored
		& Serial flash pins become SDR SDRAM bus function.*/
	unsigned char temp;
	LCD_CmdWrite(0x01);
	temp = LCD_DataRead();
	temp |= cSetb1;
	LCD_DataWrite(temp);     
}



void GTFont_Select_GT30L24T3Y(void)
{
/*
GT Serial Font ROM Select
000b: GT21L16T1W
001b: GT30L16U2W
010b: GT30L24T3Y
011b: GT30L24M1Z
100b: GT30L32S4W
101b: GT20L24F6Y
110b: GT21L24S1W
*/
	unsigned char temp;
	LCD_CmdWrite(0xCE);
	temp = LCD_DataRead();
    temp &= cClrb7;
    temp |= cSetb6;
    temp &= cClrb5;
	LCD_DataWrite(temp);
}


void IDEC_Select_SFI_24bit_Address(void)
{
/*[REG PAGE 1],[B7h] [bit5]
IDEC Serial Flash/ROM Address Mode
0: 24 bits address mode
1: 32 bits address mode
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp &= cClrb5;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void Select_standard_SPI_Mode0_or_Mode3(void)
{
/*[bit4]
RA8875 compatible mode
0: standard SPI mode 0 or mode 3 timing
1: Follow RA8875 mode 0 & mode 3 timing
*/
	unsigned char temp;
	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp &= cClrb4;
	LCD_DataWrite(temp);
}



void Select_SFI_24bit_Address(void)
{
/*[bit5]
Serial Flash/ROM Address Mode
0: 24 bits address mode
1: 32 bits address mode
*/
	unsigned char temp;
	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp &= cClrb5;
	LCD_DataWrite(temp);
}



void Select_SFI_Single_Mode_Dummy_0T_03h(void)
{
/*
(1) [B6h]bit7-6=0x00
(2) [B7h]bit3-0=
000xb: 1x read command code = 03h. Without dummy cycle between address and data.
010xb: 1x read command code = 0Bh. 8 dummy cycles inserted between address and data.
1x0xb: 1x read command code = 1Bh. 16 dummy cycles inserted between address and data.
*/
	unsigned char temp;

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0x3F;
	LCD_DataWrite(temp);

	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp &= 0xF0;
	LCD_DataWrite(temp);

}


void Set_CPOL(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp |= cSetb1;
  LCD_DataWrite(temp);
}



void Set_CPHA(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp |= cSetb0;
  LCD_DataWrite(temp);
}



void Reset_CPOL(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp &= cClrb1;
  LCD_DataWrite(temp);
}



void Reset_CPHA(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp &= cClrb0;
  LCD_DataWrite(temp);
}



void SPI_Clock_Period(unsigned char temp)
{
/*
SPI_clock= CORE_FREQ / ((Divisor+1)x2)
*/
   LCD_CmdWrite(0xBB);
   LCD_DataWrite(temp);
} 



void Select_LCD_DE_Mode(void)
{
/*
To Control panel's synchronous signals
0: Sync Mode: Enable XVSYNC, XHSYNC, XDE
1: DE Mode: Only XDE enable, XVSYNC & XHSYNC in idle state
*/
	unsigned char temp;
	LCD_CmdWrite(0x10);
	temp = LCD_DataRead();
    temp |= cSetb0;
	LCD_DataWrite(temp);
}



void PCLK_Falling(void)
{
/*
PCLK Inversion
0: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK falling edge.
1: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK rising edge.
*/
	unsigned char temp;
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
    temp |= cSetb7;
	LCD_DataWrite(temp);
}



void VSCAN_T_to_B(void)
{
/*	
Vertical Scan direction
0 : From Top to Bottom
1 : From bottom to Top
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp &= cClrb3;
	LCD_DataWrite(temp);
}



void PDATA_Set_RGB(void)
{
/*parallel PDATA[23:0] Output Sequence
000b : RGB
001b : RBG
010b : GRB
011b : GBR
100b : BRG
101b : BGR
110b : Gray			
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
    temp &=0xf8;
	LCD_DataWrite(temp);
}



void HSYNC_Low_Active(void)
{
/*	
HSYNC Polarity
0 : Low active.
1 : High active.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x13);
	temp = LCD_DataRead();
    temp &= cClrb7;
	LCD_DataWrite(temp);
}



void DE_High_Active(void)
{
/*	
DE Polarity
0 : High active.
1 : Low active.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x13);
	temp = LCD_DataRead();
	temp &= cClrb5;
	LCD_DataWrite(temp);
}



void LCD_HorizontalWidth_VerticalHeight(unsigned short WX,unsigned short HY)
{
/*
[14h] Horizontal Display Width Setting Bit[7:0]
[15h] Horizontal Display Width Fine Tuning (HDWFT) [3:0]
The register specifies the LCD panel horizontal display width in
the unit of 8 pixels resolution.
Horizontal display width(pixels) = (HDWR + 1) * 8 + HDWFTR

[1Ah] Vertical Display Height Bit[7:0]
Vertical Display Height(Line) = VDHR + 1
[1Bh] Vertical Display Height Bit[10:8]
Vertical Display Height(Line) = VDHR + 1
*/
	unsigned char temp;
	if(WX<8)
    {
	LCD_CmdWrite(0x14);
	LCD_DataWrite(0x00);
    
	LCD_CmdWrite(0x15);
	LCD_DataWrite(WX);
    
    temp=HY-1;
	LCD_CmdWrite(0x1A);
	LCD_DataWrite(temp);
	    
	temp=(HY-1)>>8;
	LCD_CmdWrite(0x1B);
	LCD_DataWrite(temp);
	}
	else
	{
    temp=(WX/8)-1;
	LCD_CmdWrite(0x14);
	LCD_DataWrite(temp);
    
    temp=WX%8;
	LCD_CmdWrite(0x15);
	LCD_DataWrite(temp);
    
    temp=HY-1;
	LCD_CmdWrite(0x1A);
	LCD_DataWrite(temp);
	    
	temp=(HY-1)>>8;
	LCD_CmdWrite(0x1B);
	LCD_DataWrite(temp);
	}
}



void VSYNC_Low_Active(void)
{
/*	
VSYNC Polarity
0 : Low active.
1 : High active.
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x13);
	temp = LCD_DataRead();
    temp &= cClrb6;
	LCD_DataWrite(temp);
}



void LCD_Horizontal_Non_Display(unsigned short WX)
{
/*
[16h] Horizontal Non-Display Period(HNDR) Bit[4:0]
This register specifies the horizontal non-display period. Also
called back porch.
Horizontal non-display period(pixels) = (HNDR + 1) * 8 + HNDFTR

[17h] Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]
This register specifies the fine tuning for horizontal non-display
period; it is used to support the SYNC mode panel. Each level of
this modulation is 1-pixel.
Horizontal non-display period(pixels) = (HNDR + 1) * 8 + HNDFTR
*/
	unsigned char temp;
	if(WX<8)
	{
	LCD_CmdWrite(0x16);
	LCD_DataWrite(0x00);
    
	LCD_CmdWrite(0x17);
	LCD_DataWrite(WX);
	}
	else
	{
    temp=(WX/8)-1;
	LCD_CmdWrite(0x16);
	LCD_DataWrite(temp);
    
    temp=WX%8;
	LCD_CmdWrite(0x17);
	LCD_DataWrite(temp);
	}	
}



void LCD_HSYNC_Start_Position(unsigned short WX)
{
/*
[18h] HSYNC Start Position[4:0]
The starting position from the end of display area to the
beginning of HSYNC. Each level of this modulation is 8-pixel.
Also called front porch.
HSYNC Start Position(pixels) = (HSTR + 1)x8
*/
	unsigned char temp;
	if(WX<8)
	{
	LCD_CmdWrite(0x18);
	LCD_DataWrite(0x00);
	}
	else
	{
    temp=(WX/8)-1;
	LCD_CmdWrite(0x18);
	LCD_DataWrite(temp);	
	}
}



void LCD_HSYNC_Pulse_Width(unsigned short WX)
{
/*
[19h] HSYNC Pulse Width(HPW) [4:0]
The period width of HSYNC.
HSYNC Pulse Width(pixels) = (HPW + 1)x8
*/
	unsigned char temp;
	if(WX<8)
	{
	LCD_CmdWrite(0x19);
	LCD_DataWrite(0x00);
	}
	else
	{
    temp=(WX/8)-1;
	LCD_CmdWrite(0x19);
	LCD_DataWrite(temp);	
	}
}



void LCD_Vertical_Non_Display(unsigned short HY)
{
/*
[1Ch] Vertical Non-Display Period Bit[7:0]
Vertical Non-Display Period(Line) = (VNDR + 1)

[1Dh] Vertical Non-Display Period Bit[9:8]
Vertical Non-Display Period(Line) = (VNDR + 1)
*/
	unsigned short temp;
    temp=HY-1;
	LCD_CmdWrite(0x1C);
	LCD_DataWrite(temp);

	LCD_CmdWrite(0x1D);
	LCD_DataWrite(temp>>8);
}



void LCD_VSYNC_Start_Position(unsigned short HY)
{
/*
[1Eh] VSYNC Start Position[7:0]
The starting position from the end of display area to the beginning of VSYNC.
VSYNC Start Position(Line) = (VSTR + 1)
*/
	unsigned char temp;
    temp=HY-1;
	LCD_CmdWrite(0x1E);
	LCD_DataWrite(temp);
}



void LCD_VSYNC_Pulse_Width(unsigned short HY)
{
/*
[1Fh] VSYNC Pulse Width[5:0]
The pulse width of VSYNC in lines.
VSYNC Pulse Width(Line) = (VPWR + 1)
*/
	unsigned char temp;
    temp=HY-1;
	LCD_CmdWrite(0x1F);
	LCD_DataWrite(temp);
}

//**************************************跟初始化8889相关的函数



void Foreground_color_16M(unsigned long temp)
{

	LCD_CmdWrite(0xD2);
	LCD_DataWrite(temp>>16);
	
	LCD_CmdWrite(0xD3);
	LCD_DataWrite(temp>>8);
	
	LCD_CmdWrite(0xD4);
	LCD_DataWrite(temp);

}



void BTE_Destination_Memory_Start_Address(unsigned long Addr)	
{
/*
[A7h] BTE Destination Memory Start Address [7:0]
[A8h] BTE Destination Memory Start Address [15:8]
[A9h] BTE Destination Memory Start Address [23:16]
[AAh] BTE Destination Memory Start Address [31:24]
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0xA7,Addr);
	LCD_RegisterWrite(0xA8,Addr>>8);
	LCD_RegisterWrite(0xA9,Addr>>16);
	LCD_RegisterWrite(0xAA,Addr>>24);
}



void BTE_Destination_Image_Width(unsigned short WX)	
{
/*
[ABh] BTE Destination Image Width [7:0]
[ACh] BTE Destination Image Width [12:8]
Unit: Pixel.
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0xAB,WX);
	LCD_RegisterWrite(0xAC,WX>>8);
}



void BTE_Destination_Window_Start_XY(unsigned short WX,unsigned short HY)	
{
/*
[ADh] BTE Destination Window Upper-Left corner X-coordinate [7:0]
[AEh] BTE Destination Window Upper-Left corner X-coordinate [12:8]
[AFh] BTE Destination Window Upper-Left corner Y-coordinate [7:0]
[B0h] BTE Destination Window Upper-Left corner Y-coordinate [12:8]
*/

	LCD_RegisterWrite(0xAD,WX);
	LCD_RegisterWrite(0xAE,WX>>8);

	LCD_RegisterWrite(0xAF,HY);
	LCD_RegisterWrite(0xB0,HY>>8);
}



void BTE_Window_Size(unsigned short WX, unsigned short HY)
{
/*
[B1h] BTE Window Width [7:0]
[B2h] BTE Window Width [12:8]

[B3h] BTE Window Height [7:0]
[B4h] BTE Window Height [12:8]
*/
        LCD_RegisterWrite(0xB1,WX);
        LCD_RegisterWrite(0xB2,WX>>8);
	
	    LCD_RegisterWrite(0xB3,HY);
        LCD_RegisterWrite(0xB4,HY>>8);
}



void BTE_Operation_Code(unsigned char setx)
{	
/*
BTE Operation Code[Bit3:0]
	
0000/ 0 : MPU Write BTE with ROP.
0001    : NA
0010/ 2 : Memory copy (move) BTE in positive direction with ROP.
0011    : NA
0100/ 4 : MPU Write with chroma keying (w/o ROP)
0101/ 5 : Memory copy (move) with chroma keying (w/o ROP)
0110/ 6 : Pattern Fill with ROP
0111/ 7 : Pattern Fill with chroma keying (w/o ROP)
1000/ 8 : MPU Write with Color Expansion (w/o ROP)
1001/ 9 : MPU Write with Color Expansion and chroma keying (w/o ROP)
1010/10 : Memory write with opacity (w/o ROP)
1011/11 : MPU Write with opacity (w/o ROP)
1100/12 : Solid Fill (w/o ROP)
1101    : NA
1110/14 : Memory write with Color Expansion (w/o ROP)
1111/15 : Memory write with Color Expansion and chroma keying (w/o ROP)
*/
    unsigned char temp;
    LCD_CmdWrite(0x91);
    temp = LCD_DataRead();
	temp &= 0xf0 ;
	temp |= setx ;
	LCD_DataWrite(temp);

}



void BTE_Enable(void)
{	
/*
BTE Function Enable
0 : BTE Function disable.
1 : BTE Function enable.
*/
    unsigned char temp;
    LCD_CmdWrite(0x90);
    temp = LCD_DataRead();
    temp |= cSetb4 ;
	LCD_DataWrite(temp);  
}



void Check_BTE_Busy(void)
{	
/*
case1: [90h]BTE Function Control Register_bit4
Read
0 : BTE function is idle.
1 : BTE function is busy.

case2: Status Register_bit3
0 : BTE function is idle.
1 : BTE function is busy.
*/
	unsigned char temp;

	//case1: using BTE Function Control Register
	do
	{
	    LCD_CmdWrite(0x90);
	    temp = LCD_DataRead();
	}while(temp&0x10);	

	//case2: using status register 	
	do
	{
		temp=LCD_StatusRead();
	}while(temp&0x08);
}



void PDATA_Set_BGR(void)
{
/*parallel PDATA[23:0] Output Sequence
000b : RGB
001b : RBG
010b : GRB
011b : GBR
100b : BRG
101b : BGR
110b : Gray			
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp &=0xf8;
	temp |= cSetb2;
    temp |= cSetb0;
	LCD_DataWrite(temp);
}
//**************************************跟bte相关的函数


void SPI_Master_LatchEdge_Select_Falling(void)
{
/*[REG PAGE 0],[C5h] 
[bit5] SPI master rx register latch edge
0: cclk rising edge
1: cclk falling edge
*/
	unsigned char temp;

	REG_Switch_to_REG0();

	LCD_CmdWrite(0xC5);
	temp = LCD_DataRead();
	temp |= 0x20;			//設定REG c5h, bit 5=1, B0010_0000.
	LCD_DataWrite(temp);
}



void SPIM_Clock_Divided_1(void)//
{
/*
REG[46h] [bit2] Spi master frequency eliminator			   

0: SPIM_clock = ( Core clock / 2 ) / ( frequency eliminator )  
1: SPIM_clock = ( Core clock / 1 ) / ( frequency eliminator )
*/
	unsigned char temp;

	REG_Switch_to_REG1();

		LCD_CmdWrite(0x46);
		temp=LCD_DataRead();
		temp |= cSetb2;
		LCD_DataWrite(temp);

	REG_Switch_to_REG0();

}



void IDEC_SPI_Clock_Divide(unsigned char IDEC_SPIclock_divide)// 
{
/*[REG PAGE 1],[BBh] idec SF Clock divide
[bit 1-0]
00: idec_SF clock = cclk
01: idec_SF clock = cclk/2
10: idec SF clock  = cclk/4
11: reverse

NOTE: IDEC_clock must be more than 2 times OSC clock. IDEC_clock must be > 2 x OSC_clock.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xBB);
	LCD_DataWrite(IDEC_SPIclock_divide);

	REG_Switch_to_REG0();
}



void IDEC_Select_Bus_0(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit3] 
IDEC sck and data bus select
0: SPI bus 0 is selected and the relative pins (xmosi, xmiso, xsio2, xsio3) are active.
1: SPI bus 1 is selected and the relative pins (xsp1_msio0, xsp1_msio1, xsp1_msio2, xsp1_msio3) are active.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0xF6;			//if bit0=1, IDEC will start .
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void SPIM_Select_Bus_0(void)	
{
/*[REG PAGE 0],[C5h] 
[bit7] SPI master bus select
0b:  Bus 0
1b:  Bus 1
*/
	unsigned char temp;

	REG_Switch_to_REG0();

	LCD_CmdWrite(0xC5);		
	temp = LCD_DataRead();
	temp &= 0x7F;			//設定REG c5h, bit 7=0
	LCD_DataWrite(temp);
}



void IDEC_Select_Bus_1(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit3] 
IDEC sck and data bus select
0: SPI bus 0 is selected and the relative pins (xmosi, xmiso, xsio2, xsio3) are active.
1: SPI bus 1 is selected and the relative pins (xsp1_msio0, xsp1_msio1, xsp1_msio2, xsp1_msio3) are active.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0xF6;			//if bit0=1, IDEC will start .
	temp |= 0x08;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void SPIM_Select_Bus_1(void) //
{
/*[REG PAGE 0],[C5h] 
[bit7] SPI master bus select
0b:  Bus 0
1b:  Bus 1
*/
	unsigned char temp;

	REG_Switch_to_REG0();

	LCD_CmdWrite(0xC5);		
	temp = LCD_DataRead();
	temp |= 0x80;			//設定REG c5h, bit 7=1
	LCD_DataWrite(temp);
}



void IDEC_Select_SFI_0(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit7-6] 
00: Serial Flash/ROM 0 I/F is selected.
01: Serial Flash/ROM 1 I/F is selected.
10: Serial Flash/ROM 2 I/F is selected.
11: Serial Flash/ROM 3 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();
	
	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0x3E;			//if bit0=1, IDEC will start .
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void Select_nSS_drive_on_xnsfcs0(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp &= cClrb7;
  temp &= cClrb5;
  LCD_DataWrite(temp);

}



void IDEC_Select_SFI_1(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit7-6] 
00: Serial Flash/ROM 0 I/F is selected.
01: Serial Flash/ROM 1 I/F is selected.
10: Serial Flash/ROM 2 I/F is selected.
11: Serial Flash/ROM 3 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0x3E;			//if bit0=1, IDEC will start .
	temp |= 0x40;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void Select_nSS_drive_on_xnsfcs1(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp &= cClrb7;
  temp |= cSetb5;
  LCD_DataWrite(temp);

}



void IDEC_Select_SFI_2(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit7-6] 
00: Serial Flash/ROM 0 I/F is selected.
01: Serial Flash/ROM 1 I/F is selected.
10: Serial Flash/ROM 2 I/F is selected.
11: Serial Flash/ROM 3 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0x3E;			//if bit0=1, IDEC will start .
	temp |= 0x80;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void Select_nSS_drive_on_xnsfcs2(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp |= cSetb7;
  temp &= cClrb5;
  LCD_DataWrite(temp);

}



void IDEC_Select_SFI_3(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit7-6] 
00: Serial Flash/ROM 0 I/F is selected.
01: Serial Flash/ROM 1 I/F is selected.
10: Serial Flash/ROM 2 I/F is selected.
11: Serial Flash/ROM 3 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0x3E;			//if bit0=1, IDEC will start .
	temp |= 0xC0;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void Select_nSS_drive_on_xnsfcs3(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp |= cSetb7;
  temp |= cSetb5;
  LCD_DataWrite(temp);

}



void nSS_Active(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp |= cSetb4;
  LCD_DataWrite(temp);

}



unsigned char SPI_Master_FIFO_Data_Put(unsigned char Data)
{
    unsigned char temp;
	LCD_CmdWrite(0xB8);
	LCD_DataWrite(Data);
	do{
		temp=Tx_FIFO_Empty_Flag();
	}while(temp==0);
//	while(Tx_FIFO_Empty_Flag()==0);	//空了再執行下一筆
	temp = SPI_Master_FIFO_Data_Get();

	return temp;
}



void nSS_Inactive(void)
{
  unsigned char temp;
  LCD_CmdWrite(0xB9);
  temp = LCD_DataRead();
  temp &= cClrb4;
  LCD_DataWrite(temp);

}



void IDEC_Select_SFI_32bit_Address(void)
{
/*[REG PAGE 1],[B7h] [bit5]
IDEC Serial Flash/ROM Address Mode
0: 24 bits address mode
1: 32 bits address mode
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp |= cSetb5;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void IDEC_Select_RA8875_SPI_Mode0_and_Mode3(void)
{
/*[REG PAGE 1],[B7h] [bit4]
IDEC Serial Interface
0: standard SPI mode 0 or mode 3 timing
1: Follow RA8875 mode 0 & mode 3 timing
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp |= cSetb4;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void IDEC_AVI_Decoding_to_PIP1_and_Shadow(void)
{
/*[REG PAGE 1],[C5h] 
[bit1-0]
00b: AVI_Decoding_to_PIP1_and_Shadow
01b: AVI_Decoding_to_PIP2_and_Shadow
1xb: AVI_Decoding_to_PIP1_no_Shadow
*/
	REG_Switch_to_REG1();

	LCD_CmdWrite(0xC5);
	LCD_DataWrite(0x00);

	REG_Switch_to_REG0();
}



void IDEC_Select_SFI_Quad_Mode_Dummy_8T_6Bh(void)// 
{
/*[REG PAGE 1],[B7h] 
[bit3-0]
1010b: 4x read command code – 6Bh. 
1100b: 4x read command code – EBh. 
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
	temp &= 0xF0;
	temp |= 0x0A;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}



void IDEC_Destination_Image_Width(unsigned short WX)// ,JPG,BMP	// 
{
/*[REG PAGE 1]
REG[CEh] IDEC (JPG/BMP) Destination Image_Width [7:0]
REG[CFh] IDEC (JPG/BMP) Destination Image_Width [12:8]
Note: just only for JPG/BMP
*/

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xCE);	LCD_DataWrite(WX);
	LCD_CmdWrite(0xCF);	LCD_DataWrite(WX>>8);

	REG_Switch_to_REG0();
}



void IDEC_Destination_Upper_Left_Corner(unsigned short WX,unsigned short HY)
{
/*
[C0h][C1h]: IDEC_Destination X-coordinates [7:0][15:8]
[C2h][C3h]: IDEC_Destination Y-coordinates [7:0][15:8]
*/

	REG_Switch_to_REG1();
 
	LCD_CmdWrite(0xC0);
	LCD_DataWrite(WX);
	LCD_CmdWrite(0xC1);
	LCD_DataWrite(WX>>8);
	
	LCD_CmdWrite(0xC2);
	LCD_DataWrite(HY);
	LCD_CmdWrite(0xC3);
	LCD_DataWrite(HY>>8);

	REG_Switch_to_REG0();
}



void IDEC_Source_Start_Address(unsigned long Addr)//AVI,JPG,BMP	// 
{
/*[REG PAGE 1]
[BCh] Serial flash IDEC Source START ADDRESS [7:0]
[BDh] Serial flash IDEC Source START ADDRESS [15:8]
[BEh] Serial flash IDEC Source START ADDRESS [23:16]
[BFh] Serial flash IDEC Source START ADDRESS [31:24]
*/

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xBC);	LCD_DataWrite(Addr);
	LCD_CmdWrite(0xBD);	LCD_DataWrite(Addr>>8);
	LCD_CmdWrite(0xBE);	LCD_DataWrite(Addr>>16);
	LCD_CmdWrite(0xBF);	LCD_DataWrite(Addr>>24);

	REG_Switch_to_REG0();
}



void IDEC_Transfer_Number(unsigned long Num)
{
/*
IDEC Transfer Number [7:0][15:8][23:16][31:24]
*/
	REG_Switch_to_REG1();

	LCD_CmdWrite(0xC6);
	LCD_DataWrite(Num);
	LCD_CmdWrite(0xC7);
	LCD_DataWrite(Num>>8);
	LCD_CmdWrite(0xC8);
	LCD_DataWrite(Num>>16);
	LCD_CmdWrite(0xC9);
	LCD_DataWrite(Num>>24);

	REG_Switch_to_REG0();
}



void IDEC_Starts_Decoding(void)
{	
/*[REG PAGE 1], REG[B6h], 
[bit0] 
Write Function: IDEC Start Bit
Set to 1 by MPU and reset to 0 automatically
It cannot start when fontwr_busy is 1. And if IDEC is enabled,
serial flash I/F can’t be set as text mode & send character code.
Read Function: IDEC Busy Check Bit
0: Idle
1: Busy
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp |= cSetb0;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0(); 
}



void Check_Busy_Media_Decode(void)
{
/*[REG PAGE 1], REG[A0h], 
[bit6] Media decode busy
*/
	unsigned char temp;

	REG_Switch_to_REG1();
	
	//case4: check AVI
	LCD_CmdWrite(0xA0);
	do{
		temp=LCD_DataRead();
	}while(temp&0x40);

	REG_Switch_to_REG0();
}



unsigned char Tx_FIFO_Empty_Flag(void)
{
  LCD_CmdWrite(0xBA);
  if((LCD_DataRead()&0x80)==0x80)
  return 1;
  else
  return 0;
}



unsigned char SPI_Master_FIFO_Data_Get(void)
{
   unsigned char temp;

	while(Rx_FIFO_Empty_Flag()==1);//不是空的往下執行
	LCD_CmdWrite(0xB8);
	temp=LCD_DataRead();
	//while(Rx_FIFO_full_flag()); //連續寫入16筆資料才需要
   return temp;
}



unsigned char Rx_FIFO_Empty_Flag(void)
{
  LCD_CmdWrite(0xBA);
  if((LCD_DataRead()&0x20)==0x20)
  return 1;
  else
  return 0;
} 
//跟图片相关API





void Background_color_16M(unsigned long temp)
{
    LCD_CmdWrite(0xD5);
 LCD_DataWrite(temp>>16);
  
    LCD_CmdWrite(0xD6);
 LCD_DataWrite(temp>>8);
   
    LCD_CmdWrite(0xD7);
 LCD_DataWrite(temp);
}


void Font_Select_8x16_16x16(void)
{
//[bit5-4]
//Font Height Setting
//00b : 8x16 / 16x16.
//01b : 12x24 / 24x24.
//10b : 16x32 / 32x32.
//*** User-defined Font width is decided by font code. 
//Genitop serial flash’s font width is decided by font code or GT Font ROM control register.

	unsigned char temp;
	LCD_CmdWrite(0xCC);
	temp = LCD_DataRead();
    temp &= cClrb5;
    temp &= cClrb4;
	LCD_DataWrite(temp);
}//*/



void Font_Select_12x24_24x24(void)
{
/*[bit5-4]
Font Height Setting
00b : 8x16 / 16x16.
01b : 12x24 / 24x24.
10b : 16x32 / 32x32.
*** User-defined Font width is decided by font code. Genitop
serial flash’s font width is decided by font code or GT Font ROM
control register.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCC);
	temp = LCD_DataRead();
    temp &= cClrb5;
    temp |= cSetb4;
	LCD_DataWrite(temp);
}



void Font_Select_16x32_32x32(void)
{
//[bit5-4]
//Font Height Setting
//00b : 8x16 / 16x16.
//01b : 12x24 / 24x24.
//10b : 16x32 / 32x32.
//*** User-defined Font width is decided by font code. 
//Genitop serial flash’s font width is decided by font code or GT Font ROM control register.

	unsigned char temp;
	LCD_CmdWrite(0xCC);
	temp = LCD_DataRead();
    temp |= cSetb5;
    temp &= cClrb4;
	LCD_DataWrite(temp);
}//*/



void Font_Width_X1(void)
{
/*
Horizontal Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb3;
    temp &= cClrb2;
	LCD_DataWrite(temp);
}



void Font_Width_X2(void)
{
/*
Horizontal Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb3;
    temp |= cSetb2;
	LCD_DataWrite(temp);
}



void Font_Width_X3(void)
{
/*
Horizontal Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb3;
    temp &= cClrb2;
	LCD_DataWrite(temp);
}



void Font_Width_X4(void)
{
/*
Horizontal Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb3;
    temp |= cSetb2;
	LCD_DataWrite(temp);
}


void Font_Height_X2(void)
{
/*
Vertical Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb1;
    temp |= cSetb0;
	LCD_DataWrite(temp);
}



void Font_Height_X1(void)
{
/*
Vertical Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb1;
    temp &= cClrb0;
	LCD_DataWrite(temp);
}



void Font_Height_X3(void)
{
/*
Vertical Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb1;
    temp &= cClrb0;
	LCD_DataWrite(temp);
}



void Font_Height_X4(void)
{
/*
Vertical Font Enlargement
00b : X1.
01b : X2.
10b : X3.
11b : X4.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb1;
    temp |= cSetb0;
	LCD_DataWrite(temp);
}


void Font_Background_select_Color(void)
{
/*
Font Transparency
0 : Character background displayed with specified color.
1 : Character background displayed with original canvas background.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb6;
	LCD_DataWrite(temp);
}



void Font_Background_select_Original_Canvas(void)
{
/*		
Font Transparency
0 : Character background displayed with specified color.
1 : Character background displayed with original canvas background.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb6;
	LCD_DataWrite(temp);
}



void Disable_Font_Alignment(void)
{
/*
Full Alignment Selection Bit
0 : Full alignment disable.
1 : Full alignment enable.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp &= cClrb7;
	LCD_DataWrite(temp);
}



void Enable_Font_Alignment(void)
{
/*
Full Alignment Selection Bit
0 : Full alignment disable.
1 : Full alignment enable.
*/
	unsigned char temp;
	LCD_CmdWrite(0xCD);
	temp = LCD_DataRead();
    temp |= cSetb7;
	LCD_DataWrite(temp);
}


void Check_Mem_WR_FIFO_Empty(void)
{
/*[Status Register] bit6
Host Memory Write FIFO empty
0: Memory Write FIFO is not empty.
1: Memory Write FIFO is empty.
When Memory Write FIFO is empty, MPU may write 8bpp data 64
pixels, or 16bpp data 32 pixels, 24bpp data 16 pixels directly.
*/	
	unsigned short i;
	// Please according to your usage to modify delay(check) time. // 請依據您的使用情況修改執行時間
	for(i=0;i<1000;i++)
	{
		if( (LCD_StatusRead()&0x40)==0x40 ){break;}
	}

#ifdef Check_While_Busy	
	while( (LCD_StatusRead()&0x40) == 0x00 );
#endif
}



void Text_Mode(void)
{
	unsigned char temp;
	LCD_CmdWrite(0x03);
	temp = LCD_DataRead();
    temp |= cSetb2;
	LCD_DataWrite(temp);
}



void Check_Mem_WR_FIFO_not_Full(void)
{
/*[Status Register] bit7
Host Memory Write FIFO full
0: Memory Write FIFO is not full.
1: Memory Write FIFO is full.
Only when Memory Write FIFO is not full, MPU may write another
one pixel.
*/ 
	unsigned short i;
	// Please according to your usage to modify delay(check) time. // 請依據您的使用情況修改執行時間
//	for(i=0;i<1000;i++)
//	{
//		if( (LCD_StatusRead()&0x80)==0 ){break;}
//	}
	
	#ifdef Check_While_Busy		
		while( LCD_StatusRead()&0x80 );
	#endif

//	delay_us(1);
}



void CGROM_Select_Internal_CGROM(void)
{
/*[bit7-6]
User-defined Font /CGROM Font Selection Bit in Text Mode
00 : Internal CGROM
01 : Genitop serial flash
10 : User-defined Font
*/
	unsigned char temp;
	LCD_CmdWrite(0xCC);
	temp = LCD_DataRead();
	temp &= cClrb7;
    temp &= cClrb6;
	LCD_DataWrite(temp);
}



void Goto_Text_XY(unsigned short WX,unsigned short HY)	
{
/*
Set Text Write position
Text Write X-coordinate [12:8][7:0]
Text Write Y-coordinate [12:8][7:0]
Reference Canvas image coordinate.
Unit: Pixel
*/
	LCD_CmdWrite(0x63);	LCD_DataWrite(WX);
	LCD_CmdWrite(0x64);	LCD_DataWrite(WX>>8);
	LCD_CmdWrite(0x65);	LCD_DataWrite(HY);
	LCD_CmdWrite(0x66);	LCD_DataWrite(HY>>8);
}



void BTE_S0_Memory_Start_Address(unsigned long Addr)	
{
/*
[93h] BTE S0 Memory Start Address [7:0]
[94h] BTE S0 Memory Start Address [15:8]
[95h] BTE S0 Memory Start Address [23:16]
[96h] BTE S0 Memory Start Address [31:24]
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0x93,Addr);
	LCD_RegisterWrite(0x94,Addr>>8);
	LCD_RegisterWrite(0x95,Addr>>16);
	LCD_RegisterWrite(0x96,Addr>>24);
}



void BTE_S0_Image_Width(unsigned short WX)	
{
/*
[97h] BTE S0 Image Width [7:0]
[98h] BTE S0 Image Width [12:8]
Unit: Pixel.
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0x97,WX);
	LCD_RegisterWrite(0x98,WX>>8);
}




void BTE_S0_Window_Start_XY(unsigned short WX,unsigned short HY)	
{
/*
[99h] BTE S0 Window Upper-Left corner X-coordinate [7:0]
[9Ah] BTE S0 Window Upper-Left corner X-coordinate [12:8]
[9Bh] BTE S0 Window Upper-Left corner Y-coordinate [7:0]
[9Ch] BTE S0 Window Upper-Left corner Y-coordinate [12:8]
*/

	LCD_RegisterWrite(0x99,WX);
	LCD_RegisterWrite(0x9A,WX>>8);

	LCD_RegisterWrite(0x9B,HY);
	LCD_RegisterWrite(0x9C,HY>>8);
}



void BTE_S1_Memory_Start_Address(unsigned long Addr)	
{
/*
[9Dh] BTE S1 Memory Start Address [7:0]
[9Eh] BTE S1 Memory Start Address [15:8]
[9Fh] BTE S1 Memory Start Address [23:16]
[A0h] BTE S1 Memory Start Address [31:24]
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0x9D,Addr);
	LCD_RegisterWrite(0x9E,Addr>>8);
	LCD_RegisterWrite(0x9F,Addr>>16);
	LCD_RegisterWrite(0xA0,Addr>>24);
}



void BTE_S1_Image_Width(unsigned short WX)	
{
/*
[A1h] BTE S1 Image Width [7:0]
[A2h] BTE S1 Image Width [12:8]
Unit: Pixel.
Bit [1:0] tie to “0” internally.
*/
	LCD_RegisterWrite(0xA1,WX);
	LCD_RegisterWrite(0xA2,WX>>8);
}



void BTE_S1_Window_Start_XY(unsigned short WX,unsigned short HY)	
{
/*
[A3h] BTE S1 Window Upper-Left corner X-coordinate [7:0]
[A4h] BTE S1 Window Upper-Left corner X-coordinate [12:8]
[A5h] BTE S1 Window Upper-Left corner Y-coordinate [7:0]
[A6h] BTE S1 Window Upper-Left corner Y-coordinate [12:8]
*/

	LCD_RegisterWrite(0xA3,WX);
	LCD_RegisterWrite(0xA4,WX>>8);

	LCD_RegisterWrite(0xA5,HY);
	LCD_RegisterWrite(0xA6,HY>>8);
}



void BTE_ROP_Code(unsigned char setx)
{	
/*
BTE ROP Code[Bit7:4]
	
0000 : 0(Blackness)
0001 : ~S0.~S1 or ~ ( S0+S1 )
0010 : ~S0.S1
0011 : ~S0
0100 : S0.~S1
0101 : ~S1
0110 : S0^S1
0111 : ~S0+~S1 or ~ ( S0.S1 )
1000 : S0.S1
1001 : ~ ( S0^S1 )
1010 : S1
1011 : ~S0+S1
1100 : S0
1101 : S0+~S1
1110 : S0+S1
1111 : 1 ( Whiteness )
*/
		unsigned char temp;
    LCD_CmdWrite(0x91);
    temp = LCD_DataRead();
    temp &= 0x0f ;
		temp |= (setx<<4);
	  LCD_DataWrite(temp);
}



void Select_LCD_Sync_Mode(void)
{
/*
To Control panel's synchronous signals
0: Sync Mode: Enable XVSYNC, XHSYNC, XDE
1: DE Mode: Only XDE enable, XVSYNC & XHSYNC in idle state
*/
	unsigned char temp;
	LCD_CmdWrite(0x10);
	temp = LCD_DataRead();
  temp &= cClrb0;
	LCD_DataWrite(temp);
}


void Square_Start_XY(unsigned short WX,unsigned short HY)
{
/*
[68h] Draw Line/Square/Triangle Start X-coordinate [7:0]
[69h] Draw Line/Square/Triangle Start X-coordinate [12:8]
[6Ah] Draw Line/Square/Triangle Start Y-coordinate [7:0]
[6Bh] Draw Line/Square/Triangle Start Y-coordinate [12:8]
*/
	LCD_CmdWrite(0x68);
	LCD_DataWrite(WX);

	LCD_CmdWrite(0x69);
	LCD_DataWrite(WX>>8);

	LCD_CmdWrite(0x6A);
	LCD_DataWrite(HY);

	LCD_CmdWrite(0x6B);
	LCD_DataWrite(HY>>8);
}



void Square_End_XY(unsigned short WX,unsigned short HY)
{
/*
[6Ch] Draw Line/Square/Triangle End X-coordinate [7:0]
[6Dh] Draw Line/Square/Triangle End X-coordinate [12:8]
[6Eh] Draw Line/Square/Triangle End Y-coordinate [7:0]
[6Fh] Draw Line/Square/Triangle End Y-coordinate [12:8]
*/
	LCD_CmdWrite(0x6C);
	LCD_DataWrite(WX);

	LCD_CmdWrite(0x6D);
	LCD_DataWrite(WX>>8);

	LCD_CmdWrite(0x6E);
	LCD_DataWrite(HY);

	LCD_CmdWrite(0x6F);
	LCD_DataWrite(HY>>8);
}


void Start_Square(void)
{
	LCD_CmdWrite(0x76);
	LCD_DataWrite(0xA0);//B1010_XXXX
	Check_2D_Busy();
}




void Start_Square_Fill(void)
{
	LCD_CmdWrite(0x76);
	LCD_DataWrite(0xE0);//B1110_XXXX

	Check_2D_Busy();
}


void Line_Start_XY(unsigned short WX,unsigned short HY)
{
/*
[68h] Draw Line/Square/Triangle Start X-coordinate [7:0]
[69h] Draw Line/Square/Triangle Start X-coordinate [12:8]
[6Ah] Draw Line/Square/Triangle Start Y-coordinate [7:0]
[6Bh] Draw Line/Square/Triangle Start Y-coordinate [12:8]
*/
	LCD_CmdWrite(0x68);
	LCD_DataWrite(WX);

	LCD_CmdWrite(0x69);
	LCD_DataWrite(WX>>8);

	LCD_CmdWrite(0x6A);
	LCD_DataWrite(HY);

	LCD_CmdWrite(0x6B);
	LCD_DataWrite(HY>>8);
}



void Line_End_XY(unsigned short WX,unsigned short HY)
{
/*
[6Ch] Draw Line/Square/Triangle End X-coordinate [7:0]
[6Dh] Draw Line/Square/Triangle End X-coordinate [12:8]
[6Eh] Draw Line/Square/Triangle End Y-coordinate [7:0]
[6Fh] Draw Line/Square/Triangle End Y-coordinate [12:8]
*/
	LCD_CmdWrite(0x6C);
	LCD_DataWrite(WX);

	LCD_CmdWrite(0x6D);
	LCD_DataWrite(WX>>8);

	LCD_CmdWrite(0x6E);
	LCD_DataWrite(HY);

	LCD_CmdWrite(0x6F);
	LCD_DataWrite(HY>>8);
}



void Start_Line(void)
{
	unsigned char temp;

	LCD_CmdWrite(0x67);
	temp = LCD_DataRead();
	temp &= cClrb1;
	temp |= cSetb7;
	LCD_DataWrite(temp);

	Check_2D_Busy();
}


void VSCAN_B_to_T(void)
{
/*	
Vertical Scan direction
0 : From Top to Bottom
1 : From bottom to Top
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp |= cSetb3;
	LCD_DataWrite(temp);
}



void HSCAN_R_to_L(void)
{
/*	
Horizontal Scan direction
0 : From Left to Right
1 : From Right to Left
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp |= cSetb4;
	LCD_DataWrite(temp);
}


void HSCAN_L_to_R(void)
{
/*	
Horizontal Scan direction
0 : From Left to Right
1 : From Right to Left
*/
	unsigned char temp;
	
	LCD_CmdWrite(0x12);
	temp = LCD_DataRead();
	temp &= cClrb4;
	LCD_DataWrite(temp);
}



void Select_SFI_Font_Mode(void)
{
/*[bit6]
Serial Flash /ROM Access Mode
0: Font mode  for external cgrom
1: DMA mode  for cgram , pattern , bootstart image or osd
*/
	unsigned char temp;
	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp &= cClrb6;
	LCD_DataWrite(temp);
}


void CGROM_Select_Genitop_FontROM(void)
{
/*[bit7-6]
User-defined Font /CGROM Font Selection Bit in Text Mode
00 : Internal CGROM
01 : Genitop serial flash
10 : User-defined Font
*/
	unsigned char temp;
	LCD_CmdWrite(0xCC);
	temp = LCD_DataRead();
	temp &= cClrb7;
    temp |= cSetb6;
	LCD_DataWrite(temp);
}



void Set_GTFont_Decoder(unsigned char temp)
{
/*
[bit7-3]
FONT ROM Coding Setting
For specific GT serial Font ROM, the coding method must be set for decoding.
00000b: GB2312
00001b: GB12345/GB18030
00010b: BIG5
00011b: UNICODE
00100b: ASCII
00101b: UNI-Japanese
00110b: JIS0208
00111b: Latin/Greek/ Cyrillic / Arabic/Thai/Hebrew
01000b: Korea
10001b: ISO-8859-1
10010b: ISO-8859-2
10011b: ISO-8859-3
10100b: ISO-8859-4
10101b: ISO-8859-5
10110b: ISO-8859-6
10111b: ISO-8859-7
11000b: ISO-8859-8
11001b: ISO-8859-9
11010b: ISO-8859-10
11011b: ISO-8859-11
11100b: ISO-8859-12
11101b: ISO-8859-13
11110b: ISO-8859-14
11111b: ISO-8859-15

[bit1-0]
ASCII / Latin/Greek/ Cyrillic / Arabic
		(ASCII)		(Latin/Greek/Cyrillic)	(Arabic)
00b		Normal			Normal 					NA
01b		Arial 		Variable Width 			Presentation Forms-A
10b		Roman 			NA 					Presentation Forms-B
11b		Bold			NA 						NA
*/
	LCD_CmdWrite(0xCF);
	LCD_DataWrite(temp);
}


void Select_RA8875_SPI_Mode0_and_Mode3(void)
{
/*[bit4]
RA8875 compatible mode
0: standard SPI mode 0 or mode 3 timing
1: Follow RA8875 mode 0 & mode 3 timing
*/
	unsigned char temp;
	LCD_CmdWrite(0xB7);
	temp = LCD_DataRead();
    temp |= cSetb4;
	LCD_DataWrite(temp);
}


void Select_SFI_0(void)
{
/*[bit7]
Serial Flash/ROM I/F # Select
0: Serial Flash/ROM 0 I/F is selected.
1: Serial Flash/ROM 1 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

		LCD_CmdWrite(0xB7);
		temp=LCD_DataRead();
		temp &= cClrb7;
		LCD_DataWrite(temp);

	REG_Switch_to_REG0();

		LCD_CmdWrite(0xB7);
		temp = LCD_DataRead();
	    temp &= cClrb7;
		LCD_DataWrite(temp);
}
void Select_SFI_1(void)
{
/*[bit7]
Serial Flash/ROM I/F # Select
0: Serial Flash/ROM 0 I/F is selected.
1: Serial Flash/ROM 1 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

		LCD_CmdWrite(0xB7);
		temp=LCD_DataRead();
		temp &= cClrb7;
		LCD_DataWrite(temp);

	REG_Switch_to_REG0();

		LCD_CmdWrite(0xB7);
		temp = LCD_DataRead();
	    temp |= cSetb7;
		LCD_DataWrite(temp);
}
void Select_SFI_2(void)
{
/*[bit7]
Serial Flash/ROM I/F # Select
0: Serial Flash/ROM 0 I/F is selected.
1: Serial Flash/ROM 1 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

		LCD_CmdWrite(0xB7);
		temp=LCD_DataRead();
		temp |= cSetb7;
		LCD_DataWrite(temp);

	REG_Switch_to_REG0();

		LCD_CmdWrite(0xB7);
		temp = LCD_DataRead();
	    temp &= cClrb7;
		LCD_DataWrite(temp);

}
void Select_SFI_3(void)
{
/*[bit7]
Serial Flash/ROM I/F # Select
0: Serial Flash/ROM 0 I/F is selected.
1: Serial Flash/ROM 1 I/F is selected.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

		LCD_CmdWrite(0xB7);
		temp=LCD_DataRead();
		temp |= cSetb7;
		LCD_DataWrite(temp);

	REG_Switch_to_REG0();

		LCD_CmdWrite(0xB7);
		temp = LCD_DataRead();
	    temp |= cSetb7;
		LCD_DataWrite(temp);
}


void FONT_DMA_Select_Bus_0(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit4] FONT/DMA serial flash sck and data bus select
0: SPI bus 0 is selected and the relative pins (xmosi, xmiso, xsio2, xsio3) are active.
1: SPI bus 1 is selected and the relative pins (xsp1_msio0, xsp1_msio1, xsp1_msio2, xsp1_msio3) are active.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0xEE;			//if bit0=1, IDEC will start .
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}


void FONT_DMA_Select_Bus_1(void)	
{
/*[REG PAGE 1], REG[B6h], 
[bit4] FONT/DMA serial flash sck and data bus select
0: SPI bus 0 is selected and the relative pins (xmosi, xmiso, xsio2, xsio3) are active.
1: SPI bus 1 is selected and the relative pins (xsp1_msio0, xsp1_msio1, xsp1_msio2, xsp1_msio3) are active.
*/
	unsigned char temp;

	REG_Switch_to_REG1();

	LCD_CmdWrite(0xB6);
	temp = LCD_DataRead();
	temp &= 0xEE;			//if bit0=1, IDEC will start .
	temp |= 0x10;
	LCD_DataWrite(temp);

	REG_Switch_to_REG0();
}










 







