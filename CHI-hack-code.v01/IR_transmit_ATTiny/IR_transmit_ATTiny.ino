/*
IR Transmitter for ATTiny
Antonio Gamba-Bari, Phd Candidte.
Semaphore Lab, Faculty of Information
University of Toronto
April, 2014

The turorial now moved to:
http://learn.adafruit.com/ir-sensor
.... add other credits
*/

/* ///////////////////////////////
  Configuration
/////////////////////////////// */

// This value can be a number between 0-9. 
// The IRpulseId indicates a unique id in the IR pulse code array
int IRpulseId = 0;

// IR LED pin
int IRledPin =  0;

// LED pin
int ledPin =  4;

///////////////////////////////

// include IR codes lib
#include "IR-Codes-10-transmit.h";

void setup()   {                
  // initialize PINs
  pinMode(IRledPin, OUTPUT);      
  pinMode(ledPin, OUTPUT);      
  digitalWrite(ledPin, LOW); 

  // Blink 3 times informing setup finished.
  digitalWrite(ledPin, HIGH); 
  delay(200);  // 1/2 sec
  digitalWrite(ledPin, LOW); 
  delay(200);  // 1/2 sec
  digitalWrite(ledPin, HIGH); 
  delay(200);  // 1/2 sec  
  digitalWrite(ledPin, LOW); 
  delay(200);  // 1/2 sec
  digitalWrite(ledPin, HIGH); 
  delay(200);  // 1/2 sec  
  digitalWrite(ledPin, LOW); 

//  testIrPulse();

  // Use this only for debug in Arduino Uno
//  Serial.begin(9600); 
}
 
void loop()                     
{

// pulse
//  testIrPulse1();
  
  // send a IR signal for the IR puse id
   pulseIrFromArray(IRpulseId);

  // blink LED for confirmation
  digitalWrite(ledPin, LOW); 
  digitalWrite(ledPin, HIGH); 
  delay(200);  
  digitalWrite(ledPin, LOW); 

  // Wait 5 sec before sending another IR signal
  delay(5000);  
}

void pulseIrFromArray(int IRid) {
  int i;  
  for (i = 0; i < sizeof(IRsignalTransmit[IRid]) - 1; i=i+2){
    // Get first pair of modulated IR pulse
    if(i==0) {
      pulseIR(IRsignalTransmit[IRid][0]);
      delayMicroseconds(IRsignalTransmit[IRid][1]);
    } else {
      pulseIR(IRsignalTransmit[IRid][i]);
      delayMicroseconds(IRsignalTransmit[IRid][i+1]);
    }

/*
    // for debuging only!! very slow
    Serial.println("");
    Serial.print(IRsignalTransmit[IRid][i]);
//    Serial.print(",");
//    Serial.print(IRsignalTransmit[IRid][i+1]);
    Serial.println("");
//    delay(50);
*/    
  }
  // slow down for testing
  // delay(1000); 
}

// This procedure sends a 38KHz pulse to the IRledPin for a certain # (microsecs) of microseconds.
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  // Turn off any background interrupts
  cli();  
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  // Turn interrupts back on
  sei();  
}
 
// not used now. Remains here for testing purposes. 
// and just in case you want to create your own "hand made" modulated IR pulse
void testIrPulse() {
  pulseIR(500);
  delayMicroseconds(4000);
  pulseIR(500);
  delayMicroseconds(4000);
  pulseIR(2000);
  delayMicroseconds(2000);
  pulseIR(350);
  delayMicroseconds(15000);
  pulseIR(250);
  delay(65);
  //Serial.println("testIrPulse sent!");
}

void testIrPulse1() {
  pulseIR(100);
  delayMicroseconds(100);
  pulseIR(100);
  delayMicroseconds(100);
  pulseIR(1000);
  delayMicroseconds(1000);
  pulseIR(1000);
  delayMicroseconds(1000);
  pulseIR(10000);
  delayMicroseconds(10000);
  pulseIR(10000);
  delayMicroseconds(10000);
  //Serial.println("testIrPulse sent!");
}



