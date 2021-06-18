#include "delay.h"
#include "wk2xxx.h"
#include "sys.h"
#include "usart.h"
#include "wk2xxx_test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
/*wk芯片的自发自收测试*/
u8 wk_test1(u8 port)
{
	int num,i;
	u8 err=0,dat,dat1;
	/*读写GNEA，测试主接口通信是否成功*/
	dat1=WkReadGReg(WK2XXX_GENA);
	printf("gena=0x%x.\n",dat1);
	/*根据主接口选择不同，读出的寄存器默认值不一样*/
	WkWriteGReg(WK2XXX_GENA,0x05);
	dat1=WkReadGReg(WK2XXX_GENA);
	printf("gena1=0x%x.\n",dat1);
	WkWriteGReg(WK2XXX_GENA,0x0);
	Wk_Init(port);
	Wk_SetBaud(port,B9600);

	for(i=0;i<=255;i++)
		{
			WkWriteSReg(port,WK2XXX_FDAT,i);

		}
		delay_ms(100);
	for(i=0;i<=255;i++)
		{  
			 dat=WkReadSReg(port,WK2XXX_FDAT);
				if(dat!=i)
				{ 
					printf("port:%d;dat1=0x%x.i=0x%x!!\n",port,dat,i);
					err=1;
			  }
		}
		
	 if(err)
	 {
		 printf("port:%d tset fail!!\n",port);
		 while(1);
	 }
	 else
		 printf("port:%d test success!!\n",port);
	 
	 Wk_DeInit(port);
	 return err;
	 
	 
}
/*常用寄存器值的打印*/
void wk_test2(u8 port)
{
	u8 dat1,dat2,dat3,dat4;
	
		dat1=WkReadGReg(WK2XXX_GENA);
	dat2=WkReadGReg(WK2XXX_GIER);
  printf("%x",dat1);
	printf("\n\r\r\n");
	printf("%x",dat2);
	printf("\n\r\r\n");
	/*根据主接口选择不同，读出的寄存器默认值不一样*/
	WkWriteGReg(WK2XXX_GENA,0x05);
	WkWriteGReg(WK2XXX_GIER,0x05);
  dat1=WkReadGReg(WK2XXX_GENA);
	dat2=WkReadGReg(WK2XXX_GIER);
  printf("%x",dat1);
	printf("\n\r\r\n");
	printf("%x",dat2);
	printf("\n\r\r\n");
  WkWriteGReg(WK2XXX_GENA,0x00);
	dat1=WkReadGReg(WK2XXX_GENA);
  printf("%x",dat1);
	printf("\n\r\r\n");
	
	
	dat1=WkReadGReg(WK2XXX_GENA);
	dat2=WkReadGReg(WK2XXX_GRST);
	dat3=WkReadGReg(WK2XXX_GIER);
	dat4=WkReadGReg(WK2XXX_GIFR);
	printf("GENA=0x%x.GRST=0x%x;GIER=0x%x.GIFR=0x%x.!!\n",dat1,dat2,dat3,dat4);
	dat1=WkReadSReg(port,WK2XXX_SPAGE);
	dat2=WkReadSReg(port,WK2XXX_SCR);
	dat3=WkReadSReg(port,WK2XXX_LCR);
	dat4=WkReadSReg(port,WK2XXX_FCR);
	printf("SPAGE=0x%x.SCR=0x%x;LCR=0x%x.FCR=0x%x.!!\n",dat1,dat2,dat3,dat4);
	dat1=WkReadSReg(port,WK2XXX_SIER);
	dat2=WkReadSReg(port,WK2XXX_SIFR);
	dat3=WkReadSReg(port,WK2XXX_FSR);
	dat4=WkReadSReg(port,WK2XXX_FWCR);
	printf("SIER=0x%x.SIFR=0x%x;FSR=0x%x.FWCR=0x%x.!!\n",dat1,dat2,dat3,dat4);
	
	WkWriteSReg(port,WK2XXX_SPAGE,1);
	dat1=WkReadSReg(port,WK2XXX_BAUD1);
	dat2=WkReadSReg(port,WK2XXX_BAUD0);
	dat3=WkReadSReg(port,WK2XXX_PRES);
	WkWriteSReg(port,WK2XXX_SPAGE,0);
	printf("BAUD1=0x%x.BAUD0=0x%x;PRES=0x%x.!!\n",dat1,dat2,dat3);
		
}

