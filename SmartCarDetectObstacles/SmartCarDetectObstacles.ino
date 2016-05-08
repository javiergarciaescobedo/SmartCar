#include <Servo.h>

// MOTOR 1 
// Pines de conexión en la tarjeta Arduino. Los pines de conexión 
//  unidos a enA y enB de la tarjeta L298N, deben ser PWM (~) 
int enA = 5; // Pin enA de la tarjeta controladora L298N 
int in1 = 8;  // Pin in1 "  "  "       "            " 
int in2 = 9;  // Pin in2 "  "  "       "            " 
// MOTOR 2 
// Pines de conexión en la tarjeta Arduino  
int in3 = 12; // Pin in3 de la tarjeta controladora L298N 
int in4 = 13; // Pin in4 "  "  "       "            " 
int enB = 11; // Pin enB "  "  "       "            " 

int pinServoEyes = 7;
Servo servoEyes;

int pinEcho = 5;
int pinTrig = 4;

int pinTrackRight = 3;
int pinTrackLeft = 2;

const int LOOK_RIGHT = 0;
const int LOOK_LEFT = 1;
const int LOOK_FRONT_R = 2;
const int LOOK_FRONT_L = 3;

const int DEGREES_LOOK_RIGHT = 30;
const int DEGREES_LOOK_LEFT = 170;
const int DEGREES_LOOK_FRONT_R = 100;
const int DEGREES_LOOK_FRONT_L = 100;

int eyesPosition = LOOK_FRONT_R;
 
void setup() { 
  Serial.begin(9600);
  
  // Establecer el modo de salida para todos los pines utilizados 
  //  para la conexión de los motores 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT); 

  servoEyes.attach(pinServoEyes);
  
  // PONER LOS 2 MOTORES A MÁXIMA VELOCIDAD HACIA ADELANTE 
  // Motor 1 
  // En función de las conexiones del cableado, es posible que se 
  //  deba activar in1 o in2. Según se active uno u otro, el motor 
  //  girará en un sentido o el contrario 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  // El pin enA permite establecer la velocidad del motor, indicando 
  //  un valor entre 0 (apagado) y 255 (máxima velocidad) 
  analogWrite(enA, 255); 
 
  // Motor 2 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enB, 255); 

  servoEyes.write(100);

  pinMode(pinTrig, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(pinEcho, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
} 
 
void loop() { 
  int distancia = getDistancePlus();
  if(distancia < 20) {
    analogWrite(enA, 0); 
    analogWrite(enB, 0); 
    
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH); 
    analogWrite(enB, 255); 

    delay(1000);

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    analogWrite(enA, 255); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH); 
    analogWrite(enB, 255); 

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    analogWrite(enA, 255); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW); 
    analogWrite(enB, 255);     
  }
  Serial.print("Distancia ");
  Serial.print(distancia);
  Serial.println(" cm");
  Serial.print("looking ");
  Serial.print(eyesPosition);
  moveEyes();
  delay(1000);
  
} 

int getDistancePlus() {
    long pulseDuration;
    long distance;
    int tries = 0;
    int echoPort = pinEcho;
    digitalWrite(pinTrig, LOW); 
    delayMicroseconds(10);
    // Envío del pulso ultrasónico
    digitalWrite(pinTrig, HIGH); 
    delayMicroseconds(10);
    do {
        pulseDuration = pulseIn( echoPort, HIGH, 10000);
        Serial.println(pulseDuration);
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

void moveEyes() {
  switch(eyesPosition) {
    case LOOK_FRONT_R:
      eyesPosition = LOOK_LEFT;
      servoEyes.write(DEGREES_LOOK_LEFT);
      break;
    case LOOK_LEFT:
      eyesPosition = LOOK_FRONT_L;
      servoEyes.write(DEGREES_LOOK_FRONT_L);
      break;
    case LOOK_FRONT_L:
      eyesPosition = LOOK_RIGHT;
      servoEyes.write(DEGREES_LOOK_RIGHT);
      break;
    case LOOK_RIGHT:
      eyesPosition = LOOK_FRONT_R;
      servoEyes.write(DEGREES_LOOK_FRONT_R);
      break;
  }
}

