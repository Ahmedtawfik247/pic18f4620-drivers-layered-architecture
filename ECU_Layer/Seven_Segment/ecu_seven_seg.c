/* 
 * File:   ecu_seven_seg.c
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */

#include "ecu_seven_seg.h"


/**
 * @brief This function is used to initialize the seven segment module
 * @param[in] seven_seg : A pointer to a seven_seg_t structure which contains the
 * configuration of the seven segment pins
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise
 */
Std_ReturnType seven_seg_init(const seven_seg_t * seven_seg)
{
    if(NULL == seven_seg)
    {
        return E_NOT_OK;
    }

    else
    {
        /**
         * Initialize each pin of the seven segment display
         */
        gpio_pin_init(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN0]));
        gpio_pin_init(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN1]));
        gpio_pin_init(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN2]));
        gpio_pin_init(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN3]));

        return E_OK;
    }

}

/**
 * @brief Writes a number to the seven segment display.
 * @param[in] seven_seg : A pointer to a seven_seg_t structure which contains the
 * configuration of the seven segment pins.
 * @param[in] number : The number to be displayed on the seven segment (0-9).
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType seven_seg_write_number(const seven_seg_t * seven_seg , uint8 number)
{
    /* Check for invalid parameters: NULL pointer or number out of range */
    if((NULL == seven_seg) || (number > 9))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Write each bit of the number to the corresponding seven segment pin */
        gpio_pin_write_logic(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN0]), (number & SEVEN_SEG_PIN_MASK));
        gpio_pin_write_logic(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN1]), ((number >> SHIFT_ONE_BIT) & SEVEN_SEG_PIN_MASK));
        gpio_pin_write_logic(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN2]), ((number >> SHIFT_TWO_BIT) & SEVEN_SEG_PIN_MASK));
        gpio_pin_write_logic(&(seven_seg->seven_seg_pins[SEVEN_SEG_PIN3]), ((number >> SHIFT_THREE_BIT) & SEVEN_SEG_PIN_MASK));

        /* Return OK status after writing the number */
        return E_OK;
    }
}
