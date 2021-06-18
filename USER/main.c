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
	 
	//wk2xxx��ض���
	u8 irq_flag,gifr;
	 int aaa=0x32;
	 uint8_t rx ;
  unsigned char dat1,dat2,sendbuf[256]={0x2B,0x2B,0x2B },readbuf[256];
	int i,len,scr;
	delay_init(168);	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2��2λ����Ӧ��2λ����
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
  WK_SPI_Init();//��ʼ��SPI����
	/*��дGNEA���������ӿ�ͨ���Ƿ�ɹ�*/
	/*��ʼ���Ӵ���*/
	Wk_Init(1);
	Wk_Init(2);
	Wk_Init(3);
	Wk_Init(4);
	/*�����Ӵ��ڲ�����*/
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
//д���ݼĴ�������������	
	//WkWriteSReg(4,WK2XXX_FDAT,+++);
	
	wk_TxChars(2,3,sendbuf);
//		wk_RxChars(4,readbuf);
	dat1=WkReadSReg(2,WK2XXX_FDAT);
	printf("%d",dat1);
	printf("\r\n");
	//дFIFO�����256���ֽ�
	//WkWriteSFifo(4,sendbuf,10);
 // WkReadSFifo(4,readbuf,10);
	
//��װ����
//	wk_TxChars(2,3,sendbuf);
//	wk_RxChars(2,readbuf);
//	for(i=0;i<10;i++)
//	printf("%x",readbuf[i]);
//	printf("\n\r\r\n");
	delay_ms(1000);
}

}
