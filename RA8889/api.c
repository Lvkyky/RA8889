#include "UserDef.h"
#include "RA8889.h"
#include "spi.h"
#include "api.h"
#include "delay.h"               //引入微秒延时，可能会出现bug.
#include "USART.h"
#include "screen.h"
#include "All_8889_Pic_NOR.h"


///*************************BTE DEMO*****************************/
void BTE_Solid_Fill                      //从块传输引擎
(
unsigned long Des_Addr //start address of destination 
,unsigned short Des_W // image width of destination (recommend = canvas image width) 
, unsigned short XDes //coordinate X of destination 
,unsigned short YDes //coordinate Y of destination 
,unsigned long Foreground_color //Solid Fill color
,unsigned short X_W //Width of BTE Window
,unsigned short Y_H //Length of BTE Window 
)
{

#ifdef MCU_8bit_ColorDepth_8bpp	
  Foreground_color_256(Foreground_color);
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Foreground_color_65k(Foreground_color);
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Foreground_color_16M(Foreground_color);
#endif

#ifdef MCU_16bit_ColorDepth_16bpp	
  Foreground_color_65k(Foreground_color);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Foreground_color_16M(Foreground_color);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Foreground_color_16M(Foreground_color);
#endif
  BTE_Destination_Memory_Start_Address(Des_Addr);
  BTE_Destination_Image_Width(Des_W);
  BTE_Destination_Window_Start_XY(XDes,YDes);
  BTE_Window_Size(X_W,Y_H);
  BTE_Operation_Code(0x0c);		//BTE Operation: Solid Fill (w/o ROP)
  BTE_Enable();
  Check_BTE_Busy();  
}



void BTE_Memory_Copy
(
unsigned long S0_Addr //Start address of Source 0
,unsigned short S0_W //image width of Source 0 (recommend = canvas image width)
,unsigned short XS0 //coordinate X of Source 0
,unsigned short YS0 //coordinate Y of Source 0
,unsigned long S1_Addr //Start address of Source 1
,unsigned short S1_W //image width of Source 1 (recommend = canvas image width)
,unsigned short XS1 //coordinate X of Source 1
,unsigned short YS1 //coordinate Y of Source 1
,unsigned long Des_Addr //start address of Destination
,unsigned short Des_W //image width of Destination (recommend = canvas image width)
,unsigned short XDes //coordinate X of Destination
,unsigned short YDes //coordinate Y of Destination
,unsigned int ROP_Code
/*ROP_Code :
   0000b		0(Blackness)
   0001b		~S0!E~S1 or ~(S0+S1)
   0010b		~S0!ES1
   0011b		~S0
   0100b		S0!E~S1
   0101b		~S1
   0110b		S0^S1
   0111b		~S0 + ~S1 or ~(S0 + S1)
   1000b		S0!ES1
   1001b		~(S0^S1)
   1010b		S1
   1011b		~S0+S1
   1100b		S0
   1101b		S0+~S1
   1110b		S0+S1
   1111b		1(whiteness)*/
,unsigned short X_W //X_W : Width of BTE Window
,unsigned short Y_H //Y_H : Length of BTE Window
)
{
  BTE_S0_Memory_Start_Address(S0_Addr);
  BTE_S0_Image_Width(S0_W);
  BTE_S0_Window_Start_XY(XS0,YS0);

  BTE_S1_Memory_Start_Address(S1_Addr);
  BTE_S1_Image_Width(S1_W); 
  BTE_S1_Window_Start_XY(XS1,YS1);

  BTE_Destination_Memory_Start_Address(Des_Addr);
  BTE_Destination_Image_Width(Des_W);
  BTE_Destination_Window_Start_XY(XDes,YDes);	
   
  BTE_ROP_Code(ROP_Code);	
  BTE_Operation_Code(0x02); //BTE Operation: Memory copy (move) with ROP.
  BTE_Window_Size(X_W,Y_H); 
  BTE_Enable();
  Check_BTE_Busy();
}

void BTE_Memory_Copy_Chroma_key
(
unsigned long S0_Addr //Start address of Source 0
,unsigned short S0_W //image width of Source 0 (recommend = canvas image width) 
,unsigned short XS0 //coordinate X of Source 0
,unsigned short YS0 //coordinate Y of Source 0
,unsigned long Des_Addr //start address of Destination
,unsigned short Des_W //image width of Destination (recommend = canvas image width) 
,unsigned short XDes //coordinate X of Destination
,unsigned short YDes //coordinate Y of Destination
,unsigned long Background_color // transparent color
,unsigned short X_W //Width of BTE Window
,unsigned short Y_H //Length of BTE Window
)
{

#ifdef MCU_8bit_ColorDepth_8bpp	
  Background_color_256(Background_color); 
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Background_color_65k(Background_color); 
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Background_color_16M(Background_color); 
#endif
#ifdef MCU_16bit_ColorDepth_16bpp	
  Background_color_65k(Background_color); 
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Background_color_16M(Background_color); 
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Background_color_16M(Background_color); 
#endif
  BTE_S0_Memory_Start_Address(S0_Addr);
  BTE_S0_Image_Width(S0_W);
  BTE_S0_Window_Start_XY(XS0,YS0);	

  BTE_Destination_Memory_Start_Address(Des_Addr);
  BTE_Destination_Image_Width(Des_W);
  BTE_Destination_Window_Start_XY(XDes,YDes);
   
  BTE_Operation_Code(0x05);	//BTE Operation: Memory copy (move) with chroma keying (w/o ROP)
  BTE_Window_Size(X_W,Y_H); 
  BTE_Enable();
  Check_BTE_Busy();
}
///*************************BTE DEMO*****************************/







///*************************JPEG DEMO*****************************/

void switch_24bits_to_32bits(unsigned char BUS,unsigned char SCS)
{
	Enable_SFlash_SPI();
	SPI_Master_LatchEdge_Select_Falling();
  SPIM_Clock_Divided_1();
	SPI_Clock_Period(2);
	
	switch(BUS)
  {	
	  case 0:
      SPIM_Select_Bus_0();	
	  break;
		
	  case 1:
      SPIM_Select_Bus_1();	
	  break;
	}
	
  if(SCS == 0)
  {
   Select_nSS_drive_on_xnsfcs0();
  }
  if(SCS == 1)
  {														    
   Select_nSS_drive_on_xnsfcs1();
  }	
  if(SCS == 2)
  {														    
   Select_nSS_drive_on_xnsfcs2();
  }	
  if(SCS == 3)
  {														    
   Select_nSS_drive_on_xnsfcs3();
  }		
//**************************//data are read on the clock's rising edge(low!鑐igh transition)
//**************************//and data are changed on a falling edge (high!鑇ow clock transition) 
  Reset_CPOL();						   
  //Set_CPOL();
  Reset_CPHA();
  //Set_CPHA();
//**************************
  //Enter 4-byte mode
  								   
  nSS_Active();					   //nSS port will goes low
  SPI_Master_FIFO_Data_Put(0xB7);  

  delay_ms(1); 
  nSS_Inactive();				   //nSS port will goes high
}






void SPI_NOR_Flash_switch_QUAD_MODE  // DMA 外部flash选择
(
unsigned char BUS /*select SPI Bus 0 or 1*/
,unsigned char SCS /*select SPI CS 0~3*/
,unsigned char flash /*select flash: 0 =MXIC , 1=WINBOND*/
)

{
	unsigned char temp;


	Enable_SFlash_SPI();
	SPI_Master_LatchEdge_Select_Falling();
  SPIM_Clock_Divided_1();
	SPI_Clock_Period(2);

  switch(BUS)
  {	
	  case 0:
      SPIM_Select_Bus_0();	
	  break;
	  case 1:
      SPIM_Select_Bus_1();	
	  break;
  }		

  switch(SCS)
  {	
	  case 0:
      Select_nSS_drive_on_xnsfcs0();
	  break;
	
	  case 1:
      Select_nSS_drive_on_xnsfcs1();
	  break;

	  case 2:
      Select_nSS_drive_on_xnsfcs2();
	  break;
		
	  case 3:
      Select_nSS_drive_on_xnsfcs3();
	  break;
  }	
	
  Reset_CPOL();						   
  //Set_CPOL();
	Reset_CPHA();
  //Set_CPHA();	
	
  //WREN : write enable
  nSS_Active();
  SPI_Master_FIFO_Data_Put(0x06);  
  nSS_Inactive();

  //RDSR : check writable

  do{
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x05);  //
    temp = SPI_Master_FIFO_Data_Put(0xff);
    nSS_Inactive();
    delay_us(100);
    }while((temp&0x02)==0x00);  //WEL=1 ? WRITABLE : UNWRITABLE

  switch(flash)
  {
	  case 0:
    //**********************************MXIC Flash Quad mode
    //WRITE STATUS REG                      
      nSS_Active();
      SPI_Master_FIFO_Data_Put(0x01);  
      SPI_Master_FIFO_Data_Put(0x40);
      nSS_Inactive();                        
    ///*************************************	
	  break;
	
		case 1:

    //******************************Winbond Flash Quad mode
    //WRITE STATUS REG
      nSS_Active();
      SPI_Master_FIFO_Data_Put(0x31);  // Status Register-2
      SPI_Master_FIFO_Data_Put(0x02);    // QE=1, Quad Mode
      nSS_Inactive();
    ///*****************************		
	  break;
  }	

  //check flash busy 
  do                
  {                           
    //RDSR
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x05);  //
    temp = SPI_Master_FIFO_Data_Put(0xff);
    nSS_Inactive();
  }while((temp & 0x01)==0x01);   //WIP=1 ? BUSY:IDLE

}





void SPI_NOR_initial_JPG_AVI
(
unsigned char flash//0 : MXIC , 1 : Winbond
,unsigned char addr_24b_32b//flash addr : 0:24bit addr, 1:32bit addr
,unsigned char BUS//BUS : 0 = Use BUS0, 1 = Use BUS1
,unsigned char SCS//SCS : 0 = Use SCS0, 1 = Use SCS1 ,2 = Use SCS2 ,3 = Use SCS3
,unsigned char SCK_Divide//media decode divide : IDEC Clock = CORE CLK/2^SCK_Divide ,range:0~3, recommend <= 60MHz
)
{
	unsigned char temp;

	Enable_SFlash_SPI();
	SPI_Master_LatchEdge_Select_Falling();
  SPIM_Clock_Divided_1();
	IDEC_SPI_Clock_Divide(SCK_Divide);
	SPI_Clock_Period(2);
                                            

  switch(BUS)
  {	
	  case 0:
      IDEC_Select_Bus_0();                     //MEDIA ?I?IBUS 0
      SPIM_Select_Bus_0();	
	  break;
	  case 1:
      IDEC_Select_Bus_1();                     //MEDIA ?I?IBUS 1
      SPIM_Select_Bus_1();	
	  break;
  }		

  switch(SCS)
  {	
	  case 0:
			IDEC_Select_SFI_0();                               //MEDIA?I?ICS0
			Select_nSS_drive_on_xnsfcs0();
		break;
		
		case 1:
			IDEC_Select_SFI_1();                               //MEDIA?I?ICS1
			Select_nSS_drive_on_xnsfcs1();
		break;

		case 2:
			IDEC_Select_SFI_2();                               //MEDIA?I?ICS2
			Select_nSS_drive_on_xnsfcs2();
		break;
		
		case 3:
			IDEC_Select_SFI_3();                               //MEDIA?I?ICS3
			Select_nSS_drive_on_xnsfcs3();
		break;
	}
  
	SPI_NOR_Flash_switch_QUAD_MODE(BUS,SCS,flash);		//Into Quad Mode

	if(addr_24b_32b==0)
	  IDEC_Select_SFI_24bit_Address();
 	else
	{
		switch_24bits_to_32bits(BUS,SCS);
		IDEC_Select_SFI_32bit_Address();
	}
	         
  IDEC_Select_RA8875_SPI_Mode0_and_Mode3();         
  IDEC_Select_SFI_Quad_Mode_Dummy_8T_6Bh();       //MEDIA QUAD MODE
  //IDEC_Select_SFI_Quad_Mode_Dummy_4T_EBh();

  IDEC_AVI_Decoding_to_PIP1_and_Shadow();        
}




void JPG_NOR 
(
unsigned long addr// JPG pic addr in flash
,unsigned long JPGsize //JPG pic size
,unsigned long IDEC_canvas_width //recommend = canvas_image_width
,unsigned short x//JPG pic write to sdram coordinate of x
,unsigned short y//JPG pic write to sdram coordinate of y
)
{
	
  IDEC_Destination_Image_Width(IDEC_canvas_width);
	IDEC_Destination_Upper_Left_Corner(x,y);

	IDEC_Source_Start_Address(addr);    //JPG起cl|i址
	IDEC_Transfer_Number(JPGsize);             //JPG SIZE
	IDEC_Starts_Decoding();        //?}cl?NJPG
	Check_Busy_Media_Decode(); 

}



//void NOR_JPG_Demo(void)
//{
//u8 i;
//PrintString1("开始jpeg初始化\r\n");
//delay_ms(200);
//delay_ms(200);	
//SPI_NOR_initial_JPG_AVI (1,0,1,2,1);
//PrintString1("jieg初始化完成\r\n");
//delay_ms(200);
//delay_ms(200);	

//	


//PrintString1("图片资源加载中\r\n");	
//delay_ms(200);
//delay_ms(200);
//for(i=41;i<120;i++)
//	{
//	JPG_NOR ( BINARY_INFO[i].start_addr,BINARY_INFO[i].img_size,canvas_image_width,0,0);
//	}
//PrintString1("加载完毕\r\n");	
//delay_ms(200);
//delay_ms(200);
//}	
	///*************************JPEG DEMO*****************************/


///**********************字体 DEMO******************************/
void Print_GB2312String //打印GB2312
(
unsigned char Clk //Clk : SPI CLK = System Clock / 2*(Clk+1)
,unsigned char BUS	// 0 : Bus0, 1:Bus1
,unsigned char SCS //0 : use CS0 , 1 : use CS1 , 2 : use CS2, 3 :use CS3 
,unsigned short x //coordinate x for print string
,unsigned short y //coordinate y for print string
,unsigned short X_W //active window width
,unsigned short Y_H //active window height
,unsigned long FontColor //Set Font Color
,unsigned long BackGroundColor //Set Font BackGround Color 
/*Font Color and BackGround Color dataformat :
ColorDepth_8bpp : R3G3B2
ColorDepth_16bpp : R5G6B5
ColorDepth_24bpp : R8G8B8*/
,char tmp2[] //tmp2 : GB2312 Font String which you want print on LCD
)
{

  Select_SFI_Font_Mode();
  CGROM_Select_Genitop_FontROM();
  SPI_Clock_Period(Clk);
  Set_GTFont_Decoder(0x01);      

	Select_SFI_24bit_Address();
	Select_RA8875_SPI_Mode0_and_Mode3();
	Select_SFI_Single_Mode_Dummy_0T_03h();

switch(SCS)	
{
	case 0:
  Select_SFI_0();
	break;
	case 1:
  Select_SFI_1();
	break;
	case 2:
  Select_SFI_2();
	break;
	case 3:
  Select_SFI_3();
	break;
}


switch(BUS)
{
	case 0:
	FONT_DMA_Select_Bus_0();
	break;
	case 1:
	FONT_DMA_Select_Bus_1();
	break;
}


#ifdef MCU_8bit_ColorDepth_8bpp	
  Foreground_color_256(FontColor);
  Background_color_256(BackGroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Foreground_color_65k(FontColor);
  Background_color_65k(BackGroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_16bpp	
  Foreground_color_65k(FontColor);
  Background_color_65k(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
  Text_Mode();
  Active_Window_XY(x,y);
  Active_Window_WH(X_W,Y_H);
  Goto_Text_XY(x,y);
//  sprintf(tmp1,"%s",tmp2); 
//  Show_String(tmp1);
  Show_String(tmp2);
}


void Print_UnicodeString
(
unsigned char Clk //SPI CLK = System Clock / 2*(Clk+1)
,unsigned char BUS	// 0 : Bus0, 1:Bus1
,unsigned char SCS //0 : use CS0 , 1 : use CS1 , 2 : use CS2, 3 :use CS3 
,unsigned short x //Print font start coordinate of X
,unsigned short y //Print font start coordinate of Y
,unsigned short X_W //active window width
,unsigned short Y_H //active window height
,unsigned long FontColor //Set Font Color
,unsigned long BackGroundColor //Set Font BackGround Color 
/*Font Color and BackGround Color dataformat :
ColorDepth_8bpp : R3G3B2
ColorDepth_16bpp : R5G6B5
ColorDepth_24bpp : R8G8B8*/
,unsigned short *tmp2 /*tmp2 : Unicode Font String which you want print on LCD (L"string" in keil c is Unicode string)*/
)
{
  Select_SFI_Font_Mode();
  CGROM_Select_Genitop_FontROM();
  SPI_Clock_Period(Clk);

	Select_SFI_24bit_Address();
	Select_RA8875_SPI_Mode0_and_Mode3();
	Select_SFI_Single_Mode_Dummy_0T_03h();

switch(SCS)	
{
	case 0:
  Select_SFI_0();
	break;
	case 1:
  Select_SFI_1();
	break;
	case 2:
  Select_SFI_2();
	break;
	case 3:
  Select_SFI_3();
	break;
}

switch(BUS)
{
	case 0:
	FONT_DMA_Select_Bus_0();
	break;
	case 1:
	FONT_DMA_Select_Bus_1();
	break;
}

#ifdef MCU_8bit_ColorDepth_8bpp	
  Foreground_color_256(FontColor);
  Background_color_256(BackGroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Foreground_color_65k(FontColor);
  Background_color_65k(BackGroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_16bpp	
  Foreground_color_65k(FontColor);
  Background_color_65k(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Foreground_color_16M(FontColor);
  Background_color_16M(BackGroundColor);
#endif
  Text_Mode();
  Active_Window_XY(x,y);
  Active_Window_WH(X_W,Y_H);
  Goto_Text_XY(x,y);
  while(*tmp2 != '\0')
  {
    if((*tmp2)>0x0020 && (*tmp2)<0x0080)
		{
			/* ASCII Code*/
			Set_GTFont_Decoder(0x21); 
			LCD_CmdWrite(0x04);
			LCD_DataWrite(*tmp2);
			Check_2D_Busy();
		}
    else
		{
			/* Unicode */
	        Set_GTFont_Decoder(0x18);
			LCD_CmdWrite(0x04);
			LCD_DataWrite((*tmp2)>>8); 
            LCD_DataWrite(*tmp2);
            Check_2D_Busy();
      
		}
 	        ++tmp2;
  }
  
  Graphic_Mode(); //back to graphic mode
}





void Select_Font_Height_WxN_HxN_ChromaKey_Alignment                      //选择字体
(
unsigned char Font_Height 
/*Font_Height:
16 : Font = 8x16 、16x16
24 : Font = 12x24、24x24  
32 : Font = 16x32、32x32 */
,unsigned char XxN //XxN :Font Width x 1~4
,unsigned char YxN //YxN :Font Height x 1~4
,unsigned char ChromaKey 
/*ChromaKey :
0 : Font Background color not transparency
1 : Set Font Background color transparency*/
,unsigned char Alignment // 0 : no alignment, 1 : Set font alignment
)
{
	if(Font_Height==16)	Font_Select_8x16_16x16();
	if(Font_Height==24)	Font_Select_12x24_24x24();
	if(Font_Height==32)	Font_Select_16x32_32x32();

	//(*)
	if(XxN==1)	Font_Width_X1();
	if(XxN==2)	Font_Width_X2();
	if(XxN==3)	Font_Width_X3();
	if(XxN==4)	Font_Width_X4();

	//(*)	
	if(YxN==1)	Font_Height_X1();
	if(YxN==2)	Font_Height_X2();
	if(YxN==3)	Font_Height_X3();
	if(YxN==4)	Font_Height_X4();

	//(*)
	if(ChromaKey==0)
	{	Font_Background_select_Color();	}

	if(ChromaKey==1)
	{	Font_Background_select_Original_Canvas();	}

	//(*)
	if(Alignment==0)
	{	Disable_Font_Alignment();	}

	if(Alignment==1)
	{	Enable_Font_Alignment();	}

} 



void Show_String(char *str)
{  
	Check_Mem_WR_FIFO_Empty();
	
	Text_Mode();
	
	LCD_CmdWrite(0x04);
	while(*str != '\0')
	{
		Check_Mem_WR_FIFO_not_Full();  
		LCD_DataWrite(*str);
		++str; 
	} 
	Check_2D_Busy();
	Graphic_Mode(); //back to graphic mode
}

///******************字体 DEMO***********************/





///*****************矩形***********************/
void Draw_Square
(
unsigned long ForegroundColor 
/*ForegroundColor: Set Curve or Curve Fill color. ForegroundColor Color dataformat :
ColorDepth_8bpp : R3G3B2、ColorDepth_16bpp : R5G6B5、ColorDepth_24bpp : R8G8B8*/
,unsigned short X1 //X of point1 coordinate
,unsigned short Y1 //Y of point1 coordinate
,unsigned short X2 //X of point2 coordinate
,unsigned short Y2 //Y of point2 coordinate
)
{
#ifdef MCU_8bit_ColorDepth_8bpp	
  Foreground_color_256(ForegroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Foreground_color_65k(ForegroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Foreground_color_16M(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_16bpp	
  Foreground_color_65k(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Foreground_color_16M(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Foreground_color_16M(ForegroundColor);
#endif
  Square_Start_XY(X1,Y1);
  Square_End_XY(X2,Y2);
  Start_Square();
  Check_2D_Busy(); 
}



void Draw_Square_Fill
(
unsigned long ForegroundColor 
/*ForegroundColor: Set Curve or Curve Fill color. ForegroundColor Color dataformat :
ColorDepth_8bpp : R3G3B2、ColorDepth_16bpp : R5G6B5、ColorDepth_24bpp : R8G8B8*/
,unsigned short X1 //X of point1 coordinate
,unsigned short Y1 //Y of point1 coordinate
,unsigned short X2 //X of point2 coordinate
,unsigned short Y2 //Y of point2 coordinate
)
{
#ifdef MCU_8bit_ColorDepth_8bpp	
  Foreground_color_256(ForegroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_16bpp	
  Foreground_color_65k(ForegroundColor);
#endif
#ifdef MCU_8bit_ColorDepth_24bpp	
  Foreground_color_16M(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_16bpp	
  Foreground_color_65k(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_1	
  Foreground_color_16M(ForegroundColor);
#endif
#ifdef MCU_16bit_ColorDepth_24bpp_Mode_2	
  Foreground_color_16M(ForegroundColor);
#endif
  Square_Start_XY(X1,Y1);
  Square_End_XY(X2,Y2);
  Start_Square_Fill();
  Check_2D_Busy(); 
}

///*****************矩形和线***********************/



