## Tribute64 for Switch Code (Atmega32U4)

This one is a WORK IN PROGRESS sketch for use with retro-bit's Tribute64, in order to give it
proper right stick functionality, making it compatible with N64 NSO and other games/apps.

The Code itself has proper Button-Debounce, and 3 Modes of input.


## Building Instructions

- Download Arduino IDE, 

- Download the Bounce2 Library inside the Arduino IDE
- Download Arduino Lufa from https://github.com/Palatis/Arduino-Lufa and follow the instructions on it's repository
- Build and Flash for your ATMEGA32U4 Board
- Have Fun

## Pinmapping

Here is the Pinnumbers to Button Mapping for Connecting the actual physical cables to a Pro Micro.
    joystickUP.attach(0,INPUT_PULLUP);
    joystickDOWN.attach(1,INPUT_PULLUP);
    joystickLEFT.attach(2,INPUT_PULLUP);
    joystickRIGHT.attach(3,INPUT_PULLUP);

    buttonA.attach(4,INPUT_PULLUP);
    buttonB.attach(5,INPUT_PULLUP);
    buttonSTART.attach(6,INPUT_PULLUP);

    buttonCUP.attach(7,INPUT_PULLUP);
    buttonCDOWN.attach(8,INPUT_PULLUP);
    buttonCLEFT.attach(9,INPUT_PULLUP);
    buttonCRIGHT.attach(10,INPUT_PULLUP);

    buttonLB.attach(14,INPUT_PULLUP);
    buttonRB.attach(15,INPUT_PULLUP);
    buttonLT.attach(16,INPUT_PULLUP);
    buttonRT.attach(18,INPUT_PULLUP);

	#define N64_STICKX_PIN A1
	#define N64_STICKY_PIN A2

### Credits

Forked from fluffymadness' ATMega32U4-Switch-Fightstick sketch (https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick)

Special thanks to shinyquagsire's and progmem's reverseengineering work for the pokken tournament controller. (https://github.com/progmem/Switch-Fightstick)

Dean Camera for the LUFA Library

zlittell, msf-xinput was very helpful for starting.

thomasfredericks for the Bounce2Lib.
