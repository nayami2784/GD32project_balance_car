#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_KEY_RCU   RCU_GPIOA      // �����˿�ʱ��
#define BSP_KEY_PORT  GPIOA          // �����˿�
#define BSP_KEY_PIN   GPIO_PIN_0     // ��������


#define BSP_KEY_EXTI_IRQN			 		EXTI0_IRQn          // �ⲿ�ж�0
#define BSP_KEY_EXTI_PORT_SOURCE 	EXTI_SOURCE_GPIOA   // �ⲿ�ж϶˿���Դ
#define BSP_KEY_EXTI_PIN_SOURCE  	EXTI_SOURCE_PIN0    // �ⲿ�ж�������Դ
#define BSP_KEY_EXTI_LINE 				EXTI_0              // �ⲿ�ж�
#define BSP_KEY_EXTI_IRQHANDLER   EXTI0_IRQHandler    // �ⲿ�жϺ�����


void key_gpio_config(void); // key gpio��������
void key_scan(void); // ����ɨ��

#endif