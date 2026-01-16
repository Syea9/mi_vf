#include "main.h"
#include "pwm.h"

void m_pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_PinAFConfig(PWM_AH_PORT, PWM_AH_AF, GPIO_AF_TIM1);
	GPIO_PinAFConfig(PWM_BH_PORT, PWM_BH_AF, GPIO_AF_TIM1);
	GPIO_PinAFConfig(PWM_CH_PORT, PWM_CH_AF, GPIO_AF_TIM1);
	GPIO_PinAFConfig(PWM_AL_PORT, PWM_AL_AF, GPIO_AF_TIM1);
	GPIO_PinAFConfig(PWM_BL_PORT, PWM_BL_AF, GPIO_AF_TIM1);
	GPIO_PinAFConfig(PWM_CL_PORT, PWM_CL_AF, GPIO_AF_TIM1);
	
	GPIO_InitStruct.GPIO_Pin = PWM_AH_PIN;
	GPIO_Init(PWM_AH_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = PWM_BH_PIN;
	GPIO_Init(PWM_BH_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = PWM_CH_PIN;
	GPIO_Init(PWM_CH_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = PWM_AL_PIN;
	GPIO_Init(PWM_AL_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = PWM_BL_PIN;
	GPIO_Init(PWM_BL_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = PWM_CL_PIN;
	GPIO_Init(PWM_CL_PORT, &GPIO_InitStruct);
	
	TIM_DeInit(PWM_TIM);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	
	/* 3 chnel complementary pwm */
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0x0;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStruct.TIM_Period = PWM_TIM_PULSE;
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStruct.TIM_Pulse = PWM_TIM_PULSE >> 1;
	
	TIM_OC1Init(PWM_TIM, &TIM_OCInitStruct);
	TIM_OC2Init(PWM_TIM, &TIM_OCInitStruct);
	TIM_OC3Init(PWM_TIM, &TIM_OCInitStruct);
	
	/* TIM1 CH4 OC4 trigger ADC sampling */
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = PWM_TIM_PULSE;
	
	TIM_OC4Init(PWM_TIM, &TIM_OCInitStruct);
}
