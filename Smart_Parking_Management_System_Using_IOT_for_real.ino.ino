#define BLYNK_TEMPLATE_ID "TMPL3zSzwgQhh"
#define BLYNK_TEMPLATE_NAME "Smart Parking System"
#define BLYNK_AUTH_TOKEN "UAFKKFDUFFHFEIFIEHFIHAKDIEH"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27,16,2);

char ssid[] = "Wifi name";
char pass[] = "password";
char auth[] = BLYNK_AUTH_TOKEN;

#define ir D0
#define trigger D1
#define echo D2

BlynkTimer timer;

void checkSlot(){
  long distance;
  long duration;
  String slotstatus;
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  duration=pulseIn(echo,HIGH);
  distance=duration*0.0343/2;

  int a=digitalRead(ir);

  lcd.setCursor(0,0);

  if(a==LOW){
    slotstatus="OCCUPIED";
  }
  else{
    slotstatus="AVAILABLE";
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Slot:");
  lcd.print(slotstatus);
  lcd.setCursor(0,1);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm");

  Blynk.virtualWrite(V0,slotstatus);
  Blynk.virtualWrite(V1,distance);
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ir, INPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Parking");

  timer.setInterval(1000L, checkSlot);
}

void loop(){
  Blynk.run();
  timer.run();
}
