/* 
 * File:   ecu_keypad.c
 * Author: botsha
 *
 * Created on December 22, 2024, 12:25 PM
 */


#include "ecu_keypad.h"

static const uint8 keypad_values[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = {
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}
};

/**
 * @brief This function is used to initialize the keypad module.
 * @param[in] keypad : A pointer to a keypad_t structure which contains the 
 * configuration of the keypad pins.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType keypad_init(const keypad_t *keypad)
{
    if(NULL == keypad)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 rows_counter = ZERO_INIT;
        uint8 cols_counter = ZERO_INIT;
        /* Initialize the rows pins as output */
        for(rows_counter = ZERO_INIT ; rows_counter < KEYPAD_ROWS_NUM ; rows_counter++)
        {
            gpio_pin_init(&(keypad->keypad_rows_pins[rows_counter]));
        }

        /* Initialize the columns pins as input */
        for(cols_counter = ZERO_INIT ; cols_counter < KEYPAD_COLS_NUM ; cols_counter++)
        {
            gpio_pin_direction_init(&(keypad->keypad_cols_pins[cols_counter]));
        }

        return E_OK;
    }

}

/**
 * @brief This function is used to read the value of the key pressed in the keypad.
 * @param[in] keypad : A pointer to a keypad_t structure which contains the 
 * configuration of the keypad pins.
 * @param[out] value : A pointer to a variable which will hold the value of the 
 * key pressed in the keypad.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value)
{
    if((NULL == keypad) || (NULL == value))
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 rows_counter = ZERO_INIT;
        uint8 cols_counter = ZERO_INIT;
        uint8 counter = ZERO_INIT;
        logic_t cols_value = ZERO_INIT;
        /* Scan the rows of the keypad */
        for(rows_counter = ZERO_INIT ; rows_counter < KEYPAD_ROWS_NUM ; rows_counter++)
        {
            /* Make all the rows low except the current row */
            for(counter = ZERO_INIT ; counter < KEYPAD_ROWS_NUM ; counter++)
            {
                gpio_pin_write_logic(&(keypad->keypad_rows_pins[counter]),LOW);
            }
            /* Make the current row high */
            gpio_pin_write_logic(&(keypad->keypad_rows_pins[rows_counter]),HIGH);
            /* Scan the columns of the keypad */
            for(cols_counter = ZERO_INIT ; cols_counter < KEYPAD_COLS_NUM ; cols_counter++)
            {
                /* Read the value of the current column */
                gpio_pin_read_logic(&(keypad->keypad_cols_pins[cols_counter]),&cols_value);
                /* Check if the current column is high */
                if(HIGH == cols_value)
                {
                    /* Store the value of the key pressed in the keypad */
                    *value = keypad_values[rows_counter][cols_counter];
                }
            }
        }

        return E_OK;
    }

}
