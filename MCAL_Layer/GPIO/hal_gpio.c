/* 
 * File:   hal_gpio.c
 * Author: botsha
 *
 * Created on December 22, 2024, 12:25 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_registers[] = {&TRISA , &TRISB ,&TRISC ,&TRISD ,&TRISE};
volatile uint8 *lat_registers[] = {&LATA , &LATB ,&LATC ,&LATD ,&LATE};
volatile uint8 *port_registers[] = {&PORTA , &PORTB ,&PORTC ,&PORTD ,&PORTE};

#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE

/**
 * @brief This function is used to initialize a specific pin according to the 
 * given configuration.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_init(const pin_config_t * _pin_config)
{
    /* Check if the pointer to the pin configuration is valid or not */
    if((NULL == _pin_config) || (_pin_config -> pin > PORT_PIN_MAX_NUM - 1))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Initialize the pin direction */
        gpio_pin_direction_init(_pin_config);
        /* Initialize the pin logic */
        gpio_pin_write_logic(_pin_config,_pin_config->logic);
        
        /* Return OK status */
        return E_OK;
    }
}



/**
 * @brief This function is used to initialize a specific pin direction according 
 * to the given configuration.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_direction_init(const pin_config_t * _pin_config)
{
    if((NULL == _pin_config) || 
            (_pin_config->pin > PORT_PIN_MAX_NUM - 1) || 
            (_pin_config->port > PORTE_INDEX))
    {
        return E_NOT_OK;
    }
    
    /* Switch on the pin direction */
    switch(_pin_config->direction)
    {
        /* If the direction is output clear the TRISX register */
        case OUTPUT :
            CLEAR_BIT(*(tris_registers[_pin_config->port]) , _pin_config -> pin);
            return E_OK;
        
        /* If the direction is input set the TRISX register */
        case INPUT :
            SET_BIT(*((tris_registers[_pin_config->port])) , _pin_config -> pin);
            return E_OK;
        
        /* If the direction is neither output nor input return E_NOT_OK */
        default :
            return E_NOT_OK;
    }
    
     
}


/**
 * @brief This function is used to read the direction status of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number, port number, direction and logic status.
 * @param[out] _pin_direction : A pointer to a variable which will store the 
 * direction status of the pin.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config , direction_t * _pin_direction)
{
    if((NULL == _pin_config) || (NULL == _pin_direction) || (_pin_config -> pin > PORT_PIN_MAX_NUM - 1))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Read the pin direction from the TRISX register */
        *_pin_direction = READ_BIT(*(tris_registers[_pin_config->port]),_pin_config->pin);
        return E_OK;
    } 
}


/**
 * @brief This function writes a logic level to a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @param[in] _logic : The logic level to write to the pin, either HIGH or LOW.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config , logic_t _logic)
{
    /* Validate the pin configuration pointer and pin number */
    if(NULL == _pin_config || (_pin_config -> pin > PORT_PIN_MAX_NUM - 1))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Write the specified logic level to the pin */
        switch(_logic)
        {
            case LOW :
                /* Clear the bit in the LAT register to set the pin LOW */
                CLEAR_BIT(*(lat_registers[_pin_config -> port]) , _pin_config -> pin);
                return E_OK;
            case HIGH :
                /* Set the bit in the LAT register to set the pin HIGH */
                SET_BIT(*(lat_registers[_pin_config -> port]) , _pin_config -> pin);
                return E_OK;
            default:
                /* Invalid logic level, return error */
                return E_NOT_OK;
        }
        
    } 
}


/**
 * @brief Reads the logic level of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @param[out] _logic : A pointer to a variable which will store the current 
 * logic level of the pin.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config , logic_t *_logic)
{
    if(NULL == _pin_config || NULL == _logic || (_pin_config -> pin > PORT_PIN_MAX_NUM - 1))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Read the current logic level of the pin from the PORT register */
        *_logic = READ_BIT(*(port_registers[_pin_config->port]) , _pin_config->pin);
        return E_OK;
    }  
}


/**
 * @brief Toggles the logic level of a specific pin.
 * @param[in] _pin_config : A pointer to a pin configuration structure which 
 * contains the pin number and port number.
 * @return Std_ReturnType : A return status of the function, 
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config)
{
    if(NULL == _pin_config || (_pin_config -> pin > PORT_PIN_MAX_NUM - 1))
    {
        /* Invalid pin configuration, return error */
        return E_NOT_OK;
    }
    else
    {
        /* Toggle the pin logic */
        TOGGLE_BIT(*(lat_registers[_pin_config->port]) , _pin_config->pin);
        /* Return OK status */
        return E_OK;
    }
}

#endif



#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE

/**
 * @brief Initializes the direction of an entire port.
 * @param[in] port : The port index to be configured.
 * @param[in] _port_direction : The desired direction for the port (input or output).
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_direction_init(port_index_t port, direction_t _port_direction)
{
    /* Check if the port index is valid */
    if (port > PORT_MAX_NUM - 1)
    {
        /* Invalid port index, return error */
        return E_NOT_OK;
    }
    else
    {
        /* Set the entire port direction using the TRIS register */
        *tris_registers[port] = _port_direction;

        /* Return OK status */
        return E_OK;
    }
}

/**
 * @brief Retrieves the current direction status of an entire port.
 * @param[in] port : The port index to be read.
 * @param[out] _port_direction : A pointer to a variable which will store the
 * current direction status of the port (input or output).
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port , direction_t * _port_direction)
{
    /* Check if the port index is valid and the pointer is not null */
    if((NULL == _port_direction) || (port > PORT_MAX_NUM - 1))
    {
        /* Invalid port index or null pointer, return error */
        return E_NOT_OK;
    }
    else
    {
        /* Read the current port direction from the TRIS register */
        *_port_direction = *tris_registers[port];

        /* Return OK status */
        return E_OK;
    }
}

/**
 * @brief Writes a logic level to an entire port.
 * @param[in] port : The port index to be written.
 * @param[in] _logic : The desired logic level to be written to the port.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the writing is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8 _logic)
{
    /* Check if the port index is valid */
    if((port > PORT_MAX_NUM - 1))
    {
        /* Invalid port index, return error */
        return E_NOT_OK;
    }
    else
    {
        /* Write the specified logic level to the port */
        *lat_registers[port] = _logic;

        /* Return OK status */
        return E_OK;
    } 
}

/**
 * @brief Reads the current logic level of an entire port.
 * @param[in] port : The port index to be read.
 * @param[out] _logic : A pointer to a variable which will store the current
 * logic level of the port.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the reading is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *_logic)
{
    if(NULL == _logic || (port > PORT_MAX_NUM - 1))
    {
        /* Invalid port index or null pointer, return error */
        return E_NOT_OK;
    }
    else
    {
        /* Read the current port logic from the PORT register */
        *_logic = *port_registers[port];

        /* Return OK status */
        return E_OK;
    }  
}

/**
 * @brief Toggles the logic level of an entire port.
 * @param[in] port : The port index to be toggled.
 * @return Std_ReturnType : A return status of the function,
 * E_OK if the operation is successful, E_NOT_OK otherwise.
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    if((port > PORT_MAX_NUM - 1))
    {
        return E_NOT_OK;
    }
    else
    {
        /* Toggle the port logic */
        TOGGLE_PORT(*lat_registers[port]);

        /* Return OK status */
        return E_OK;
    }
}

#endif