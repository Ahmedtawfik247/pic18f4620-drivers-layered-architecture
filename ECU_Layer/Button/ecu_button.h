/* 
 * File:   ecu_button.h
 * Author: botsha
 *
 * Created on December 25, 2024, 12:25 PM
 */

#ifndef ECU_PUSH_BTN_H
#define	ECU_PUSH_BTN_H

/* Section : Inlcudes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/* Section : Macro Declerations */

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef enum{
    PRESSED,
    RELEASED
}btn_state_t;

typedef enum{
   BTN_ACTIVE_HIGH,
   BTN_ACTIVE_LOW
}btn_active_t;

typedef struct{
    pin_config_t btn_pin;
    btn_state_t btn_state;
    btn_active_t btn_connection;
}btn_t;

/* Section : Functions Declerations */

/**
 * @brief Initializes the button module with the given configuration.
 * 
 * @param[in] btn : A pointer to the button configuration structure
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise
 */
Std_ReturnType btn_init(const btn_t *btn);

/**
 * @brief Reads the current state of the button.
 * 
 * This function checks the logic level of the button pin and determines
 * the button state based on its active configuration (active high or active low).
 * 
 * @param[in] btn : A pointer to the button configuration structure.
 * @param[out] btn_state : A pointer to store the current state of the button.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType btn_read_state(const btn_t *btn, btn_state_t *btn_state);


#endif	/* ECU_PUSH_BTN_H */

