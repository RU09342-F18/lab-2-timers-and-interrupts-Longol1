#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;      // P1.0 LED is an output

    P2DIR &= ~BIT1;     // P2.1 switch is an input
    P2IE  |= BIT1;      // Makes P2.1 switch an interrupt pin
    P2IES |= BIT1;          // Detects the falling edge
    P2REN |= BIT1;         // Disables the pullup resistor
    P2OUT |= BIT1;
    P2IFG &= ~BIT1;     // Disables the interrupt flag

    TA1CCTL0 = CCIE;                           // CCR0 interrupt enabled
    TA1CTL = TASSEL_1 + MC_1 + ID_3;   // SMCLK, continuous mode, clear timer A register, 8 part divider
    TA1CCR0 = (400);                            // Sets the period

    __bis_SR_register(GIE);                   // Allows for the use of interrupts


    __bis_SR_register(LPM0_bits);             // Used for entering Low Power Mode


    while(1){}  //infinite loop, doesn't affect the cpu at all



   return 0;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)       //Interrupt for Timer1A0
{
    P1OUT ^= BIT0;   // Toggles P1.0 LED
    P2IFG &= ~BIT1;  // Disables the interrupt flag
}
#pragma vector=PORT2_VECTOR     //interrupt at Port 2
__interrupt void Port_2(void)
{
    if((P2IES & BIT1) != 0)         // interrupt is detected by falling edge
            {
                TA1CTL = TACLR;     // clears the clock
                TA1CTL= TASSEL_1 + MC_2 + ID_3;    //ACLK, Continuous mode, CLK/8
                P2IES &= ~BIT1;     // detects the rising edge

            }
            else
            {
                TA1CTL = MC_0;       // stops the clock
                TA1CCR0 = TA1R;         // takes the period how long you held down button and puts it into  CCR0
                TA1CTL = TASSEL_1 + MC_1 + ID_3;    //ACLK, Up-mode, CLK/8
                P2IES |= BIT1;      // detects the falling edge
            }
        P2IFG &= ~BIT1;  // Disables the interrupt flag

}
