#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR &= ~BIT3;         // This sets P1.3 Button to an input
    P1DIR |= BIT0;          // P1.0 are going to be used as outputs
    P1DIR |= BIT6;          // P1.6 are going to be used as outputs
    P1IE  |= BIT3;          // This sets the P1.3 to an interrupt pin


    P1OUT &= ~BIT0;         // This turns P1.0 LED off
    P1OUT |= BIT6;          // This turns P1.6 LED on

    __enable_interrupt();   //enables interrupts to be used

    while(1){}              //infinite loop to keep running

    return 0;
}


#pragma vector=PORT1_VECTOR     //interrupt at Port 1
__interrupt void Port_1(void)
{
        P1OUT ^= BIT0;   // Toggles the P1.0 LED
        P1OUT ^= BIT6;   // Toggles the P1.6 LED
        P1IFG &= ~BIT3;  // Disables the interrupt flag


}








