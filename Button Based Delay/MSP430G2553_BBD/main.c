#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	CCTL0 = CCIE;        // CCR0 Interrupt enabled
	TA0CTL = TASSEL_1 + MC_1 + ID_3;    //ACLK, Up-mode, CLK/8
	CCR0 = (400);     // sets the timer speed to blink at 10Hz

	P1DIR &= ~BIT3;         // sets P1.3 switch to an input
	P1IE  |= BIT3;           // Enables P1.3 to be an interrupt pin
	P1IES |= BIT3;          // Detects the falling edge
	P1REN &= ~BIT3;         // Disables the pullup resistor
    P1IFG &= ~BIT3;         // Disables the interrupt flag

	P1DIR |= BIT0;          // P1.0 is an output


	__enable_interrupt();


	while(1){}

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

    if((P1IES & BIT3) != 0)         // interrupt is detected by falling edge
        {
            TA0CTL = TACLR;     // clears the clock
            TA0CTL = TASSEL_1 + MC_2 + ID_3;    //ACLK, Continuous mode, CLK/8
            P1IES &= ~BIT3;     // detects the rising edge

        }
        else
        {
            TA0CTL = MC_0;       // stops the clock
            CCR0 = TAR;         // takes the period how long you held down button and puts it into  CCR0
            TA0CTL = TASSEL_1 + MC_1 + ID_3;    //ACLK, Up-mode, CLK/8
            P1IES |= BIT3;      // detects the falling edge
        }
    P1IFG &= ~BIT3;  // Disables the interrupt flag

}


