#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
//EXTI_InitTypeDef EXTI_InitStructure;
//NVIC_InitTypeDef NVIC_InitStructure;
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供参考开发使用，未经作者许可，不得用于其它任何用途
//WK2124 DEMO
//STM32 外部中断  
//成都为开微电子
//技术论坛:www.wkmic.com
//修改日期:2017/8/10
//版本：V1.0
//版权所有，盗版必究。
//////////////////////////////////////////////////////////////////////////////////   	 
void EXTIX_Init(void);//外部中断初始化		 
void Exti_Enable(void);
void Exti_Disable(void);
#endif

