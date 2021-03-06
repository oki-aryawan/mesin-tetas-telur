/* 
 *  Oki Wiradita
 *  @oki_aryawan
 *  Panji Anom, 17 Feb 2021
*/

#include "DHT.h"
#define DHTPIN 12    
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int lampu = 2;
const int lampu_mati = HIGH;
const int lampu_hidup = LOW;

const int buzzer = 4;
int status_buzzer = LOW;
const int buzz_hidup = HIGH;
const int buzz_mati = LOW;

unsigned long previousMillis = 0;
const long interval = 1000; 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <EEPROM.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() {
  Serial.begin(57600);
  lcd.begin();
  dht.begin();
  pinMode (lampu, OUTPUT);
  pinMode (buzzer, OUTPUT);
 //rtc.adjust(DateTime(2021, 4, 28, 14, 21, 0));
}
void loop() {
  sensor ();
  //jam();
}

void jam (){
  DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 
    lcd.setCursor (0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print("  ");
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    delay(3000);
}
void sensor (){
  int kelm = dht.readHumidity();
  int suhu = dht.readTemperature();
  int f = dht.readTemperature(true);

  if (suhu<=38){
    digitalWrite(lampu, lampu_hidup); 
  } else digitalWrite (lampu, lampu_mati);
  
  if (isnan(kelm) || isnan(suhu) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(0,0);
    lcd.print("  Sistem Gagal  ");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("  Mulai  Ulang  ");
    delay(2000);
    return;
  }
  float hif = dht.computeHeatIndex(f, kelm);
  float hic = dht.computeHeatIndex(suhu, kelm, false);

  /*Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("??C "));
  Serial.print(f);
  Serial.print(F("??F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("??C "));
  Serial.print(hif);
  Serial.println(F("??F")); */

  lcd.setCursor(1,0);
  lcd.print(F("T: "));
  lcd.print(suhu);
  lcd.print(F("C "));
  lcd.setCursor(9,0);
  lcd.print("H: ");
  lcd.print(kelm);
  lcd.print("%");
}

void balik (){
  DateTime now = rtc.now();
  if (now.hour()== 12 && now.minute () ==00){
    lcd.setCursor(1,0);
    lcd.print ("  BALIK  TELUR  ");
    digitalWrite (pembalik, pembalik_hidup);
    delay(12000);
  }else digitalWrite(pembalik, pembalik_mati);

  if (now.hour()== 18 && now.minute () ==00){
    lcd.setCursor(1,0);
    lcd.print ("  BALIK  TELUR  ");
    digitalWrite (pembalik, pembalik_hidup);
    delay(12000);
  }else digitalWrite(buzzer, buzz_mati);
  
  if (now.hour()== 24 && now.minute () ==00){
    lcd.setCursor(1,0);
    lcd.print ("  BALIK  TELUR  ");
    digitalWrite (pembalik, pembalik_hidup);
    delay(12000);
  }else digitalWrite(pembalik, pembalik_mati);
  
  if (now.hour()== 6 && now.minute () ==00){
    lcd.setCursor(1,0);
    lcd.print ("  BALIK  TELUR  ");
    digitalWrite (pembalik, pembalik_hidup);
    delay(12000);
  } else digitalWrite(pembalik, pembalik_mati);
} 
