#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "wk2xxx.h"

	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
//外部中断0服务程序
void EXTIX_Init(void)
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
  //GPIOA.1 中断线以及中断初始化配置   下降沿触发
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //PB0对应IO配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB0

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
 
}
void EXTI1_IRQHandler(void)
{ 
	 u8 gifr,sier,sifr,rxbuf[256],txbuf[256];
	 int txlen,rxlen,len,num,i;
  printf("IN EXTI1_IRQ");
	printf("\n\r\n\r");
	/*关闭LED灯*/

	if(EXTI_GetFlagStatus(EXTI_Line1)!= RESET)
	{   	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
			gifr=WkReadGReg(WK2XXX_GIFR);/**/
		do{
			if(gifr&WK2XXX_UT1INT)//判断子串口1是否有中断
			{ /*数据处理*/
						/*数据接收*/
						rxlen=wk_RxChars(1,rxbuf);//一次接收的数据不会超过256Byte
						/*数据发送*/
						//把接收的数据发送出去
						wk_TxChars(1,rxlen,rxbuf);

			}
			
			if(gifr&WK2XXX_UT2INT)//判断子串口2是否有中断
			{
				/*数据接收*/
						rxlen=wk_RxChars(2,rxbuf);//一次接收的数据不会超过256Byte
						/*数据发送*/
						//把接收的数据发送出去
						wk_TxChars(2,rxlen,rxbuf);
			
			  }
			if(gifr&WK2XXX_UT3INT)//判断子串口3是否有中断
			{
				/*数据接收*/
						rxlen=wk_RxChars(3,rxbuf);//一次接收的数据不会超过256Byte
						/*数据发送*/
						//把接收的数据发送出去
						wk_TxChars(3,rxlen,rxbuf);
				   // printf("port!!!!\n");
			}
			if(gifr&WK2XXX_UT4INT)//判断子串口4是否有中断
			{
				/*数据接收*/
						rxlen=wk_RxChars(4,rxbuf);//一次接收的数据不会超过256Byte
						/*数据发送*/
						//把接收的数据发送出去
				   //wk_TxChars(4,rxlen,rxbuf);
			}
			
		gifr=WkReadGReg(WK2XXX_GIFR);
			delay_ms(1000);
		}while(gifr&0x0f);
		printf("over\n");
		printf("\n\r\n\r");
	}
}

//
void Exti_Enable(void)
{
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}

void Exti_Disable(void)
{
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}

