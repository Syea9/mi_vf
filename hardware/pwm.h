#ifndef __PWM_H
#define __PWM_H

#define PWM_TIM 		TIM1
#define PWM_TIM_CLOCK	180000000

#define PWM_FREQ		10000
#define PWM_TIM_PULSE	(PWM_TIM_CLOCK/(2*PWM_FREQ))
#define PWM_TPWM		(PWM_TIM_CLOCK/PWM_FREQ)


#define PWM_AH_PORT 	GPIOA
#define PWM_AH_PIN		GPIO_Pin_8
#define PWM_AH_AF 		GPIO_PinSource8

#define PWM_BH_PORT 	GPIOA
#define PWM_BH_PIN		GPIO_Pin_9
#define PWM_BH_AF 		GPIO_PinSource9

#define PWM_CH_PORT 	GPIOA
#define PWM_CH_PIN		GPIO_Pin_10
#define PWM_CH_AF 		GPIO_PinSource10

#define PWM_AL_PORT 	GPIOB
#define PWM_AL_PIN		GPIO_Pin_13
#define PWM_AL_AF 		GPIO_PinSource13

#define PWM_BL_PORT 	GPIOB
#define PWM_BL_PIN		GPIO_Pin_14
#define PWM_BL_AF 		GPIO_PinSource14

#define PWM_CL_PORT 	GPIOB
#define PWM_CL_PIN		GPIO_Pin_15
#define PWM_CL_AF 		GPIO_PinSource15


#endif
