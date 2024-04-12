#include "LUFAConfig.h"
#include <LUFA.h>
#include "Joystick.h"
#define BOUNCE_WITH_PROMPT_DETECTION
#include <Bounce2.h>

#define MILLIDEBOUNCE 1 //Debounce time in milliseconds
#define pinOBLED 21  //Onboard LED pin


byte buttonStatus[15];

/*
  0x4000,
  0x8000,
#define CAPTURE_MASK_ON 0x2000
#define R3_MASK_ON 0x800
#define L3_MASK_ON 0x400
 */
#define DPAD_UP_MASK_ON         0b0000000000000000
#define DPAD_UPRIGHT_MASK_ON    0b0000000000000001
#define DPAD_RIGHT_MASK_ON      0b0000000000000010
#define DPAD_DOWNRIGHT_MASK_ON  0b0000000000000011
#define DPAD_DOWN_MASK_ON       0b0000000000000100
#define DPAD_DOWNLEFT_MASK_ON   0b0000000000000101
#define DPAD_LEFT_MASK_ON       0b0000000000000110
#define DPAD_UPLEFT_MASK_ON     0b0000000000000111
#define DPAD_NOTHING_MASK_ON    0b0000000000001000
#define Y_MASK_ON       0b0000000000000001
#define B_MASK_ON       0b0000000000000010
#define A_MASK_ON       0b0000000000000100
#define X_MASK_ON       0b0000000000001000
#define LB_MASK_ON      0b0000000000010000
#define RB_MASK_ON      0b0000000000100000
#define ZL_MASK_ON      0b0000000001000000
#define ZR_MASK_ON      0b0000000010000000
#define SELECT_MASK_ON  0b0000000100000000
#define START_MASK_ON   0b0000001000000000
#define HOME_MASK_ON    0b0001000000000000

#define BUTTONUP 0
#define BUTTONDOWN 1
#define BUTTONLEFT 2
#define BUTTONRIGHT 3
#define BUTTONA 4
#define BUTTONB 5
#define BUTTONCUP 6
#define BUTTONCDOWN 7
#define BUTTONLB 8
#define BUTTONRB 9
#define BUTTONLT 10
#define BUTTONRT 11
#define BUTTONSTART 12
#define BUTTONCLEFT 13
#define BUTTONCRIGHT 14

#define N64_STICKX_PIN A9
#define N64_STICKY_PIN A8

Bounce joystickUP = Bounce();
Bounce joystickDOWN = Bounce();
Bounce joystickLEFT = Bounce();
Bounce joystickRIGHT = Bounce();
Bounce buttonA = Bounce();
Bounce buttonB = Bounce();

Bounce buttonCUP = Bounce();
Bounce buttonCDOWN = Bounce();
Bounce buttonCLEFT = Bounce();
Bounce buttonCRIGHT = Bounce();

Bounce buttonLB = Bounce();
Bounce buttonRB = Bounce();
Bounce buttonLT = Bounce();
Bounce buttonRT = Bounce();
Bounce buttonSTART = Bounce();


void setupPins(){
    joystickUP.attach(2,INPUT_PULLUP);
    joystickDOWN.attach(0,INPUT_PULLUP);
    joystickLEFT.attach(1,INPUT_PULLUP);
    joystickRIGHT.attach(3,INPUT_PULLUP);

    buttonA.attach(20,INPUT_PULLUP);
    buttonB.attach(21,INPUT_PULLUP);
    buttonSTART.attach(5,INPUT_PULLUP);

    buttonCUP.attach(14,INPUT_PULLUP);
    buttonCDOWN.attach(19,INPUT_PULLUP);
    buttonCLEFT.attach(18,INPUT_PULLUP);
    buttonCRIGHT.attach(15,INPUT_PULLUP);

    buttonLB.attach(7,INPUT_PULLUP);
    buttonRB.attach(10,INPUT_PULLUP);
    buttonLT.attach(6,INPUT_PULLUP);
    buttonRT.attach(16,INPUT_PULLUP);
    

    joystickUP.interval(MILLIDEBOUNCE);
    joystickDOWN.interval(MILLIDEBOUNCE);
    joystickLEFT.interval(MILLIDEBOUNCE);
    joystickRIGHT.interval(MILLIDEBOUNCE);

    buttonA.interval(MILLIDEBOUNCE);
    buttonB.interval(MILLIDEBOUNCE);
    buttonSTART.interval(MILLIDEBOUNCE);

    buttonCUP.interval(MILLIDEBOUNCE);
    buttonCDOWN.interval(MILLIDEBOUNCE);
    buttonCLEFT.interval(MILLIDEBOUNCE);
    buttonCRIGHT.interval(MILLIDEBOUNCE);

    buttonLB.interval(MILLIDEBOUNCE);
    buttonRB.interval(MILLIDEBOUNCE);
    buttonLT.interval(MILLIDEBOUNCE);
    buttonRT.interval(MILLIDEBOUNCE);
    
    
    pinMode(pinOBLED, OUTPUT);  
    //Set the LED to low to make sure it is off
    digitalWrite(pinOBLED, HIGH);
}


void setup() {
    setupPins();
    SetupHardware();
    GlobalInterruptEnable();
}


void loop() {
    buttonRead();
    //processDPAD()
    processLANALOG();
    processRANALOG();
    buttonProcessing();
    HID_Task();
    // We also need to run the main USB management task.
    USB_USBTask();
}

void buttonRead()
{
  if (joystickUP.update()) {buttonStatus[BUTTONUP] = joystickUP.fell();}
  if (joystickDOWN.update()) {buttonStatus[BUTTONDOWN] = joystickDOWN.fell();}
  if (joystickLEFT.update()) {buttonStatus[BUTTONLEFT] = joystickLEFT.fell();}
  if (joystickRIGHT.update()) {buttonStatus[BUTTONRIGHT] = joystickRIGHT.fell();}
  if (buttonA.update()) {buttonStatus[BUTTONA] = buttonA.fell();}
  if (buttonB.update()) {buttonStatus[BUTTONB] = buttonB.fell();}

  if (buttonCUP.update()) {buttonStatus[BUTTONCUP] = buttonCUP.fell();}
  if (buttonCDOWN.update()) {buttonStatus[BUTTONCDOWN] = buttonCDOWN.fell();}
  if (buttonCLEFT.update()) {buttonStatus[BUTTONCLEFT] = buttonCLEFT.fell();}
  if (buttonCRIGHT.update()) {buttonStatus[BUTTONCRIGHT] = buttonCRIGHT.fell();}

  if (buttonLB.update()) {buttonStatus[BUTTONLB] = buttonLB.fell();}
  if (buttonRB.update()) {buttonStatus[BUTTONRB] = buttonRB.fell();}
  if (buttonLT.update()) {buttonStatus[BUTTONLT] = buttonLT.fell();}
  if (buttonRT.update()) {buttonStatus[BUTTONRT] = buttonRT.fell();}
  if (buttonSTART.update()) {buttonStatus[BUTTONSTART] = buttonSTART.fell();}

}

void processDPAD(){
    if ((buttonStatus[BUTTONUP]) && (buttonStatus[BUTTONRIGHT])){ReportData.HAT = DPAD_UPRIGHT_MASK_ON;}
    else if ((buttonStatus[BUTTONDOWN]) && (buttonStatus[BUTTONRIGHT])) {ReportData.HAT = DPAD_DOWNRIGHT_MASK_ON;} 
    else if ((buttonStatus[BUTTONDOWN]) && (buttonStatus[BUTTONLEFT])) {ReportData.HAT = DPAD_DOWNLEFT_MASK_ON;}
    else if ((buttonStatus[BUTTONUP]) && (buttonStatus[BUTTONLEFT])){ReportData.HAT = DPAD_UPLEFT_MASK_ON;}
    else if (buttonStatus[BUTTONUP]) {ReportData.HAT = DPAD_UP_MASK_ON;}
    else if (buttonStatus[BUTTONDOWN]) {ReportData.HAT = DPAD_DOWN_MASK_ON;}
    else if (buttonStatus[BUTTONLEFT]) {ReportData.HAT = DPAD_LEFT_MASK_ON;}
    else if (buttonStatus[BUTTONRIGHT]) {ReportData.HAT = DPAD_RIGHT_MASK_ON;}
    else{ReportData.HAT = DPAD_NOTHING_MASK_ON;}
}

void processLANALOG(){
    int LX = analogRead(N64_STICKX_PIN);
    LX += (( (int)(0.027 * 255 / 2) ) << 2); //center the axis
    LX -= 512; //center was around 512, now it's around 0
    LX *= 1.615; //adjust the range
    LX += 512; //center was around 0, now it's around 512
    LX >>= 2; //center was around 512, now it's around 128
    if (LX > 255) {LX = 255;}
    if (LX < 0) {LX = 0;}

    int LY = analogRead(N64_STICKY_PIN);
    LY += (( (int)(-0.106 * 255 / 2) ) << 2); //center the axis
    LY -= 512; //center was around 512, now it's around 0
    LY *= 1.615; //adjust the range
    LY += 512; //center was around 0, now it's around 512
    LY >>= 2; //center was around 512, now it's around 128
    if (LY > 255) {LY = 255;}
    if (LY < 0) {LY = 0;}

    if ((LX > 118) && (LX < 138) && (LY > 118) && (LY < 138)) {
      LX = 128;
      LY = 128;
    }

    ReportData.LX = (uint8_t) LX;
    ReportData.LY = (uint8_t) LY;
}

void processRANALOG(){
    byte RY = 128;
    if (buttonStatus[BUTTONCUP]) {RY -= 128;}
    if (buttonStatus[BUTTONCDOWN]) {RY += 127;}
    ReportData.RY = RY;

    byte RX = 128;
    if (buttonStatus[BUTTONCLEFT]) {RX -= 128;}
    if (buttonStatus[BUTTONCRIGHT]) {RX += 127;}
    ReportData.RX = RX;
}

void buttonProcessing(){
  if (buttonStatus[BUTTONA]) {ReportData.Button |= A_MASK_ON;}
  if (buttonStatus[BUTTONB]) {ReportData.Button |= B_MASK_ON;}
  if (buttonStatus[BUTTONSTART]){ReportData.Button |= START_MASK_ON;}
  if (buttonStatus[BUTTONLB]) {ReportData.Button |= LB_MASK_ON;}
  if (buttonStatus[BUTTONRB]) {ReportData.Button |= RB_MASK_ON;}
  if (buttonStatus[BUTTONLT]) {ReportData.Button |= ZL_MASK_ON;}

  if (buttonStatus[BUTTONRT]) {
    ReportData.HAT = DPAD_NOTHING_MASK_ON;

    if (buttonStatus[BUTTONDOWN]) {ReportData.Button |= SELECT_MASK_ON;}
    else if (buttonStatus[BUTTONRIGHT]) {ReportData.Button |= HOME_MASK_ON;}
    else if (buttonStatus[BUTTONUP]) {ReportData.Button |= X_MASK_ON;}
    else if (buttonStatus[BUTTONLEFT]) {ReportData.Button |= Y_MASK_ON;}
    else {ReportData.Button |= ZR_MASK_ON;}

  } else {
    processDPAD();
  }
}