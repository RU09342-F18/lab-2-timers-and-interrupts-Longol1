#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	CCTL0 = CCIE;        // CCR0 Interrupt enabled
	TA0CTL = TASSEL_1 + MC_1 + ID_3;    //ACLK, Up-mode, 8 part divider
	CCR0 = (20000);     // sets the timer speed

	P1DIR &= ~BIT3;     // makes P1.3 switch an input
	P1DIR |= BIT0;      // makes P1.0 an output
	P1DIR |= BIT6;      // makes P1.6 an output
    P1IE  |= BIT3;      // This sets the P1.3 to an interrupt pin


    __enable_interrupt();

    _BIS_SR(CPUOFF + GIE);        // Enter low power mode, and also enables the use of interrupts

    while(1){}  //infinite loop does not affect the cpu


	return 0;
}

#pragma vector=TIMER0_A0_VECTOR     // interrupt for timer0A0
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;   // Toggles P1.0 LED
    P1IFG &= ~BIT3;  // Disables the interrupt flag


}

#pragma vector=PORT1_VECTOR     //interrupt at Port 1
__interrupt void Port_1(void)
{
        P1OUT ^= BIT6;   // Toggles the P1.6 LED
        P1IFG &= ~BIT3;  // Disables the interrupt flag

}
