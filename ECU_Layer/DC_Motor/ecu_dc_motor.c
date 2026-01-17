/* 
 * File:   ecu_dc_motor.c
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */


#include "ecu_dc_motor.h"


/**
 * @brief Initializes the DC motor by configuring its control pins.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if initialization is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_init(const dc_motor_t * dc_motor){

    /* Check if the dc_motor pointer is NULL */
    if(NULL == dc_motor){
        /* Return not OK if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Initialize the first control pin of the DC motor */
        gpio_pin_init(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN1]));
        
        /* Initialize the second control pin of the DC motor */
        gpio_pin_init(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN2]));
        
        /* Return OK status after successful initialization */
        return E_OK;
    }
}

/**
 * @brief Turns the DC motor forward.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is turned on successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_turn_forward(const dc_motor_t * dc_motor){

    if(NULL == dc_motor){
        /* Return not OK if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Set the first control pin of the DC motor to high */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN1]),HIGH);
        
        /* Set the second control pin of the DC motor to low */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN2]),LOW);
        
        /* Return OK status after successful motor turn on */
        return E_OK;
    }

    
}

/**
 * @brief Turns the DC motor backward.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is turned on successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_turn_backward(const dc_motor_t * dc_motor){

    /* Check if the dc_motor pointer is NULL */
    if(NULL == dc_motor){
        /* Return not OK if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Set the first control pin of the DC motor to low */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN1]),LOW);
        
        /* Set the second control pin of the DC motor to high */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN2]),HIGH);
        
        /* Return OK status after successful motor turn on */
        return E_OK;
    }
}

/**
 * @brief Stops the DC motor.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is stopped successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_stop(const dc_motor_t * dc_motor){

    /* Check if the dc_motor pointer is NULL */
    if(NULL == dc_motor){
        /* Return not OK if the pointer is NULL */
        return E_NOT_OK;
    }
    else
    {
        /* Set the first control pin of the DC motor to low */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN1]),LOW);
        
        /* Set the second control pin of the DC motor to low */
        gpio_pin_write_logic(&(dc_motor->dc_motor_pins[DC_MOTOR_PIN2]),LOW);
        
        /* Return OK status after successful motor stop */
        return E_OK;
    }
    
}
