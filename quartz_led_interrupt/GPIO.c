#include <msp430f2272.h>

#include "GPIO.h"

#define LED BIT6                                            // Bind P4.6 as LED


void init_GPIO(){



    P2DIR |= BIT1;                                          // P2.1 - output pin for SMCLK
    P2SEL |= BIT1;

    P3DIR |= BIT1;                                          // Init P3.1 - pin10 for oscilator
    P3OUT |= BIT1;

    P4DIR |= LED;                                           // Init P4.6 - led
    P4OUT |= ~LED;


}
