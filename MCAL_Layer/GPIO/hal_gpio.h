/* 
 * File:   hal_gpio.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:25 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Inlcudes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/* Section : Macro Declerations */

#define BIT_MASK                    1
#define PORT_MAX_NUM                5
#define PORT_PIN_MAX_NUM            8
#define PORT_MASK                   0xFF
#define PORT_DIRECTION_OUTPUT       0x00
#define PORT_DIRECTION_INPUT        0xFF


/* Section : Macro Functions Declerations */

#define HWREG8(_x)                 (*((volatile uint8 *)(_x)))

#define SET_BIT(REG,BIT_POSN)      (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)    (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)   (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)     (REG >> BIT_POSN & BIT_MASK)

#define SET_PORT(REG)              (REG |= PORT_MASK)
#define CLEAR_PORT(REG)            (REG &= ~PORT_MASK)
#define TOGGLE_PORT(REG)           (REG ^= PORT_MASK)



/* Section : Data Type Declerations */

typedef enum
{
    LOW = 0,
    HIGH
}logic_t;

typedef enum
{
    OUTPUT = 0,
    INPUT
}direction_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;


typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef struct 
{
    uint8 port :3;          /* @ref port_index_t*/
    uint8 pin :3;           /* @ref pin_index_t*/
    uint8 direction :1;     /* @ref direction_t*/
    uint8 logic :1;         /* @ref logic_t*/
}pin_config_t;

/* Section : Functions Declerations */

/**
 * @brief This function is used to initialize a specific pin according to the 
 * given configuration.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_init(const pin_config_t * _pin_config);

/**
 * @brief This function is used to initialize a specific pin direction according 
 * to the given configuration.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_direction_init(const pin_config_t * _pin_config);

/**
 * @brief This function is used to read the direction status of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @param[out] _pin_direction : A pointer to a variable which will store the 
 * direction status of the pin.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config , direction_t * _pin_direction);

/**
 * @brief This function writes a logic level to a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @param[in] _logic : The logic level to write to the pin, either HIGH or LOW.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config , logic_t _logic);

/**
 * @brief Reads the logic level of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @param[out] _logic : A pointer to a variable which will store the current 
 * logic level of the pin.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config , logic_t *_logic);

/**
 * @brief Toggles the logic level of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);

/**
 * @brief Initializes the direction of an entire port.
 * @param[in] port : The port index to be configured.
 * @param[in] _port_direction : The desired direction for the port (input or output).
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_direction_init(port_index_t port , direction_t _port_direction);

/**
 * @brief Retrieves the current direction status of an entire port.
 * @param[in] port : The port index to be read.
 * @param[out] _port_direction : A pointer to a variable which will store the
 * current direction status of the port (input or output).
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port , direction_t * _port_direction);

/**
 * @brief Writes a logic level to an entire port.
 * @param[in] port : The port index to be written.
 * @param[in] _logic : The desired logic level to be written to the port.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the writing is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8 _logic);

/**
 * @brief Reads the current logic level of an entire port.
 * @param[in] port : The port index to be read.
 * @param[out] _logic : A pointer to a variable which will store the current
 * logic level of the port.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *_logic);

/**
 * @brief Toggles the logic level of an entire port.
 * @param[in] port : The port index to be toggled.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HAL_GPIO_H */

