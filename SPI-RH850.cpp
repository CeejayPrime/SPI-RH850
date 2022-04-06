/*
  This project demonstrates SPI communication protocol by listening to status requests from a master controller, then, the slave device, an arduino,
  after getting the status message, sends a response message to the master, telling it it's status. We will use the SPI library.
*/

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

#define cycle_start 3
#define select 4
#define returnHome 5

int i = 0;
uint32_t message;

boolean current_return = HIGH;
boolean last_return = HIGH;

boolean current_select = HIGH;
boolean last_select = HIGH;

int state = HIGH;
int reading;
int previous = LOW;

long time = 0;
long debounce = 200;

unsigned long startCycleTime;
unsigned long endCycleTime;
const long CycleTime = 5000;

volatile boolean received_Data;
volatile byte command = 0;

String display[9] = {"0x000000", "0x400000", "0x100000", "0x002000", "0x000100", "0x000080", "0x000040", "0x000008", "0x000004"};
long int myMessages[9] = {0x000000, 0x400000, 0x100000, 0x002000, 0x000100, 0x000080, 0x000040, 0x000008, 0x000004};

bool cycle_active = false;

int numOfPages = 9;
int numOfMenuPages = sizeof(myMessages) / sizeof(myMessages[0]);

byte b1 = (myMessages[0] >> 16);
byte b2 = (myMessages[0] >> 8);
byte b3 = (myMessages[0]);





/****This is to check if the cycle button have been turned on. The purpose for this
  is that we can start and stop the cycle with the press of only 1 push button****/

boolean is_button_pressed() {
  bool is_pressed = false;
  reading = digitalRead(cycle_start);

  if (reading == HIGH and previous == LOW and millis() - time > debounce) {
    if (state == HIGH) {
      state = LOW;
      Serial.println(state);
    }
    else {
      state = HIGH;
      Serial.println(state);
      is_pressed = true;
    }
    time = millis();
  }

  previous = reading;
  return is_pressed;
}

/*******************************************************************************************************************************************************/
/*******************************************************************************************************************************************************/
/*******************************************************************************************************************************************************/

boolean debounceTime(boolean last, int pin) {
  boolean current = digitalRead(pin);

  if (last != current) {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

int selectButtonPressed() {
  current_select = debounceTime(last_select, select);
  uint32_t j;
  if (last_select == HIGH and current_select == LOW) {
    i = j;
    Serial.println(j);
    last_select = current_select;
  }
}

void LCD_home() {
  lcd.setCursor(0, 0);
  lcd.print("No Fault");
  lcd.setCursor(0, 1);
  lcd.print("Code: 0x000000");
}

/****Slave message sending****/
ISR(SPI_STC_vect) {
  byte c = SPDR;
  command = c;

  switch (command) {
    case 0:
      command = c;
      SPDR = 0;
      break;
    case 1:
      command == 1;
      SPDR = b1;
      break;
    case 2:
      command == 2;
      SPDR = b2;
      break;
    case 3:
      command == 3;
      SPDR = b3;
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("WELCOME");
  delay(1500);
  lcd.clear();
  //Initialization complete

  pinMode(MISO, OUTPUT);
  pinMode(cycle_start, INPUT_PULLUP);

  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
}

void loop() {

  current_select = debounceTime(last_select, select);

  if (is_button_pressed()) {
    cycle_active = true;
  }

  if (cycle_active and millis() - time > 5000) {
    i++;
    if (i >= 9) {
      i = 0;
    }
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Fault Code: " + String(display[i]));
    Serial.println(i);
    time = millis();
  }
  if (cycle_active) {
    if (current_select != last_select) {
      last_select = current_select;

      if (last_select == HIGH) {
        cycle_active = false;
        lcd.setCursor(0, 2);
        lcd.print(String(display[i]) + " Selected");
        message = myMessages[i];
        Serial.println(message, HEX);
      }
    }
  }
  //  Serial.println("Value of I: " +String(i));
  if (digitalRead(SS) == HIGH) {
    command = 0;
  }
}
