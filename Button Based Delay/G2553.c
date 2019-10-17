//Michael Johns
//MSP430G2553
//Button Delay
#include <msp430.h>

long frequency;
int reset = 0;
int start = 0;
int end = 0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   //stop watchdog timer

    CCTL0 |= CCIE;                              //enable timer interrupt in compare mode
    CCTL0 &= ~TAIFG;                            //clear interrupt flag
    TA0CTL = TASSEL_1 + MC_2 + ID_3;            //ACLK, continuous mode, clock divided by 8
    TA0CCR0 = 0;                                //initialize timer A0 capture control register
    frequency = 0;                              //initialize frequency variable

    P1IE  |= BIT3;                              //enable interrupt on P1.3
    P1IES |= BIT3;                              //Hi/Lo edge triggered
    P1REN |= BIT3;                              //enable pull up resistor
    P1OUT |= BIT3;                              //turn on pin
    P1IFG &= ~BIT3;                             //clear interrupt flag
    P1DIR |= BIT0;                              //set direction to output

    __bis_SR_register(GIE);                     //enable interrupts

    while(1){
        if(reset == 1)                          //if reset = 1
        {
            reset = 0;                          //reset variable
            if(end <= start){                   //if counter resets between holds
                TA0CCR0 = 65535-start+end+TA0R; //TA0 = 2^16 - when button is pressed + when button is let go + last button press time
                frequency = 65535+end-start;    //frequency gets new value
            }
            else
            {
                TA0CCR0=end-start+TA0R;         //TA0 = when button is released - button pressed + last button press time
                frequency = end-start;          //frequency gets new value
            }
        }
    }
}

#pragma vector=TIMER0_A0_VECTOR                     //interrupt protocol and memory allocation
__interrupt void Timer_A (void)                     //interrupt name
{
    P1OUT ^= BIT0;                                  //toggle LED
    TA0CCR0 = TA0CCR0 + frequency;                  //increment TA0CCR0
}
#pragma vector=PORT1_VECTOR                         //interrupt protocol and memory allocation
__interrupt void Port_1(void)                       //interrupt name
{
    if(P1IES & BIT3)                                //if button is pressed
    {
        start = TA0R;                               //start gets time button is pressed
    }
    else                                            //interrupt occurs and button is no longer pressed
    {
        end = TA0R;                                 //end gets time button was released
        reset = 1;                                  //set reset to 1
    }
    P1IES ^= BIT3;                                  //Lo/Hi edge triggered
    P1IFG &= ~BIT3;                                 //reset interrupt flag
}
