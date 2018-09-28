#include <msp430.h>



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // enables the use of GPIO

    P1DIR &= ~BIT1;     // Makes P1.1 switch an input
    P1REN |= BIT1;      // P1.1 pull up resistor is enabled
    P1OUT |= BIT1;      // P1.1 makes the resistor pull up
    P1IE |= BIT1;       // P1.1 is now the interrupt pin

    P1DIR |= BIT0;      // P1.0 LED is an output
    P1OUT &= ~BIT0;
    P2DIR |= BIT0;      // P2.0 LED is an output


    int i1;             // counter

    __enable_interrupt();

    while(1)
    {
        if(i1 > 10000)          // the speed of the blink
        {
            P2OUT ^= BIT0;      // P2.0 LED toggles
            i1 = 0;             // Resets i1 to 0 so i1 can count back up to 10000
        }
        i1++;                   // the counter is incremented

    }

    return 0;
}


#pragma vector=PORT1_VECTOR     //interrupt at Port 1
__interrupt void Port_1(void)
{
        P1OUT ^= BIT0;   // Toggles the P1.0 LED
        P1IFG &= ~BIT1;  // Disables the interrupt flag


}


