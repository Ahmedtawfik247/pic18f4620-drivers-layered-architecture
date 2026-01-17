/* 
 * File:   ecu_led.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Inlcudes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"



/* Section : Macro Declerations */

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef enum{
    OFF = 0,
    ON
}led_status_t;

typedef struct{
    uint8 port_name : 3;
    uint8 pin : 3;
    uint8 led_status : 1;
    uint8 reserved : 1;
}led_t;

/* Section : Functions Declerations */

/**
 * @brief Initializes the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if initialization is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_init(const led_t *led);

/**
 * @brief Turns on the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief Turns off the LED with the specified configuration.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief Toggles the state of the LED with the specified configuration.
 * 
 * This function toggles the state of the LED by writing the opposite of the current state to the
 * pin. For example, if the LED is currently ON, it will be turned OFF, and vice versa.
 * 
 * @param[in] led : A pointer to the led_t structure containing the LED configuration.
 * @return Std_ReturnType : Returns E_OK if the operation is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType led_toggle(const led_t *led);


#endif	/* ECU_LED_H */

