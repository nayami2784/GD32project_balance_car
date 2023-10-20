#include "bsp_led.h"

/************************************************
�������� �� led_gpio_config
��    �� �� led��gpio��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void led_gpio_config(void)
{
  /* ʹ��ʱ�� */
	rcu_periph_clock_enable(RCU_LED2);
	/* ����Ϊ���ģʽ ����ģʽ */
	gpio_mode_set(PORT_LED2,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,PIN_LED2);
	/* ����Ϊ������� 50MHZ */
	gpio_output_options_set(PORT_LED2,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,PIN_LED2);
}