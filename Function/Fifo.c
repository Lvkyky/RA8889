#include "Fifo.h"
#include "screen.h"
#include "USART.h"

struct Buffer_FIFO RX2_Buffer_FIFO; 
struct Buffer_FIFOBig RX2_Buffer_FIFOBig; 

//===============================================
// 函数: QueueInit()
// 描述: 接收队列初始化
// 参数:无
// 版本: V1.0, 2021-6-26
//===============================================
void QueueInit()
{
	u8 i,j;
	RX2_Buffer_FIFO.head=0;
	RX2_Buffer_FIFO.tail=0;//空
	
	RX2_Buffer_FIFOBig.head=0;
	RX2_Buffer_FIFOBig.tail=0;
	for(i=0;i<(FIFO_Length-1);i++)	
	{
		for(j=0;j<(Buffer_Length-1);j++)
		{
			RX2_Buffer_FIFO.dataa[i][j]=0;
		}
	}
	
	for(i=0;i<(FIFO_LengthBig-1);i++)	
	{
		for(j=0;j<(Buffer_LengthBig-1);j++)
		{
			RX2_Buffer_FIFOBig.dataa[i][j]=0;
		}
	}
}


//===============================================
// 函数: DeQueue()
// 描述: 小缓冲队列出队伍
// 参数:无
// 版本: V1.0, 2021-6-26
//===============================================
u8 DeQueue()
{	
	u8 DataLength;
	u8 j;	
	if(RX2_Buffer_FIFO.head!=RX2_Buffer_FIFO.tail)//小粒度缓冲区
	{ 
		DataLength=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][0];
		CurentCmd.Cmd=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][1];
		switch(CurentCmd.Cmd)
		{
			case 0x80:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.ByteSize=DataLength-2;
				for(j=0;j<DataLength-2;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][j+3];  						
				} 
				break;
			}		
			case 0x81:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.ByteSize=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3]; 
				break;
			}
			case 0x82:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3];
				CurentCmd.ByteSize=DataLength-3;//要写入的字节长度
				for(j=0;j<DataLength-3;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][j+4];   
				}

				break;
			}
			case 0x83:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3];
				CurentCmd.ByteSize=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][4];//要读取的字长度 
				break;
			}
			
			default :
			{	
				#ifdef Debug	
				PrintString1("无法识别的指令\r\n");
				#endif
				RX2_Buffer_FIFO.tail=(RX2_Buffer_FIFO.tail+1)%FIFO_Length;//本条命令周期完成
				return 0;
			}
		}		
		CmdUpdateFlag=1;
		RX2_Buffer_FIFO.tail=(RX2_Buffer_FIFO.tail+1)%FIFO_Length;//本条命令周期完成
		return 1;
	}
	else if((RX2_Buffer_FIFO.head==RX2_Buffer_FIFO.tail)&&RxStatus==1)
	{
		DataLength=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][0];
		CurentCmd.Cmd=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][1];
		switch(CurentCmd.Cmd)
		{
			case 0x80:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.ByteSize=DataLength-2;
				for(j=0;j<DataLength-2;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][j+3];  						
				} 
				break;
			}		
			case 0x81:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.ByteSize=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3]; 
				break;
			}
			case 0x82:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3];
				CurentCmd.ByteSize=DataLength-3;//要写入的字节长度
				for(j=0;j<DataLength-3;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][j+4];   
				}
				break;
			}
			case 0x83:
			{
				CurentCmd.Addr=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][3];
				CurentCmd.ByteSize=RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.tail][4];//要读取的字长度 
				break;
			}		
			default :
			{	
				#ifdef Debug	
				PrintString1("无法识别的指令\r\n");
				#endif
				RxStatus=0;//本条命令周期完成
				first_FIFO=1;
				return 0;
			}
		}		
		CmdUpdateFlag=1;
		RxStatus=0;//本条命令周期完成
		first_FIFO=1;
		return 1;
	}
	else
	{
	  return 0;
	}
}

//===============================================
// 函数: DeQueueBig()
// 描述: 大缓冲队列出队伍
// 参数:无
// 版本: V1.0, 2021-6-26
//===============================================
u8 DeQueueBig()
{	
	u8 DataLength;
	u8 j;		
	if(RX2_Buffer_FIFOBig.head!=RX2_Buffer_FIFOBig.tail)//大粒度缓冲区    RxStatusBig
	{
		DataLength=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][0];
		CurentCmd.Cmd=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][1];
		switch(CurentCmd.Cmd)
		{
			case 0x80:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.ByteSize=DataLength-2;
				for(j=0;j<DataLength-2;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][j+3];  						
				} 
				break;
			}		
			case 0x81:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.ByteSize=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3]; 
				break;
			}
			case 0x82:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3];
				CurentCmd.ByteSize=DataLength-3;//要写入的字节长度
				for(j=0;j<DataLength-3;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][j+4];   
				}
				break;
			}
			case 0x83:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3];
				CurentCmd.ByteSize=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][4];//要读取的字长度 
				break;
			}
			
			default :
			{	
				#ifdef Debug	
				PrintString1("无法识别的指令\r\n");
				#endif
				RX2_Buffer_FIFOBig.tail=(RX2_Buffer_FIFOBig.tail+1)%FIFO_LengthBig;//本条命令周期完成
				return 0;
			}
		}		
		CmdUpdateFlag=1;
		RX2_Buffer_FIFOBig.tail=(RX2_Buffer_FIFOBig.tail+1)%FIFO_LengthBig;//本条命令周期完成
		return 1;
	}

	else if((RX2_Buffer_FIFOBig.head==RX2_Buffer_FIFOBig.tail)&&RxStatusBig==1)//大粒度缓冲区    RxStatusBig{}
	{
		DataLength=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][0];
		CurentCmd.Cmd=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][1];
		switch(CurentCmd.Cmd)
		{
			case 0x80:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.ByteSize=DataLength-2;
				for(j=0;j<DataLength-2;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][j+3];  						
				} 
				break;
			}		
			case 0x81:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.ByteSize=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3]; 
				break;
			}
			case 0x82:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3];
				CurentCmd.ByteSize=DataLength-3;//要写入的字节长度
				for(j=0;j<DataLength-3;j++)
				{
					CurentCmd.Data[j]=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][j+4];   
				}
				break;
			}
			case 0x83:
			{
				CurentCmd.Addr=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][2];
				CurentCmd.Addr=CurentCmd.Addr<<8;
				CurentCmd.Addr=CurentCmd.Addr&0xFF00;
				CurentCmd.Addr=CurentCmd.Addr^RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][3];
				CurentCmd.ByteSize=RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.tail][4];//要读取的字长度 
				break;
			}
			
			default :
			{	
				#ifdef Debug	
				PrintString1("无法识别的指令\r\n");
				#endif
				first_FIFOBig=1;
				RxStatusBig=0;//本条命令周期完成
				return 0;
			}
		}		
		CmdUpdateFlag=1;
		first_FIFOBig=1;
		RxStatusBig=0;//本条命令周期完成
		return 1;
	}
	else
	{
		return 0;
	}
}
		




