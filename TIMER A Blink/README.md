# TIMER A Blink
The purpose of TIMER A Blink is the same as Multiple Bink except there is not a software loop with delays. Instead,
a TIMER is used to control the rate at which the LEDs blink. The clock for the timer was set, and the capture 
compare register was set and the interrupt was enabled. Every time the timer reaches the value of the capture 
compare register, the LED toggles.

## Processor
- MSP430FR6989
- MSP430G2553
# Differences
- The only difference is the pins for the LEDs on each board.