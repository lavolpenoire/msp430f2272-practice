#include <msp430f2272.h>


#include "MSstopwatch.h"
#include "Crystal.h"



void intit_MSSTW(expected_frequency){
    TBCCTL0 = CCIE;                                                 // CCR0 interrupt enabled OUTMOD_2

    switch (expected_frequency){                                    // CCR0 timer range 0-0xFFF (65535)
        case 1:                                                     // For 2MHz, 1 ms --> 125 ticks * ID_3
            TBCCR0 = 62;                                            // 62 -> 1000 Hz(tact in second) ,
                                                                    // 625 -> 100 Hz(tact in second) ,
                                                                    // 6250 -> 10 Hz(tact in second)
            break;
        case 2:                                                     // For 2MHz, 1 ms --> 250 ticks * ID_3
            TBCCR0 = 125;                                           // 125 -> 1000 Hz(tact in second) ,
                                                                    // 1250 -> 100 Hz(tact in second) ,
                                                                    // 12500 -> 10 Hz(tact in second)
            break;
        case 4:                                                     // For 4MHz, 1 ms --> 500 ticks * ID_3
            TBCCR0 = 250;                                           // 250 -> 1000 Hz(tact in second) ,
                                                                    // 2500 -> 100 Hz(tact in second) ,
                                                                    // 25000 -> 10 Hz(tact in second)
            break;
        case 8:                                                     // For 8MHz, 1 ms --> 1000 ticks * ID_3
            TBCCR0 = 500;                                           // 500 -> 1000 Hz(tact in second) ,
                                                                    // 5000 -> 100 Hz(tact in second) ,
                                                                    // 50000 -> 10 Hz(tact in second)
            break;
        default:                                                    // Default == 8MHz
            TBCCR0 = 500;                                           // 500 -> 1000 Hz(tact in second) ,
                                                                    // 5000 -> 100 Hz(tact in second) ,
                                                                    // 50000 -> 10 Hz(tact in second)
            break;
        }

    TBCTL |= TBSSEL_2 | MC_1 | ID_3 ;
}
