// Pin de sensores seguidores de líneas
int pinAnalogLineTrackingRight = 1;
int pinAnalogLineTrackingLeft = 0;


/* 
 *  
 *  SETUP
 *  
 */
void setup() { 
  Serial.begin(9600);
  Serial.println("Sensores seguidores de linea: ");
  } 

/* 
 *  
 *  LOOP
 *  
 */
void loop() { 
  Serial.print("   Sensor derecho: (");
  int onLineRight = analogRead(pinAnalogLineTrackingRight);  
  Serial.println(onLineRight);
  delay(500);
  
  Serial.println();

  Serial.print("   Sensor izquierdo: (");
  int onLineLeft = analogRead(pinAnalogLineTrackingLeft);  
  Serial.println(onLineLeft);
  delay(500);
}
