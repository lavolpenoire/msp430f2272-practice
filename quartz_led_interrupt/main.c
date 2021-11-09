#include <msp430f2272.h>

#include "GPIO.h"                                           // Include for init_GPIO()  - initialize function for pins configure
#include "Crystal.h"                                        // Include for init_HF()    - initialize function for 8MHz crystal
#include "MSstopwatch.h"                                    // Include for init_MSSTW() - initialize function for 1ms counter

/*
 * TO-DO Tasks
 * 1. DIVS ? Must work ------------------------- DONE
 * 2. I/o pins Init -> file -------------------- DONE
 * 4. Clock Init -> file ----------------------- DONE
 * 5. MAKE MS COUNTER FROM TIMER EXIST---------- DONE
 * 6. Make interrupt by interrupting timer ----- DONE
 * 7. Write programm for pushbutton interrupt --
 * 8. Write UART -------------------------------
 *
 */

int ms_count=0;
int on_cycle = 500;                                         // 1000 == 1000 ms == 1 s
int off_cycle = 500;                                       // 1000 == 1000 ms == 1 s
int expected_frequency= 1;

int isLED = 1;



void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;		                        // Stop watchdog timer

    init_HF(expected_frequency);                            // Change argument  with 1,2,4,8 - to set 1 MHz, 2 MHz, 4 MHz, 8 MHz

    init_GPIO();                                            // Configure pins

    intit_MSSTW(expected_frequency);

    on_cycle *=2;
    off_cycle *=2;

    __bis_SR_register(LPM0_bits + GIE);                     // Enter LPM0

}



#pragma vector=TIMERB0_VECTOR

__interrupt void Timer_B (void)
{
    ms_count++;

    if (isLED == 0){                                        // Check if LED off
        if(ms_count>=on_cycle){                            // Count LED ON timer
            P3OUT  ^=BIT1;                                  // Toggle pins
            P4OUT ^= LED;
            //__delay_cycles(15);                             // For prevent lagging
            ms_count = 10;
            isLED = 1;
        }
    }
    if (isLED == 1){                                        // Check if LED oon
        if(ms_count>=off_cycle){                             // Count LED ON timer
            P3OUT  ^=BIT1;                                  // Toggle pins
            P4OUT ^= LED;
            //__delay_cycles(15);                             // For prevent lagging
            ms_count = 10;
            isLED = 0;
        }
    }
}
