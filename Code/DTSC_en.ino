// Add libs.
#include <SPI.h>
#include <SD.h>

// Let's write the pins that the Ultrasonic sensor is connected to.
#define trigPin 2  // example
#define echoPin 3 // example

// Let's determine the UltraSonic values.
long duration; 
int distance; 

File myFile; 

// The part of the transactions.
void setup() {
  
Serial.begin(9600);

// Let's determine the input and output pins of the Ultrasonic sensor.
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 

Serial.print("Checking SD card..");

// Let's run trigPin..
digitalWrite(trigPin, HIGH);

// Code to open/create the file.
myFile = SD.open("qiyascc.txt", FILE_WRITE);
SD.begin(10);

if ((trigPin, LOW) && (!SD.begin(10))) {
    Serial.println("There are two problems right now.");
    Serial.println("First: Either the SD card is not inserted or there is a problem with the connections. Please check and try again.");
    Serial.println("Secondly: Ultrasonic sensor not working. Check the connections and try again.");      
} else if (!SD.begin(10) && (trigPin, HIGH)) {
        Serial.println("I have good news and bad news. Which one should I start first? Anyway, I'll decide for myself anyway, hahaha!");
        Serial.println("Bad news: SD card not found. The SD card is either not inserted or there is a problem with the connections.");
        Serial.println("Good news: The Ultrasonic sensor is working.");
} else if ((trigPin, LOW) && (SD.begin(10))) { 
        Serial.println("I have good news and bad news. Which one should I start first? Anyway, I'll decide for myself anyway, hahaha!");
        Serial.println("Bad news: The Ultrasonic sensor is not working.");
        Serial.println("Good news: SD card found, the module is working.");      
} else if ((SD.begin(10)) && (trigPin, HIGH)) {
        Serial.println("There are no problems, the system works flawlessly.");
} 

// Let's turn off trigPin for now.
digitalWrite(trigPin, LOW);
 
// Get a alert if the file is not/created.
if (!myFile) {
        Serial.println("Error: Problem creating file, check and try again.");
} else {       
        Serial.print("The qiyascc.txt file has been created.");

//   Description - including file.
        myFile.println("This file is for writing the measured distance.");

//  Codes to determine the distance.
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH);
        int distance = duration * 0.034 / 2;
      
  
//      Data transfer to SD card.
        Serial.println("The file is opened, now let's measure and write the distance..");
        Serial.println("The information is written to the SD card...");
        myFile.println("Distance: ");
        myFile.print(distance);
        myFile.print(" cm.");
        myFile.close();
        Serial.println("Transaction terminated successfully..");
        Serial.println("The qiyascc.txt file was created and the distance information received was saved to the file.");
}
while(1);
}

void loop() {
// This time we did not use this place.
}
