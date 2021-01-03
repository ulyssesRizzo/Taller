
/*  Automatización para Todos
 *  www.automatizacionparatodos.com
 *  
 *  Como controlar un LED RGB
 *  
 *  EJEMPLO 02
 *  
 *  Ejemplo donde elegimos los colores para el 
 *  LED RGB mediante código.
 */
 
int pinR = 10;
int pinG = 11;
int pinB = 12;
 
void setup() {
  pinMode(pinR,OUTPUT);
  pinMode(pinG,OUTPUT);
  pinMode(pinB,OUTPUT);
}
 
void loop() {
  analogWrite(pinR, 255);
  analogWrite(pinG, 50);
  analogWrite(pinB, 0);
}
