/*
IR Transmitter for ATTiny

Antonio Gamba-Bari, Phd Candidte.
Semaphore Lab, Faculty of Information
University of Toronto

April, 2014

The following code adapts code procided in the following turotials:

http://learn.adafruit.com/ir-sensor


*/


/* Raw IR decoder sketch!
This sketch/program uses the Arduno and a PNA4602 to
decode IR received. This can be used to make a IR receiver
(by looking for a particular code)
or transmitter (by pulsing an IR LED at ~38KHz for the
durations detected
Code is public domain, check out www.ladyada.net and adafruit.com
for more tutorials!
*/


/* ///////////////////////////////
  Configuration
/////////////////////////////// */

#define IRpin 2 // IR receiver PIN

/* ////////////////////////////// */

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping

// for Arduino Uno
#define IRpin_PIN PIND

// for Arduino MEGA use these!
//#define IRpin_PIN PINE
//#define IRpin 4

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000
#define NUMPULSES 50

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you woIR_decoder_unoIR_decoder_unont get
// accurate timing
#define RESOLUTION 20

// What percent we will allow in variation to match the same code
#define FUZZINESS 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing

// include IR code lib
//#include "IR-Codes-10-decode.h";

int clockCounter = 0; // for debuging purposes we do a count of at every loop

void setup(void) {

  Serial.println("Ready to decode IR!");
}

void loop(void) {
  int numberpulses;
  numberpulses = listenForIR();
 
  Serial.print("Listened a ");
  Serial.print(numberpulses);
  Serial.println(" pulses long IR signal");
/*
  //Look for a match between incoming pulse (numberpulses) and reference data stored in IR-Codes-10-decode.h
  if (IRcompare(numberpulses, IRsignalDecode1)) {
    Serial.println("Code 1");
  }
  if (IRcompare(numberpulses, IRsignalDecode2)) {
    Serial.println("Code 2");
  }
  if (IRcompare(numberpulses, IRsignalDecode3)) {
    Serial.println("Code 3");
  }
  if (IRcompare(numberpulses, IRsignalDecode4)) {
    Serial.println("Code 4");
  }
  if (IRcompare(numberpulses, IRsignalDecode5)) {
    Serial.println("Code 5");
  }
  if (IRcompare(numberpulses, IRsignalDecode6)) {
    Serial.println("Code 6");
  }
  if (IRcompare(numberpulses, IRsignalDecode7)) {
    Serial.println("Code 7");
  }
  if (IRcompare(numberpulses, IRsignalDecode8)) {
    Serial.println("Code 8");
  }
  if (IRcompare(numberpulses, IRsignalDecode9)) {
    Serial.println("Code 9");
  }
  if (IRcompare(numberpulses, IRsignalDecode10)) {
    Serial.println("Code 10");
  }
*/
  // for debuding, print incoming pulses
  printpulses();
}

int listenForIR(void) {
//  Serial.println(clockCounter);
  currentpulse = 0;
 
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
 
//  while (digitalRead(IRpin)) { // this is too slow, don't even try this! Here only for reference
    while (IRpin_PIN & (1 << IRpin)) {
       // count off another few microseconds
       highpulse++;
       delayMicroseconds(RESOLUTION);
 
       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
 
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
       delayMicroseconds(RESOLUTION);
       if ((lowpulse >= MAXPULSE)  && (currentpulse != 0)) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;
 
    // we read one high-low pulse successfully, continue!
    currentpulse++;

    // uncomment this if debuging clock counter
    //Serial.println(clockCounter);
  }
}

boolean IRcompare(int numpulses, int Signal[]) {
 
  for (int i=0; i< numpulses-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;

 
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }

    // uncomment the following lines when debuging IR comparison of 
    // incomming signal and reference data
    /*
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
    */

    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }

    // uncomment the following lines when debuging IR comparison of 
    // incomming signal and reference data
    /*
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
    */
 
  }

  // Everything matched!
  return true;
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
//    Serial.print(pulses[i][0], DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
//    Serial.print(pulses[i][1], DEC);
    Serial.println(" usec");
  }
 
  // print it in a 'array' format
  Serial.println("int IRsignalDecode[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");  
}

/*
void sendDataToServer(char webAction[], char data[]){
  
}
*/



