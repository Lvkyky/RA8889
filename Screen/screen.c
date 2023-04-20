#include "screen.h"
#include "timer.h"
#include "USART.h"
#include "delay.h"
#include "Exti.h"
#include "api.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include  "RA8889.h"
#include  "Button.h"
#include  "Win.h"
#include  "Page.h"
#include  "String.h"
#include  "Stdlib.h"
#include  "Icon.h"
#include  "Fifo.h"
#include  "Input.h"
#include  "StringLabel.h"
#include  "NumLabel.h"
/*************	功能说明	**************
本文件是屏幕的内核，实现了串口屏的寄存器
变量以及命令帧的解释执行。
******************************************/
u8 send[15]; //下发命令帧缓冲区

u8 VerifyFlag=0; 
u8 VerifyFlag1=0; 
u8 RxSwitch=0;//关闭  
u8 first_BYET=1;
u8 first_FIFO=1;
u8 first_FIFOBig=1;
u8 Rxcount=0;
u8 ParticleFlag=0;   //0：小粒度   1：大粒度
u8 RxStatus=0;      //0:空      1满
u8 RxStatusBig=0;      //0:空      1满
u8 CmdExchange=1;


u16 x;
u16 y; 
u8 TouchStatus=Rlease;
u8 TouchDetectSwit=1;//触摸坐标

u8 CmdUpdateFlag=0;
struct CmdType CurentCmd;//当前命令


u8 FileSelect=0xFF;//文件选中标志 0XFF表示未选中


u8 FlushExchange=0; //交替刷新
/******************************寄存器堆************************/
const struct ResType code ResGroup[ResCount]={
{0x03,res_03,2},
{0x05,res_05,1},	
{0x07,res_07,4},	
{0x0B,res_0B,1}	
};

u8 res_03[2];   //页面ID
u8 res_05[1];   //触屏坐标更新标志
u8 res_07[4];   //触摸屏按压坐标值
u8 res_0B[1];   //触摸屏使能位
/************************寄存器堆***********************/



/************************变量堆************************/
const struct MappingType code VarMapTable[VarCount]={
{0x0140,mem_0140,40},	
{0x0603,mem_0603,2},	
{0x0604,mem_0604,2},		
{0x0030,mem_0030,16},		
{0x0038,mem_0038,16},		
{0x0020,mem_0020,2},		
{0x0021,mem_0021,2},		
{0x0022,mem_0022,2},		
{0x0060,mem_0060,2},		
{0x0061,mem_0061,2},		
{0x0062,mem_0062,2},	
{0x00B0,mem_00B0,16},	
{0X0700,mem_0700,2},
///////温度变量/////
{0X0000,mem_0000,2},		
{0X0001,mem_0001,2},		
{0X0006,mem_0006,2},		
{0X0008,mem_0008,2},		
{0X0003,mem_0003,2},		
{0X0004,mem_0004,2},		
{0X0007,mem_0007,2},		
{0X0009,mem_0009,2},

{0X0100,mem_0100,2},	
{0X0101,mem_0101,2},		
{0X0106,mem_0106,2},		
{0X0108,mem_0108,2},

///////MOVE(x,y,z)/////
{0X0073,mem_0073,4},		
{0X0075,mem_0075,4},		
{0X0077,mem_0077,4},

///////MOTOR(x,y,z,e)/////
{0X0011,mem_0011,4},		
{0X0013,mem_0013,4},	
{0X0015,mem_0015,4},		
{0X0017,mem_0017,4},

///////编辑MOTOR(x,y,z,e)/////
{0X0111,mem_0111,4},		
{0X0113,mem_0113,4},	
{0X0115,mem_0115,4},		
{0X0117,mem_0117,4},

//////版本变量//////
{0x0027,mem_0027,4},

//////Fans(YZE)///////
{0X000C,mem_000C,2},		
{0X0071,mem_0071,2},		
{0X0072,mem_0072,2},	
//////Fans Edit///////
{0X010C,mem_010C,2},		
{0X0171,mem_0171,2},
{0X0172,mem_0172,2},
/////预热变量(p1,p2,p3,p4)///////
{0X000F,mem_000F,2},		
{0X0010,mem_0010,2},
{0X0019,mem_0019,2},
{0X001A,mem_001A,2},
/////预热编辑变量(p1,p2,p3,p4)///////
{0X010F,mem_010F,2},		
{0X0110,mem_0110,2},
{0X0119,mem_0119,2},
{0X011A,mem_011A,2},
/////AutoLevel变量//////
{0X0079,mem_0079,2},
{0X007A,mem_007A,2},
/////AutoLevel编辑变量//////
{0X0179,mem_0179,2},
{0X017A,mem_017A,2},
/////文件图标////////
{0X030F,mem_030F,2},		
{0X031F,mem_031F,2},
{0X032F,mem_032F,2},
{0X033F,mem_033F,2},
{0X034F,mem_0344F,2},
{0X035F,mem_0355F,2},
{0X036F,mem_036F,2},

{0x0024,mem_0024,5},//打印时间
{0x0023,mem_0023,2},//百分比	

{0X000B,mem_000B,2},
{0X000C,mem_000C,2},
{0X000D,mem_000D,2},

{0X010B,mem_010B,2},
{0X010C,mem_010C,2},
{0X010D,mem_010D,2}
};

u8 mem_0140[40];
u8 mem_0603[2];  //弹窗变量
u8 mem_0604[2];  //信息弹窗时间
u8 mem_0030[16];
u8 mem_0038[16];
u8 mem_0020[2];
u8 mem_0021[2];
u8 mem_0022[2];
u8 mem_0060[2];
u8 mem_0061[2];
u8 mem_0062[2];
u8 mem_00B0[16];
u8 mem_0700[2];  //cmd

u8 mem_0000[2];
u8 mem_0001[2];
u8 mem_0006[2];
u8 mem_0008[2];
u8 mem_0003[2];
u8 mem_0004[2];
u8 mem_0007[2];
u8 mem_0009[2];//温度变量

u8 mem_0100[2];
u8 mem_0101[2];
u8 mem_0106[2];
u8 mem_0108[2];//编辑并返回的温度变量



u8 mem_0011[4];
u8 mem_0013[4];
u8 mem_0015[4];
u8 mem_0017[4];//电机参数X,Y,Z，E   

u8 mem_0027[4];//版本信息


u8 mem_0111[4];//电机参数X,Y,Z，E    
u8 mem_0113[4];//Y
u8 mem_0115[4];//Z
u8 mem_0117[4];//E



u8 mem_000C[2];//Y 风扇参数
u8 mem_0071[2];//Z
u8 mem_0072[2];//E

u8 mem_010C[2];//Y 风扇参数
u8 mem_0171[2];//Z
u8 mem_0172[2];//E

u8 mem_001A[2];//预热
u8 mem_0010[2];
u8 mem_0019[2];
u8 mem_000F[2];

u8 mem_011A[2];//预热(编辑)
u8 mem_0110[2];
u8 mem_0119[2];
u8 mem_010F[2];


u8 mem_0073[4];//Move(x,y,z)
u8 mem_0075[4];
u8 mem_0077[4];

u8 mem_0079[2];//AutoLevel(al1 al2)
u8 mem_007A[2];

u8 mem_0179[2];//AutoLevel(al1 al2)编辑
u8 mem_017A[2];


u8 mem_030F[2];//文件图标变量
u8 mem_031F[2];
u8 mem_032F[2];
u8 mem_033F[2];
u8 mem_0344F[2];
u8 mem_035F[2];
u8 mem_0355F[2];
u8 mem_036F[2];


u8 mem_0024[5];//打印时间
u8 mem_0023[2];//百分比


u8 mem_000B[2];//打印速度
u8 mem_000C[2];//Flow rate
u8 mem_000D[2];//冷却速度

u8 mem_010B[2];
u8 mem_010C[2];
u8 mem_010D[2];

u8 mem_0021[2];
/*********************变量堆**********************/



/**************************内核函数*******************************/
//===============================================
// 函数: Cmd_receive1()
// 描述: 接受命令到缓冲区
// 参数:串口硬件缓冲
// 版本: V1.0, 2021-6-16
//===============================================
void CmdReceive1(u8 SBUF)
{	
	if(VerifyFlag1==1)
	{
		RxSwitch=1;//打开接收开关
		Rxcount=(SBUF+1);//要接收的字节
		COM2.RX_Cnt=0;//清零接收计数
		VerifyFlag1=0;//
		if(Rxcount<10)						
		{	
			ParticleFlag=0;
			if(first_FIFO==1) first_FIFO=0;
			else
			{
				if((RX2_Buffer_FIFO.head+1)%FIFO_Length!=RX2_Buffer_FIFO.tail)//缓冲区未满
				{
					RX2_Buffer_FIFO.head=(RX2_Buffer_FIFO.head+1)%FIFO_Length;//分配下一个缓冲区
				}
				else
				{
					PrintString1("小粒度缓冲区溢出\r\n");
				}	
			}
			RxStatus=0;
		}
		else
		{	
			ParticleFlag=1;
			if(first_FIFOBig==1) first_FIFOBig=0;
			else
			{
				if((RX2_Buffer_FIFOBig.head+1)%FIFO_LengthBig!=RX2_Buffer_FIFOBig.tail)//缓冲区未满
				{
					RX2_Buffer_FIFOBig.head=(RX2_Buffer_FIFOBig.head+1)%FIFO_LengthBig;//分配下一个缓冲区
				}
				else
				{
					PrintString1("大粒度缓冲区溢出\r\n");
				}	
			}
			RxStatusBig=0;
		}	
	}	
	
	if(VerifyFlag==1) 
	{
		if(SBUF==0xA5)//A5验证
		{
			VerifyFlag1=1;
		}
		VerifyFlag=0;
	}
	if(SBUF==0x5A) //5A验证
	{
		VerifyFlag=1;
	}
	
	if(RxSwitch==1)//命令帧接收
	{	
		if(ParticleFlag==0)
		{
			if(Rxcount>0) 
			{
				RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.head][COM2.RX_Cnt++]=SBUF;
				Rxcount--;	
			}
			if(Rxcount==0)
			{	
				RxSwitch=0;
				RxStatus=1;
			}	
		}
		else if(ParticleFlag==1)
		{
			if(Rxcount>0) 
			{
				RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.head][COM2.RX_Cnt++]=SBUF;
				Rxcount--;	
			}
			if(Rxcount==0)
			{	
				RxSwitch=0;
				RxStatusBig=1;
			}	
		}
	}	
}



//===============================================
// 函数: CmdUpdate()
// 描述: 从接收缓冲队列中取一条指令更新当前指令
// 参数:接收到的数据
// 版本: V1.0, 2021-6-10
//===============================================
void UpdateCmd()
{
	if(Page_Name==MainUdisk||Page_Name==UdiskNext||Page_Name==UdiskBoth||Page_Name==UdiskLast||Page_Name==UdiskOne||
		Page_Name==UdiskNextUp||Page_Name==UdiskBothUp||Page_Name==UdiskLastUp||Page_Name==UdiskOneUp)
	{
		CmdExchange=1;//大缓冲区优先	
	}
	else if(Page_Name==PrintPause||Page_Name==Print)
	{
			CmdExchange=0;//小缓冲区优先
	}
	
	if(CmdExchange==1)                                         															
	{	
		CmdExchange=0;
		if(DeQueueBig()==0) DeQueue();
	}
	else
	{
		CmdExchange=1;
		if(DeQueue()==0) DeQueueBig();
	}
}


//===============================================
//名字：VaddrtoPaddrRes
//功能：由虚拟寄存器地址得到寄存器实际地址
//参数：寄存器虚拟地址
//返回值：寄存器物理地址
//===============================================
u8* VaddrtoPaddrRes(u8 ResAddress)        
{
	u8 index;
	for(index=0;index<ResCount;index++)
	{   
		if(ResAddress==ResGroup[index].ResAddr)  break;
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Res address\r\n");
		return NULL;;
	}
	else
	{
		return ResGroup[index].p;
	}
}


//===============================================
//名字：VaddrtoPaddrVar()
//功能：由虚拟变量地址到实际变量地址的转换
//参数：虚拟变量地址
//返回值：实际变量地址
//===============================================
u8 *VaddrtoPaddrVar( u16 Vaddr)  
{
	u8 index;
	for(index=0;index<VarCount;index++)
	{
		if(Vaddr==VarMapTable[index].VarAddress) break;  
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Var address\r\n");
		return NULL;
	}
	else
	{
		return VarMapTable[index].p;
	}	
}


//===============================================
//名字：VaddrtoCountVar
//功能：由虚拟变量地址到实际内存地址的转换
//参数：虚拟变量地址
//返回值：实际变量地址内存大小
//===============================================
u8 VaddrtoCountVar(u16 Vaddr)
{
	u8 index;
	for(index=0;index<VarCount;index++)
	{
		if(Vaddr==VarMapTable[index].VarAddress) break;  
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Var address\r\n");
		return NULL;
	}
	else
	{
		return VarMapTable[index].Size;
	}	
}



//===============================================
//名字：Send_Mesg_res()
//功能：下发寄存器信息
//参数：寄存器地址，寄存器数据长度
//返回值：无
//===============================================
void Send_Mesg_res(u8 res_address,u8 data_length_r)      
{
	u8 j;
	u8 *DataPointer;
	DataPointer=VaddrtoPaddrRes(res_address);
	if(DataPointer==NULL)
	{
		PrintString1("无效的地址寄存器下发失败\r\n");
		return;	
	}	
	send[0]=0x5A;
	send[1]=0xA5;
	send[2]=0x03+data_length_r; //数据长度
	send[3]=0x81; //指令
	send[4]=res_address;//寄存器地址
	send[5]=data_length_r; //读取字节长度								
	for(j=0;j<data_length_r;j++)
	{
		send[j+6]=DataPointer[j]; 			 
	} 
	for(j=0;j<data_length_r+0x06;j++)
	{
		TX2_write2buff(send[j]);
	}								
}



//===============================================
//名字：Send_Mesg_var()
//功能：下发变量信息
//参数：变量地址，变量地址长度
//返回值：无
//===============================================
void Send_Mesg_var(u16 var_addres,u8 data_length_r )    
{
	u8 j;
	u8 T;
	u8 *DataPointer;
	DataPointer=VaddrtoPaddrVar(var_addres);
	if(DataPointer==NULL)
	{
		PrintString1("无效的地址变量下发失败\r\n");
		return;	
	}
	
	
	send[0]=0x5A;
	send[1]=0xA5;
	send[2]=0x04+data_length_r*2; //数据长度
	send[3]=0x83; //指令
	send[4]=(var_addres>>8)&0x00FF;//寄存器地址高位
	send[5]=var_addres&0x00FF;//寄存器地址低位
	send[6]=data_length_r;  
	T=data_length_r*2;
	for(j=0;j<T;j++)
	{
		send[7+j]=DataPointer[j];		
	}
	T=data_length_r*2+7;
	for(j=0;j<T;j++)
	{
		TX2_write2buff(send[j]);   //发给MASTER   
	}
}





//===============================================
//名字Update_var_res
//功能:利用当前指令更新寄存器和变量的值
//参数：命令
//返回值：无
//===============================================
void Update_var_res()
{
	u8	j;
	u8 str[8];
	u8 res_address;
	u16 var_addres;
	u8 *DataPointer;
	switch(CurentCmd.Cmd)
	{
		case 0x80: 
		{ 				
			res_address=CurentCmd.Addr&0x00FF;
			DataPointer=VaddrtoPaddrRes(res_address); //得到寄存器索引	
			if(DataPointer==NULL)
			{
				PrintString1("无效的地址不进行寄存器更新\r\n");
			}
			else
			{
				for(j=0;j<CurentCmd.ByteSize;j++)//写入数据;
				{
					DataPointer[j]=CurentCmd.Data[j];   
				} 	
			}	
			break;
		 }    
					 
		case 0x82: 
		 {     
			var_addres=(0x00FF&(CurentCmd.Addr>>8));  
			var_addres=var_addres<<8;						 
			var_addres=(var_addres&0xFF00);
			var_addres|=(0x00FF&CurentCmd.Addr);	 
			DataPointer=VaddrtoPaddrVar(var_addres); //得到变量索引	
			if(DataPointer==NULL)
			{	
				Select_Font_Height_WxN_HxN_ChromaKey_Alignment(16,1,1,0,0);	
				switch(var_addres)
				{		
					case 0x6000://直接写向缓存
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*0+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*0+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6100:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*1+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*1+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6200:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*2+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*2+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6300:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*3+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*3+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6400:
					{	BTE_Solid_Fill(0,canvas_image_width,480,(40*4+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*4+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6500:
					{	BTE_Solid_Fill(0,canvas_image_width,480,(40*5+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*5+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6600:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*6+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*6+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					default:
					{
						PrintString1("无效的地址不进行变量更新\r\n");
						break;
					}
				}
			}
			else
			{	
				for(j=0;j<CurentCmd.ByteSize;j++)
				{
					DataPointer[j]=CurentCmd.Data[j];  // 写入数据;			
				}
			}
			break;
		 } 
		default:
		{
			PrintString1("未能识别的指令\r\n");
			break;
		}
	}
}



//===============================================
//名字：Return_var_res
//功能:返回要读取的寄存器和变量的值
//参数：命令
//返回值：无
//===============================================
void Return_var_res()
{
	u8 res_address;
	u16 var_addres;  
	switch(CurentCmd.Cmd)
	{
		case 0x81://返回要读取的寄存器值
		 { 						     		
			res_address=CurentCmd.Addr&0x00FF;		
			Send_Mesg_res(res_address,CurentCmd.ByteSize);  
			break;
		 }    
											 
		case 0x83: //返回要读取的变量的值
		 {					 
			var_addres=(CurentCmd.Addr>>8)&0X00FF;   
			var_addres=var_addres<<8;						 
			var_addres=var_addres&0xFF00;
			var_addres|=CurentCmd.Addr&0X00FF;				  						 
			Send_Mesg_var(var_addres,CurentCmd.ByteSize);
			break;
		 }                                                       									 
	}
}



//===============================================
//名字：ImediaFlushScreen
//功能:对页面，弹窗等需要立即刷新的元素进行刷新
//参数：页面名称
//返回值：无
//===============================================         
void ImediaFlushScreen(u8 PageName)
{
	u16 PageId;
	u8 res_address;	
	u16 var_addres;
	u8  *DataPointer;
	u8 str[4];
	PageId=res_03[0];
	PageId =PageId<<8;
	PageId|=res_03[1];
	switch(CurentCmd.Cmd)
	{
		case 0x80:              
		 {   
			res_address=(CurentCmd.Addr&0x00FF);	
			switch(res_address)                  
			{
				case 0x03://切换页面
				{ 		   		
//					PrintString1("page_shift(u8 ID):");		
//					PrintString1(u8_to_str_hex(res_03[0],str));
//					PrintString1(u8_to_str_hex(res_03[1],str));			
//					PrintString1("\r\n");
//					PrintString1("");
					WindowOff(CurentWin);
					InputOff(CurrentInput);
					PageShift(PageName);			
					FileNameFlush(PageName);//文件名字刷新
					FileIconFlush(PageName);//文件图标刷新
					NumLabelFlush(PageName);
					StringLabelFlush(PageName);
				}
				
				case 0x0B: //打开触控
				{
					PrintString1("open_touch(void);\r\n");	
					break;
				}
				
				default:
				{
					PrintString1("触控坐标寄存器被重写\r\n");	
					PrintString1("触控更新标志被重置\r\n");	
					break;
				}
			} 
			break;
		}   
							 
			case 0x82:                
			 {
				  var_addres=(CurentCmd.Addr>>8)&0X00FF;   
				  var_addres=var_addres<<8;						 
				  var_addres=var_addres&0xFF00;
				  var_addres|=(CurentCmd.Addr&0X00FF);
				  DataPointer=VaddrtoPaddrVar(var_addres); //得到变量索引		  
				  if(var_addres==0x0603)
				  {	    
					  WinFlush(PageName);				  
				  }
				  break;
			 }			  					
	}
}	 
/**********************内核函数**************************/








/*********************屏幕刷新函数**********************/


//============================================
// 函数: WinFlush()
// 描述: 窗体刷新函数
// 返回: 无
// 版本: V1.0, 2021-6-17
//============================================
void WinFlush(u8 PageName)
{
	u8 Index;
	u16 M0603;
	M0603=mem_0603[0];
	M0603 =M0603<<8;
	M0603|=mem_0603[1];
	if(M0603==0x00)
	{	
		WindowOff(CurentWin);
	}
	else
	{
		for(Index=0;Index<Wincount;Index++)
		{
			if(WinGroup[Index].PageName==PageName&&M0603==WinGroup[Index].Addr)break;
		}
		if(Index==Wincount||Index>Wincount) PrintString1("无效的弹窗\r\n");
		else
		{	PrintString1("创建弹窗\r\n");	
			WindowOn(WinGroup[Index].Name);
		}
	}
}




//============================================
// 函数: FileNameFlush()
// 描述: 对文件名字进行刷新
// 参数:当前页面
// 返回: 无
// 版本: V1.0, 2021-6-23
//============================================
void FileNameFlush(u8 PageName)
{		
	if(PageName==UdiskOne||PageName==UdiskNext||PageName==UdiskBoth||PageName==UdiskLast||
		PageName==UdiskNextUp||PageName==UdiskBothUp||PageName==UdiskLastUp||PageName==UdiskOneUp)   
	{		
		BTE_Memory_Copy(0,canvas_image_width,480,544,0,canvas_image_width,480,544,0,canvas_image_width,30,0,12,380,272);
	}
	else if(PageName==PrintConfirm)
	{	
		if(FileSelect==0xFF) 
		{
			
		}
		else
		{
			BTE_Memory_Copy(0,canvas_image_width,480,(544+40*FileSelect),0,canvas_image_width,480,(544+40*FileSelect),0,canvas_image_width,40,120,12,380,16);
			FileSelect=0xFF;
		}
	}
}



	
	


