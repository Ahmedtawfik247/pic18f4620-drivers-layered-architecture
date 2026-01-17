#ifndef ECU_CHR_LCD_H
#define ECU_CHR_LCD_H

/* Section : Inlcudes */

#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section : Macro Declerations */

#define LCD_4_BIT_DATA_PINS         4
#define LCD_8_BIT_DATA_PINS         8

#define LCD_PIN_MASK                (uint8)0x01

#define LCD_8_BIT_MODE_2_Lines      0x38
#define LCD_4_BIT_MODE_2_Lines      0x28


#define LCD_CLEAR_DISPLAY           0x01
#define LCD_RETURN_HOME             0x02


#define LCD_INC_CURSOR_SHIFT_OFF    0x06
#define LCD_INC_CURSOR_SHIFT_ON     0x07
#define LCD_DEC_CURSOR_SHIFT_OFF    0x04
#define LCD_DEC_CURSOR_SHIFT_ON     0x05

#define LCD_CURSOR_FIRST_LINE       0X80
#define LCD_CURSOR_SECOND_LINE      0XC0
#define LCD_CURSOR_THIRD_LINE       0X94
#define LCD_CURSOR_FOURTH_LINE      0XD4


#define LCD_DISPLAY_OFF_CURSOE_OFF_BLINK_OFF 0X08
#define LCD_DISPLAY_OFF_CURSOE_OFF_BLINK_ON  0X09
#define LCD_DISPLAY_OFF_CURSOE_ON_BLINK_OFF  0X0A
#define LCD_DISPLAY_OFF_CURSOE_ON_BLINK_ON   0X0B

#define LCD_DISPLAY_ON_CURSOE_OFF_BLINK_OFF  0X0C
#define LCD_DISPLAY_ON_CURSOE_OFF_BLINK_ON   0X0D
#define LCD_DISPLAY_ON_CURSOE_ON_BLINK_OFF   0X0E
#define LCD_DISPLAY_ON_CURSOE_ON_BLINK_ON    0X0F

#define LCD_DISPLAY_SHIFT_LEFT       0X18
#define LCD_DISPLAY_SHIFT_RIGHT      0X1C

#define UINT_8_ARRAY_SIZE           4
#define UINT_16_ARRAY_SIZE          6
#define UINT_32_ARRAY_SIZE          11

#define LCD_CGRAM_START             0x40
#define LCD_DDRAM_START             0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[LCD_4_BIT_DATA_PINS];
}lcd_4_bit_t;


typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[LCD_8_BIT_DATA_PINS];
}lcd_8_bit_t;

/* Section : Functions Declerations */

Std_ReturnType lcd_4_bit_init(const lcd_4_bit_t * lcd);
Std_ReturnType lcd_4_bit_send_command(const lcd_4_bit_t * lcd , uint8 command);
Std_ReturnType lcd_4_bit_send_char_data(const lcd_4_bit_t * lcd , uint8 data);
Std_ReturnType lcd_4_bit_send_char_data_pos(const lcd_4_bit_t * lcd , uint8 row , uint8 col , uint8 data);
Std_ReturnType lcd_4_bit_send_string(const lcd_4_bit_t * lcd , uint8 *str);
Std_ReturnType lcd_4_bit_send_string_pos(const lcd_4_bit_t * lcd , uint8 row , uint8 col , uint8 *str);
Std_ReturnType lcd_4_bit_send_custom_char(const lcd_4_bit_t * lcd , uint8 row , uint8 col , const uint8 chr[] , uint8 memPos);


Std_ReturnType lcd_8_bit_init(const lcd_8_bit_t * lcd);
Std_ReturnType lcd_8_bit_send_command(const lcd_8_bit_t * lcd , uint8 command);
Std_ReturnType lcd_8_bit_send_char_data(const lcd_8_bit_t * lcd , uint8 data);
Std_ReturnType lcd_8_bit_send_char_data_pos(const lcd_8_bit_t * lcd , uint8 row , uint8 col , uint8 data);
Std_ReturnType lcd_8_bit_send_string(const lcd_8_bit_t * lcd , uint8 *str);
Std_ReturnType lcd_8_bit_send_string_pos(const lcd_8_bit_t * lcd , uint8 row , uint8 col , uint8 *str);
Std_ReturnType lcd_8_bit_send_custom_char(const lcd_8_bit_t * lcd , uint8 row , uint8 col , const uint8 chr[] , uint8 memPos);

Std_ReturnType convert_byte_to_string(uint8 data , uint8 *str);
Std_ReturnType convert_short_to_string(uint16 data , uint8 *str);
Std_ReturnType convert_int_to_string(uint32 data , uint8 *str);

#endif // ECU_CHR_LCD_H