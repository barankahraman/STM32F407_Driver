#include "stm32f407xx.h"

void USART_init(USART_TypeDef *usart_type, GPIO_TypeDef *port,
    uint8_t pin);


void Send_Byte(char *text, USART_TypeDef *usart_type, 
    GPIO_TypeDef *port, uint8_t pin, float baud_rate, float clock_speed,
    float oversampling);

void SPI_init(uint8_t spi_number, GPIO_TypeDef *port);