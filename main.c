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
		if (!(TIM1->CR1 & TIM_CR1_CEN))
		{
			TIM1->CR1 |= TIM_CR1_CEN;
			GPIOA->ODR ^= GPIO_ODR_ODR6;
		}
	}
	return 0;
}

void Gpio_setup(void)
{

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// A6 as output
	GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
	GPIOA->CRL |= GPIO_CRL_MODE6;
}

void Timer_setup(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1->CNT = 0;
	TIM1->CR1 |= TIM_CR1_DIR;// down counter
	TIM1->CR1 |= TIM_CR1_OPM;
	TIM1->PSC = 7200 - 1;
	TIM1->ARR = 5000;

	//TIM1->CR1 |= TIM_CR1_CEN;
}