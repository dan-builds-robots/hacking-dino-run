#include <Servo.h>

int servoPin = 9;
int servoPos = 0;
int computedDelay = 10000;
Servo myServo;
int photoresistor = A0;
int delaytime = 200;
int lightVal;
int cactiCount = 0;

int originalDelay = 1100;

long onTime = 400;           // milliseconds of on-time
long responseTime = 1100;          // milliseconds of off-time

int timeOfLastJump = 0;

int iterationCount = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(photoresistor, INPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(servoPos + 90);
}

void loop() {
  unsigned long currentMillis = millis();
  lightVal = analogRead(photoresistor);
  
  //Serial.print("Photoresistor value: ");
  //Serial.print(lightVal);
  //Serial.println("");
      
  if (lightVal < 650 && iterationCount % 2 == 0) {
    
    iterationCount = 0;
    cactiCount++;
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.print("obstacle ");
    Serial.print(cactiCount);
    Serial.print(" detected");
    Serial.println("");
    
    servoUp();
    
    // wait a little
    delay(250);

    // release the spacebar
    servoDown();
    
    // jumps sooner as the game speeds up
    responseTime-=1;
    
  }

  iterationCount++;
  
}

void servoUp() {
  
  Serial.print("Time Since Last Jump: ");
  Serial.print(millis() - timeOfLastJump);
  Serial.println();
  
  int delayPeriod = 0;
  
  //calculate how long to delay for

  // if more than a second has passed since the last jump...
  if (millis() - timeOfLastJump > originalDelay) { 

    //then delay for 1 second before jumping
    delayPeriod = originalDelay;
    
  } else {

    //if less than 1 sec has passed since the last jump,
    //delay for 1 sec minus the time that has passed since the last jump
    delayPeriod = originalDelay - (millis() - timeOfLastJump);

  }

  Serial.print("Delay Period: ");
  Serial.print(delayPeriod);
  Serial.println();

  //delayPeriod - responseTime;
  
  // delay the dinosaurs jump
  delay(delayPeriod);

  Serial.println("Servo delay period complete.");
  
  // press the spacebar
  myServo.write(servoPos + 118);
  
  // Save the time of the jump
  timeOfLastJump = millis();

  Serial.println("Spacebar pressed.");
  
}

void servoDown() {
  myServo.write(servoPos + 90);
  Serial.print("Spacebar released.");
}
