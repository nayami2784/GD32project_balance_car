#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_USART_TX_RCU  RCU_GPIOA   // ����TX�Ķ˿�ʱ��
#define BSP_USART_RX_RCU  RCU_GPIOA   // ����RX�Ķ˿�ʱ��
#define BSP_USART_RCU     RCU_USART0  // ����0��ʱ��

#define BSP_USART_TX_PORT GPIOA				// ����TX�Ķ˿�
#define BSP_USART_RX_PORT GPIOA				// ����RX�Ķ˿�
#define BSP_USART_AF 			GPIO_AF_7   // ����0�ĸ��ù���
#define BSP_USART_TX_PIN  GPIO_PIN_9  // ����TX������
#define BSP_USART_RX_PIN  GPIO_PIN_10 // ����RX������

#define BSP_USART 				USART0      // ����0


void usart_gpio_config(uint32_t band_rate);  // ���ô���
void usart_send_data(uint8_t ucch);          // ����һ���ַ�
void usart_send_string(uint8_t *ucstr);      // ����һ���ַ���

#endif  /* BSP_USART_H */