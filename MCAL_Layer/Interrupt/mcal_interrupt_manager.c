

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1;
static volatile uint8 RB5_flag = 1;
static volatile uint8 RB6_flag = 1;
static volatile uint8 RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() interrupt_Handler_High(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();   
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();   
    }
    else {/* Nothing */}
    
}

void __interrupt(low_priority) interrupt_Handler_Low(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();   
    }
    else {/* Nothing */}

}

#else


void __interrupt() interrupt_Handler(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();   
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();   
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();   
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
    && (HIGH == PORTBbits.RB4) && (RB4_flag == 1))
    {
        RB4_flag = 0;
        RB4_ISR(HIGH);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (LOW == PORTBbits.RB4) && (RB4_flag == 0))
    {
        RB4_flag = 1;
        RB4_ISR(LOW);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (HIGH == PORTBbits.RB5) && (RB5_flag == 1))
    {
        RB5_flag = 0;
        RB5_ISR(HIGH);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (LOW == PORTBbits.RB5) && (RB5_flag == 0))
    {
        RB5_flag = 1;
        RB5_ISR(LOW);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (HIGH == PORTBbits.RB6) && (RB6_flag == 1))
    {
        RB6_flag = 0;
        RB6_ISR(HIGH);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (LOW == PORTBbits.RB6) && (RB6_flag == 0))
    {
        RB6_flag = 1;
        RB6_ISR(LOW);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (HIGH == PORTBbits.RB7) && (RB7_flag == 1))
    {
        RB7_flag = 0;
        RB7_ISR(HIGH);      
    }
    else {/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (LOW == PORTBbits.RB7) && (RB7_flag == 0))
    {
        RB7_flag = 1;
        RB7_ISR(LOW);      
    }
    else {/* Nothing */}
}

#endif