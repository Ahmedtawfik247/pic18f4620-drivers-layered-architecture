/* 
 * File:   ecu_relay.c
 * Author: botsha
 *
 * Created on December 24, 2024, 3:44 PM
 */


#include "ecu_relay.h"



/**
 * @brief This function is used to initialize a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure which contains the port 
 * number, pin number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_init(const relay_t *relay){
    if(NULL == relay)
    {
        return E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {
        .port = relay->relay_port,
        .pin = relay->relay_pin,
        .direction = OUTPUT,
        .logic = relay->relay_status
        };
        /* Initialize the pin */
        gpio_pin_init(&pin_obj);
        return E_OK;
    }
}

/**
 * @brief This function is used to turn on a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure which contains the port 
 * number, pin number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    if(NULL == relay)
    {
        return E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {
        .port = relay->relay_port,
        .pin = relay->relay_pin,
        .direction = OUTPUT,
        .logic = relay->relay_status
        };
        /* Write the logic HIGH to the pin to turn on the relay */
        gpio_pin_write_logic(&pin_obj,HIGH);
        return E_OK;
    }

}

/**
 * @brief This function is used to turn off a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure containing the port
 * number, pin number, direction, and logic status.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    if(NULL == relay)
    {
        /* Return an error if the relay configuration pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Create a pin configuration object based on the relay settings */
        pin_config_t pin_obj = {
        .port = relay->relay_port,
        .pin = relay->relay_pin,
        .direction = OUTPUT,
        .logic = relay->relay_status
        };
        /* Write the logic LOW to the pin to turn off the relay */
        gpio_pin_write_logic(&pin_obj,LOW);
        /* Return OK status upon successful operation */
        return E_OK;
    }
}

/**
 * @brief Toggles the state of a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure containing the port
 * number, pin number, direction, and logic status.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_toggle(const relay_t *relay)
{
    if(NULL == relay)
    {
        return E_NOT_OK;
    }
    else
    {
        /* Create a pin configuration object based on the relay settings */
        pin_config_t pin_obj = {
        .port = relay->relay_port,
        .pin = relay->relay_pin,
        .direction = OUTPUT,
        .logic = relay->relay_status
        };
        /* Toggle the state of the relay by writing the opposite of the current state to the pin */
        gpio_pin_toggle_logic(&pin_obj);
        /* Return OK status upon successful operation */
        return E_OK;
    }

}
