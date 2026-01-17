#ifndef MCAL_EXTERNAL_INTERRUPT_H_
#define MCAL_EXTERNAL_INTERRUPT_H_

/* Section : Inlcudes */

#include "mcal_interrupt_cfg.h"


/* Section : Macro Declerations */

/* Section : Macro Functions Declerations */

#if EXTERNAL_INTERRUPT_INTx_ENABLE==INTERRUPT_FEATURE_ENABLE

// ------------------ INT 0 ----------------------------

/* this macro is used to enable external INT0 interrupt */
#define EXT_INT0_INTERRUPT_ENABLE()                 (INTCONbits.INT0IE = INTERRUPT_ENABLE)
/* this macro is used to disable external INT0 interrupt */
#define EXT_INT0_INTERRUPT_DISABLE()                (INTCONbits.INT0IE = INTERRUPT_DISABLE)

/* this macro is used to clear external INT0 interrupt flag */
#define EXT_INT0_INTERRUPT_FLAG_CLEAR()             (INTCONbits.INT0IF = INTERRUPT_NOT_OCCUR)

/* this macro is used to set external INT0 interrupt rising edge */
#define EXT_INT0_INTERRUPT_RISING_EDGE_SET()        (INTCON2bits.INTEDG0 = INTERRUPT_RISING_EDGE)
/* this macro is used to set external INT0 interrupt falling edge */
#define EXT_INT0_INTERRUPT_FALLING_EDGE_SET()       (INTCON2bits.INTEDG0 = INTERRUPT_FALLING_EDGE)

// ------------------ INT 1 ----------------------------

/* this macro is used to enable external INT1 interrupt */
#define EXT_INT1_INTERRUPT_ENABLE()                 (INTCON3bits.INT1IE = INTERRUPT_ENABLE)
/* this macro is used to disable external INT1 interrupt */
#define EXT_INT1_INTERRUPT_DISABLE()                (INTCON3bits.INT1IE = INTERRUPT_DISABLE)

/* this macro is used to clear external INT1 interrupt flag */
#define EXT_INT1_INTERRUPT_FLAG_CLEAR()             (INTCON3bits.INT1IF = INTERRUPT_NOT_OCCUR)

/* this macro is used to set external INT1 interrupt rising edge */
#define EXT_INT1_INTERRUPT_RISING_EDGE_SET()        (INTCON2bits.INTEDG1 = INTERRUPT_RISING_EDGE)
/* this macro is used to set external INT1 interrupt falling edge */
#define EXT_INT1_INTERRUPT_FALLING_EDGE_SET()       (INTCON2bits.INTEDG1 = INTERRUPT_FALLING_EDGE)

// ------------------ INT 2 ----------------------------

/* this macro is used to enable external INT2 interrupt */
#define EXT_INT2_INTERRUPT_ENABLE()                 (INTCON3bits.INT2IE = INTERRUPT_ENABLE)
/* this macro is used to disable external INT2 interrupt */
#define EXT_INT2_INTERRUPT_DISABLE()                (INTCON3bits.INT2IE = INTERRUPT_DISABLE)

/* this macro is used to clear external INT2 interrupt flag */
#define EXT_INT2_INTERRUPT_FLAG_CLEAR()             (INTCON3bits.INT2F = INTERRUPT_NOT_OCCUR)

/* this macro is used to set external INT2 interrupt rising edge */
#define EXT_INT2_INTERRUPT_RISING_EDGE_SET()        (INTCON2bits.INTEDG2 = INTERRUPT_RISING_EDGE)
/* this macro is used to set external INT2 interrupt falling edge */
#define EXT_INT2_INTERRUPT_FALLING_EDGE_SET()       (INTCON2bits.INTEDG2 = INTERRUPT_FALLING_EDGE)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro is used to HIGH external INT1 interrupt priority */
#define EXT_INT1_INTERRUPT_PRIORITY_HIGH()          (INTCON3bits.INT1IP = INTERRUPT_PRIORITY_HIGH)
/* this macro is used to LOW external INT1 interrupt priority */
#define EXT_INT1_INTERRUPT_PRIORITY_LOW()           (INTCON3bits.INT1IP = INTERRUPT_PRIORITY_LOW)

/* this macro is used to HIGH external INT2 interrupt priority */
#define EXT_INT2_INTERRUPT_PRIORITY_HIGH()          (INTCON3bits.INT2IP = INTERRUPT_PRIORITY_HIGH)
/* this macro is used to LOW external INT2 interrupt priority */
#define EXT_INT2_INTERRUPT_PRIORITY_LOW()           (INTCON3bits.INT2IP = INTERRUPT_PRIORITY_LOW)

#endif

#endif


#if EXTERNAL_INTERRUPT_OnChange_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro is used to enable external RBx interrupt */
#define EXT_RBx_INTERRUPT_ENABLE()                  (INTCONbits.RBIE = INTERRUPT_ENABLE)
/* this macro is used to disable external RBx interrupt */
#define EXT_RBx_INTERRUPT_DISABLE()                 (INTCONbits.RBIE = INTERRUPT_DISABLE)

/* this macro is used to clear external RBx interrupt flag */
#define EXT_RBx_INTERRUPT_FLAG_CLEAR()              (INTCONbits.RBIF = INTERRUPT_NOT_OCCUR)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro is used to HIGH external RBx interrupt priority */
#define EXT_RBx_INTERRUPT_PRIORITY_HIGH()           (INTCON2bits.RBIP = INTERRUPT_PRIORITY_HIGH)
/* this macro is used to LOW external RBx interrupt priority */
#define EXT_RBx_INTERRUPT_PRIORITY_LOW()            (INTCON2bits.RBIP = INTERRUPT_PRIORITY_LOW)

#endif

#endif

/* Section : Data Type Declerations */

typedef void (* InterruptHandler)(void);

typedef enum{
    INTERRUPT_EXT_INT0,
    INTERRUPT_EXT_INT1,
    INTERRUPT_EXT_INT2
}interrupt_INTx_src_t;

typedef struct{
    void (*EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    uint8 edge;
    interrupt_INTx_src_t source;
    uint8 priority;
}interrupt_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_High)(void);
    void (*EXT_InterruptHandler_Low)(void);
    pin_config_t mcu_pin;
    uint8 priority;

}interrupt_RBx_t;

/* Section : Functions Declerations */

Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *INTx_Config);
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *INTx_Config);

Std_ReturnType interrupt_RBx_Init(const interrupt_RBx_t *RBx_Config);
Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t *RBx_Config);

#endif /* MCAL_EXTERNAL_INTERRUPT_H_ */