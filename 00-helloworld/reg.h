#ifndef __REG_H_
#define __REG_H_

#define __REG_TYPE volatile uint32_t
#define __REG __REG_TYPE *

/* RCC Memory Map */
/* RCC means Reset and Control */
#define RCC ((__REG_TYPE)0x40021000)
// APB2 peripheral clock enable register
#define RCC_APB2ENR ((__REG)(RCC + 0x18))
// APB1 peripheral clock enable register
#define RCC_APB1ENR ((__REG)(RCC + 0x1C))

/* GPIO Memory Map */
#define GPIOA ((__REG_TYPE)0x40010800)
#define GPIOA_CRL ((__REG)(GPIOA + 0x00))
#define GPIOA_CRH ((__REG)(GPIOA + 0x04))

/* USART2 Memory Map */
#define USART2 ((__REG_TYPE)0x40004400)
#define USART2_SR ((__REG)(USART2 + 0x00))
#define USART2_DR ((__REG)(USART2 + 0x04))
#define USART2_CR1 ((__REG)(USART2 + 0x0C))

#endif
