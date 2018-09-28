#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;      // P1.0 LED is an output
    P1OUT &= ~BIT0;     // P1.0 LED is turned off
    P4DIR |= BIT7;      // P4.7 LED is an output

    P2DIR &= ~BIT1;     // P2.1 switch is an input
    P2IE  |= BIT1;      // Makes P2.1 switch an interrupt pin
    P2REN |= BIT1;      // Enables pull up resistor for P2.1 switch
    P2OUT |= BIT1;      // sets the P2.1 switch resistor to be pull up
    P2IFG &= ~BIT1;     // Disables the interrupt flag

    TA1CCTL0 = CCIE;                           // CCR0 interrupt enabled
    TA1CTL = TASSEL_2 + MC_2 + TACLR + ID_3;   // SMCLK, continuous mode, clear timer A register, 8 part divider
    TA0CCR0 = 1000;                            // Sets the period

    __bis_SR_register(GIE);                   // Allows for the use of interrupts


    __bis_SR_register(LPM0_bits);             // Used for entering Low Power Mode


    while(1){}  //infinite loop, doesn't affect the cpu at all



   return 0;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)       //Interrupt for Timer1A0
{
    P4OUT ^= BIT7;   // Toggles P4.7 LED

}
#pragma vector=PORT2_VECTOR     //interrupt at Port 2
__interrupt void Port_1(void)
{
        P1OUT ^= BIT0;   // Toggles the P1.6 LED
        P2IFG &= ~BIT1;  // Disables the interrupt flag

}
