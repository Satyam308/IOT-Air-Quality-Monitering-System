#include <ThingSpeak.h>
#include<LiquidCrystal.h>
#include<ESP8266WiFi.h>
#include <WiFiClient.h>
#include<DHT.h>
#define dht_pin 4
#define d0 16
#define d1 5
#define dht_type DHT11
DHT dht(dht_pin,dht_type);
const char *ssid = "Avinash";    
const char *pass = "Sumit#$130";  

unsigned long ChannelID= 858955;
const char * WriteAPIKey = "VWZ8DY338AB65GH5";

WiFiClient client;
int sensorValue;
const int rs = 0, en = 2, d4 = 15, d5 = 13, d6 = 12, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(dht_pin,INPUT);
  pinMode(d0,OUTPUT);
  pinMode(d1,OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
    WiFi.begin(ssid,pass); 
  ThingSpeak.begin(client);
}

void loop() {
    lcd.setCursor(0, 0);
  float temp=dht.readTemperature();
  float humidity=dht.readHumidity();
  lcd.clear();
  lcd.print("Temperature:");
  lcd.print(temp);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.print(humidity);
  delay(2000);
  lcd.clear();
  sensorValue = analogRead(0);       // read analog input pin 0
lcd.setCursor(0,0);
lcd.print("ArQ=");
lcd.print(sensorValue,DEC);
lcd.print(" PPM");
lcd.println("       "); 
lcd.print("  ");
delay(2000);      // wait 100ms for next reading
if (sensorValue<=220)
{ 
  lcd.clear();
  //lcd.setCursor(0,0);
  lcd.setCursor(0,1);
  lcd.print("Fresh Air");
  digitalWrite(d1,LOW);
  digitalWrite(d0,HIGH);
  delay(500);
  }
  else if(sensorValue>=221)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bad Air");
    digitalWrite(d0,LOW);
    digitalWrite(d1,HIGH);
    
    delay(500); 
  }
  Serial.print("Temperature");
  Serial.println(temp);
  delay(500);
  Serial.print("humidity");
  Serial.println(humidity);
  delay(500);
  Serial.print("Air Quality");
  Serial.print(sensorValue);
Serial.println(" PPM");
  delay(500);
  ThingSpeak.writeField(ChannelID,1, temp, WriteAPIKey);
  delay(500);
  ThingSpeak.writeField(ChannelID,2, humidity ,WriteAPIKey);
  delay(500);
  ThingSpeak.writeField(ChannelID,3, sensorValue, WriteAPIKey);
  delay(500);
 
}
