#include <stdint.h>
#include "reg.h"

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */
#define USART_FLAG_TXE	((uint16_t) 0x0080)

/* greet is a global variable
 * This variable will be load by the loader at LMA and will be
 * copy to VMA by startup.c during startup.
 *
 * Add a global variable greet instead of a string literal
 * because string literal is in .rodata region and is put
 * under the .text region by the linker script
 */
/*
LMA - Load Memory Address - write from LMA to VMA
VMA - Virtual Memory Address - rip should be VMA
http://msyksphinz.hatenablog.com/entry/2017/02/09/010728

☻  arm-none-eabi-objdump -h hello.elf
hello.elf:     file format elf32-littlearm
Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000270  08000000  08000000  00010000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         0000000e  20000000  08000270  00020000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .comment      0000007e  00000000  00000000  0002000e  2**0
                  CONTENTS, READONLY
  3 .ARM.attributes 00000033  00000000  00000000  0002008c  2**0
                  CONTENTS, READONLY
*/
static char greet[] = "Hello World!\n";

void print_str(const char *str)
{
	while (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
}

void main(void)
{
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;

	print_str(greet);

	while (1);
}
