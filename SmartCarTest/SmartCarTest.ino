// Para poder programar servo-motores se debe incluir la librería Servo.h 
#include <Servo.h>

#include "NewPing.h"

// MOTOR 1 (Izquierdo)
// Pines de conexión en la tarjeta Arduino. Los pines de conexión 
//  unidos a enA y enB de la tarjeta L298N, deben ser PWM (~) 
int enA = 6; // Pin enA de la tarjeta controladora L298N 
int in1 = 7;  // Pin in1 "  "  "       "            " 
int in2 = 5;  // Pin in2 "  "  "       "            " 
// MOTOR 2 (Derecho)
int in3 = 4; // Pin in3 de la tarjeta controladora L298N 
int in4 = 2; // Pin in4 "  "  "       "            " 
int enB = 3; // Pin enB "  "  "       "            " 

// Pin de la tarjeta Arduino donde se haya conectado el pin Echo del sensor ultrasonidos 
int pinEcho = 10;
// Pin de la tarjeta Arduino donde se haya conectado el pin Trig del sensor ultrasonidos 
int pinTrig = 11;

// Pin de la tarjeta Arduino donde se ha conectado el pin de señal del servo 
int pinServo1 = 9;   

// Pin de sensores seguidores de líneas
int pinLineTrackingRight = 13;
int pinLineTrackingLeft = 12;

// El servo-motor se va a ir posicionando sucesivamente 
//  para mirar al centro, derecha e izquierda, por lo que se van a  
//  almacenar en 3 constantes los ángulos que debe tomar el servo-motor 
//  para tomar las posiciones deseadas 
const int ANGULO_CENTRO = 90; 
const int ANGULO_IZQUIERDA = 120; 
const int ANGULO_DERECHA = 60; 

// Variable que hace referencia al servo-motor del sensor de obstáculos
Servo servo1; 

int max_distance = 200; // Distancia máxima a detectar en cm
 
NewPing sonar(pinTrig, pinEcho, max_distance);

/* 
 *  
 *  SETUP
 *  
 */
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

  // Activación del pin TRIG como salida, para enviar el pulso ultrasónico 
  pinMode(pinTrig, OUTPUT);
  // Activación del pin ECHO como entrada, para recibir el pulso ultrasónico 
  pinMode(pinEcho, INPUT);
  
  pinMode(pinLineTrackingRight, INPUT); 
  pinMode(pinLineTrackingLeft, INPUT);

  servo1.attach(pinServo1);

  // Esperar un momento para preparar el coche en su lugar
  delay(5000);
} 

/* 
 *  
 *  LOOP
 *  
 */
void loop() { 
  servo1.write(ANGULO_CENTRO);
  
  Serial.println("Test sensor distancia: ");
  for(int i=0; i<10; i++) {
    Serial.print("   distancia: (");
    Serial.print(i+1);
    Serial.print(" de 10): ");
    Serial.println(sonar.ping_cm());
    delay(500);
  }

  Serial.println("Test servomotor: ");
  Serial.println("   Derecha: ");
  servo1.write(ANGULO_DERECHA);
  delay(500);
  Serial.println("   Izquierda: ");
  servo1.write(ANGULO_IZQUIERDA);
  delay(500);
  Serial.println("   Centro: ");
  servo1.write(ANGULO_CENTRO);
  delay(500);  
  
  Serial.println("Sensores seguidores de linea: ");
  for(int i=0; i<10; i++) {
    Serial.print("   Sensor derecho: (");
    Serial.print(i+1);
    Serial.print(" de 10): ");
    int onLineRight = digitalRead(pinLineTrackingRight);  
    Serial.println(onLineRight);
    delay(500);
  }
  Serial.println();
  for(int i=0; i<10; i++) {
    Serial.print("   Sensor izquierdo: (");
    Serial.print(i+1);
    Serial.print(" de 10): ");
    int onLineLeft = digitalRead(pinLineTrackingLeft);  
    Serial.println(onLineLeft);
    delay(500);
  }
  
  Serial.println("Motor izquierdo: ");
  Serial.println("  Adelante: ");
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  analogWrite(enA, 255); 
  delay(200);
  analogWrite(enA, 0); 
  delay(500);
  Serial.println("  Atrás: ");
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  analogWrite(enA, 255); 
  delay(200);
  analogWrite(enA, 0); 
  delay(500);

  Serial.println("Motor derecho: ");
  Serial.println("  Adelante: ");
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enB, 255); 
  delay(200);
  analogWrite(enB, 0); 
  delay(500);
  Serial.println("  Atrás: ");
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enB, 255); 
  delay(200);
  analogWrite(enB, 0); 
}
