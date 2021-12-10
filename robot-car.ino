#include <Servo.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <SoftwareSerial.h> 

Servo sensor;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

long duration, distanceAhead;
long newDistanceRight, newDistanceLeft, newDistanceAhead;

//Ultrasonic Module pins
const int trigPin = 13; // 10 microsecond high pulse causes chirp , wait 50 us??
const int echoPin = 12; //distance
const int servoPin = 11; //mechanics

// Motor control pins : L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1 --> forwards
const int in2Pin = 5; // Left motor Direction 2 --> backwards
const int in3Pin = 4; // Right motor Direction 1 --> forwards
const int in4Pin = 2; // Right motor Direction 2 --> backwards
const int enBPin = 3; // Right motor PWM speed control

void defineOutputOrInput() {

  //motors
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);

  //sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //it will always be low so that's why in this function
  digitalWrite ( trigPin , LOW);
}

void goStraight() {
  lcd.print("I'm going straight!");
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 170);
  analogWrite(enBPin, 160);
}

void goBack() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enAPin, 170);
  analogWrite(enBPin, 160);
}

void stopMoving() {
  lcd.print("I'm stopping!");
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 0);
  analogWrite(enBPin, 0);
}

void turnLeft() {
  lcd.print("I'm turning left!");
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 190);
  analogWrite(enBPin, 160);
}

void turnRight() {
  lcd.print("I'm turning right!");
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enAPin, 190);
  analogWrite(enBPin, 160);
}

long checkDistanceAhead() {
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceAhead = duration / 58;

  return distanceAhead;
}

int lookRight() {
  sensor.attach(servoPin);
  sensor.write(30); //rotate right
  delay(500);
  int distanceRight = checkDistanceAhead();
  delay(100);
  sensor.write(105);  //look forward

  return distanceRight;
}

int lookLeft() {
  sensor.attach(servoPin);
  sensor.write(180); //rotate left
  delay(500);
  int distanceLeft = checkDistanceAhead();
  delay(100);
  sensor.write(105);  //look forward

  return distanceLeft;
}

void setup () {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("Hello World!"); // Print the string "Hello World!"
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("My name is Ardi!");
  defineOutputOrInput();
}

void loop () {

  while (!Serial.available()) {}
  // serial read section
    while (Serial.available()) {
      char c = Serial.read(); 
      switch (c) {
        case 'S':
          stopMoving();
          break;
        case 'F':
          goStraight();
          break;
        case 'L':
          turnLeft();
          break;
        case 'R':
          turnRight();
          break;
        case 'B':
          goBack();
          break;
        default:
          lcd.print("I don't know what to do!");
          break;
      }
    }
}
