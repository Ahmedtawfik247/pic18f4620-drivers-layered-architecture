#include "hal_eeprom.h"


/**
 * @brief Writes a byte to EEPROM.
 * @param address Memory address to write data to.
 * @param data Data to be written.
 * @return E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType EEPROM_data_write_byte(uint16 address, uint8 data)
{
    uint8 interruptGlobalStatus = INTCONbits.GIE;

    // Set the address
    EEADRH = (uint8)(address >> 8) & EEADRH_ADDRESS_MASK;
    EEADR = (uint8)(address & EEADR_ADDRESS_MASK);

    // Set the data
    EEDATA = data;

    // Set the access bits
    EEPROM_ACCESS();
    EEPROM_DATA_ACCESS();

    // Enable the flash program cycle
    EEPROM_FLASH_ALLOW_WRITE_CYCLES();

    // Disable interrupts
    INTERRUPT_Global_Interrupt_Disable();

    // Perform the write sequence
    EECON2 = FIRST_FIXED_SEQUENCE;
    EECON2 = SECOND_FIXED_SEQUENCE;

    // Start the write cycle
    EEPROM_WTITE_ERASE();

    // Wait for the write cycle to complete
    while(EEPROM_WRITING);

    // Disable the flash program cycle
    EEPROM_FLASH_ALLOW_WRITE_CYCLES_DISABLE();

    // Clear the write complete flag
    EEPROM_CLEAR_FLAG();

    // Enable interrupts if they were previously enabled
    if(interruptGlobalStatus)
    {
        INTERRUPT_Global_Interrupt_Enable();
    }

    return E_OK;
}



/**
 * @brief Reads a byte from EEPROM.
 * @param address Memory address to read data from.
 * @param data Pointer to where the read data should be stored.
 * @return E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType EEPROM_data_read_byte(uint16 address, uint8 *data)
{
    if(NULL == data)
    {
        return E_NOT_OK;
    }
    else
    {
        /* Set the address */
        EEADRH = (uint8)(address >> 8) & EEADRH_ADDRESS_MASK;
        EEADR = (uint8)(address & EEADR_ADDRESS_MASK);

        /* Set the access bits */
        EEPROM_ACCESS();
        EEPROM_DATA_ACCESS();

        /* Start the read cycle */
        EEPROM_READ();

        /* Used When you used processor with high frequency */
        NOP();
        NOP();

        /* Read the data */
        *data = EEDATA;

        return E_OK;
    }

}
