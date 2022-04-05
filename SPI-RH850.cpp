/*
  This project demonstrates SPI communication protocol by listening to status requests from a master controller, then, the slave device, an arduino,
  after getting the status message, sends a response message to the master, telling it it's status. We will use the SPI library.
*/

#include <SPI.h>

#define cycle_start 3

unsigned long startCycleTime;
unsigned long endCycleTime;
const long CycleTime = 5000;

long time = 0;
long debounce = 200;

volatile boolean received_Data;
volatile byte command = 0;

uint32_t display[4] = {};
long int myMessages[4] = {0x400000, 0x200000, 0x002000, 0x100000};

byte b1 = (myMessages[2] >> 16);
byte b2 = (myMessages[2] >> 8);
byte b3 = (myMessages[2]);

ISR(SPI_STC_vect) {
  byte c = SPDR;
  command = c;

  if (command == 0) {
    command = c;
    SPDR = 0;
  } else {
    if (command == 1) {
      SPDR = b1|b2|b3;
    }
  }

}

void setup() {
  Serial.begin(115200);

  pinMode(MISO, OUTPUT);
  pinMode(cycle_start, INPUT_PULLUP);

  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
}

void loop() {

    if (digitalRead(SS) == HIGH){
    command = 0;
    }
}
