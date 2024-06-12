#include <Arduino.h>
#include <LiquidCrystal.h>

// Pins
int trigger_pin = 3;
int echo_pin = 4;
int RS_pin = 5;
int E_pin = 6;
int D4_pin = 7;
int D5_pin = 8;
int D6_pin = 9;
int D7_pin = 10;
int led_pin = 2; 

LiquidCrystal lcd(RS_pin, E_pin, D4_pin, D5_pin, D6_pin, D7_pin); 

// Variables
unsigned long ultrasonicDelay = 200; 
unsigned long lastTime = 0; 
int distance = 0;

void trigger() {
  digitalWrite(trigger_pin, LOW);
  delay(2);
  digitalWrite(trigger_pin, HIGH);
  delay(10);
  digitalWrite(trigger_pin, LOW);
}

int get_distance() {
  long duration = pulseIn(echo_pin, HIGH);
  int distance = duration / 58;
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" us, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void led_frequency(int distance) {

  digitalWrite(led_pin, HIGH);
  delay(distance * 5);
  digitalWrite(led_pin, LOW);
  delay(distance * 5);
}

void setup() {
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin, OUTPUT); 
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(0, 0); 
  String start_message = "Starting...";
  lcd.setCursor(0, 0); 

  for (int i = 0; i < start_message.length(); i++) {
    lcd.print(start_message[i]);
    delay(200);
  }
  delay(500);
  lcd.clear();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= ultrasonicDelay) {
    trigger(); 
    distance = get_distance();
    lastTime = currentTime; 
    if(distance < 40){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("warning!!!");
    lcd.setCursor(0,1);
    lcd.print("obstacle nearby");
    }
    else{
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Distance: ");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print(" cm");
    }
  }

  led_frequency(distance);
}
