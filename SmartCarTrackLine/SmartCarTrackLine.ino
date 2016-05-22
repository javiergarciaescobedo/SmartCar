int pinLineTrackingRight = 3;
int pinLineTrackingLeft = 2;

// MOTOR 1 
// Pines de conexión en la tarjeta Arduino. Los pines de conexión 
//  unidos a enA y enB de la tarjeta L298N, deben ser PWM (~) 
int enA = 5;  // Pin enA de la tarjeta controladora L298N 
int in1 = 8;  // Pin in1 "  "  "       "            " 
int in2 = 9;  // Pin in2 "  "  "       "            " 
// MOTOR 2 
// Pines de conexión en la tarjeta Arduino  
int in3 = 12; // Pin in3 de la tarjeta controladora L298N 
int in4 = 13; // Pin in4 "  "  "       "            " 
int enB = 11; // Pin enB "  "  "       "            " 

boolean turnRight = true;
boolean lastTurnChangeRight = true;
int speedRight, speedLeft;

const int PARADO = 0;
const int MARCHA_FRENTE = 1;
const int GIRO_DERECHA = 2;
const int GIRO_IZQUIERDA = 3;
const int DERRAPE_DERECHA = 4;
const int DERRAPE_IZQUIERDA = 5;
int modoGiro = MARCHA_FRENTE;
boolean ultimoEnLineaEsDerecha = true;
boolean estaFueraLinea = false;

void setup() {
  pinMode(pinLineTrackingRight, INPUT); 
  pinMode(pinLineTrackingLeft, INPUT);
   
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT);  

  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);  
}

void loop() {
  int onLineRight = digitalRead(pinLineTrackingRight);  
  int onLineLeft = digitalRead(pinLineTrackingLeft);  
    
  if(onLineRight == 0 && onLineLeft == 1) { 
    // Fuera de línea por la derecha. Girar a izquierda
    modoGiro = GIRO_IZQUIERDA;
    ultimoEnLineaEsDerecha = false;
    estaFueraLinea = false;
  } else if(onLineRight == 1 && onLineLeft == 0) { 
    // Fuera de línea por la izquierda. Girar a derecha
    modoGiro = GIRO_DERECHA;
    ultimoEnLineaEsDerecha = true;
    estaFueraLinea = false;
  } else if(onLineRight == 0 && onLineLeft == 0) { 
    // Fuera de línea por los dos lados
    if(ultimoEnLineaEsDerecha) {
      modoGiro = GIRO_DERECHA;
    } else {
      modoGiro = GIRO_IZQUIERDA;
    }
    estaFueraLinea = true;
  } else if(onLineRight == 1 && onLineLeft == 1) { 
    // En línea por los dos lados
    if(estaFueraLinea) {
      switch(modoGiro) {
        case GIRO_DERECHA:
          modoGiro = GIRO_IZQUIERDA;
          break;
        case GIRO_IZQUIERDA:
          modoGiro = GIRO_DERECHA;
          break;
      }
    } else {
      modoGiro = GIRO_DERECHA;
    }
    estaFueraLinea = false;
  }

  switch(modoGiro) {
    case GIRO_DERECHA:
      speedRight = 0;
      speedLeft = 150;
      break;
    case GIRO_IZQUIERDA:
      speedRight = 150;
      speedLeft = 0;
      break;
  }

  analogWrite(enA, speedRight); 
  analogWrite(enB, speedLeft);
}
