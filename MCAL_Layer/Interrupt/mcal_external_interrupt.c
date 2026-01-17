

#include "mcal_external_interrupt.h"
#include "mcal_interrupt_manager.h"

/* Pointer to functions to hold the callbacks for INTx */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

/* Pointer to functions to hold the callbacks for RBx */
static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB4_InterruptHandler_Low = NULL;
static InterruptHandler RB5_InterruptHandler_High = NULL;
static InterruptHandler RB5_InterruptHandler_Low = NULL;
static InterruptHandler RB6_InterruptHandler_High = NULL;
static InterruptHandler RB6_InterruptHandler_Low = NULL;
static InterruptHandler RB7_InterruptHandler_High = NULL;
static InterruptHandler RB7_InterruptHandler_Low = NULL;


static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *INTx_Config);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *INTx_Config);
static Std_ReturnType interrupt_INTx_Priority_init(const interrupt_INTx_t *INTx_Config);
static Std_ReturnType interrupt_INTx_Edge_init(const interrupt_INTx_t *INTx_Config);
static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *INTx_Config);
static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *INTx_Config);

static Std_ReturnType interrupt_INTx_set_InterruptHandler(const interrupt_INTx_t *INTx_Config);


static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *RBx_Config);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *RBx_Config);
static Std_ReturnType interrupt_RBx_Priority_init(const interrupt_RBx_t *RBx_Config);
static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t *RBx_Config);
static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t *RBx_Config);

static Std_ReturnType interrupt_RBx_set_InterruptHandler(const interrupt_RBx_t *RBx_Config);



Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        interrupt_INTx_Disable(INTx_Config);
        interrupt_INTx_clear_flag(INTx_Config);
        interrupt_INTx_Edge_init(INTx_Config);

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            interrupt_INTx_Priority_init(INTx_Config);
        #else
            INTERRUPT_Global_Interrupt_Enable();
            INTERRUPT_PeripheralInterrupt_Enable();
        #endif
        
        interrupt_INTx_pin_init(INTx_Config);
        
        /*callback*/
        interrupt_INTx_set_InterruptHandler(INTx_Config);
        
        interrupt_INTx_Enable(INTx_Config);
        return E_OK;
    }
}

Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        interrupt_INTx_Disable(INTx_Config);
        interrupt_INTx_clear_flag(INTx_Config);
        return E_OK;
    }
    
}

static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        switch(INTx_Config->source)
        {
            case INTERRUPT_EXT_INT0:
                EXT_INT0_INTERRUPT_ENABLE();
                return E_OK;

            case INTERRUPT_EXT_INT1:
                EXT_INT1_INTERRUPT_ENABLE();
                return E_OK;

            case INTERRUPT_EXT_INT2:
                EXT_INT2_INTERRUPT_ENABLE();
                return E_OK;
            default:
                return E_NOT_OK;
        }
    }

}

static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        switch(INTx_Config->source)
        {
            case INTERRUPT_EXT_INT0:
                EXT_INT0_INTERRUPT_DISABLE();
                return E_OK;

            case INTERRUPT_EXT_INT1:
                EXT_INT1_INTERRUPT_DISABLE();
                return E_OK;

            case INTERRUPT_EXT_INT2:
                EXT_INT2_INTERRUPT_DISABLE();
                return E_OK;
            default:
                return E_NOT_OK;
        }
    }

}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_Priority_init(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        switch(INTx_Config->source)
        {
            INTERRUPT_PriorityLevelsEnable();

            case INTERRUPT_EXT_INT0:
                INTERRUPT_Global_Interrupt_High_Enable();
                return E_OK;

            case INTERRUPT_EXT_INT1:
                if(INTERRUPT_PRIORITY_LOW == INTx_Config->priority)
                {
                    INTERRUPT_Global_Interrupt_Low_Enable();
                    EXT_INT1_INTERRUPT_PRIORITY_LOW();
                    return E_OK;
                }
                else if(INTERRUPT_PRIORITY_HIGH == INTx_Config->priority)
                {
                    INTERRUPT_Global_Interrupt_High_Enable();
                    EXT_INT1_INTERRUPT_PRIORITY_HIGH();
                    return E_OK;
                }
                else
                {
                    return E_NOT_OK;
                }

            case INTERRUPT_EXT_INT2:
                if(INTERRUPT_PRIORITY_LOW == INTx_Config->priority)
                {
                    INTERRUPT_Global_Interrupt_Low_Enable();
                    EXT_INT2_INTERRUPT_PRIORITY_LOW();
                    return E_OK;
                }
                else if(INTERRUPT_PRIORITY_HIGH == INTx_Config->priority)
                {
                    INTERRUPT_Global_Interrupt_High_Enable();
                    EXT_INT2_INTERRUPT_PRIORITY_HIGH();
                    return E_OK;
                }
                else
                {
                    return E_NOT_OK;
                }

            default:
                return E_NOT_OK;
        }

    }

}
#endif

static Std_ReturnType interrupt_INTx_Edge_init(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {

        switch(INTx_Config->source)
        {
            case INTERRUPT_EXT_INT0:

                if(INTERRUPT_FALLING_EDGE == INTx_Config->edge)
                {
                    EXT_INT0_INTERRUPT_FALLING_EDGE_SET();
                    return E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == INTx_Config->edge)
                {
                    EXT_INT0_INTERRUPT_RISING_EDGE_SET();
                    return E_OK;
                }
                else
                {
                    return E_NOT_OK;
                }

            case INTERRUPT_EXT_INT1:

                if(INTERRUPT_FALLING_EDGE == INTx_Config->edge)
                {
                    EXT_INT1_INTERRUPT_FALLING_EDGE_SET();
                    return E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == INTx_Config->edge)
                {
                    EXT_INT1_INTERRUPT_RISING_EDGE_SET();
                    return E_OK;
                }
                else
                {
                    return E_NOT_OK;
                }

            case INTERRUPT_EXT_INT2:
                if(INTERRUPT_FALLING_EDGE == INTx_Config->edge)
                {
                    EXT_INT2_INTERRUPT_FALLING_EDGE_SET();
                    return E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == INTx_Config->edge)
                {
                    EXT_INT2_INTERRUPT_RISING_EDGE_SET();
                    return E_OK;
                }
                else
                {
                    return E_NOT_OK;
                }

            default:
                return E_NOT_OK;
        }

    }

}

static Std_ReturnType interrupt_INTx_pin_init(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        gpio_pin_direction_init(&(INTx_Config->mcu_pin));
        return E_OK;
    }

}

static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }
    else
    {
        if(INTERRUPT_EXT_INT0 == INTx_Config->source)
        {
            EXT_INT0_INTERRUPT_FLAG_CLEAR();
            return E_OK;
        }
        else if(INTERRUPT_EXT_INT1 == INTx_Config->source)
        {
            EXT_INT1_INTERRUPT_FLAG_CLEAR();
            return E_OK;
        }
        else if(INTERRUPT_EXT_INT2 == INTx_Config->source)
        {
            EXT_INT2_INTERRUPT_FLAG_CLEAR();
            return E_OK;
        }
        else
        {
            return E_NOT_OK;
        }
    }
}

static Std_ReturnType interrupt_INTx_set_InterruptHandler(const interrupt_INTx_t *INTx_Config)
{
    if(NULL == INTx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        switch(INTx_Config->source)
        {
            case INTERRUPT_EXT_INT0:
                INT0_InterruptHandler = INTx_Config->EXT_InterruptHandler;
                return E_OK;

            case INTERRUPT_EXT_INT1:
                INT1_InterruptHandler = INTx_Config->EXT_InterruptHandler;
                return E_OK;
            
            case INTERRUPT_EXT_INT2:
                INT2_InterruptHandler = INTx_Config->EXT_InterruptHandler;
                return E_OK;
            
            default:
                return E_NOT_OK;
        }
    }    
}

void INT0_ISR(void)
{
    EXT_INT0_INTERRUPT_FLAG_CLEAR();

    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}
void INT1_ISR(void)
{
    EXT_INT1_INTERRUPT_FLAG_CLEAR();

    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void)
{
    EXT_INT2_INTERRUPT_FLAG_CLEAR();

    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}



Std_ReturnType interrupt_RBx_Init(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {

        interrupt_RBx_Disable(RBx_Config);       

        interrupt_RBx_clear_flag(RBx_Config);

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        interrupt_RBx_Priority_init(RBx_Config);  
        #else
            INTERRUPT_Global_Interrupt_Enable();
            INTERRUPT_PeripheralInterrupt_Enable();
        #endif

        interrupt_RBx_pin_init(RBx_Config);

        /*callback*/
        interrupt_RBx_set_InterruptHandler(RBx_Config);

        interrupt_RBx_Enable(RBx_Config);

        return E_OK;
    }
    
}

Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        interrupt_RBx_Disable(RBx_Config);
        interrupt_RBx_clear_flag(RBx_Config);
        return E_OK;
    }

}

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        EXT_RBx_INTERRUPT_ENABLE();        
        return E_OK;
    }
}

static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        EXT_RBx_INTERRUPT_DISABLE(); 
        return E_OK;
    }

}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_RBx_Priority_init(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_PRIORITY_LOW == RBx_Config->priority)
        {
            INTERRUPT_Global_Interrupt_Low_Enable();
            EXT_RBx_INTERRUPT_PRIORITY_LOW();
        }
        else if(INTERRUPT_PRIORITY_HIGH == RBx_Config->priority)
        {
            INTERRUPT_Global_Interrupt_High_Enable();
            EXT_RBx_INTERRUPT_PRIORITY_HIGH();
        }
        return E_OK;
    }

}
#endif

static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }    
    else
    {
        gpio_pin_direction_init(&(RBx_Config->mcu_pin));
        return E_NOT_OK;
    }

}

static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }
    else
    {
        EXT_RBx_INTERRUPT_FLAG_CLEAR();
        return E_OK;
    }
}

static Std_ReturnType interrupt_RBx_set_InterruptHandler(const interrupt_RBx_t *RBx_Config)
{
    if(NULL == RBx_Config)
    {
        return E_NOT_OK;
    }
    else 
    {
        switch(RBx_Config->mcu_pin.pin)
        {
            case PIN4 :

                RB4_InterruptHandler_High = RBx_Config->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low = RBx_Config->EXT_InterruptHandler_Low;
                break;
            case PIN5 :
                RB5_InterruptHandler_High  = RBx_Config->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low = RBx_Config->EXT_InterruptHandler_Low;
                break;
            case PIN6 :
                RB6_InterruptHandler_High = RBx_Config->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low = RBx_Config->EXT_InterruptHandler_Low;
                break;
            case PIN7 :
                RB7_InterruptHandler_High = RBx_Config->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low = RBx_Config->EXT_InterruptHandler_Low;
                break;
            default:
                return E_NOT_OK;
        }
        return E_OK;
    }
}

void RB4_ISR(uint8 RBx_source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(LOW == RBx_source)
    {
        if(RB4_InterruptHandler_Low)
        {
            RB4_InterruptHandler_Low();
        }
    }
    else if(HIGH == RBx_source)
    {
        if(RB4_InterruptHandler_High)
        {
            RB4_InterruptHandler_High();
        }
    }
}
void RB5_ISR(uint8 RBx_source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(LOW == RBx_source)
    {
        if(RB5_InterruptHandler_Low)
        {
            RB5_InterruptHandler_Low();
        }
    }
    else if(HIGH == RBx_source)
    {
        if(RB5_InterruptHandler_High)
        {
            RB5_InterruptHandler_High();
        }
    }
}
void RB6_ISR(uint8 RBx_source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(LOW == RBx_source)
    {
        if(RB6_InterruptHandler_Low)
        {
            RB6_InterruptHandler_Low();
        }
    }
    else if(HIGH == RBx_source)
    {
        if(RB6_InterruptHandler_High)
        {
            RB6_InterruptHandler_High();
        }
    }
}
void RB7_ISR(uint8 RBx_source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(LOW == RBx_source)
    {
        if(RB7_InterruptHandler_Low)
        {
            RB7_InterruptHandler_Low();
        }
    }
    else if(HIGH == RBx_source)
    {
        if(RB7_InterruptHandler_High)
        {
            RB7_InterruptHandler_High();
        }
    }
}
