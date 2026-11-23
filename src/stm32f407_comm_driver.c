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


    int usart_mask;

    if((usart_type == USART1) || (usart_type == USART6)){
        if(usart_type == USART1){
            usart_mask = (1 << 4);
        }
        else if(usart_type == USART6){
            usart_mask = (1 << 6);
        }
        RCC -> APB2ENR |= usart_mask;
    }

    else if((usart_type == USART2) || (usart_type == USART3) || (usart_type == UART4) || (usart_type == UART5)){
        if(usart_type == USART2){
            usart_mask = (1u << 17);
        }
        else if(usart_type == USART3){
            usart_mask = (1u << 18);
        }
        else if(usart_type == UART4){
            usart_mask = (1u << 19);
        }
        else if(usart_type == UART5){
            usart_mask = (1u << 20);
        }
        
        RCC -> APB1ENR |= usart_mask;
    }
}


void Send_Byte(char *text, USART_TypeDef *usart_type, 
    GPIO_TypeDef *port, uint8_t pin, float baud_rate, 
    float clock_speed, float oversampling){

    USART_init(usart_type,port,pin);
    float USART_DIV;

    USART_DIV = ((clock_speed / oversampling)/baud_rate);

    uint32_t usart_mantissa = (int) USART_DIV;
    float usart_fraction = USART_DIV - ((float)usart_mantissa);
    usart_fraction = (int)((usart_fraction * oversampling) + 0.5);
    if(usart_fraction == oversampling) {usart_mantissa++; usart_fraction = 0;}
    usart_type ->BRR = ((usart_mantissa << 4) | ((int) usart_fraction << 0));
    // BRR should not be "OR"ed because we do not want previous values from
    // the previous transmission
    
    if(oversampling == 8.0) usart_type -> CR1 |= (1<<15);
    else usart_type ->CR1 &= ~(1u << 15);

    usart_type -> CR1 |= (1 << 3);
    usart_type -> CR1 |= (1 << 13);


    while(*text != '\0'){
        
        while(!(usart_type ->SR & (1 << 7))){}
        usart_type -> DR = *text;
        text++;
    }


}