#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define PIN_TX    7
#define PIN_RX    8
#define BAUDRATE  9600
#define PHONE_NUMBER "8504034506"
#define MESSAGE  "RAJASTHAN DIGIFEST DUSTBIN HALL B (B/E/11) IS Full PLEASE EMPTY ME"


GPRS gprs(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,BaudRate



// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration;
int distance;
int safetyDistance;


void setup() {
 gprs.checkPowerUp();
  Serial.begin(9600);   
  
  while(!gprs.init()) {
      delay(1000);
      Serial.println("Initialization failed!");
  }  

  while(!gprs.isNetworkRegistered())
  {
    delay(1000);
    Serial.println("Network has not registered yet!");
  }

  Serial.println("gprs initialize done!");
  
  


  

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delay(10000);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 15){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  gprs.sendSMS(PHONE_NUMBER,MESSAGE);
      Serial.println("SMS sent OK");
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}






















