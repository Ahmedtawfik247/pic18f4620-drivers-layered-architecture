#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4_bits(const lcd_4_bit_t * lcd , uint8 data_command);
static Std_ReturnType lcd_4_bits_send_enabel_signal(const lcd_4_bit_t * lcd);
static Std_ReturnType lcd_8_bits_send_enabel_signal(const lcd_8_bit_t * lcd);
static Std_ReturnType lcd_8_bits_set_cursor(const lcd_8_bit_t * lcd , uint8 row , uint8 col);
static Std_ReturnType lcd_4_bits_set_cursor(const lcd_4_bit_t * lcd , uint8 row , uint8 col);



Std_ReturnType lcd_4_bit_init(const lcd_4_bit_t * lcd)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 counter = ZERO_INIT;
        
        gpio_pin_init(&(lcd->lcd_rs));
        gpio_pin_init(&(lcd->lcd_en));

        for(counter = ZERO_INIT ; counter < LCD_4_BIT_DATA_PINS ; counter++)
        {
            gpio_pin_init(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        lcd_4_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        __delay_ms(5);
        lcd_4_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        __delay_us(150);
        lcd_4_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        lcd_4_bit_send_command(lcd,LCD_CLEAR_DISPLAY);
        lcd_4_bit_send_command(lcd,LCD_RETURN_HOME);
        lcd_4_bit_send_command(lcd,LCD_INC_CURSOR_SHIFT_OFF);
        lcd_4_bit_send_command(lcd,LCD_DISPLAY_ON_CURSOE_OFF_BLINK_OFF);
        lcd_4_bit_send_command(lcd,LCD_4_BIT_MODE_2_Lines);
        lcd_4_bit_send_command(lcd,LCD_CURSOR_FIRST_LINE);

        return E_OK;
    }

}

Std_ReturnType lcd_4_bit_send_command(const lcd_4_bit_t * lcd , uint8 command)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        lcd_send_4_bits(lcd , command >> 4);
        lcd_4_bits_send_enabel_signal(lcd);
        lcd_send_4_bits(lcd , command);
        lcd_4_bits_send_enabel_signal(lcd);
        return E_OK;
    }
}

Std_ReturnType lcd_4_bit_send_chr_data(const lcd_4_bit_t * lcd , uint8 data)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        lcd_send_4_bits(lcd , data >> LCD_4_BIT_DATA_PINS);
        lcd_4_bits_send_enabel_signal(lcd);
        lcd_send_4_bits(lcd , data);
        lcd_4_bits_send_enabel_signal(lcd);

        return E_OK;
    }
}

Std_ReturnType lcd_4_bit_send_chr_data_pos(const lcd_4_bit_t * lcd , uint8 row , uint8 col , uint8 data)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        lcd_4_bits_set_cursor(lcd , row , col);
        lcd_4_bit_send_chr_data(lcd , data);
        return E_OK;
    }
}

Std_ReturnType lcd_4_bit_send_string(const lcd_4_bit_t * lcd , uint8 *str)
{
    if((NULL == lcd) || (NULL == str))
    {
        return E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            lcd_4_bit_send_char_data(lcd , *str++);
        }
        return E_OK;
    }
}

Std_ReturnType lcd_4_bit_send_string_pos(const lcd_4_bit_t * lcd , uint8 row , uint8 col , uint8 *str)
{
    if((NULL == lcd) || (NULL == str))
    {
        return E_NOT_OK;
    }
    else
    {
        lcd_4_bits_set_cursor(lcd , row , col);
        lcd_4_bit_send_string(lcd , str);
        return E_OK;
    }
}

Std_ReturnType lcd_4_bit_send_custom_chr(const lcd_4_bit_t * lcd , uint8 row , uint8 col , const uint8 chr[] , uint8 memPos)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 counter = ZERO_INIT;
       
        lcd_4_bit_send_command(lcd , ((LCD_CGRAM_START + (memPos*8))));
        
        for(counter = 0 ; counter < LCD_4_BIT_DATA_PINS ; counter++)
        {
            lcd_4_bit_send_char_data(lcd , chr[counter]);
        }
        lcd_4_bit_send_chr_data_pos(lcd , row , col , memPos);
        return E_OK;
    }
}





Std_ReturnType lcd_8_bit_init(const lcd_8_bit_t * lcd)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 counter = ZERO_INIT;
        
        gpio_pin_init(&(lcd->lcd_rs));
        gpio_pin_init(&(lcd->lcd_en));

        for(counter = ZERO_INIT ; counter < LCD_8_BIT_DATA_PINS ; counter++)
        {
            gpio_pin_init(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        lcd_8_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        __delay_ms(5);
        lcd_8_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        __delay_us(150);
        lcd_8_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        lcd_8_bit_send_command(lcd,LCD_CLEAR_DISPLAY);
        lcd_8_bit_send_command(lcd,LCD_RETURN_HOME);
        lcd_8_bit_send_command(lcd,LCD_INC_CURSOR_SHIFT_OFF);
        lcd_8_bit_send_command(lcd,LCD_DISPLAY_ON_CURSOE_OFF_BLINK_OFF);
        lcd_8_bit_send_command(lcd,LCD_8_BIT_MODE_2_Lines);
        lcd_8_bit_send_command(lcd,LCD_CURSOR_FIRST_LINE);

        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_command(const lcd_8_bit_t * lcd , uint8 command)
{
    uint8 counter = ZERO_INIT;
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        for(counter = 0 ; counter < LCD_8_BIT_DATA_PINS ; counter++)
        {
            gpio_pin_write_logic(&(lcd->lcd_data[counter]) , (command >> counter) & LCD_PIN_MASK);
        }
        lcd_8_bits_send_enabel_signal(lcd);

        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_chr_data(const lcd_8_bit_t * lcd , uint8 data)
{   
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 counter = ZERO_INIT;
        gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        for(counter = 0 ; counter < LCD_8_BIT_DATA_PINS ; counter++)
        {
            gpio_pin_write_logic(&(lcd->lcd_data[counter]) , (data >> counter) & LCD_PIN_MASK);
        }
        lcd_8_bits_send_enabel_signal(lcd);
        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_chr_data_pos(const lcd_8_bit_t * lcd , uint8 row , uint8 col , uint8 data)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        lcd_8_bits_set_cursor(lcd , row , col);
        lcd_8_bit_send_chr_data(lcd,  data);
        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_string(const lcd_8_bit_t * lcd , uint8 *str)
{
    if((NULL == lcd) || (NULL == str))
    {
        return E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            lcd_8_bit_send_char_data(lcd , *str++);
        }
        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_string_pos(const lcd_8_bit_t * lcd , uint8 row , uint8 col , uint8 *str)
{
    if((NULL == lcd) || (NULL == str))
    {
        return E_NOT_OK;
    }
    else
    {
        lcd_8_bits_set_cursor(lcd , row , col);
        lcd_8_bit_send_string(lcd , str);
        return E_OK;
    }
}

Std_ReturnType lcd_8_bit_send_custom_chr(const lcd_8_bit_t * lcd , uint8 row , uint8 col , const uint8 chr[] , uint8 memPos)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        uint8 counter = ZERO_INIT;
       
        lcd_8_bit_send_command(lcd , ((LCD_CGRAM_START + (memPos*8))));
        
        for(counter = 0 ; counter < LCD_8_BIT_DATA_PINS ; counter++)
        {
            lcd_8_bit_send_char_data(lcd , chr[counter]);
        }
        lcd_8_bit_send_chr_data_pos(lcd , row , col , memPos);
        return E_OK;
    }
}

Std_ReturnType convert_byte_to_string(uint8 data , uint8 *str)
{
    if(NULL == str)
    {
        return E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , UINT_8_ARRAY_SIZE);
        sprintf((char*)str , "%i" , data);
        return E_OK;
    }
}

Std_ReturnType convert_short_to_string(uint16 data , uint8 *str)
{
    if(NULL == str)
    {
        return E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , UINT_16_ARRAY_SIZE);
        sprintf((char *)str , "%i" , data);
        return E_OK;
    }

}

Std_ReturnType convert_int_to_string(uint32 data , uint8 *str)
{
    if(NULL == str)
    {
        return E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , UINT_32_ARRAY_SIZE);
        sprintf((char *)str , "%i" , data);

        return E_OK;
    }

}

static Std_ReturnType lcd_send_4_bits(const lcd_4_bit_t * lcd , uint8 data_command)
{
    uint8 counter = ZERO_INIT;
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        for(counter = 0 ; counter < LCD_4_BIT_DATA_PINS ; counter++)
        {
            gpio_pin_write_logic(&(lcd->lcd_data[counter]) , (data_command >> counter) & LCD_PIN_MASK);
        }
        return E_OK;
    }
}

static Std_ReturnType lcd_4_bits_send_enabel_signal(const lcd_4_bit_t * lcd)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_en) , HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en) , LOW);
        return E_OK;
    }

}

static Std_ReturnType lcd_8_bits_send_enabel_signal(const lcd_8_bit_t * lcd)
{
    if(NULL == lcd)
    {
        return E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(lcd->lcd_en) , HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en) , LOW);
        return E_OK;
    }

}

static Std_ReturnType lcd_8_bits_set_cursor(const lcd_8_bit_t * lcd , uint8 row , uint8 col)
{
    col--;
    switch(row)
    {
        case ROW1:
            lcd_8_bit_send_command(lcd, LCD_CURSOR_FIRST_LINE + col);
            return E_OK;

        case ROW2:
            lcd_8_bit_send_command(lcd, LCD_CURSOR_SECOND_LINE + col);
            return E_OK;

        case ROW3:
            lcd_8_bit_send_command(lcd, LCD_CURSOR_THIRD_LINE + col);
            return E_OK;

        case ROW4:
            lcd_8_bit_send_command(lcd, LCD_CURSOR_FOURTH_LINE + col);
            return E_OK;
        default:
            return E_NOT_OK;
    }
}

static Std_ReturnType lcd_4_bits_set_cursor(const lcd_4_bit_t * lcd , uint8 row , uint8 col)
{
    col--;
    switch(row)
    {
        case ROW1:
            lcd_4_bit_send_command(lcd, LCD_CURSOR_FIRST_LINE + col);
            return E_OK;

        case ROW2:
            lcd_4_bit_send_command(lcd, LCD_CURSOR_SECOND_LINE + col);
            return E_OK;

        case ROW3:
            lcd_4_bit_send_command(lcd, LCD_CURSOR_THIRD_LINE + col);
            return E_OK;

        case ROW4:
            lcd_4_bit_send_command(lcd, LCD_CURSOR_FOURTH_LINE + col);
            return E_OK;
        default:
            return E_NOT_OK;
    }
}