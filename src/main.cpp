#include <Arduino.h>

#define RED_PIN 19
#define GREEN_PIN 26
#define BLUE_PIN 25
#define WHITE_PIN 18 // with some Red,Green & Blue LEDs

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);

  digitalWrite(WHITE_PIN,LOW);
  digitalWrite(RED_PIN,LOW);
  digitalWrite(GREEN_PIN,LOW);
  digitalWrite(BLUE_PIN,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(WHITE_PIN,LOW);
  digitalWrite(RED_PIN, HIGH);
  delay(2000);
  digitalWrite(RED_PIN,LOW);
  digitalWrite(GREEN_PIN,HIGH);
  delay(2000);
  digitalWrite(GREEN_PIN,LOW);
  digitalWrite(BLUE_PIN,HIGH);
  delay(2000);
  digitalWrite(BLUE_PIN,LOW);
  digitalWrite(WHITE_PIN,HIGH);
  delay(2000);
  
}