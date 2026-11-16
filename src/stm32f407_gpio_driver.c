#include "stm32f407_gpio_driver.h"
#include "stm32f407xx.h"

void GPIO_init(GPIO_TypeDef *port, uint8_t pin_number,
    uint8_t pin_mode, uint8_t output_type, uint8_t output_speed,
    uint8_t gpio_pull, uint8_t pin_alternate_func){


    GPIO_Handle *port_handle;
    uint8_t MASK;


    if(port == GPIOA) MASK = (1u << 0);
    else if(port == GPIOB) MASK = (1u << 1);
    else if(port == GPIOC) MASK = (1u << 2);
    else if(port == GPIOD) MASK = (1u << 3);
    else if(port == GPIOE) MASK = (1u << 4);
    else if(port == GPIOF) MASK = (1u << 5);
    else if(port == GPIOG) MASK = (1u << 6);
    else if(port == GPIOH) MASK = (1u << 7);
    else if(port == GPIOI) MASK = (1u << 8);

    RCC -> AHB1ENR |= MASK; 
    
    port_handle -> specs.pin_no = pin_number;
    port_handle -> specs.gpio_mode = pin_mode;
    port_handle -> specs.gpio_output_type = output_type;
    port_handle -> specs.gpio_output_speed = output_speed;
    port_handle -> specs.gpio_pull_up_down = gpio_pull;
    port_handle -> specs.gpio_alternate_function_no = pin_alternate_func;

    
    port  -> MODER &= ~(1 << (port_handle ->specs.pin_no)*2);
    port  -> MODER |= ((port_handle -> specs.gpio_mode) << (port_handle->specs.pin_no)*2);

    port -> OTYPER &= ~(1 << (port_handle -> specs.pin_no));
    port -> OTYPER |= ((port_handle->specs.gpio_output_type)<<(port_handle->specs.pin_no));

    port -> OSPEEDR &= ~(1 << (port_handle ->specs.pin_no)*2);
    port -> OSPEEDR |= ((port_handle->specs.gpio_output_speed) << (port_handle->specs.pin_no)*2);

    port -> PUPDR &= ~(0b11u << (port_handle->specs.pin_no)*2);
    port -> PUPDR |= ((port_handle ->specs.gpio_pull_up_down) << (port_handle->specs.pin_no)*2);

    if(pin_alternate_func != 0b11111u)
        {
            if(port_handle -> specs.pin_no <= 7){
            port -> AFR[0] &= ~(0b1111u << (port_handle -> specs.pin_no)*4);
            port -> AFR[0] |= ((port_handle ->specs.gpio_alternate_function_no) << (port_handle -> specs.pin_no)*4);
        }
        else{
            port -> AFR[1] &= ~(0b1111u << (port_handle -> specs.pin_no)*4);
            port -> AFR[1] |= ((port_handle ->specs.gpio_alternate_function_no) << (port_handle -> specs.pin_no)*4);
        }
    }

}

void Output_pin_set(GPIO_TypeDef *port, uint8_t pin){
    GPIO_init(
        port,pin,GPIO_PORT_MODE_OUTPUT,GPIO_PORT_OUTPUT_TYPE_PP,
        GPIO_PORT_OUTPUT_SPEED_HIGH, GPIO_PORT_PULLUP_PULLDOWN_NO, GPIO_ALTERNATE_FUNC_NO);

    port -> BSRR |= (BIT_SET << pin);
}