/*
  This project demonstrates SPI communication protocol by listening to status requests from a master controller, then, the slave device, an arduino,
  after getting the status message, sends a response message to the master, telling it it's status. We will use the SPI library.
*/

#include <SPI.h>

#define cycle_start 2

unsigned long startCycleTime;
unsigned long endCycleTime;
const long CycleTime = 5000;

int is_start_state;

int x;
byte b1;
byte b2;
byte b3;

void setup() {
  Serial.begin(115200);

  pinMode(cycle_start, INPUT_PULLUP);

  digitalWrite(SS, HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

}

byte transferAndWait (const uint16_t what) {
  uint16_t a = SPI.transfer(what);
  delayMicroseconds(20);

//  Serial.println(a);
  return a;
}

void loop() {
  //  byte Master_Send, Master_Receive;
  byte a;

  int last_button_state = HIGH;

  is_start_state = digitalRead(cycle_start);

  startCycleTime = millis();

  if (is_start_state != last_button_state)
  {
    x = 1;
    last_button_state = is_start_state;
  } else
  {
    x = 0;
    last_button_state = is_start_state;
  }

//  Serial.println(x);

  digitalWrite(SS, LOW);
  transferAndWait(x);
  transferAndWait(x);
  b1 = transferAndWait(x);

  

  digitalWrite(SS, HIGH);


  if (startCycleTime - endCycleTime >= CycleTime) {
    Serial.println(b1, DEC);
    endCycleTime = startCycleTime;
  }

}
