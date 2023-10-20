/********************************************************************************
 * �� �� ��: bsp_pwm.c
 * �� �� ��: ����
 * �޸�����: LC
 * �޸�����: 2022��04��19��
 * ���ܽ���:
 ******************************************************************************
 * ע������:
 *********************************************************************************/
#include "bsp_pwm.h"

/************************************************
�������� �� pwm_gpio_config
��    �� �� pwm��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
static void pwm_gpio_config(void)
{
	/* ʹ��ʱ�� */
	rcu_periph_clock_enable(BSP_PWM_RCU);
	/* ����GPIO��ģʽ */
	gpio_mode_set(BSP_PWM_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, BSP_PWM_PIN);
	/* ����GPIO����� */
	gpio_output_options_set(BSP_PWM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_PWM_PIN);
	/* ����GPIO�ĸ��� */
	gpio_af_set(BSP_PWM_PORT, BSP_PWM_AF, BSP_PWM_PIN);
}

/************************************************
�������� �� pwm_config
��    �� �� PWM����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void pwm_config(uint16_t pre, uint16_t per)
{
	timer_parameter_struct timere_initpara;	   // ���嶨ʱ���ṹ��
	timer_oc_parameter_struct timer_ocintpara; // ��ʱ���Ƚ�����ṹ��

	pwm_gpio_config(); // ʹ��GPIO

	rcu_periph_clock_enable(BSP_PWM_TIMER_RCU);			  // ������ʱ��ʱ��
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // ���ö�ʱ��ʱ��

	/* ���ö�ʱ������ */
	timer_deinit(BSP_PWM_TIMER);						 // ��λ��ʱ��
	timere_initpara.prescaler = pre - 1;				 // ʱ��Ԥ��Ƶֵ   PSC_CLK= 200MHZ / 200 = 1MHZ
	timere_initpara.alignedmode = TIMER_COUNTER_EDGE;	 // ��Ե����
	timere_initpara.counterdirection = TIMER_COUNTER_UP; // ���ϼ���
	timere_initpara.period = per - 1;					 // ����    T = 10000 * 1MHZ = 10ms  f = 100HZ
	/* �����벶���ʱ��ʹ��  �����˲���ʹ�õĲ���Ƶ��֮��ķ�Ƶ���� */
	timere_initpara.clockdivision = TIMER_CKDIV_DIV1; // ��Ƶ����
	/* ֻ�и߼���ʱ������ ����Ϊx�����ظ�x+1�ν����ж� */
	timere_initpara.repetitioncounter = 0;		 // �ظ������� 0-255
	timer_init(BSP_PWM_TIMER, &timere_initpara); // ��ʼ����ʱ��

	/* ��������ṹ�� */
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH; // ��Ч��ƽ�ļ���
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;		 // ���ñȽ����ģʽ״̬ Ҳ����ʹ��PWM������˿�
	/* ���ö�ʱ��������� */
	timer_channel_output_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, &timer_ocintpara);

	/* ����ռ�ձ� */
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, 0);					 // ���ö�ʱ��ͨ���������ֵ
	timer_channel_output_mode_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, TIMER_OC_MODE_PWM0);		 // ���ö�ʱ��ͨ������Ƚ�ģʽ
	timer_channel_output_shadow_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, TIMER_OC_SHADOW_DISABLE); // ���ö�ʱ��ͨ�����Ӱ�ӼĴ���

	/* ֻ�и߼���ʱ��ʹ�� */
	//	timer_primary_output_config(TIMER0,ENABLE);
	timer_auto_reload_shadow_enable(BSP_PWM_TIMER);
	/* ʹ�ܶ�ʱ�� */
	timer_enable(BSP_PWM_TIMER);
}

/************************************************
�������� �� pwm_breathing_lamp
��    �� �� ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� LC
*************************************************/
void pwm_breathing_lamp(void)
{
	static uint8_t direct = 0; // ����
	static uint16_t value = 0; // ����ֵ

	if (direct == 0) // �𽥱���
	{
		value += 300; // ֵԽ�� Խ��
		if (value > 10000)
			direct = 1; // �ı䷽��
	}
	else // �𽥱䰵
	{
		value -= 300; // ֵԽС Խ��
		if (value <= 0)
			direct = 0;
	}
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, value); // ���ö�ʱ��ͨ���������ֵ
	delay_1ms(50);																	// ��ʱ50ms
}
