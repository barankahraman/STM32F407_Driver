#include "stm32f407_gpio_driver.h"
#include "stm32f407_comm_driver.h"

int main(void){
    
    Send_Byte("A",USART1,GPIOA,9,115200,16000000,16);


    return 0;
}