/* 
 * File:   ecu_button.c
 * Author: botsha
 *
 * Created on December 25, 2024, 12:25 PM
 */


#include "ecu_button.h"



/**
 * @brief Initializes the button module with the given configuration.
 * 
 * @param[in] btn : A pointer to the button configuration structure
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise
 */
Std_ReturnType btn_init(const btn_t *btn){
    /* Check if the button configuration pointer is valid */
    if(NULL == btn)
    {
        return E_NOT_OK;
    }
    else
    {
        /* Initialize the button pin as an input */
        gpio_pin_direction_init(&(btn->btn_pin));
        return E_OK;
    }

}


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
Std_ReturnType btn_read_state(const btn_t *btn, btn_state_t *btn_state) {

    logic_t btn_logic;

    /* Validate the input pointers */
    if ((NULL == btn) || (NULL == btn_state)) {
        return E_NOT_OK;
    } else {
        /* Read the current logic level of the button pin */
        gpio_pin_read_logic(&(btn->btn_pin), &btn_logic);

        /* Determine the button state based on the active configuration */
        if ((BTN_ACTIVE_HIGH == btn->btn_connection)) {
            /* Button is active high */
            if (HIGH == btn_logic) {
                *btn_state = PRESSED;
            } else {
                *btn_state = RELEASED;
            }
        } else if ((BTN_ACTIVE_LOW == btn->btn_connection)) {
            /* Button is active low */
            if (HIGH == btn_logic) {
                *btn_state = RELEASED;
            } else {
                *btn_state = PRESSED;
            }
        } else {
            /* Invalid configuration, do nothing */
        }
        return E_OK;
    }
}
