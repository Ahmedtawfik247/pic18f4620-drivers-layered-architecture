#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_

/* Section : Inlcudes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"


/* Section : Macro Declerations */

#define EEADRH_ADDRESS_MASK     0x03
#define EEADR_ADDRESS_MASK      0xFF

#define FIRST_FIXED_SEQUENCE    0x55
#define SECOND_FIXED_SEQUENCE   0xAA

#define EEPROM_WRITING          EECON1bits.WR

/* Section : Macro Functions Declerations */

#define EEPROM_ACCESS()                             (EECON1bits.EEPGD = LOW)
#define EEPROM_DATA_ACCESS()                        (EECON1bits.CFGS = LOW)

#define EEPROM_FLASH_ALLOW_WRITE_CYCLES()           (EECON1bits.WREN = HIGH)
#define EEPROM_FLASH_ALLOW_WRITE_CYCLES_DISABLE()   (EECON1bits.WREN = LOW)

#define EEPROM_READ()                               (EECON1bits.RD = HIGH)

#define EEPROM_WTITE_ERASE()                        (EECON1bits.WR = HIGH)

#define EEPROM_CLEAR_FLAG()                         (PIR2bits.EEIF = LOW)

/* Section : Data Type Declerations */

/* Section : Functions Declerations */

Std_ReturnType EEPROM_data_write_byte(uint16 address, uint8 data);
Std_ReturnType EEPROM_data_read_byte(uint16 address, uint8 *data);


#endif /* HAL_EEPROM_H_ */