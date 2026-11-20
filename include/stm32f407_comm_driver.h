#include "stm32f407xx.h"

void USART_init(USART_TypeDef *usart_type, GPIO_TypeDef *port,
    uint8_t pin);

void Send_Byte(char *text);