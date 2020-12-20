#include <Arduino.h>
#include <LiquidCrystal.h>

#define blueLed A0
#define redLed A1
#define greenLed A2
#define bp1 10
#define bp2 11
#define bp3 12
#define echoPin 9
#define trigPin 8

#define seuil 500

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void menu()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("====BILAN N1====");
  lcd.setCursor(0, 1);
  lcd.print("1:Dist");
  lcd.setCursor(9, 1);
  lcd.print("2:Temps");
}

void setup()
{
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(bp1, INPUT_PULLUP);
  pinMode(bp2, INPUT_PULLUP);
  pinMode(bp3, INPUT_PULLUP);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  lcd.begin(16, 2);
  menu();
}

void calcule_distance_duree()
{
    long duree;
    long distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
    distance = duree*340/(2*10000);
    Serial.println(distance);
    delay(50);
}

void distance()
{
  int breakornot = HIGH;
  while(breakornot != LOW)
  {
    long duree, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
    distance = duree * 340 / (2 * 10000);
    lcd.setCursor(0, 0);
    lcd.print("Mode distance");
    lcd.setCursor(0, 1);
    lcd.print("Dist :");
    lcd.setCursor(7, 1);
    lcd.print(distance);
    lcd.setCursor(14, 1);
    lcd.print("cm");
    delay(50);
    lcd.clear();
    if(distance > 5 && distance < 10)
    {
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      delay(20);
      digitalWrite(redLed, LOW);
    }
    else if(distance > 10 && distance < 15)
    {
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, HIGH);
      delay(50);
      digitalWrite(blueLed, LOW);
    }
    else if(distance > 15)
    {
      digitalWrite(greenLed, HIGH);
    }
    breakornot = digitalRead(bp3);
  }
}

void duree()
{
  int breakornot = HIGH;
  while(breakornot != LOW)
  {
   long duree, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duree = pulseIn(echoPin, HIGH);
    Serial.print("duree :");
    Serial.println(duree);
    lcd.setCursor(0, 0);
    lcd.print("Mode duree");
    lcd.setCursor(0, 1);
    lcd.print("Tps :");
    lcd.setCursor(7, 1);
    lcd.print(duree);
    lcd.setCursor(14, 1);
    lcd.print("s");
    delay(75);
    lcd.clear();
    if(duree > seuil)
    {
      digitalWrite(redLed, HIGH),
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
      delay(30);
      digitalWrite(redLed, LOW),
      digitalWrite(greenLed, HIGH);
      digitalWrite(blueLed, LOW);
      delay(30);
      digitalWrite(redLed, LOW),
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, HIGH);
      delay(30);
    }
    else
    {
      digitalWrite(blueLed, LOW);
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
    } 
    breakornot = digitalRead(bp3);
  }
}

void loop()
{
  int stateBP1 = digitalRead(bp1);
  int stateBP2 = digitalRead(bp2);
  int stateBP3 = digitalRead(bp3);

  if(stateBP1 == LOW)
  {
    distance();
  }
  else if(stateBP2 == LOW)
  {
    duree();
  }
  menu();
}
