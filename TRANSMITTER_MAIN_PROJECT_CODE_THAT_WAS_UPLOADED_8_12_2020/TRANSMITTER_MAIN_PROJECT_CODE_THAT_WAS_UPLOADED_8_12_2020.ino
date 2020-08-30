//Call your library below so you can use the library function./
//____________________________________________________________
#include <dht11.h>                                            /////                                        /////
#include "Arduino.h"                                         /////
#include <SPI.h>                                            /////  
#include <RF24.h>                                           ////
//__________________________________________________________///

//___________________ This is just the way the RF24 library works:__________________________________
// Hardware configuration: Set up nRF24L01 radio on SPI bus (pins 10, 11, 12, 13) plus pins 7 & 8
RF24 radio(7, 8);
dht11 DHT11; 
//__________________________________________________________________________________________________

//_______________________________Machine state parameters___________________________________________
int ledState = LOW;
unsigned long previousMillis= 0; // will store the last time the LED was updated.
long onTime = 20; // millisecons of ON-Time'
long offTime = 5000; // milliseconds of OFF-Time' 

int NRFstate1 = LOW;
unsigned long previousMillis1= 0; // will store the last time the LED was updated.
long onTime1 = 40; // millisecons of ON-Time'
long offTime1 = 40; // milliseconds of OFF-Time' 
//_____________________________________________________________________________________________________________

// ________________________COMPONENT PIN CONNECTION TO THE ARDUINO_____________________________________________

#define DHT11PIN 4 // connect the DHT pin to digital Pin 4
#define tiltPin 3
#define  LED 10
#define pirPin 5
//_____________________________________________________________________________________________________________

int PIR;
int TILT;
//____________________________________________________________________________________________________________

// ________________________create the pipe node for the connection of two or more arduino's___________________

byte addresses[][6] = {"0Node", "1Node", "2Node", "3Node", "4Node", "5Node"};
//____________________________________________________________________________________________________________

////Concatinate your data as a single packet____++++++++++____________________________________________________
struct package{
  int id = 3;
  float temperature = 0.00;
  float humidity = 0.00;
  int TiltStatus = 0;
  int PIRstatus = 0;
};
  typedef struct package Package;
Package data;
//__________________________________________________+++____________________________________________________
// -----------------------------------------------------------------------------
// SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP
// -----------------------------------------------------------------------------
void setup() {
  
  //_________________PIN mode (output or input) for different components plugged into the Ardiuno I/O pin.__________________
  pinMode(tiltPin, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(pirPin, INPUT);
//_________________________________________________________________________________________________________________________

  Serial.begin(9600);
  Serial.println("THIS IS THE TRANSMITTER CODE - YOU NEED THE OTHER ARDIUNO TO SEND BACK A RESPONSE");
//_________________________________NRF24L01____________________________________________________________________________
  // Initiate the radio object
  radio.begin();

  // Set the transmit power to lowest available to prevent power supply related issues
  radio.setPALevel(RF24_PA_MIN);

  // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);

  // Open a writing and reading pipe on each radio, with opposite addresses(it was numbered from 0 to 5 for the 6 whole 
  radio.openWritingPipe(addresses[3]);
     
  // Ensure we have stopped listening (even if we're not) or we won't be able to transmit
  radio.stopListening(); 
 //______________________________________________________________________________________________________________________
 
}

// -----------------------------------------------------------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP   LOOP     LOOP     LOOP     LOOP
// -----------------------------------------------------------------------------------------------------------------

void loop() {
//*****************************************************************************************************************
//____________________________________Put Codes To Run Repeatedly here_____________________________________________
//*****************************************************************************************************************
 
//____________________________________Status LED Blinking Setup____________________________________________________
   unsigned long currentMillis = millis();
  if((ledState == HIGH) && (currentMillis - previousMillis >=onTime))
  {
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(LED, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
  {
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(LED, ledState);    // Update the actual LED2
  }
//____________________________________________________________________________________________________________________

 //________________Setting up the DHT11 data for transmission______________________________________
int chk = DHT11.read(DHT11PIN);
data.temperature = DHT11.temperature;
data.humidity = DHT11.humidity;
//_________________________________________________________________________________________________

//______________________________________Setting up the Tilt sensor for transmisssion________________________________________
   TILT = digitalRead(tiltPin);
  if (TILT==LOW)
{
  data.TiltStatus=0;
  
     }
else 
    data.TiltStatus =1;

//________________________________________________________________________________________________________________

//_____________________________________________Setting up the PIR sensor__________________________________________
 PIR = digitalRead(pirPin);
  if (PIR==HIGH)
  {
  data.PIRstatus = 1;
     }
     else 
     data.PIRstatus = 0;
//__________________________________________________________________________________________________________________

//______________________________________Normal Tx time for after 500 milli seconds__________________________________
 unsigned long currentMillis1 = millis();
  if((NRFstate1 == HIGH) && (currentMillis1 - previousMillis1 >=onTime1))
  {
   NRFstate1 = LOW;  // Turn it off
   previousMillis1 = currentMillis1;  // Remember the time
   
  }
  else if ((NRFstate1 == LOW) && (currentMillis1 - previousMillis1 >= offTime1))
  {
    NRFstate1 = HIGH;  // turn it on
    previousMillis1 = currentMillis1;   // Remember the time
    //radio.write(&data, sizeof(data));
    radio.write(&data, sizeof(data));
  }
 // __________________________________________________________________________________________________________________
 
  // Did we manage to SUCCESSFULLY transmit that (by getting an acknowledgement back from the other Arduino)?
  // Even we didn't we'll continue with the sketch, you never know, the radio fairies may help us
  //if (!radio.write( &data, sizeof(data) )) {
    Serial.println("Transmitting");  
    Serial.println ((float)data.humidity, 2);  
    Serial.println ((float)data.temperature, 2);  
    Serial.print("TILT ");
    Serial.print (data.TiltStatus);
    Serial.print("\n");
    Serial.print("PIR ");
    Serial.print (data.PIRstatus);
    Serial.print("\n");
  //}
 //delay(100); 
}
