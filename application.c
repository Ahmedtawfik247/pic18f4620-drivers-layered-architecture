/* 
 * File:   application.c
 * Author: botsha
 *
 * Created on December 22, 2024, 11:34 AM
 */

#include "application.h"
#include "MCAL_Layer/GPIO/hal_gpio.h"

pin_config_t led_1 = {
    .port = PORTC_INDEX,
    .direction = OUTPUT,
    .pin = PIN0,
    .logic = LOW
};

int main() {
    gpio_pin_direction_init(&led_1);
    gpio_pin_write_logic(&led_1,HIGH);
    

    return 0;
}

