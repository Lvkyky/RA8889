#ifndef __FIFO_H
#define __FIFO_H
#include "STC15Fxxxx.H"

#define FIFO_Length   25
#define Buffer_Length 10

#define FIFO_LengthBig   5
#define Buffer_LengthBig 80

struct Buffer_FIFO
{ 
	u8	head;		//串口号
	u8	tail;		//发送读指针
	u8  dataa[FIFO_Length][Buffer_Length];  //接收缓冲队列
}; 



struct Buffer_FIFOBig
{ 
	u8	head;
	u8	tail;		
	u8  dataa[FIFO_LengthBig][Buffer_LengthBig];  //接收缓冲队列
}; 




extern struct Buffer_FIFO RX2_Buffer_FIFO; 	
extern struct Buffer_FIFOBig RX2_Buffer_FIFOBig; 



void QueueInit();
u8 DeQueueBig();
u8 DeQueue();
#endif
