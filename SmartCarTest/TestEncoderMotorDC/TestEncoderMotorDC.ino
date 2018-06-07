
// MOTOR 1 (Derecho)
// Pines de conexión en la tarjeta Arduino. Los pines de conexión 
//  unidos a enA y enB de la tarjeta L298N, deben ser PWM (~) 
int enA = 5; // Pin enA de la tarjeta controladora L298N 
int in1 = 6;  // Pin in1 "  "  "       "            " 
int in2 = 7;  // Pin in2 "  "  "       "            " 
// MOTOR 2 (Izquierdo)
int in3 = 12; // Pin in3 de la tarjeta controladora L298N 
int in4 = 13; // Pin in4 "  "  "       "            " 
int enB = 11; // Pin enB "  "  "       "            " 

// Pin encoder motores DC
int pinEncoderMotorDer = 2;   
int pinEncoderMotorIzq = 3;   

unsigned long rpmDer = 0;           // Revoluciones por minuto calculadas.
unsigned long rpmIzq = 0;           // Revoluciones por minuto calculadas.
float velocityDer = 0;                 //Velocidad en [Km/h]
float velocityIzq = 0;                 //Velocidad en [Km/h]
volatile byte pulsesDer = 0;       // Número de pulsos leidos por el Arduino en un segundo
volatile byte pulsesIzq = 0;       // Número de pulsos leidos por el Arduino en un segundo
unsigned long timeoldDer = 0;  // Tiempo 
unsigned long timeoldIzq = 0;  // Tiempo 
static volatile unsigned long debounceDer = 0; // Tiempo del rebote.
static volatile unsigned long debounceIzq = 0; // Tiempo del rebote.

unsigned int pulsesperturn = 20; // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 65;   // Diámetro de la rueda pequeña[mm]

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

  attachInterrupt(digitalPinToInterrupt(pinEncoderMotorDer), contadorPulsosMotorDerecho, RISING); 
  attachInterrupt(digitalPinToInterrupt(pinEncoderMotorIzq), contadorPulsosMotorIzquierdo, RISING); 

  pulsesDer = 0;
  rpmDer = 0;
  timeoldDer = 0;
  pulsesIzq = 0;
  rpmIzq = 0;
  timeoldIzq = 0;
  
  Serial.print("Seconds ");
  Serial.print("RPM ");
  Serial.print("Pulses ");
  Serial.println("Velocity[Km/h]");
} 

/* 
 *  
 *  LOOP
 *  
 */
void loop() { 
  Serial.println("Motor derechio: ");
  
  Serial.println("  Adelante vel.255: ");
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  analogWrite(enA, 255); 

  for(int i=0; i<5; i++) {
    mostrarVelocidadDerecha();
    delay(1000);
  }
  
  Serial.println("  Adelante vel.150: ");
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  analogWrite(enA, 150); 

  for(int i=0; i<5; i++) {
    mostrarVelocidadDerecha();
    delay(1000);
  }
   
  Serial.println("Motor izquierdo: ");
  
  Serial.println("  Adelante vel.255: ");
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enB , 255); 

  for(int i=0; i<5; i++) {
    mostrarVelocidadIzquierda();
    delay(1000);
  }
  
  Serial.println("  Adelante vel.150: ");
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enB, 150); 

  for(int i=0; i<5; i++) {
    mostrarVelocidadIzquierda();
    delay(1000);
  }

}

void mostrarVelocidadDerecha() {
  if (millis() - timeoldDer >= 1000){  // Se actualiza cada segundo
      noInterrupts(); //Don't process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
      rpmDer = (60L * 1000 / pulsesperturn )/ (millis() - timeoldDer)* pulsesDer; // Calculamos las revoluciones por minuto
      velocityDer = rpmDer * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h] 
      timeoldDer = millis(); // Almacenamos el tiempo actual.
      Serial.print(millis()/1000); Serial.print("       ");// Se envia al puerto serie el valor de tiempo, de las rpm y los pulsos.
      Serial.print(rpmDer,DEC); Serial.print("   ");
      Serial.print(pulsesDer,DEC); Serial.print("     ");
      Serial.println(velocityDer, 2); 
      pulsesDer = 0;  // Inicializamos los pulsos.
      interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
   }
}

void mostrarVelocidadIzquierda() {
  if (millis() - timeoldIzq >= 1000){  // Se actualiza cada segundo
      noInterrupts(); //Don't process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
      rpmIzq = (60L * 1000 / pulsesperturn )/ (millis() - timeoldIzq)* pulsesIzq; // Calculamos las revoluciones por minuto
      velocityIzq = rpmIzq * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h] 
      timeoldIzq = millis(); // Almacenamos el tiempo actual.
      Serial.print(millis()/1000); Serial.print("       ");// Se envia al puerto serie el valor de tiempo, de las rpm y los pulsos.
      Serial.print(rpmIzq,DEC); Serial.print("   ");
      Serial.print(pulsesIzq,DEC); Serial.print("     ");
      Serial.println(velocityIzq,2); 
      pulsesIzq = 0;  // Inicializamos los pulsos.
      interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
   }
}

void contadorPulsosMotorDerecho(){
  // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
  if( digitalRead (pinEncoderMotorDer) && (micros()-debounceDer > 500) && digitalRead (pinEncoderMotorDer) ) { 
    debounceDer = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
    pulsesDer++;  // Suma el pulso bueno que entra.
  } 
}

void contadorPulsosMotorIzquierdo(){
  // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
  if( digitalRead (pinEncoderMotorIzq) && (micros()-debounceIzq > 500) && digitalRead (pinEncoderMotorIzq) ) { 
    debounceIzq = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
    pulsesIzq++;  // Suma el pulso bueno que entra.
  } 
}
