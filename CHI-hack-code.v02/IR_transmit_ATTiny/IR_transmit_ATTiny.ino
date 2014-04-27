/*
IR Transmitter for ATTiny
Antonio Gamba-Bari, Phd Candidte.
Semaphore Lab, Faculty of Information
University of Toronto
April, 2014

This code has been adapted from
http://learn.adafruit.com/ir-sensor
*/

/* ///////////////////////////////
  Configuration
/////////////////////////////// */
// IR LED pin
int IRledPin =  0;

// LED pin
int ledPin =  4;
///////////////////////////////

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
}
 
void loop()                     
{
//  testIrPulse1();
//  testIrPulse2();
  testIrPulse3();
//    testIrPulse4();
//    testIrPulse5();
  
  // send a IR signal for the IR puse id
//   pulseIrFromArray(IRpulseId);

  // blink LED for confirmation
  digitalWrite(ledPin, LOW); 
  digitalWrite(ledPin, HIGH); 
  delay(200);  
  digitalWrite(ledPin, LOW); 

  // Wait 5 sec before sending another IR signal
  delay(5000);  
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

void testIrPulse1() {
  pulseIR(500);
  delayMicroseconds(500);
  pulseIR(600);
  delayMicroseconds(500);
  pulseIR(700);
  delayMicroseconds(500);
  pulseIR(800);
  delayMicroseconds(500);
  pulseIR(900);
  delayMicroseconds(500);
  pulseIR(1000);
  delayMicroseconds(500);
  pulseIR(1100);
  delayMicroseconds(5000);
}

void testIrPulse2() {
  pulseIR(1500);
  delayMicroseconds(1000);
  pulseIR(1600);
  delayMicroseconds(1000);
  pulseIR(1700);
  delayMicroseconds(1000);
  pulseIR(1800);
  delayMicroseconds(1000);
  pulseIR(1900);
  delayMicroseconds(1000);
  pulseIR(2000);
  delayMicroseconds(1000);
  pulseIR(2100);
  delayMicroseconds(8000);
}

void testIrPulse3() {
  pulseIR(3500);
  delayMicroseconds(1500);
  pulseIR(3600);
  delayMicroseconds(1500);
  pulseIR(3700);
  delayMicroseconds(1500);
  pulseIR(3800);
  delayMicroseconds(1500);
  pulseIR(3900);
  delayMicroseconds(1500);
  pulseIR(4000);
  delayMicroseconds(1500);
  pulseIR(4100);
  delayMicroseconds(9000);
}

void testIrPulse4() {
  pulseIR(4500);
  delayMicroseconds(2000);
  pulseIR(4600);
  delayMicroseconds(2000);
  pulseIR(4700);
  delayMicroseconds(2000);
  pulseIR(4800);
  delayMicroseconds(2000);
  pulseIR(4900);
  delayMicroseconds(2000);
  pulseIR(5000);
  delayMicroseconds(2000);
  pulseIR(5100);
  delayMicroseconds(9500);
}

void testIrPulse5() {
  pulseIR(5500);
  delayMicroseconds(2500);
  pulseIR(5600);
  delayMicroseconds(2500);
  pulseIR(5700);
  delayMicroseconds(2500);
  pulseIR(5800);
  delayMicroseconds(2500);
  pulseIR(5900);
  delayMicroseconds(2500);
  pulseIR(6000);
  delayMicroseconds(2500);
  pulseIR(6100);
  delayMicroseconds(10000);
}
