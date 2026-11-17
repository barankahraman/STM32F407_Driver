#include "stm32f407_gpio_driver.h"


int main(void){
    Output_pin_set(GPIOD, 12);
    Output_pin_set(GPIOD, 13);
    Output_pin_set(GPIOD, 14);
    Output_pin_set(GPIOD, 15);


    return 0;
}