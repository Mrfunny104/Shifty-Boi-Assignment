//Libaries 
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <Wire.h>
#include <DS3231.h>

//RTC Setup
DS3231 clock;
RTCDateTime dt;

//Shift Register Setup
int latch=9;  //74HC595  pin 9 STCP
int clockPin=10; //74HC595  pin 10 SHCP
int dataPin=8;   //74HC595  pin 8 DS

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

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
  
  //shift stuff
  pinMode(latch,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}

void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}

void loop() {
  dt = clock.getDateTime();

  // Time Display

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

//Code for Later
  /*Display(1);
  delay(500);
  Display(2);
  delay(500);
  Display(3);
  delay(500);
  Display(4);
  delay(500);
  Display(5);
  delay(500);
  Display(6);
  delay(500);
  Display(7);
  delay(500);
  Display(8);
  delay(500);
  Display(9);
  delay(500);
  Display(10);
  delay(500);
  Display(11);
  delay(500);
  Display(12);
  delay(500);
  Display(13);
  delay(500);
  Display(14);
  delay(500);
  Display(15);
  delay(500);*/
}
