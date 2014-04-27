/*
IR Transmitter for ATTiny
 
 Antonio Gamba-Bari, Phd Candidte.
 Semaphore Lab, Faculty of Information
 University of Toronto
 
 April, 2014
 
 The following code adapts code procided in the following tutorials:
 
 http://learn.adafruit.com/ir-sensor
 
 And WiflyShield by Sparkfun code
 https://github.com/sparkfun/WiFly-Shield
 
 */




#include <SPI.h>
#include <WiFly.h>
#include "String.h"

#include "Credentials.h"
#include "IR-codes-decode.h";

WiFlyClient client("api.thingspeak.com", 80);

#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

//COMMUNICATION TO THINKSPEAK
#define UPDATE_INTERVAL            30000    // if the connection is good wait 10 seconds before updating again - should not be less than 5
#define RETRY_INTERVAL						 20000    // Wait this ms before trying to connect to the network again
#define THINGSPEAK_API_KEY  "WOAZL1KCFOXGU598" // fill in your API key 
static uint32_t timeLastUpdated=0;
int connTries=0;
int numberpulses;
int rId = 1; // change this for each reviever
//String dataHost= "api.thingspeak.com";
bool checkNetwork()
{
  const char * status=WiFly.getConnectionStatus();
  if(status[1]=='3')
  {
    return true;
  }
  else
  {
    return false;
  }
}

//IR SETUP
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

void setup()
{
  Serial.begin(9600);
  Serial.println("Thingspeak example!");
  Serial.println("Will send some data to Thingspeak every UPDATE_INTERVAL ms");
  Serial.println("Ready to decode IR!");
  WiFly.begin();

}

void loop()
{
  if (millis() - timeLastUpdated > UPDATE_INTERVAL)
  { // time for the next update
    if(!checkNetwork())
    {
      Serial.println("Not connected to the wifi network.");
      while(!WiFly.join(ssid,passphrase))
      {
        Serial.println("Joining the network failed. Retrying in RETRY_INTERVAL.");
        delay(RETRY_INTERVAL);
        connTries++;
      }
      Serial.println("Joined!");
    }
    //
    //    Serial.print("Time from last update: ");
    //    Serial.println(millis() - timeLastUpdated);
    //    // Convert a float to a string with style
    //    char buffer[14];
    //    dtostrf(temp,7,2,buffer);
    //    String stemp(buffer);
    //    stemp.trim();
    //
    //    // float is now in the string stemp
    //    if(client.connect())

    //    {
    //      Serial.println("connected... Sending data to Thingspeak.");
 //  thingspeak_out("receiverID="+stemp+"&personId="+sret);
    //    }
    //    else
    //    {
//    //      Serial.println("Error connecting. Will try again at next interval.");
    //    }
  }
  delay(UPDATE_INTERVAL);

  // loop compare
  numberpulses = listenForIR();

  Serial.print("listening... ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal");
  String _dataTemp = "";
  String rIdTemp = toString(rId);
  timeLastUpdated = millis();
  String sret(connTries);

  //check signal 
  if (IRcompare(numberpulses, IRsignalDecode1)) {
    Serial.println("Press 1");
    //    thingspeak_out("receiverID="+rIdTemp+"&personId=1");
  }
  if (IRcompare(numberpulses, IRsignalDecode2)) {
    Serial.println("Press 2");
    //    thingspeak_out("receiverID="+rId+"&personId="+2);
  }

  if (IRcompare(numberpulses, IRsignalDecode3) && (client.connect())) {
    Serial.println("Press 3");
    //    thingspeak_out("receiverID="+rId+"&personId="+3);
  }
  if (IRcompare(numberpulses, IRsignalDecode4) && (client.connect())) {
    Serial.println("Press 4");
    //    thingspeak_out("receiverID="+rId+"&personId="+4);
  }

  if (IRcompare(numberpulses, IRsignalDecode5)) {
    Serial.println("Press 5");
    //    thingspeak_out("receiverID="+rId+"&personId="+5);
  }

  if (IRcompare(numberpulses, IRsignalDecode6) && (client.connect())) {
    Serial.println("Press 6");
    _dataTemp = "receiverID="+rIdTemp+"&personId=6 l.";
    Serial.println(_dataTemp);
    
//    thingspeak_out();
  }

  if (IRcompare(numberpulses, IRsignalDecode7) && (client.connect())) {
    Serial.println("Press 7");
    thingspeak_out("receiverID="+rIdTemp+"&personId=7"+sret);
  }

 // for debuging
    printpulses();

}

String toString(int a){
  char buffer[5];
  //dtostrf(temp,7,2,buffer);
  String stemp(buffer);
  stemp.trim();
  return stemp;
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
    } 
    else {
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
    } 
    else {
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

void thingspeak_out(String _data)
{
  client.println("POST /update HTTP/1.1"); 
  client.println("Host: api.thingspeak.com");
  client.println("Connection: close");
  client.print("X-THINGSPEAKAPIKEY: ");
  client.println(THINGSPEAK_API_KEY);
  //client.println("User-Agent: Arduino (WiFly RN-XV)");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(_data.length());
  client.print("\n\n");
  client.println(_data);

  delay(2000); // Give the server some time to answer back

  while (client.available()) 
  {
    // TODO verify success (HTTP/1.1 200 OK)
    Serial.print(client.readChar());  // display the result
  }
  Serial.println();

  if (client.connected()) 
  {
    Serial.println("disconnecting...");
    client.stop();
  } 
}

void sendDataToWeb(int a, int b){

}


