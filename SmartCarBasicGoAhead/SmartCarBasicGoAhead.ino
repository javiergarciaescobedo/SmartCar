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
 
void setup() { 
  // Establecer el modo de salida para todos los pines utilizados 
  //  para la conexión de los motores 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT); 
} 
 
void loop() { 
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
} 
