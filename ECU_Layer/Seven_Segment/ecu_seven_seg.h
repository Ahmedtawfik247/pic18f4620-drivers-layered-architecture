/* 
 * File:   ecu_seven_seg.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:20 PM
 */


#ifndef ECU_SEVEN_SEG_H_
#define ECU_SEVEN_SEG_H_

/* Section : Inlcudes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"

/* Section : Macro Declerations */

#define SEVEN_SEG_PIN_MASK 0x01

#define SHIFT_ONE_BIT      1
#define SHIFT_TWO_BIT      2
#define SHIFT_THREE_BIT    3

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef enum{
    SEVEN_SEG_PIN0,
    SEVEN_SEG_PIN1,
    SEVEN_SEG_PIN2,
    SEVEN_SEG_PIN3,
}seven_seg_pins_t;

typedef enum{
    SEVEN_SEG_ANODE,
    SEVEN_SEG_CATHODE
}seven_seg_type_t;

typedef struct{
    pin_config_t seven_seg_pins[4];
    seven_seg_type_t seven_seg_type;
}seven_seg_t;

/* Section : Functions Declerations */

/**
 * @brief This function is used to initialize the seven segment module
 * @param[in] seven_seg : A pointer to a seven_seg_t structure which contains the
 * configuration of the seven segment pins
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise
 */
Std_ReturnType seven_seg_init(const seven_seg_t * seven_seg);

/**
 * @brief Writes a number to the seven segment display.
 * @param[in] seven_seg : A pointer to a seven_seg_t structure which contains the
 * configuration of the seven segment pins.
 * @param[in] number : The number to be displayed on the seven segment (0-9).
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType seven_seg_write_number(const seven_seg_t * seven_seg,uint8 number);

#endif /* ECU_SEVEN_CFG_H_ */