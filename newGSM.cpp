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

#include "Arduino.h"
#include "newGSM.h"

//constructor
newGSM::newGSM(uint8_t rx, uint8_t tx)
	: _newGSMSerial(rx,tx)
{
	pin_RX = rx;
	pin_TX = tx;
}

// destructor
newGSM::~newGSM()
{
	_newGSMSerial.~SoftwareSerial();
}

void newGSM::begin(int baud_rate)
{
    _newGSMSerial.begin(baud_rate);
}

//returns 0 for timeout and no match,
//1 if the response of ATCommand is expected_answer1
int8_t newGSM::_sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout)
{
    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    memset(response, '\0', 100);    // Initialize the string
    delay(100);
    while( _newGSMSerial.available() > 0) _newGSMSerial.read();    // Clean the input buffer
    _newGSMSerial.println(ATcommand);    // Send the AT command
    x = 0;
    previous = millis();
    // this loop waits for the answer
    do{
        if(_newGSMSerial.available() != 0){
            // if there are data in the UART input buffer, reads it and checks for the asnwer
            response[x] = _newGSMSerial.read();
            x++;
            // check if the desired answer  is in the response of the module
            if (strstr(response, expected_answer) != NULL)
            {
                answer = 1;
            }
        }
    }while((answer == 0) && ((millis() - previous) < timeout)); // Waits for the asnwer with time out
    return answer;
}

//returns 0 for timeout and no match,
//1 if the response of ATCommand is expected_answer1, 2 if the response of ATCommand is expected_answer2
int8_t newGSM::_sendATcommand2(char* ATcommand, char* expected_answer1,char* expected_answer2, unsigned int timeout)
{
    uint8_t x=0,  answer=0; //x counts the length of the string, answer is finally returned
    char response[100]; //response is stored in this string variable
    unsigned long previous; //keeps the time
    memset(response, '\0', 100);    // Initialize the response string with '\0'
    delay(100);
    while(_newGSMSerial.available() > 0) _newGSMSerial.read();    // Clean the input buffer
    _newGSMSerial.println(ATcommand);    // Send the AT command
    x = 0;
    previous = millis();
    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(_newGSMSerial.available() != 0){
            response[x] = _newGSMSerial.read(); //read the whole response string by one after another letter
            x++;
            // check if the desired answer 1 is in the response of the module
            if (strstr(response, expected_answer1) != NULL) //strstr finds a string in another string
            {
                answer = 1;
            }
            // check if the desired answer 2 is in the response of the module
            if (strstr(response, expected_answer2) != NULL)
            {
                answer = 2;
            }
        }
        // do the same thing until expected_response is not found and time has not been out yet!
    }while((answer == 0) && ((millis() - previous) < timeout));
    return answer;
}

//Alhamdulillah! working fine
//will return OK if everything works fine
//else will return Error!
void newGSM::ATtest()
{
    if(_sendATcommand("AT", "OK", 5000))
    {
        Serial.println("OK"); //Alhamdulillah
    }
    else
    {
        Serial.println("Error");
    }
}

//Alhamdulillah! working fine.
//put a number to call that number
void newGSM::call(char* number)
{
    char temp_str[50]="";
    strcat(temp_str,"ATD");
    strcat(temp_str,number);
    strcat(temp_str,";");
    _sendATcommand(temp_str,"OK",5000);
}

//Alhamdulillah! working fine.
void newGSM::SendTextMessage(char* msg, char* number)
{
    _newGSMSerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
    delay(100);
    while( _newGSMSerial.available() > 0) _newGSMSerial.read();    // Clean the input buffer
    char temp_str[50]="";
    strcat(temp_str,"AT+CMGS=");
    strcat(temp_str,"\"");
    strcat(temp_str,number);
    strcat(temp_str,"\"");
    _newGSMSerial.println(temp_str);//send sms message, be careful need to add a country code before the cellphone number
    delay(1000);
    _newGSMSerial.print(msg);//the content of the message
    delay(1000);
    _newGSMSerial.print((char)26);//the ASCII code of the ctrl+z is 26
    delay(1000);
    _newGSMSerial.println();

}

//Alhamdulillah, working fine
void newGSM::turnOff()
{
    while(_newGSMSerial.available()) _newGSMSerial.read();
    _newGSMSerial.println("AT+CPOWD=1");
}
