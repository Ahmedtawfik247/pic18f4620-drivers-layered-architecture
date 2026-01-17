/* 
 * File:   ecu_relay.h
 * Author: botsha
 *
 * Created on December 24, 2024, 3:44 PM
 */


#ifndef ECU_RELAY_H
#define ECU_RELAY_H

/* Section : Inlcudes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"

/* Section : Macro Declerations */

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */
typedef enum{
    RELAY_OFF = 0,
    RELAY_ON
}relay_status_t;

typedef struct{
    uint8 relay_port : 3;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
    uint8 reserved : 1;

}relay_t;

/* Section : Functions Declerations */

/**
 * @brief This function is used to initialize a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure which contains the port 
 * number, pin number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_init(const relay_t *relay);

/**
 * @brief This function is used to turn on a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure which contains the port 
 * number, pin number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_turn_on(const relay_t *relay);

/**
 * @brief This function is used to turn off a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure containing the port
 * number, pin number, direction, and logic status.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_turn_off(const relay_t *relay);

/**
 * @brief Toggles the state of a relay module with the given configuration.
 * @param[in] relay : A pointer to a relay configuration structure containing the port
 * number, pin number, direction, and logic status.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType relay_toggle(const relay_t *relay);

#endif /* ECU_RELAY_H */