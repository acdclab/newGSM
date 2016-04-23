/******************************************************************************
This Library is written by Shimanto, EEE, BUET
Started writing the library on April 1, 2016
mail me at shimanto@acdclabs.com for query
special thanks to my friend, with whom I can share my crazy ideas,
Shariful Islam Foysal (foysal@acdclabs.com)
and my respective senior, who taught me a lot of things and still helps me
Zaheen Mustakin Ayon

        *************************************
        **The library is under Construction**
        *************************************

*******************************************************************************/

#ifndef newGSM_h
#define newGSM_h

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include<SoftwareSerial.h>

class newGSM
{

  public:
    newGSM(uint8_t rx, uint8_t tx);
    ~newGSM();
    void ATtest();
    void begin(int baud_rate);
    byte rx_byte;
    void call(char* number);
    void SendTextMessage(char* msg, char* number);
    void turnOff();

  private:
    uint8_t pin_RX, pin_TX;
    SoftwareSerial _newGSMSerial;
    int8_t _sendATcommand2(char* ATcommand, char* expected_answer1,char* expected_answer2, unsigned int timeout);
    int8_t _sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout);
};

#endif
