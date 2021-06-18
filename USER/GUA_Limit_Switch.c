//******************************************************************************              
//name:             GUA_Limit_Switch.c             
//introduce:        限位开关驱动      
//author:           甜甜的大香瓜                     
//email:            897503845@qq.com         
//QQ group          香瓜单片机之STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//******************************************************************************      
#include "stm32f4xx.h" 
#include "GUA_Limit_Switch.h"
 
/*********************宏定义************************/
//引脚宏定义
#define GUA_LIMIT_SWITCH_UP_PORT							GPIOA
#define GUA_LIMIT_SWITCH_UP_PIN								GPIO_Pin_1
 
#define GUA_LIMIT_SWITCH_DOWN_PORT						GPIOA
#define GUA_LIMIT_SWITCH_DOWN_PIN							GPIO_Pin_4
 
/*********************内部函数************************/ 
static void GUA_Limit_Switch_IO_Init(void);
static void GUA_Limit_Switch_Exti_Init(void);
 
//******************************************************************************            
//name:             GUA_Limit_Switch_IO_Init           
//introduce:        限位开关的IO初始化         
//parameter:        none                 
//return:           none         
//author:           甜甜的大香瓜                 
//email:            897503845@qq.com     
//QQ group          香瓜单片机之STM8/STM32(164311667)                  
//changetime:       2016.12.28                     
//****************************************************************************** 
static void GUA_Limit_Switch_IO_Init(void)
{	
	//IO结构体
	GPIO_InitTypeDef GPIO_InitStructure;
		
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 	
	
	//UP配置
	GPIO_InitStructure.GPIO_Pin = GUA_LIMIT_SWITCH_UP_PIN;  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GUA_LIMIT_SWITCH_UP_PORT, &GPIO_InitStructure);	
	
	//DOWN配置
	GPIO_InitStructure.GPIO_Pin = GUA_LIMIT_SWITCH_DOWN_PIN;  	
  GPIO_InitStructure.GPIO_Pin = 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GUA_LIMIT_SWITCH_DOWN_PORT, &GPIO_InitStructure);
}
 
//******************************************************************************            
//name:             GUA_Limit_Switch_Exti_Init           
//introduce:        限位开关的IO中断初始化         
//parameter:        none                 
//return:           none         
//author:           甜甜的大香瓜                 
//email:            897503845@qq.com     
//QQ group          香瓜单片机之STM8/STM32(164311667)                  
//changetime:       2016.12.28                     
//****************************************************************************** 
static void GUA_Limit_Switch_Exti_Init(void)
{	
	EXTI_InitTypeDef EXTI_InitStructure;
 
	//UP中断配置
	EXTI_ClearITPendingBit(EXTI_Line1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);  
 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//DOWN中断配置
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
//introduce:        限位开关检测触发状态    
//parameter:        nGUA_Limit_Switch_Status:GUA_LIMIT_SWITCH_STATUS_UP or GUA_LIMIT_SWITCH_STATUS_DOWN       
//return:           GUA_LIMIT_SWITCH_STATUS_IDLE or GUA_LIMIT_SWITCH_STATUS_TRIGGER      
//author:           甜甜的大香瓜             
//QQ group          香瓜单片机之STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//******************************************************************************   
GUA_U8 GUA_Limit_Switch_Check_Pin(GUA_U8 nGUA_Limit_Switch_Status)    
{    
  //UP限位开关
  if(nGUA_Limit_Switch_Status == GUA_LIMIT_SWITCH_STATUS_UP)
  {
    //没触发
    if(GPIO_ReadInputDataBit(GUA_LIMIT_SWITCH_UP_PORT, GUA_LIMIT_SWITCH_UP_PIN) == Bit_SET) 
    {
      return GUA_LIMIT_SWITCH_STATUS_IDLE;
    }
    //触发
    else
    {
      return GUA_LIMIT_SWITCH_STATUS_TRIGGER;    
    }  
  }
  //DOWN限位开关
  else
  {
    //没触发
    if(GPIO_ReadInputDataBit(GUA_LIMIT_SWITCH_DOWN_PORT, GUA_LIMIT_SWITCH_DOWN_PIN) == Bit_SET) 
    {
      return GUA_LIMIT_SWITCH_STATUS_IDLE;
    }
    //触发
    else
    {
      return GUA_LIMIT_SWITCH_STATUS_TRIGGER;    
    }    
  }  
} 
 
//******************************************************************************        
//name:             GUA_Limit_Switch_Init        
//introduce:        限位开关初始化     
//parameter:        none       
//return:           none      
//author:           甜甜的大香瓜             
//email:            897503845@qq.com           
//QQ group          香瓜单片机之STM8/STM32(164311667)                      
//changetime:       2016.12.28                     
//****************************************************************************** 
void GUA_Limit_Switch_Init(void)
{
  //初始化IO
  GUA_Limit_Switch_IO_Init();
	
  //初始化IO的中断配置
  GUA_Limit_Switch_Exti_Init();
}