//Libaries 
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <DS3231.h>

//RTC Setup
DS3231 clock;
RTCDateTime dt;

//Temp & Humidity Sensor Setup
int pinDHT11 = 6;
SimpleDHT11 dht11;

//LCD Setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte thermometer[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte droplet[8] = //icon for water droplet
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(1,thermometer);
  lcd.createChar(2,droplet);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);    //Loads Time and Date onto Arduino with upload
}

void loop() {
  dt = clock.getDateTime();

  // Time Display for Serial & LCD
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("");
  Serial.print(dt.month);  Serial.print("");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(dt.day);   lcd.print("/");
  lcd.print(dt.month);  lcd.print("/");
  lcd.print(dt.year-2000);   lcd.print(" ");
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second); lcd.println("    ");

  //Temperature & Humidity Display
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  
  //If statement tells Arduino hox to fix any reading errors from Temp sensor
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    return;
  }
  lcd.setCursor(1,1);
  lcd.write(1); lcd.print(" "); lcd.print((int)temperature);
  lcd.print((char)223);  lcd.print("C   ");
  lcd.write(2);  lcd.print(" "); lcd.print((int)humidity);
  lcd.print("%");
  
  delay(1000);
