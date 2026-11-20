#include "stm32f407_comm_driver.h"
#include "stm32f407_gpio_driver.h"

void USART_init(USART_TypeDef *usart_type, GPIO_TypeDef *port,
    uint8_t pin){

    uint8_t usart_mask;

    if(usart_type == (USART1 || USART6)){
        if(usart_type == USART1){
            usart_mask = (1 << 4);
        }
        else if(usart_type == USART6){
            usart_mask = (1 << 6);
        }
        RCC -> APB2ENR |= usart_mask;
    }

    else if(usart_type == (USART2 || USART3 || UART4 || UART5)){
        if(usart_type == USART2){
            usart_mask = (1 << 17);
        }
        else if(usart_type == USART3){
            usart_mask = (1 << 18);
        }
        else if(usart_type == UART4){
            usart_mask = (1 << 19);
        }
        else if(usart_type == UART5){
            usart_mask = (1 << 20);
        }
        
        RCC -> APB1ENR |= usart_mask;
    }
}


void Send_Byte(char *text){
    //while(*text != "\0"){
    //    USART1 -> DR = text;
    //    while(!(USART1 ->SR && (1 << 7))){}
    //}

    // Baud rate register (mantissa and fraction)
    // control register
}