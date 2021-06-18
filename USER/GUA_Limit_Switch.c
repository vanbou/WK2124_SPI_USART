//******************************************************************************              
//name:             GUA_Limit_Switch.c             
//introduce:        ��λ��������      
//author:           ����Ĵ����                     
//email:            897503845@qq.com         
//QQ group          ��ϵ�Ƭ��֮STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//******************************************************************************      
#include "stm32f4xx.h" 
#include "GUA_Limit_Switch.h"
 
/*********************�궨��************************/
//���ź궨��
#define GUA_LIMIT_SWITCH_UP_PORT							GPIOA
#define GUA_LIMIT_SWITCH_UP_PIN								GPIO_Pin_1
 
#define GUA_LIMIT_SWITCH_DOWN_PORT						GPIOA
#define GUA_LIMIT_SWITCH_DOWN_PIN							GPIO_Pin_4
 
/*********************�ڲ�����************************/ 
static void GUA_Limit_Switch_IO_Init(void);
static void GUA_Limit_Switch_Exti_Init(void);
 
//******************************************************************************            
//name:             GUA_Limit_Switch_IO_Init           
//introduce:        ��λ���ص�IO��ʼ��         
//parameter:        none                 
//return:           none         
//author:           ����Ĵ����                 
//email:            897503845@qq.com     
//QQ group          ��ϵ�Ƭ��֮STM8/STM32(164311667)                  
//changetime:       2016.12.28                     
//****************************************************************************** 
static void GUA_Limit_Switch_IO_Init(void)
{	
	//IO�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
		
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 	
	
	//UP����
	GPIO_InitStructure.GPIO_Pin = GUA_LIMIT_SWITCH_UP_PIN;  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GUA_LIMIT_SWITCH_UP_PORT, &GPIO_InitStructure);	
	
	//DOWN����
	GPIO_InitStructure.GPIO_Pin = GUA_LIMIT_SWITCH_DOWN_PIN;  	
  GPIO_InitStructure.GPIO_Pin = 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GUA_LIMIT_SWITCH_DOWN_PORT, &GPIO_InitStructure);
}
 
//******************************************************************************            
//name:             GUA_Limit_Switch_Exti_Init           
//introduce:        ��λ���ص�IO�жϳ�ʼ��         
//parameter:        none                 
//return:           none         
//author:           ����Ĵ����                 
//email:            897503845@qq.com     
//QQ group          ��ϵ�Ƭ��֮STM8/STM32(164311667)                  
//changetime:       2016.12.28                     
//****************************************************************************** 
static void GUA_Limit_Switch_Exti_Init(void)
{	
	EXTI_InitTypeDef EXTI_InitStructure;
 
	//UP�ж�����
	EXTI_ClearITPendingBit(EXTI_Line1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);  
 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//DOWN�ж�����
	EXTI_ClearITPendingBit(EXTI_Line4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);  
 
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
}
 
//******************************************************************************        
//name:             GUA_Limit_Switch_Check_Pin        
//introduce:        ��λ���ؼ�ⴥ��״̬    
//parameter:        nGUA_Limit_Switch_Status:GUA_LIMIT_SWITCH_STATUS_UP or GUA_LIMIT_SWITCH_STATUS_DOWN       
//return:           GUA_LIMIT_SWITCH_STATUS_IDLE or GUA_LIMIT_SWITCH_STATUS_TRIGGER      
//author:           ����Ĵ����             
//QQ group          ��ϵ�Ƭ��֮STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//******************************************************************************   
GUA_U8 GUA_Limit_Switch_Check_Pin(GUA_U8 nGUA_Limit_Switch_Status)    
{    
  //UP��λ����
  if(nGUA_Limit_Switch_Status == GUA_LIMIT_SWITCH_STATUS_UP)
  {
    //û����
    if(GPIO_ReadInputDataBit(GUA_LIMIT_SWITCH_UP_PORT, GUA_LIMIT_SWITCH_UP_PIN) == Bit_SET) 
    {
      return GUA_LIMIT_SWITCH_STATUS_IDLE;
    }
    //����
    else
    {
      return GUA_LIMIT_SWITCH_STATUS_TRIGGER;    
    }  
  }
  //DOWN��λ����
  else
  {
    //û����
    if(GPIO_ReadInputDataBit(GUA_LIMIT_SWITCH_DOWN_PORT, GUA_LIMIT_SWITCH_DOWN_PIN) == Bit_SET) 
    {
      return GUA_LIMIT_SWITCH_STATUS_IDLE;
    }
    //����
    else
    {
      return GUA_LIMIT_SWITCH_STATUS_TRIGGER;    
    }    
  }  
} 
 
//******************************************************************************        
//name:             GUA_Limit_Switch_Init        
//introduce:        ��λ���س�ʼ��     
//parameter:        none       
//return:           none      
//author:           ����Ĵ����             
//email:            897503845@qq.com           
//QQ group          ��ϵ�Ƭ��֮STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//****************************************************************************** 
void GUA_Limit_Switch_Init(void)
{
  //��ʼ��IO
  GUA_Limit_Switch_IO_Init();
	
  //��ʼ��IO���ж�����
  GUA_Limit_Switch_Exti_Init();
}