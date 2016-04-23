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

Connection:
GSM --> connect to
Txd     Arduino D2
Rxd     Arduino D3
VCC     External 5V 2A source
Gnd     Gnd

Don't forget to short all grounds of the circuit
Make sure you have enough balance to send text message or call.

*******************************************************************************/

//include the library
#include <newGSM.h>
byte rx = 2;
byte tx = 3;
char* number = "+8801680529746";

newGSM myGSM(rx,tx); 

void setup() {
  Serial.begin(9600);
  myGSM.begin(9600);
  myGSM.ATtest(); //it'll print OK in Serial Monitor, if everything works fine. Else it'll print Error.
  delay(2000);
  myGSM.call(number);
}

void loop() {
  // put your main code here, to run repeatedly:

}
