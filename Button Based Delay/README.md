# Button Based Delay
To start off, an onboard LED should be set to blink at a rate of 10Hz once the board recieves power. There is 
then a button that is linked to the rate of the LED. The time the button is held, is equal to the 
time the LED is on as well as the time the LED is off. The LED will remain blinking at that rate until the button
is pressed again. 

## Code
When the button is pressed, an interrupt is called which keeps track of the time for how long the button is pressed. 
When the button is released, the time is saved then saved. The time is then set to the LED as the rate for it to 
blink. If the button is pressed again, the interrupt is called and the process is repeated. 