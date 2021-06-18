#include "wk2xxx.h"
#include "delay.h"
#include "spi.h"


/**************************************WK_RstInit***********************************/
//��������:wkоƬ��Ҫ��MCU��GPIOȥ����RST���ţ�������ͨ��stm32��A4��������WK��RST����
//��ʼ��STM32��A4���š�
//      
//*************************************************************************/


/***************************WkWriteGReg***********************************/
//�������ܣ�дȫ�ּĴ���������ǰ���ǸüĴ�����д��
//ĳЩ�Ĵ��������д1�����ܻ��Զ���1������������ֲ�)
//������
//      greg:Ϊȫ�ּĴ����ĵ�ַ
//      dat:Ϊд��Ĵ���������
//***********************************************************************/
void WkWriteGReg(unsigned char greg,unsigned char dat)
{	 u8 cmd;
	 cmd=0|greg;
	 SPI_CS_L();//����cs�ź�
	 SPI1_ReadWriteByte(cmd);	//дָ�����ָ��Ĺ��ɼ������ֲ�
	 SPI1_ReadWriteByte(dat);//д����
   SPI_CS_H();//����cs�ź�
}
/****************************WkReadGReg***********************************/
//�������ܣ���ȫ�ּĴ���
//������
//      greg:Ϊȫ�ּĴ����ĵ�ַ
//      rec:���صļĴ���ֵ
//***********************************************************************/
u8 WkReadGReg(unsigned char greg)
{	 u8 cmd,rec;
	 cmd=0x40|greg;
	 SPI_CS_L();//����cs�ź�
	 SPI1_ReadWriteByte(cmd);	//дָ�����ָ��Ĺ��ɼ������ֲ�
	 rec=SPI1_ReadWriteByte(0);//д����
   SPI_CS_H();//����cs�ź�							
	 return rec;
}

/**************************WkWriteSReg***********************************/
//��������:
//������port:Ϊ�Ӵ���
//      sreg:Ϊ�Ӵ��ڼĴ���
//      dat:Ϊд��Ĵ���������
//ע�⣺���Ӵ��ڱ���ͨ������£���FDATд������ݻ�ͨ��TX�������
//**********************************************************************/
void WkWriteSReg(u8 port,u8 sreg,u8 dat)
{	 u8 cmd;
	 cmd=0x0|((port-1)<<4)|sreg;
	 SPI_CS_L();//����cs�ź�
	 SPI1_ReadWriteByte(cmd);	//дָ�����ָ��Ĺ��ɼ������ֲ�
	 SPI1_ReadWriteByte(dat);//д����
   SPI_CS_H();//����cs�ź�
}

/**************************WkReadSReg***********************************/
//�������ܣ����Ӵ��ڼĴ���
//������portΪ�Ӵ��ڶ˿ں�
//      sreg:Ϊ�Ӵ��ڼĴ�����ַ
//      rec:���صļĴ���ֵ
//**********************************************************************/
u8 WkReadSReg(u8 port,u8 sreg)
{	 u8 cmd,rec;
	 cmd=0x40|((port-1)<<4)|sreg;
	 SPI_CS_L();//����cs�ź�
	 SPI1_ReadWriteByte(cmd);	//дָ�����ָ��Ĺ��ɼ������ֲ�
	 rec=SPI1_ReadWriteByte(0);//д����
   SPI_CS_H();	//����cs�ź�							
	 return rec;
}
/************************WkWriteSFifo***********************************/
//��������:���Ӵ���fifoд����Ҫ���͵�����
//������port:Ϊ�Ӵ���
//      *dat:д������
//      num��Ϊд�����ݵĸ��������β�����256
//ע�⣺ͨ���÷�ʽд������ݣ���ֱ��д���Ӵ��ڵĻ���FIFO��Ȼ�󱻷���
//*********************************************************************/
void WkWriteSFifo(u8 port,u8 *dat,int num)
{	 
	 u8 cmd;
	 int i;
	 cmd=0x80|((port-1)<<4);
	 if(num>0)
	 {
			 SPI_CS_L();//����cs�ź�
			 SPI1_ReadWriteByte(cmd); //дָ��,����ָ��ɼ������ֲ�
			 for(i=0;i<num;i++)
			 {
				 SPI1_ReadWriteByte( *(dat+i));//д����
			 }
			 SPI_CS_H();//����cs�ź�
   }
}

/************************WkReadSFifo***********************************/
//��������:���Ӵ��ڵ�fifo�ж������յ�������
//������port:Ϊ�Ӵ���
//      *rec�����յ�������
//      num�����������ݸ�����
//ע�⣺ͨ���÷�ʽ�����Ӵ��ڻ����е����ݡ����β��ܳ���256
//*********************************************************************/
void WkReadSFifo(u8 port,u8 *rec,int num)
{
		u8 cmd;
		int n;
	  cmd=0xc0|((port-1)<<4);
		if(num>0)
		{
				SPI_CS_L();//����cs�ź�
				SPI1_ReadWriteByte(cmd);
				for(n=0;n<num;n++)
				{	
					*(rec+n)=SPI1_ReadWriteByte(0);	
				}
				SPI_CS_H();//����cs�ź�
	  }
}


/*******WkInit*******************************************/
//�������ܣ���ʼ���Ӵ���
/*******************************************************/
void Wk_Init(u8 port)
{
    u8 gena,grst,gier,sier,scr;
		//ʹ���Ӵ���ʱ��
    gena=WkReadGReg(WK2XXX_GENA);
		gena=gena|(1<<(port-1));
		WkWriteGReg(WK2XXX_GENA,gena);
		//�����λ�Ӵ���
		grst=WkReadGReg(WK2XXX_GRST);
		grst=grst|(1<<(port-1));
		WkWriteGReg(WK2XXX_GRST,grst);
		//ʹ�ܴ������ж�
		gier=WkReadGReg(WK2XXX_GIER);
		gier=gier|(1<<(port-1));
		WkWriteGReg(WK2XXX_GIER,gier);
	  //ʹ���Ӵ��ڽ��մ����жϺͳ�ʱ�ж�
	  sier=WkReadSReg(port,WK2XXX_SIER); 
	  sier |= WK2XXX_RFTRIG_IEN|WK2XXX_RXOUT_IEN;
	  WkWriteSReg(port,WK2XXX_SIER,sier);
	  //��ʼ��FIFO�����ù̶��жϴ���
	  WkWriteSReg(port,WK2XXX_FCR,0XFF);  
	  //���������жϴ��㣬��������������Ч��
	  //��ô����FCR�Ĵ����жϵĹ̶��жϴ��㽫ʧЧ
	  WkWriteSReg(port,WK2XXX_SPAGE,1);//�л���page1
	  WkWriteSReg(port,WK2XXX_RFTL,0X40);//���ý��մ���Ϊ64���ֽ�
	  WkWriteSReg(port,WK2XXX_TFTL,0X10);//���÷��ʹ���Ϊ16���ֽ�
	  WkWriteSReg(port,WK2XXX_SPAGE,0);//�л���page0 
	  //ʹ���Ӵ��ڵķ��ͺͽ���ʹ��
	  scr=WkReadSReg(port,WK2XXX_SCR); 
	  scr|=WK2XXX_TXEN|WK2XXX_RXEN;
	  WkWriteSReg(port,WK2XXX_SCR,scr);	  		
}

/******************************Wk_DeInit*******************************************/
//�������ܣ���ʼ���Ӵ���
/*********************************************************************************/
void Wk_DeInit(u8 port)
{
	 u8 gena,grst,gier;
		//�ر��Ӵ�����ʱ��
    gena=WkReadGReg(WK2XXX_GENA);
		gena=gena&(~(1<<(port-1)));
		WkWriteGReg(WK2XXX_GENA,gena);
		//ʹ���Ӵ������ж�
		gier=WkReadGReg(WK2XXX_GIER);
		gier=gier&(~(1<<(port-1)));
		WkWriteGReg(WK2XXX_GIER,gier);
		//�����λ�Ӵ���
		grst=WkReadGReg(WK2XXX_GRST);
		grst=grst|(1<<(port-1));
		WkWriteGReg(WK2XXX_GRST,grst);
	
}

/**************************Wk_SetBaud*******************************************************/
//�������ܣ������Ӵ��ڲ����ʺ������˺����в����ʵ�ƥ��ֵ�Ǹ���11.0592Mhz�µ��ⲿ��������
// port:�Ӵ��ں�
// baud:�����ʴ�С.�����ʱ�ʾ��ʽ��
/**************************Wk2114SetBaud*******************************************************/
void Wk_SetBaud(u8 port,enum WKBaud baud)
{  
	unsigned char baud1,baud0,pres,scr;
	//���²�������Ӧ�ļĴ���ֵ�������ⲿʱ��Ϊ11.0592mhz������¼������ã����ʹ������������Ҫ���¼���
	switch (baud) 
		{
				case B600:
					baud1=0x4;
					baud0=0x7f;
					pres=0;
					break;
				case B1200:
					baud1=0x2;
					baud0=0x3F;
					pres=0;
					break;
				case B2400:
					baud1=0x1;
					baud0=0x1f;
					pres=0;
					break;
				case B4800:
					baud1=0x00;
					baud0=0x8f;
					pres=0;
					break;
				case B9600:
					baud1=0x00;
					baud0=0x47;
					pres=0;
					break;
				case B19200:
					baud1=0x00;
					baud0=0x23;
					pres=0;
					break;
				case B38400:
					baud1=0x00;
					baud0=0x11;
					pres=0;
					break;
				case B76800:
					baud1=0x00;
					baud0=0x08;
					pres=0;
					break;        
				case B1800:
					baud1=0x01;
					baud0=0x7f;
					pres=0;
					break;
				case B3600:
					baud1=0x00;
					baud0=0xbf;
					pres=0;
					break;
				case B7200:
					baud1=0x00;
					baud0=0x5f;
					pres=0;
					break;
				case B14400:
					baud1=0x00;
					baud0=0x2f;
					pres=0;
					break;
				case B28800:
					baud1=0x00;
					baud0=0x17;
					pres=0;
					break;
				case B57600:
					baud1=0x00;
					baud0=0x0b;
					pres=0;
					break;
				case B115200:
					baud1=0x00;
					baud0=0x05;
					pres=0;
					break;
				case B230400:
					baud1=0x00;
					baud0=0x02;
					pres=0;
					break;
				default:
					baud1=0x00;
					baud0=0x00;
					pres=0;
    }
		//�ص��Ӵ����շ�ʹ��
		scr=WkReadSReg(port,WK2XXX_SCR); 
		WkWriteSReg(port,WK2XXX_SCR,0);
		//���ò�������ؼĴ���
		WkWriteSReg(port,WK2XXX_SPAGE,1);//�л���page1
		WkWriteSReg(port,WK2XXX_BAUD1,baud1);
		WkWriteSReg(port,WK2XXX_BAUD0,baud0);
		WkWriteSReg(port,WK2XXX_PRES,pres);
		WkWriteSReg(port,WK2XXX_SPAGE,0);//�л���page0 
		//ʹ���Ӵ����շ�ʹ��
		WkWriteSReg(port,WK2XXX_SCR,scr);
}
/**************************WK_TxLen*******************************************/
//��������:��ȡ�Ӵ��ڷ���FIFOʣ��ռ䳤��
// port:�˿ں�
// ����ֵ������FIFOʣ��ռ䳤��
/**************************WK_Len********************************************/
int wk_TxLen(u8 port)
{
	u8 fsr,tfcnt;
	int len=0;
	fsr  =WkReadSReg(port,WK2XXX_FSR);
	tfcnt=WkReadSReg(port,WK2XXX_TFCNT);
	if(fsr& WK2XXX_TFULL)
		{ len=0;}
	else
	  {len=256-tfcnt;}
  return len;
}

/**************************WK_TxChars*******************************************/
//��������:ͨ���Ӵ��ڷ��͹̶���������
// port:�˿ں�
// len:���η��ͳ��Ȳ�����256
// 
/**************************WK_TxChars********************************************/
int wk_TxChars(u8 port,int len,u8 *sendbuf)
{
	
#if 1
	WkWriteSFifo(port,sendbuf,len);//ͨ��fifo��ʽ��������
#else
	int num=len;
	for(num=0;num<len;num++)
	{
		WkWriteSReg(port,WK2XXX_FDAT,*(sendbuf+num));
	}
#endif	
	return 0;
}

/**************************WK_RxChars*******************************************/
//��������:��ȡ�Ӵ���fifo�е�����
// port:�˿ں�
// recbuf:���յ�������
// ����ֵ���������ݵĳ���
/**************************WK_RxChars********************************************/
int wk_RxChars(u8 port,u8 *recbuf)
{
	u8  fsr=0,rfcnt=0,rfcnt2=0,sifr=0;
  int len=0;
	sifr=WkReadSReg(port,WK2XXX_SIFR);
	

	if((sifr&WK2XXX_RFTRIG_INT)||(sifr&WK2XXX_RXOVT_INT))//�н����жϺͽ��ճ�ʱ�ж�
	{ 
			fsr  =WkReadSReg(port,WK2XXX_FSR);
			rfcnt=WkReadSReg(port,WK2XXX_RFCNT);
			rfcnt2=WkReadSReg(port,WK2XXX_RFCNT);
			//printf("rfcnt=0x%x.\n",rfcnt);
			/*�ж�fifo�����ݸ���*/
			if(fsr& WK2XXX_RDAT)
			{ 
				if(!(rfcnt2>=rfcnt))
				{
					rfcnt=rfcnt2;
				}
				len=(rfcnt==0)?256:rfcnt;
			}
		#if 1
			WkReadSFifo(port,recbuf,len);
		#else
			for(n=0;n<len;n++)
			 *(recbuf+n)=WkReadSReg(port,WK2XXX_FDAT);
		#endif	
			return len;
  }
	else
	{
		len=0;
		return len;
	}
}










