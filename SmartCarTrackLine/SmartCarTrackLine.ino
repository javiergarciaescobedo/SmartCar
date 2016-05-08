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
    turnRight = false;
    lastTurnChangeRight = false;
  }
  if(onLineRight == 1 && onLineLeft == 0) { 
    // Fuera de línea por la izquierda. Girar a izquierda
    turnRight = true;
    lastTurnChangeRight = true;
  }
  if(onLineRight == 0 && onLineLeft == 0) { 
    // Fuera de línea por los dos lados
    turnRight = !lastTurnChangeRight;
  }
  if(onLineRight == 1 && onLineLeft == 1) { 
    // En línea por los dos lados
    turnRight = !lastTurnChangeRight;
  }

  if(turnRight) {
    speedRight = 0;
    speedLeft = 255;
  } else {
    speedRight = 255;
    speedLeft = 0;
  }

  analogWrite(enA, speedRight); 
  analogWrite(enB, speedLeft);
}
