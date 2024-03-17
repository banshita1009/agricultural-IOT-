#include <Servo.h>
#include "DHT.h"
#define DHTPIN 7
Servo myServo;
#define DHTTYPE DHT11   // DHT 1

int soil = A0;
#define Buzzer 12

int motor 1a  = 

// Motor control pins

const int leftMotorPin1 = 3; //A1 pin of motordriver to 17 pin of ESP
const int leftMotorPin2 = 4; //D1 pin of motordriver to 15 pin of ESP
const int rightMotorPin1 = 5; //A2 pin of motordriver to 16 pin of ESP
const int rightMotorPin2 = 6; //D2 pin of motordriver to 14 pin of ESP
DHT dht(DHTPIN, DHTTYPE);

//for pump 

int pumpPin = 1; // Assigning the pump to digital pin 9

// Define the pin for the buzzer
#define BUZZER_PIN 8

void setup() {

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  pinMode(soil, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // initialize the pump pin as an output:
  pinMode(pumpPin, OUTPUT);

  myServo.attach(9); // attach the servo to pin 9 of esp32

  // Initialize motor control pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Set the ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

}

void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void turnRight() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void turnLeft() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void stopMotors() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void loop2()
{
  digitalWrite(pumpPin, LOW);
  int sensor_data = analogRead(soil);
  Serial.print("Analog Output: ");
  Serial.println(sensor_data);

  if(sensor_data < 500)
  {
    Serial.println("Status: Soil is too wet");
    digitalWrite(pumpPin, LOW);   // send signal from pin 9 to circuit
    delay(2000);  
  }
    
  else if(sensor_data >= 500 && sensor_data < 750)
  {
    Serial.println("Status: Soil moisture is perfect");
    digitalWrite(pumpPin, LOW);   // send signal from pin 9 to circuit
    delay(2000);  
  }
  else {
    Serial.println("Status: Soil is too dry - time to water!");

    digitalWrite(pumpPin, HIGH);   // send signal from pin 9 to circuit
    delay(2000);                   // wait for 2 seconds
    digitalWrite(pumpPin, LOW);    // end signal
    delay(2000);                   // wait for 2 seconds before repeating loop

  }
  digitalWrite(pumpPin, LOW); 
}

void loop() {
  
  digitalWrite(pumpPin, LOW); 
  float h = dht.readHumidity(); // Humidity
  float t = dht.readTemperature(); //Temprature
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));

  if(t > 50%){
    digitalWrite(Buzzer, HIGH);   // Turn the LED on (HIGH is the voltage level)
    delay(1000);                   // Wait for a second (1000 milliseconds)
    digitalWrite(Buzzer, LOW);    // Turn the LED off by making the voltage LOW
    delay(1000);                   // Wait for a second
  }

  else {
    Serial.print("temperature is good!");
  }
  myServo.write(0); // move servo to 0 degrees

  // Move forward for 3 seconds
  moveForward();
  delay(3000);
  // Stop for 5 second
  stopMotors();

  myServo.write(90); // move servo to 90 degrees
  delay(4000); // wait for 4 seconds
  myServo.write(0); // move servo to 0 degrees

  // for soil 
  loop2();

  // Move forward for 3 seconds
  moveForward();
  delay(3000);

  // Turn right for 2 seconds
  turnRight();
  delay(2000);

 // Move forward for 3 seconds
  moveForward();
  delay(3000);
  // Stop for 5 second
  stopMotors();
  myServo.write(90); // move servo to 90 degrees
  delay(4000); // wait for 4 seconds
  myServo.write(0); // move servo to 0 degrees

  loop2();

  // Move forward for 3 seconds
  moveForward();
  delay(3000);

  // Turn left for 2 seconds
  turnLeft();
  delay(2000);

}