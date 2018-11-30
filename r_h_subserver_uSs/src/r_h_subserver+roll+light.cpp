/*
*
* subserver
*
* ROLLER BLINDS
* controls roller blinds
* accepts trigger from slave or master
*
*
* ROLLER BLINDS
* 2 bottons report open/shut (short press) or up/down (long press) to master
*
*/

#include <Arduino.h>
#include <HardWire.h>
#include <EasyButton.h>
#include <TMCStepper.h>
#include <NeoPixelBus.h>
// #include <SK6812.h>



// set i2c address
// set relative masters' addresses
// byte masterMaddr = 000 ; // relative master address // don't set - he will call YOU!
// byte masterSaddr = 001 ; // relative slave address // Don't set. Pi will request

// set own master & slave addresses
byte ownMaddr = 010 ; // 020,030,040,050,...
byte ownSaddr = 011 ; // 021,031,041,051,...

// set relative/fellow slave addresses // here none because this is an aio unit
// byte slave1Saddr = 031 ; // 041,051,061,071,081,...
// byte slave2Saddr = 041 ; // 051,061,071,081,091,...



void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}
