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
		// if (!(TIM1->CR1 & TIM_CR1_CEN))
		//{
		//	TIM1->CR1 |= TIM_CR1_CEN;
		//	GPIOA->ODR ^= GPIO_ODR_ODR6;
		//	}
	}
	return 0;
}

void Gpio_setup(void)
{

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

	// A6 as output
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0;
}

void Timer_setup(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->CNT = 0;
	TIM2->CR1 |= TIM_CR1_DIR; // down counter
	// TIM1->CR1 |= TIM_CR1_OPM;
	TIM2->PSC = 7200 - 1;
	TIM2->ARR = 10000;

	TIM2->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;

	TIM2->CCR1 = 5000;

	TIM2->CCER |= TIM_CCER_CC1E;

	TIM2->CR1 |= TIM_CR1_CEN;
}