#ifndef _OS_TIMER_H_
#define _OS_TIMER_H_

extern void NVIC_Configuration(void);
extern void TIM_Configuration(unsigned int time);
extern void TIM2_IRQHandler(void);

#endif
