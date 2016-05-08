int enA = 5; // Pin enA de la tarjeta controladora L298N 
int in1 = 8;  // Pin in1 "  "  "       "            " 
int in2 = 9;  // Pin in2 "  "  "       "            " 
// MOTOR 2 
// Pines de conexión en la tarjeta Arduino  
int in3 = 12; // Pin in3 de la tarjeta controladora L298N 
int in4 = 13; // Pin in4 "  "  "       "            " 
int enB = 11; // Pin enB "  "  "       "            " 

void setup()
{
  Serial.begin(9600); //Iniciar el serial

  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT); 

  analogWrite(enA, 0); 
  analogWrite(enB, 0); 
}
 
void loop()
{
  if(Serial.available()>=1) {
    char entrada = Serial.read(); //Leer un caracter
 
    if(entrada == 'w' or entrada == 'W') {
        digitalWrite(in1, LOW); 
        digitalWrite(in2, HIGH); 
        analogWrite(enA, 255); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, LOW); 
        analogWrite(enB, 255); 
    } else if(entrada == 's' or entrada == 'S') {
        digitalWrite(in1, HIGH); 
        digitalWrite(in2, LOW); 
        analogWrite(enA, 255); 
        digitalWrite(in3, LOW); 
        digitalWrite(in4, HIGH); 
        analogWrite(enB, 255); 
    } else if(entrada == 'x' or entrada == 'X') {
        digitalWrite(in1, LOW); 
        digitalWrite(in2, HIGH); 
        analogWrite(enA, 0); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, LOW); 
        analogWrite(enB, 0); 
    } 
  }
}
