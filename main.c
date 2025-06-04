#include <stm32f10x.h>
#include <system_stm32f10x.h>

void Gpio_setup(void);
void Timer_setup(void);

int main(void)
{
	Gpio_setup();
	Timer_setup();

	while (1)
	{
	}
	return 0;
}

void Gpio_setup(void)
{

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

	// A0 as input pushpull
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOA->CRL |= GPIO_CRL_CNF0_0;
}

void Timer_setup(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->CNT = 0;
	// TIM2->CR1 |= TIM_CR1_DIR; // down counter
	//  TIM1->CR1 |= TIM_CR1_OPM;
	TIM2->PSC = 7200 - 1;
	TIM2->ARR = 20000;

	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; // cc1s= 01/ TI1 as input.
	TIM2->CCMR1 |= TIM_CCMR1_IC1F;

	//	TIM2->CCR1 = 15000;

	TIM2->CCER |= TIM_CCER_CC1E;

	TIM2->CR1 |= TIM_CR1_CEN;
}