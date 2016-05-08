/* Este programa fue publicado por Transductor en su
 * tutorial de Arduino y Bluetooth :
 *
 * http://robologs.net/2015/05/15/tutorial-de-bluetooth-con-arduino-hc-06-en-linux/
 */

// RXD -> Pin 1 (TX Arduino)
// TXD -> Pin 0 (RX Arduino)
 
char nombre[10] = "ArduinoR"; //El nuevo nombre del modulo
char password[10] = "0000"; //El nuevo password. Seh, no es muy seguro...
char baud = '4'; //4 = 9600 baud
  
void setup()
{
  Serial.begin(9600);
   
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(15000); //Esperar 15 segundos para conectar el modulo
   
  Serial.print("AT"); //Iniciar la configuracion
  delay(1000);
   
  Serial.print("AT+NAME"); 
  Serial.print(nombre); //Cambiar el nombre
  delay(1000);
   
  Serial.print("AT+PIN"); 
  Serial.print(password); //Cambiar contrasena
  delay(1000);   
   
  Serial.print("AT+BAUD"); 
  Serial.print(baud); //Cambiar baudios
  delay(1000);
   
  digitalWrite(13, HIGH);
}
  
void loop(){
}
