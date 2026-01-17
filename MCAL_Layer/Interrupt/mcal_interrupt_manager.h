#ifndef MCAL_INTERRUPT_MANAGER_H_
#define MCAL_INTERRUPT_MANAGER_H_

/* Section : Inlcudes */

#include "mcal_interrupt_cfg.h"

/* Section : Macro Declerations */

/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

/* Section : Functions Declerations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RBx_source);
void RB5_ISR(uint8 RBx_source);
void RB6_ISR(uint8 RBx_source);
void RB7_ISR(uint8 RBx_source);


#endif /* MCAL_INTERRUPT_MANAGER_H_ */