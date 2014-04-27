/*
IR Transmitter for ATTiny

Antonio Gamba-Bari, Phd Candidte.
Semaphore Lab, Faculty of Information
University of Toronto

April, 2014

The following code adapts code procided in the following turotials:

http://learn.adafruit.com/ir-sensor
*/

#include "IR-codes-decode.h";

#define IRpin_PIN      PIND
#define IRpin          2

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000
#define NUMPULSES 50

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20

// we will store up to NUMPULSES pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

int clockCounter = 0;
void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

// loop compare
void loop(void) {
  int numberpulses;
  numberpulses = listenForIR();
 
  Serial.print("listening... ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");

    //check signal 
    if (IRcompare(numberpulses, IRsignalDecode1)) {
      Serial.println("Press 1");
    }
    if (IRcompare(numberpulses, IRsignalDecode2)) {
      Serial.println("Press 2");
    }

    if (IRcompare(numberpulses, IRsignalDecode3)) {
      Serial.println("Press 3");
    }
    if (IRcompare(numberpulses, IRsignalDecode4)) {
      Serial.println("Press 4");
    }

    if (IRcompare(numberpulses, IRsignalDecode5)) {
      Serial.println("Press 5");
    }

    if (IRcompare(numberpulses, IRsignalDecode6)) {
      Serial.println("Press 6");
    }

    if (IRcompare(numberpulses, IRsignalDecode7)) {
      Serial.println("Press 7");
    }
    
    // for debuging
//    printpulses();

}

boolean IRcompare(int numpulses, int Signal[]) {
 
  for (int i=0; i< numpulses-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
 
    /*
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
    */
 
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
 
    /*
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
    */
 
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
      //Serial.print(" (ok)");
    } else {
      //Serial.print(" (x)");
      // we didn't match perfectly, return a false match
      return false;
    }
 
    //Serial.println();
  }
  // Everything matched!
  return true;
}

// not used for now
void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
 
  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
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

int listenForIR(void) {
//  Serial.println(clockCounter);
  currentpulse = 0;
 
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
 
//  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH
 
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
    //Serial.println(clockCounter);
  }
}
