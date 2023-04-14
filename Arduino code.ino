#include <LiquidCrystal.h>

int SIGNAL_PIN = A5;
int waterValue = 0;

int tempPin = A4;
int tempValue;

int buzzerPin = 9;

int flamePin = 6;
int flameValue;

int echoPin = 5;
int trigPin = 8;
long duration;
int distance;

const int rs = 4, en = 7, d4 = 11, d5 = 12, d6 = 2, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  
  lcd.setCursor(0, 0);
  tempValue = analogRead(tempPin);
  float mv = (tempValue/1024.0)*5000;
  float cel = mv/10;
  Serial.print("TEMPRATURE = ");
  lcd.print(cel);
  lcd.print(" *C");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  waterValue = analogRead(SIGNAL_PIN);
  Serial.println(waterValue);
  if (waterValue > 0) {
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  flameValue = digitalRead(flamePin);
  if (flameValue > 0) {
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance > 4 && distance < 6){
    lcd.setCursor(0,1);
    lcd.print("Someone is out");
    delay(1000);
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("                ");
  }
  Serial.print("Distance: ");
  Serial.println(distance);
  
  delay(1000);
}