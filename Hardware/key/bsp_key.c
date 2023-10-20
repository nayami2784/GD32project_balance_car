/********************************************************************************
  * �� �� ��: bsp_key.c
  * �� �� ��: ����
  * �޸�����: LC
  * �޸�����: 2022��04��15��
  * ���ܽ���:          
  ******************************************************************************
  * ע������:
*********************************************************************************/
#include "bsp_key.h"
#include "sys.h"
#include "bsp_led.h"
#include "stdio.h"

void key_gpio_config(void)
{
	/* ����ʱ�� */
	rcu_periph_clock_enable(BSP_KEY_RCU);
	rcu_periph_clock_enable(RCU_SYSCFG);    // ϵͳ����ʱ��
	
	/* ����Ϊ����ģʽ ����ģʽ */ 
	gpio_mode_set(BSP_KEY_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,BSP_KEY_PIN);  // ����Ĭ��״̬�ǵ͵�ƽ������Ϊ����
	
	/* ʹ��NVIC�ж� �жϷ���Ϊ2λ��ռ���ȼ���2λ�����ȼ� */
	nvic_irq_enable(BSP_KEY_EXTI_IRQN,3U,3U);  // ��ռ���ȼ�3�������ȼ�3
	/* �����ж��ߵ�GPIO */
	syscfg_exti_line_config(BSP_KEY_EXTI_PORT_SOURCE,BSP_KEY_EXTI_PIN_SOURCE);
	/* ��ʼ���ж��� */
	exti_init(BSP_KEY_EXTI_LINE,EXTI_INTERRUPT,EXTI_TRIG_BOTH);
	
	/* ʹ���ж� */
	exti_interrupt_enable(BSP_KEY_EXTI_LINE);
	/* ����жϱ�־λ */
	exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
}

/************************************************
�������� �� BSP_KEY_EXTI_IRQHandler
��    �� �� �жϴ�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LCEDA
*************************************************/
void BSP_KEY_EXTI_IRQHANDLER(void)
{
  if(exti_interrupt_flag_get(BSP_KEY_EXTI_LINE) == SET)   // �жϱ�־λΪ1����������	
	{
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)  // ��������
		{
			 /* �������²����Ĺ��� */ 
			gpio_bit_toggle(PORT_LED2,PIN_LED2);                   // led��ƽ״̬��ת
			printf("key press!\r\n");                              // ���ڴ�ӡkey press!
		}else{                                                   // �����ͷ� 
			/* �����ɿ������Ĺ��� */ 
			printf("key release!\r\n");                            // ���ڴ�ӡkey release!
		}
	  exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);            // ���жϱ�־λ
	}
}

/************************************************
�������� �� key_scan
��    �� �� ����ɨ�躯��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void key_scan(void)
{
	/* �ȶ�ȡ�������ŵĵ�ƽ ����ߵ�ƽ���������� */
	if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)         // ��������
	{
		delay_1ms(20);  // �ӳ����� 
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)       // �ٴμ�ⰴ���Ƿ��� 
		{
			/* ִ�ж�Ӧ�Ĺ��� */
			gpio_bit_toggle(PORT_LED2,PIN_LED2);    // led��ƽ״̬��ת
			printf("key press!\r\n");								// ���ڴ�ӡkey press!
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET);  // ��ⰴ���ɿ�
			printf("key release!\r\n");             // ���ڴ�ӡkey release!
		}
	}
}