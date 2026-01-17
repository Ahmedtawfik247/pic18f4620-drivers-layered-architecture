/* 
 * File:   ecu_keypad.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:25 PM
 */

#ifndef ECU_KEYPAD_H
#define ECU_KEYPAD_H

/* Section : Inlcudes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/* Section : Macro Declerations */

#define KEYPAD_ROW_PIN_ZERO 0
#define KEYPAD_ROW_PIN_ONE 1
#define KEYPAD_ROW_PIN_TWO 2
#define KEYPAD_ROW_PIN_THREE 3

#define KEYPAD_COL_PIN_ZERO 0
#define KEYPAD_COL_PIN_ONE 1
#define KEYPAD_COL_PIN_TWO 2
#define KEYPAD_COL_PIN_THREE 3

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */


typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS_NUM];
    pin_config_t keypad_cols_pins[KEYPAD_COLS_NUM];
}keypad_t;

/* Section : Functions Declerations */

/**
 * @brief This function is used to initialize the keypad module.
 * @param[in] keypad : A pointer to a keypad_t structure which contains the 
 * configuration of the keypad pins.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType keypad_init(const keypad_t *keypad);

/**
 * @brief This function is used to read the value of the key pressed in the keypad.
 * @param[in] keypad : A pointer to a keypad_t structure which contains the 
 * configuration of the keypad pins.
 * @param[out] value : A pointer to a variable which will hold the value of the 
 * key pressed in the keypad.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif /* ECU_KEYPAD_H */