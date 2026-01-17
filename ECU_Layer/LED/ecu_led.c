/* 
 * File:   ecu_led.c
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */

#include "ecu_led.h"


/**
 * @brief Initializes the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if initialization is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_init(const led_t *led)
{
    /* Check if the LED configuration pointer is valid */
    if(NULL == led)
    {
        /* Return error status if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Create a pin configuration object with the LED settings */
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
        };
        
        /* Initialize the pin with the specified configuration */
        gpio_pin_init(&pin_obj);
        
        /* Return OK status after successful initialization */
        return E_OK;
    }
}

/**
 * @brief Turns on the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    if(NULL == led)
    {
        return E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {
        .port = led->port_name,
        .pin = led->pin,
        .direction = OUTPUT,
        .logic = led->led_status
        };
        gpio_pin_write_logic(&pin_obj,HIGH);
        return E_OK;
    }

}

/**
 * @brief Turns off the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    /* Check if the LED configuration pointer is valid */
    if(NULL == led)
    {
        /* Return error status if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Create a pin configuration object with the LED settings */
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
        };
        
        /* Write LOW logic to the pin to turn off the LED */
        gpio_pin_write_logic(&pin_obj,LOW);
        
        /* Return OK status after successful operation */
        return E_OK;
    }
}

/**
 * @brief Toggles the state of the LED with the specified configuration.
 * 
 * This function toggles the state of the LED by writing the opposite of the current state to the
 * pin. For example, if the LED is currently ON, it will be turned OFF, and vice versa.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_toggle(const led_t *led)
{
    if(NULL == led)
    {
        /* Return error status if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Create a pin configuration object with the LED settings */
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
        };
        
        /* Toggle the state of the LED by writing the opposite of the current state to the pin */
        gpio_pin_toggle_logic(&pin_obj);
        
        /* Return OK status after successful operation */
        return E_OK;
    }
}
