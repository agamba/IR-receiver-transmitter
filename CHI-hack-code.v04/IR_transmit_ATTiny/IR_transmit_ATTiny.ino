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
  // up to 50
  testIrPulse1();
//  testIrPulse2();
//  testIrPulse2();
//  testIrPulse4();
  // etc
  
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
  delayMicroseconds(4000);
  pulseIR(500);
  delayMicroseconds(4000);
  pulseIR(2000);
  delayMicroseconds(2000);
  pulseIR(350);
  delayMicroseconds(15000);
  pulseIR(350);
}


void testIrPulse2() { 

  pulseIR(700);
  delayMicroseconds(4200);
  pulseIR(700);
  delayMicroseconds(4200);
  pulseIR(2200);
  delayMicroseconds(2200);
  pulseIR(550);
  delayMicroseconds(14700);
  pulseIR(700);
}


void testIrPulse3() { 

  pulseIR(900);
  delayMicroseconds(4400);
  pulseIR(900);
  delayMicroseconds(4400);
  pulseIR(2400);
  delayMicroseconds(2400);
  pulseIR(750);
  delayMicroseconds(14400);
  pulseIR(1050);
}


void testIrPulse4() { 

  pulseIR(1100);
  delayMicroseconds(4600);
  pulseIR(1100);
  delayMicroseconds(4600);
  pulseIR(2600);
  delayMicroseconds(2600);
  pulseIR(950);
  delayMicroseconds(14100);
  pulseIR(1400);
}


void testIrPulse5() { 

  pulseIR(1300);
  delayMicroseconds(4800);
  pulseIR(1300);
  delayMicroseconds(4800);
  pulseIR(2800);
  delayMicroseconds(2800);
  pulseIR(1150);
  delayMicroseconds(13800);
  pulseIR(1750);
}


void testIrPulse6() { 

  pulseIR(1500);
  delayMicroseconds(5000);
  pulseIR(1500);
  delayMicroseconds(5000);
  pulseIR(3000);
  delayMicroseconds(3000);
  pulseIR(1350);
  delayMicroseconds(13500);
  pulseIR(2100);
}


void testIrPulse7() { 

  pulseIR(1700);
  delayMicroseconds(5200);
  pulseIR(1700);
  delayMicroseconds(5200);
  pulseIR(3200);
  delayMicroseconds(3200);
  pulseIR(1550);
  delayMicroseconds(13200);
  pulseIR(2450);
}


void testIrPulse8() { 

  pulseIR(1900);
  delayMicroseconds(5400);
  pulseIR(1900);
  delayMicroseconds(5400);
  pulseIR(3400);
  delayMicroseconds(3400);
  pulseIR(1750);
  delayMicroseconds(12900);
  pulseIR(2800);
}


void testIrPulse9() { 

  pulseIR(2100);
  delayMicroseconds(5600);
  pulseIR(2100);
  delayMicroseconds(5600);
  pulseIR(3600);
  delayMicroseconds(3600);
  pulseIR(1950);
  delayMicroseconds(12600);
  pulseIR(3150);
}


void testIrPulse10() { 

  pulseIR(2300);
  delayMicroseconds(5800);
  pulseIR(2300);
  delayMicroseconds(5800);
  pulseIR(3800);
  delayMicroseconds(3800);
  pulseIR(2150);
  delayMicroseconds(12300);
  pulseIR(3500);
}


void testIrPulse11() { 

  pulseIR(2500);
  delayMicroseconds(6000);
  pulseIR(2500);
  delayMicroseconds(6000);
  pulseIR(4000);
  delayMicroseconds(4000);
  pulseIR(2350);
  delayMicroseconds(12000);
  pulseIR(3850);
}


void testIrPulse12() { 

  pulseIR(2700);
  delayMicroseconds(6200);
  pulseIR(2700);
  delayMicroseconds(6200);
  pulseIR(4200);
  delayMicroseconds(4200);
  pulseIR(2550);
  delayMicroseconds(11700);
  pulseIR(4200);
}


void testIrPulse13() { 

  pulseIR(2900);
  delayMicroseconds(6400);
  pulseIR(2900);
  delayMicroseconds(6400);
  pulseIR(4400);
  delayMicroseconds(4400);
  pulseIR(2750);
  delayMicroseconds(11400);
  pulseIR(4550);
}


void testIrPulse14() { 

  pulseIR(3100);
  delayMicroseconds(6600);
  pulseIR(3100);
  delayMicroseconds(6600);
  pulseIR(4600);
  delayMicroseconds(4600);
  pulseIR(2950);
  delayMicroseconds(11100);
  pulseIR(4900);
}


void testIrPulse15() { 

  pulseIR(3300);
  delayMicroseconds(6800);
  pulseIR(3300);
  delayMicroseconds(6800);
  pulseIR(4800);
  delayMicroseconds(4800);
  pulseIR(3150);
  delayMicroseconds(10800);
  pulseIR(5250);
}


void testIrPulse16() { 

  pulseIR(3500);
  delayMicroseconds(7000);
  pulseIR(3500);
  delayMicroseconds(7000);
  pulseIR(5000);
  delayMicroseconds(5000);
  pulseIR(3350);
  delayMicroseconds(10500);
  pulseIR(5600);
}


void testIrPulse17() { 

  pulseIR(3700);
  delayMicroseconds(7200);
  pulseIR(3700);
  delayMicroseconds(7200);
  pulseIR(5200);
  delayMicroseconds(5200);
  pulseIR(3550);
  delayMicroseconds(10200);
  pulseIR(5950);
}


void testIrPulse18() { 

  pulseIR(3900);
  delayMicroseconds(7400);
  pulseIR(3900);
  delayMicroseconds(7400);
  pulseIR(5400);
  delayMicroseconds(5400);
  pulseIR(3750);
  delayMicroseconds(9900);
  pulseIR(6300);
}


void testIrPulse19() { 

  pulseIR(4100);
  delayMicroseconds(7600);
  pulseIR(4100);
  delayMicroseconds(7600);
  pulseIR(5600);
  delayMicroseconds(5600);
  pulseIR(3950);
  delayMicroseconds(9600);
  pulseIR(6650);
}


void testIrPulse20() { 

  pulseIR(4300);
  delayMicroseconds(7800);
  pulseIR(4300);
  delayMicroseconds(7800);
  pulseIR(5800);
  delayMicroseconds(5800);
  pulseIR(4150);
  delayMicroseconds(9300);
  pulseIR(7000);
}


void testIrPulse21() { 

  pulseIR(4500);
  delayMicroseconds(8000);
  pulseIR(4500);
  delayMicroseconds(8000);
  pulseIR(6000);
  delayMicroseconds(6000);
  pulseIR(4350);
  delayMicroseconds(9000);
  pulseIR(7350);
}


void testIrPulse22() { 

  pulseIR(4700);
  delayMicroseconds(8200);
  pulseIR(4700);
  delayMicroseconds(8200);
  pulseIR(6200);
  delayMicroseconds(6200);
  pulseIR(4550);
  delayMicroseconds(8700);
  pulseIR(7700);
}


void testIrPulse23() { 

  pulseIR(4900);
  delayMicroseconds(8400);
  pulseIR(4900);
  delayMicroseconds(8400);
  pulseIR(6400);
  delayMicroseconds(6400);
  pulseIR(4750);
  delayMicroseconds(8400);
  pulseIR(8050);
}


void testIrPulse24() { 

  pulseIR(5100);
  delayMicroseconds(8600);
  pulseIR(5100);
  delayMicroseconds(8600);
  pulseIR(6600);
  delayMicroseconds(6600);
  pulseIR(4950);
  delayMicroseconds(8100);
  pulseIR(8400);
}


void testIrPulse25() { 

  pulseIR(5300);
  delayMicroseconds(8800);
  pulseIR(5300);
  delayMicroseconds(8800);
  pulseIR(6800);
  delayMicroseconds(6800);
  pulseIR(5150);
  delayMicroseconds(7800);
  pulseIR(8750);
}


void testIrPulse26() { 

  pulseIR(5500);
  delayMicroseconds(9000);
  pulseIR(5500);
  delayMicroseconds(9000);
  pulseIR(7000);
  delayMicroseconds(7000);
  pulseIR(5350);
  delayMicroseconds(7500);
  pulseIR(9100);
}


void testIrPulse27() { 

  pulseIR(5700);
  delayMicroseconds(9200);
  pulseIR(5700);
  delayMicroseconds(9200);
  pulseIR(7200);
  delayMicroseconds(7200);
  pulseIR(5550);
  delayMicroseconds(7200);
  pulseIR(9450);
}


void testIrPulse28() { 

  pulseIR(5900);
  delayMicroseconds(9400);
  pulseIR(5900);
  delayMicroseconds(9400);
  pulseIR(7400);
  delayMicroseconds(7400);
  pulseIR(5750);
  delayMicroseconds(6900);
  pulseIR(9800);
}


void testIrPulse29() { 

  pulseIR(6100);
  delayMicroseconds(9600);
  pulseIR(6100);
  delayMicroseconds(9600);
  pulseIR(7600);
  delayMicroseconds(7600);
  pulseIR(5950);
  delayMicroseconds(6600);
  pulseIR(10150);
}


void testIrPulse30() { 

  pulseIR(6300);
  delayMicroseconds(9800);
  pulseIR(6300);
  delayMicroseconds(9800);
  pulseIR(7800);
  delayMicroseconds(7800);
  pulseIR(6150);
  delayMicroseconds(6300);
  pulseIR(10500);
}


void testIrPulse31() { 

  pulseIR(6500);
  delayMicroseconds(10000);
  pulseIR(6500);
  delayMicroseconds(10000);
  pulseIR(8000);
  delayMicroseconds(8000);
  pulseIR(6350);
  delayMicroseconds(6000);
  pulseIR(10850);
}


void testIrPulse32() { 

  pulseIR(6700);
  delayMicroseconds(10200);
  pulseIR(6700);
  delayMicroseconds(10200);
  pulseIR(8200);
  delayMicroseconds(8200);
  pulseIR(6550);
  delayMicroseconds(5700);
  pulseIR(11200);
}


void testIrPulse33() { 

  pulseIR(6900);
  delayMicroseconds(10400);
  pulseIR(6900);
  delayMicroseconds(10400);
  pulseIR(8400);
  delayMicroseconds(8400);
  pulseIR(6750);
  delayMicroseconds(5400);
  pulseIR(11550);
}


void testIrPulse34() { 

  pulseIR(7100);
  delayMicroseconds(10600);
  pulseIR(7100);
  delayMicroseconds(10600);
  pulseIR(8600);
  delayMicroseconds(8600);
  pulseIR(6950);
  delayMicroseconds(5100);
  pulseIR(11900);
}


void testIrPulse35() { 

  pulseIR(7300);
  delayMicroseconds(10800);
  pulseIR(7300);
  delayMicroseconds(10800);
  pulseIR(8800);
  delayMicroseconds(8800);
  pulseIR(7150);
  delayMicroseconds(4800);
  pulseIR(12250);
}


void testIrPulse36() { 

  pulseIR(7500);
  delayMicroseconds(11000);
  pulseIR(7500);
  delayMicroseconds(11000);
  pulseIR(9000);
  delayMicroseconds(9000);
  pulseIR(7350);
  delayMicroseconds(4500);
  pulseIR(12600);
}


void testIrPulse37() { 

  pulseIR(7700);
  delayMicroseconds(11200);
  pulseIR(7700);
  delayMicroseconds(11200);
  pulseIR(9200);
  delayMicroseconds(9200);
  pulseIR(7550);
  delayMicroseconds(4200);
  pulseIR(12950);
}


void testIrPulse38() { 

  pulseIR(7900);
  delayMicroseconds(11400);
  pulseIR(7900);
  delayMicroseconds(11400);
  pulseIR(9400);
  delayMicroseconds(9400);
  pulseIR(7750);
  delayMicroseconds(3900);
  pulseIR(13300);
}


void testIrPulse39() { 

  pulseIR(8100);
  delayMicroseconds(11600);
  pulseIR(8100);
  delayMicroseconds(11600);
  pulseIR(9600);
  delayMicroseconds(9600);
  pulseIR(7950);
  delayMicroseconds(3600);
  pulseIR(13650);
}


void testIrPulse40() { 

  pulseIR(8300);
  delayMicroseconds(11800);
  pulseIR(8300);
  delayMicroseconds(11800);
  pulseIR(9800);
  delayMicroseconds(9800);
  pulseIR(8150);
  delayMicroseconds(3300);
  pulseIR(14000);
}


void testIrPulse41() { 

  pulseIR(8500);
  delayMicroseconds(12000);
  pulseIR(8500);
  delayMicroseconds(12000);
  pulseIR(10000);
  delayMicroseconds(10000);
  pulseIR(8350);
  delayMicroseconds(3000);
  pulseIR(14350);
}


void testIrPulse42() { 

  pulseIR(8700);
  delayMicroseconds(12200);
  pulseIR(8700);
  delayMicroseconds(12200);
  pulseIR(10200);
  delayMicroseconds(10200);
  pulseIR(8550);
  delayMicroseconds(2700);
  pulseIR(14700);
}


void testIrPulse43() { 

  pulseIR(8900);
  delayMicroseconds(12400);
  pulseIR(8900);
  delayMicroseconds(12400);
  pulseIR(10400);
  delayMicroseconds(10400);
  pulseIR(8750);
  delayMicroseconds(2400);
  pulseIR(15050);
}


void testIrPulse44() { 

  pulseIR(9100);
  delayMicroseconds(12600);
  pulseIR(9100);
  delayMicroseconds(12600);
  pulseIR(10600);
  delayMicroseconds(10600);
  pulseIR(8950);
  delayMicroseconds(2100);
  pulseIR(15400);
}


void testIrPulse45() { 

  pulseIR(9300);
  delayMicroseconds(12800);
  pulseIR(9300);
  delayMicroseconds(12800);
  pulseIR(10800);
  delayMicroseconds(10800);
  pulseIR(9150);
  delayMicroseconds(1800);
  pulseIR(15750);
}


void testIrPulse46() { 

  pulseIR(9500);
  delayMicroseconds(13000);
  pulseIR(9500);
  delayMicroseconds(13000);
  pulseIR(11000);
  delayMicroseconds(11000);
  pulseIR(9350);
  delayMicroseconds(1500);
  pulseIR(16100);
}


void testIrPulse47() { 

  pulseIR(9700);
  delayMicroseconds(13200);
  pulseIR(9700);
  delayMicroseconds(13200);
  pulseIR(11200);
  delayMicroseconds(11200);
  pulseIR(9550);
  delayMicroseconds(1200);
  pulseIR(16450);
}


void testIrPulse48() { 

  pulseIR(9900);
  delayMicroseconds(13400);
  pulseIR(9900);
  delayMicroseconds(13400);
  pulseIR(11400);
  delayMicroseconds(11400);
  pulseIR(9750);
  delayMicroseconds(900);
  pulseIR(16800);
}


void testIrPulse49() { 

  pulseIR(10100);
  delayMicroseconds(13600);
  pulseIR(10100);
  delayMicroseconds(13600);
  pulseIR(11600);
  delayMicroseconds(11600);
  pulseIR(9950);
  delayMicroseconds(600);
  pulseIR(17150);
}


void testIrPulse50() { 

  pulseIR(10300);
  delayMicroseconds(13800);
  pulseIR(10300);
  delayMicroseconds(13800);
  pulseIR(11800);
  delayMicroseconds(11800);
  pulseIR(10150);
  delayMicroseconds(300);
  pulseIR(17500);
}



