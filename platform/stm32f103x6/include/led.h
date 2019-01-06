#ifndef __LED__
#define __LED__

#include "stm32f103x6.h"

void wait(){
    for (volatile int i = 0; i < 20000000; i++)
    {
    }
}

void TikaTika(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    GPIOC->CRH |= GPIO_CRH_MODE13;
    while (1)
    {
        GPIOC->BRR = GPIO_BRR_BR13_Msk;
        wait();
        GPIOC->BSRR = GPIO_BRR_BR13_Msk;
        wait();
    }
}

#endif
