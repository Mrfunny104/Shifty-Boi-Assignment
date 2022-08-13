//Libaries 
#include <LiquidCrystal.h>
#include <SimpleDHT.h>

//Temp & Humidity Sensor Setup
int pinDHT11 = 6;
SimpleDHT11 dht11;

//LCD Setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {

  //Temperature & Humidity Display
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  
  //If statement tells Arduino hox to fix any reading errors from Temp sensor
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    return;
  }
  lcd.setCursor(0,0);
  lcd.print("T: "); lcd.print((int)temperature);
  lcd.print((char)223);  lcd.print("C   ");
  lcd.print("H: "); lcd.print((int)humidity);
  lcd.print("%");
  
  delay(1000);
