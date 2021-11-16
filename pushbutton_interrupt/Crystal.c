#include "Crystal.h"


#include <msp430f2272.h>



void init_HF(expected_frequency)
{

    BCSCTL1 |= XTS ;                                        // LFXT1 = High Frequency mode XTAL
    BCSCTL3 |= LFXT1S1;                                     // LFXT1S1 = 8 Mhz


    volatile unsigned int i;
    do
    {
      IFG1 &= ~OFIFG;                                       // Clear OSCFault flag
      for (i = 0xFF; i > 0; i--)                            // Time for flag to set
      {__delay_cycles(1);}
    }
    while ((IFG1&OFIFG)!=0);                                // OSCFault flag still set?

    BCSCTL2 |= SELS;                                        // SMCLK = LFXT1 (safe)

                                                            //change DIVider to change direct Frequecy
    switch (expected_frequency){
    case 1:
        BCSCTL2 |= DIVS_3;
        break;
    case 2:
        BCSCTL2 |= DIVS_2;
        break;
    case 4:
        BCSCTL2 |= DIVS_1;
        break;
    case 8:
        BCSCTL2 |= DIVS_0;
        break;
    default:                                                // Default == 8MHz
        BCSCTL2 |= DIVS_0;
        break;
    }

}
