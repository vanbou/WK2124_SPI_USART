#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wk2xxx.h"
#include "wk2xxx_test.h"
#include "spi.h"
#include "exti.h"
#include "stm32f4xx_spi.h"


 int main(void)
 {	
	 
	//wk2xxx相关定义
	u8 irq_flag,gifr;
	 int aaa=0x32;
	 uint8_t rx ;
  unsigned char dat1,dat2,sendbuf[256]={0x2B,0x2B,0x2B },readbuf[256];
	int i,len,scr;
	delay_init(168);	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2，2位相响应，2位抢断
	uart_init(115200);	 //串口初始化为115200
  WK_SPI_Init();//初始化SPI总线
	/*读写GNEA，测试主接口通信是否成功*/
	/*初始化子串口*/
	Wk_Init(1);
	Wk_Init(2);
	Wk_Init(3);
	Wk_Init(4);
	/*设置子串口波特率*/
	Wk_SetBaud(1,B9600);
	Wk_SetBaud(2,B115200);
	Wk_SetBaud(3,B9600);
	Wk_SetBaud(4,B115200);
	wk_TxChars(2,3,sendbuf);
	wk_RxChars(2,readbuf);
	for(i=0;i<10;i++)
	printf("%x",readbuf[i]);
	printf("\n\r\r\n");

while(1)
{
//写数据寄存器，单个数据	
	//WkWriteSReg(4,WK2XXX_FDAT,+++);
	
	wk_TxChars(2,3,sendbuf);
//		wk_RxChars(4,readbuf);
	dat1=WkReadSReg(2,WK2XXX_FDAT);
	printf("%d",dat1);
	printf("\r\n");
	//写FIFO，最大256个字节
	//WkWriteSFifo(4,sendbuf,10);
 // WkReadSFifo(4,readbuf,10);
	
//封装函数
//	wk_TxChars(2,3,sendbuf);
//	wk_RxChars(2,readbuf);
//	for(i=0;i<10;i++)
//	printf("%x",readbuf[i]);
//	printf("\n\r\r\n");
	delay_ms(1000);
}

}
