#include <msp430f2272.h>



/**
 * main.c
 */
volatile unsigned int i;

void main(void)
{


    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//Pin 40 --> port2 b5
	//GPIO
	P2DIR |= ~BIT5; //P2.5 as input pin
	P2REN |= BIT5;  //P2.5 enabled for pull up\down
	P2IN |= BIT5;  //P2.5 chosen for pull up resistor
	P2IE  |= BIT5;  //P2.5 enable interrupt
	P2IES |= ~BIT5;  //P2.5 interrupt flag high-to-low , low-to-high

    P4DIR |= BIT6;                                           // Init P4.6 - led
    P4OUT |= ~BIT6;

    P2IFG &= ~BIT5;                                         //Clear flag

	__bis_SR_register(LPM0_bits + GIE);                     // Enter LPM0

}


#pragma vector=PORT2_VECTOR

__interrupt void Port2Button (void)
{
    P2IFG &= ~BIT5;                                         //Clear flag
    P4OUT ^= BIT6;                                                  //10-50ms
    for(i = 20000; i != 0; i--);
    P2IFG &= ~BIT5;                                         //Clear flag
}
