/* 
 * File:   ecu_dc_motor.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */

#ifndef ECU_DC_MOTOR_H
#define ECU_DC_MOTOR_H

/* Section : Inlcudes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/* Section : Macro Declerations */

#define DC_MOTOR_MAX_NUM 2

#define DC_MOTOR_PIN1    0
#define DC_MOTOR_PIN2    1

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef enum{
    DC_MOTOR_OFF = 0,
    DC_MOTOR_ON
}dc_motor_status_t;


typedef struct{
    pin_config_t dc_motor_pins[DC_MOTOR_MAX_NUM];
}dc_motor_t;

/* Section : Functions Declerations */

/**
 * @brief Initializes the DC motor by configuring its control pins.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if initialization is successful, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_init(const dc_motor_t * dc_motor);

/**
 * @brief Turns the DC motor forward.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is turned on successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_turn_forward(const dc_motor_t * dc_motor);

/**
 * @brief Turns the DC motor backward.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is turned on successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_turn_backward(const dc_motor_t * dc_motor);

/**
 * @brief Stops the DC motor.
 * @param[in] dc_motor : A pointer to a dc_motor_t structure containing the pin configuration for the motor.
 * @return Std_ReturnType : Returns E_OK if the motor is stopped successfully, E_NOT_OK if the pointer is NULL.
 */
Std_ReturnType dc_motor_stop(const dc_motor_t * dc_motor);

#endif // ECU_DC_MOTOR_H