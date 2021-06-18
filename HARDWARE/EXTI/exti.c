#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "wk2xxx.h"

	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
  //GPIOA.1 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //PB0��ӦIO����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB0

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
 
}
void EXTI1_IRQHandler(void)
{ 
	 u8 gifr,sier,sifr,rxbuf[256],txbuf[256];
	 int txlen,rxlen,len,num,i;
  printf("IN EXTI1_IRQ");
	printf("\n\r\n\r");
	/*�ر�LED��*/

	if(EXTI_GetFlagStatus(EXTI_Line1)!= RESET)
	{   	EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
			gifr=WkReadGReg(WK2XXX_GIFR);/**/
		do{
			if(gifr&WK2XXX_UT1INT)//�ж��Ӵ���1�Ƿ����ж�
			{ /*���ݴ���*/
						/*���ݽ���*/
						rxlen=wk_RxChars(1,rxbuf);//һ�ν��յ����ݲ��ᳬ��256Byte
						/*���ݷ���*/
						//�ѽ��յ����ݷ��ͳ�ȥ
						wk_TxChars(1,rxlen,rxbuf);

			}
			
			if(gifr&WK2XXX_UT2INT)//�ж��Ӵ���2�Ƿ����ж�
			{
				/*���ݽ���*/
						rxlen=wk_RxChars(2,rxbuf);//һ�ν��յ����ݲ��ᳬ��256Byte
						/*���ݷ���*/
						//�ѽ��յ����ݷ��ͳ�ȥ
						wk_TxChars(2,rxlen,rxbuf);
			
			  }
			if(gifr&WK2XXX_UT3INT)//�ж��Ӵ���3�Ƿ����ж�
			{
				/*���ݽ���*/
						rxlen=wk_RxChars(3,rxbuf);//һ�ν��յ����ݲ��ᳬ��256Byte
						/*���ݷ���*/
						//�ѽ��յ����ݷ��ͳ�ȥ
						wk_TxChars(3,rxlen,rxbuf);
				   // printf("port!!!!\n");
			}
			if(gifr&WK2XXX_UT4INT)//�ж��Ӵ���4�Ƿ����ж�
			{
				/*���ݽ���*/
						rxlen=wk_RxChars(4,rxbuf);//һ�ν��յ����ݲ��ᳬ��256Byte
						/*���ݷ���*/
						//�ѽ��յ����ݷ��ͳ�ȥ
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
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}

void Exti_Disable(void)
{
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}

