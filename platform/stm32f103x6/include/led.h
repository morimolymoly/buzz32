#ifndef __LED__
#define __LED__

#include "stm32f103x6.h"

void wait(){
    for (int i = 0; i < 100000000; i++) {
    }
}

void TikaTika(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    GPIOC->CRH |= GPIO_CRH_MODE13;
    while(1) {
        GPIOC->BRR |= 1 << 13;
        wait();
        GPIOC->BSRR |= 1 << 13;
        wait();
    }
}

#endif
