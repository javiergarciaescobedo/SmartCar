// connect motor controller pins to Arduino digital pins
// motor one

#include <Servo.h>

int enA = 11;
int in1 = 13;
int in2 = 12;
// motor two
int enB = 3;
int in3 = 9;
int in4 = 8;

Servo myservo;
int servoPin = 7;
int servoPos = 90;
int servoDir = -1;
int servoDelay = 0;

long distancia;
long tiempo;

const int EYES_STOPPED = 0;
const int EYES_TO_RIGHT = 1;
const int EYES_TO_LEFT = 2;
int eyesPosition = 90;
int eyesRotation = EYES_TO_RIGHT;

boolean motoresEncendidos = false;
boolean collisionDetected = false;

void setup()
{
  Serial.begin(9600);
// set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  myservo.attach(servoPin);

  pinMode(5, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(6, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/

  frontFullSpeed();
  moveEyes();
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}

void frontFullSpeed() {
  // Left motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 127);
  // Right motor
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  analogWrite(enB, 127);

  motoresEncendidos = true;
}

void parar() {
    // Left motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
//  analogWrite(enA, 0);
  // Right motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
//  analogWrite(enB, 0);

  motoresEncendidos = false;
}

void turnRight() {
  analogWrite(enA, 200);
}

//void testServo() {
//  int pos = 0;    // variable to store the servo position
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//}
//
//void servoToPos(int pos) {
//  myservo.write(pos);   
//}

void loop()
{
//  demoOne();
// delay(1000);
//  demoTwo();
//  delay(1000);
//testServo();
//servoDelay++;
//if(servoDelay > 500) {
//  servoToPos(servoPos);
//  servoPos += servoDir * 5;
//  if(servoPos < 90-70) {
//    servoDir = 1;
//  }
//  if(servoPos > 90+70) {
//    servoDir = -1;
//  }  
//  servoDelay = 0;
//}
//delay(500);
//turnRight();
//delay(500);

  distancia = getDistance();
  distancia = getDistancePlus();
  Serial.print("Distancia ");
  Serial.print(distancia);
  Serial.println(" cm");
  if(distancia != -1 && distancia < 20) {
    if(motoresEncendidos) {
      parar();
      eyesRotation = EYES_STOPPED;
      collisionDetected = true;
    }
  } else {
    if(!motoresEncendidos && !collisionDetected) {
      frontFullSpeed();
    }
  } 
  moveEyes();
  delay(100);
}

void moveEyes() {
  const int INTERVAL = 10;
  const int MAX_ROTATION_LEFT = 60;
  const int MAX_ROTATION_RIGHT = 120;

  if(eyesRotation != EYES_STOPPED) {
    if(eyesRotation == EYES_TO_RIGHT) {
      eyesPosition += INTERVAL;
    } else {
      eyesPosition -= INTERVAL;
    }
    if(eyesPosition > MAX_ROTATION_RIGHT) {
      eyesPosition = MAX_ROTATION_RIGHT;
      eyesRotation = EYES_TO_LEFT;
    } else if(eyesPosition < MAX_ROTATION_LEFT) {
      eyesPosition = MAX_ROTATION_LEFT;
      eyesRotation = EYES_TO_RIGHT;
    } 
    myservo.write(eyesPosition);
  }
}

/* Return distance in cm or -1 if distance not detected */
int getDistance() {
  const int MEASURE_COUNTER = 1;
  long pulseTime;
  int distanceCm = 0;
  boolean maxDistanceReturned = false;
  for(int i = 0; i < MEASURE_COUNTER && !maxDistanceReturned; i++) {
    // Por cuestión de estabilización del sensor
    digitalWrite(5, LOW); 
    delayMicroseconds(10);
    // Envío del pulso ultrasónico
    digitalWrite(5, HIGH); 
    delayMicroseconds(10);
    pulseTime = pulseIn(6, HIGH);
    int tmpDistanceCm = int(0.017*pulseTime); 
    if(tmpDistanceCm > 2000) {
      maxDistanceReturned = true;
    }
    distanceCm += tmpDistanceCm;
  }
  if(!maxDistanceReturned) {
    return int(distanceCm / MEASURE_COUNTER);
  } else {
    return -1;
  }
}

int getDistancePlus() {
    long pulseDuration;
    long distance;
    int tries = 0;
    int echoPort = 6;
    digitalWrite(5, LOW); 
    delayMicroseconds(10);
    // Envío del pulso ultrasónico
    digitalWrite(5, HIGH); 
    delayMicroseconds(10);
    do
    {
//        pulseDuration = pulseIn( echoPort, HIGH, 50000);
        pulseDuration = pulseIn( echoPort, HIGH, 10000);
        distance = 0.034 * pulseDuration / 2;
        if ( pulseDuration == 0 ) {
            delay(100);
            pinMode(echoPort, OUTPUT);
            digitalWrite(echoPort, LOW);
            delay(100);
            pinMode(echoPort, INPUT);
        }
    } while (pulseDuration == 0 && ++tries < 1);
    if (pulseDuration == 0)
      return -1;
    else
      return int(distance);
}
