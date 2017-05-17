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
const int ANGULO_IZQUIERDA = 150; //130
const int ANGULO_DERECHA = 30; //50

// Almacena el ángulo en el que se encuentre el servo-motor en cada momento 
int anguloServo = ANGULO_CENTRO;

// Si el servo-motor está posicionado en el ángulo central, hay que conocer 
//  si se está girando hacia la derecha o hacia la izquierda para poder establecer 
//  el siguiente ángulo, que podrá ser hacia la derecha o hacia la izquierda según 
//  el sentido de giro actual 
boolean haciaDerecha = true; 

// Valor de compensación para frenar la velocidad de los motores en caso de que
//  la velocidad sera demasiado alta. 1 = máxima velocidad
const float POTENCIA_MOTOR = 1;

// Valores para compensar la velocidad de los motores en caso de que un motor
//  tenga más velocidad que otro en todo momento
const float COMPENSA_MOTOR_IZQUIERDO = 0.9;
const float COMPENSA_MOTOR_DERECHO = 1;

const int DIRECCION_PARAR = 0;
const int DIRECCION_ADELANTE = 1;
const int DIRECCION_ATRAS = 2;
const int DIRECCION_ROTACION_DERECHA = 3;
const int DIRECCION_ROTACION_IZQUIERDA = 4;

// Variable que hace referencia al servo-motor del sensor de obstáculos
Servo servo1; 

int max_distance = 200; // Distancia máxima a detectar en cm
const int DISTANCIA_OBSTACULO = 30;

const int TIEMPO_RETROCESO = 1000;
const int TIEMPO_GIRO = 300;
 
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
  
  servo1.attach(pinServo1);
  servo1.write(ANGULO_CENTRO);

  // Esperar un momento para preparar el coche en su lugar
  delay(5000);
} 

/* 
 *  
 *  LOOP
 *  
 */
void loop() { 
  int distancia = obtenerDistanciaObstaculo();
  Serial.print("distancia = ");
  Serial.println(distancia);
  if(distancia < DISTANCIA_OBSTACULO && distancia != 0) {
    rotarMayorDistancia();
  } else {
    moverCoche(DIRECCION_ADELANTE, 255 * POTENCIA_MOTOR);
    //moverOjos();
  }
  delay(50);
} 

int obtenerDistanciaObstaculo() {
  return sonar.ping_median(3) / 100;
}

void moverOjos() {
  // Actuar de manera manera diferente según el ángulo en el que se encuentre 
  //  actualmente el servo-motor 
  switch(anguloServo) { 
    case ANGULO_DERECHA: 
      // Si está hacia la derecha, girarlo hacia el ángulo del centro 
      anguloServo = ANGULO_CENTRO; 
      // El sentido de giro se establece hacia la izquierda 
      haciaDerecha = false; 
      break; 
    case ANGULO_CENTRO: 
      // Si el servo-motor está en la posición central, hay que averiguar si queremos 
      //  girarlo hacia la derecha o hacia la izquierda, en función del sentido en el que  
      //  actualmente está girando 
      if(haciaDerecha) { 
        anguloServo = ANGULO_DERECHA; 
      } else { 
        anguloServo = ANGULO_IZQUIERDA; 
      } 
      break; 
    case ANGULO_IZQUIERDA: 
      // Si está hacia la izquierda, girarlo hacia el ángulo del centro 
      anguloServo = ANGULO_CENTRO; 
      // El sentido de giro se establece hacia la derecha 
      haciaDerecha = true; 
      break; 
  } 
  // Mover el servo-motor hasta el ángulo que se ha calculado 
  servo1.write(anguloServo); 
  // Esperar en esa posición un tiempo para asegurar que el motor ha alcanzado
  //  esa posición (Speed:  4.8V: 0.12 sec/60°)
  delay(300); 
}

void moverCoche(int direccion, int velocidad) {
  switch(direccion) {
    case DIRECCION_PARAR:
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      analogWrite(enA, 0); 
      digitalWrite(in3, LOW); 
      digitalWrite(in4, LOW); 
      analogWrite(enB, 0); 
      break;
    case DIRECCION_ADELANTE:
      digitalWrite(in1, HIGH); 
      digitalWrite(in2, LOW); 
      analogWrite(enA, velocidad * COMPENSA_MOTOR_IZQUIERDO); 
      digitalWrite(in3, HIGH); 
      digitalWrite(in4, LOW); 
      analogWrite(enB, velocidad * COMPENSA_MOTOR_DERECHO); 
      break;
    case DIRECCION_ATRAS:
      digitalWrite(in1, LOW); 
      digitalWrite(in2, HIGH); 
      analogWrite(enA, velocidad * COMPENSA_MOTOR_IZQUIERDO); 
      digitalWrite(in3, LOW); 
      digitalWrite(in4, HIGH); 
      analogWrite(enB, velocidad * COMPENSA_MOTOR_DERECHO); 
      break;
  case DIRECCION_ROTACION_IZQUIERDA: // izquierda atrás, derecha adelante
      digitalWrite(in1, LOW); 
      digitalWrite(in2, HIGH); 
      analogWrite(enA, velocidad * COMPENSA_MOTOR_IZQUIERDO); 
      digitalWrite(in3, HIGH); 
      digitalWrite(in4, LOW); 
      analogWrite(enB, velocidad * COMPENSA_MOTOR_DERECHO); 
      break;  
  case DIRECCION_ROTACION_DERECHA:  // derecha atrás, izquierda adelante
      digitalWrite(in1, HIGH); 
      digitalWrite(in2, LOW); 
      analogWrite(enA, velocidad * COMPENSA_MOTOR_IZQUIERDO); 
      digitalWrite(in3, LOW); 
      digitalWrite(in4, HIGH); 
      analogWrite(enB, velocidad * COMPENSA_MOTOR_DERECHO); 
      break;  
  }
}

void rotarMayorDistancia() {
  int distanciaDerecha, distanciaIzquierda;

  // Parar el coche
  moverCoche(DIRECCION_PARAR, 0);
  delay(500);
  // Retrodecer un poco
  moverCoche(DIRECCION_ATRAS, 255 * POTENCIA_MOTOR);
  delay(TIEMPO_RETROCESO);
  // Parar el coche
  moverCoche(DIRECCION_PARAR, 0);
  delay(500);

  // Mirar a la derecha y obtener distancia
  anguloServo = ANGULO_DERECHA; 
  servo1.write(anguloServo); 
  delay(1000); 
  distanciaDerecha = obtenerDistanciaObstaculo();
  delay(1000); 
  Serial.print("Distancia derecha: ");
  Serial.println(distanciaDerecha);

  // Mirar a la izquierda y obtener distancia
  anguloServo = ANGULO_IZQUIERDA; 
  servo1.write(anguloServo); 
  delay(1000); 
  distanciaIzquierda = obtenerDistanciaObstaculo();
  delay(1000); 
  Serial.print("Distancia izquierda: ");
  Serial.println(distanciaIzquierda);

  anguloServo = ANGULO_CENTRO; 
  servo1.write(anguloServo); 
  delay(1000); 

  // Mover un poco hacia atrás antes de girar
//  moverCoche(DIRECCION_ATRAS, 255 * POTENCIA_MOTOR);
//  delay(300);
  // Rotar el coche hacia el lado con el obstáculo más lejano
  if(distanciaDerecha == 0 || distanciaDerecha > distanciaIzquierda) {
    moverCoche(DIRECCION_ROTACION_DERECHA, 255 * POTENCIA_MOTOR);
    delay(TIEMPO_GIRO);
  } else {
    moverCoche(DIRECCION_ROTACION_IZQUIERDA, 255 * POTENCIA_MOTOR);
    delay(TIEMPO_GIRO);
  }

  // Dejar el coche moviendo hacia adelante
  moverCoche(DIRECCION_ADELANTE, 255 * 0.5);
}

