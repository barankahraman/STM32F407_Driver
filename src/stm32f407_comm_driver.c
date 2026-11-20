#include "stm32f407_comm_driver.h"
#include "stm32f407_gpio_driver.h"
//IMPLEMENT THE GPIO_init inside it so that usart/uart can work
void USART_init(USART_TypeDef *usart_type, GPIO_TypeDef *port,
    uint8_t pin){

    if((usart_type == USART1) || (usart_type == USART2) || (usart_type == USART3)){
        
        GPIO_init(port,pin,GPIO_PORT_MODE_AF,GPIO_PORT_OUTPUT_TYPE_PP, 
            GPIO_PORT_OUTPUT_SPEED_HIGH, GPIO_PORT_PULLUP_PULLDOWN_NO,
            GPIO_ALTERNATE_FUNC_AF7);
    }
    else if((usart_type == UART4) || (usart_type == UART5) || (usart_type == USART6)){
        
        GPIO_init(port,pin,GPIO_PORT_MODE_AF,GPIO_PORT_OUTPUT_TYPE_PP, 
            GPIO_PORT_OUTPUT_SPEED_HIGH, GPIO_PORT_PULLUP_PULLDOWN_NO,
            GPIO_ALTERNATE_FUNC_AF8);
    }


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


void Send_Byte(char *text, USART_TypeDef *usart_type, 
    GPIO_TypeDef *port, uint8_t pin, uint8_t baud_rate){
    
    
    // control register

    while(*text != "\0"){
        usart_type -> DR = *text;
        while(!(usart_type ->SR && (1 << 7))){}
        text++;
    }


}