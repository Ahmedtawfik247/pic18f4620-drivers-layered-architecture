#ifndef MCAL_INTERRUPT_CFG_H_
#define MCAL_INTERRUPT_CFG_H_

/* Section : Inlcudes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* Section : Macro Declerations */

#define INTERRUPT_ENABLE                1
#define INTERRUPT_DISABLE               0
    
#define INTERRUPT_OCCUR                 1
#define INTERRUPT_NOT_OCCUR             0

#define INTERRUPT_RISING_EDGE           1
#define INTERRUPT_FALLING_EDGE          0
    
#define INTERRUPT_PRIORITY_ENABLE       1
#define INTERRUPT_PRIORITY_DISABLE      0

#define INTERRUPT_PRIORITY_HIGH         1
#define INTERRUPT_PRIORITY_LOW          0

/* Section : Macro Functions Declerations */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro is used to enable priority levels */
#define INTERRUPT_PriorityLevelsEnable()          (RCONbits.IPEN = INTERRUPT_ENABLE)
/* this macro is used to disable priority levels */
#define INTERRUPT_PriorityLevelsDisable()         (RCONbits.IPEN = INTERRUPT_DISABLE)

/* this macro is used to enable high priority global interrupt */
#define INTERRUPT_Global_Interrupt_High_Enable()  (INTCONbits.GIEH = INTERRUPT_ENABLE)
/* this macro is used to disable high priority global interrupt */
#define INTERRUPT_Global_Interrupt_High_Disable() (INTCONbits.GIEH = INTERRUPT_DISABLE)

/* this macro is used to enable low priority global interrupt */
#define INTERRUPT_Global_Interrupt_Low_Enable()   (INTCONbits.GIEL = INTERRUPT_ENABLE)
/* this macro is used to disable low priority global interrupt */
#define INTERRUPT_Global_Interrupt_Low_Disable()  (INTCONbits.GIEL = INTERRUPT_DISABLE)

#else

/* this macro is used to global interrupt */
#define INTERRUPT_Global_Interrupt_Enable()       (INTCONbits.GIE = INTERRUPT_ENABLE)
/* this macro is used to global interrupt */
#define INTERRUPT_Global_Interrupt_Disable()      (INTCONbits.GIE = INTERRUPT_DISABLE)

/* this macro is used to enable peripheral interrupt */
#define INTERRUPT_PeripheralInterrupt_Enable()    (INTCONbits.PEIE = INTERRUPT_ENABLE)
/* this macro is used to disable peripheral interrupt */
#define INTERRUPT_PeripheralInterrupt_Disable()   (INTCONbits.PEIE = INTERRUPT_DISABLE)

#endif


/* Section : Data Type Declerations */

   

/* Section : Functions Declerations */



#endif /* MCAL_INTERRUPT_CFG_H_ */