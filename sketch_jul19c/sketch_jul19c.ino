#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522

#define RST_PIN  9      // constante para referenciar pin de reset
#define SS_PIN  10      // constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset

byte LecturaUID[4];         // crea array para almacenar el UID leido
byte tarjeta[4] = {0xE6, 0xB7, 0x4E, 0x1A} ;   // UID de tarjeta
byte llavero[4] = {0x06, 0x76, 0x25, 0xD9} ;   // UID de llavero diferente al que tengo

int ledrojo = 8;
int ledverde = 7;
int ledazul = 4;

int trig = 6;
int echo = 5;
long sensor;
long distancia;
//luces de abierto/cerrado horario normal
int horasON = 6;
int minutosON = 00;
int horasOFF = 18;
int minutosOFF = 00;
//luces de abierto/cerrado para prueba
int horasON1 = 21;
int minutosON1 = 35;
int horasOFF1 = 21;
int minutosOFF1 = 36;

int buzzer = 3;
int frecuencia = 200;
int frecuencia2 = 800;

void setup () {

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);

  pinMode (ledrojo, OUTPUT);
  pinMode (ledverde, OUTPUT);
  pinMode (ledazul, OUTPUT);

  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicaci¢n con el RTC
  RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  //el anterior se usa solo en la configuracion inicial
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);      // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();     // inicializa modulo lector

}
void loop() {
  DateTime now = RTC.now();
  reloj ();
  lector();
  ultrasonico();
  ledstiempo ();

  Serial.println(alarma(now));
}

void reloj () {
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

  Serial.print(now.year(), DEC); // A§o
  Serial.print('/');
  Serial.print(now.month(), DEC); // Mes
  Serial.print('/');
  Serial.print(now.day(), DEC); // Dia
  Serial.print(' ');
  Serial.print(now.hour(), DEC); // Horas
  Serial.print(':');

  Serial.print(now.minute(), DEC); // Minutos
  Serial.print(':');
  Serial.print(now.second(), DEC); // Segundos
  Serial.println();
  lcd.setCursor(0, 0);
  lcd.print("D:");
  lcd.print(now.year(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.day(), DEC);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);
  delay(1000); // La informaci¢n se actualiza cada 1 seg.
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("               ");
}

void lector () {
  if ( ! mfrc522.PICC_IsNewCardPresent())    // si no hay una tarjeta presente
    return;           // retorna al loop esperando por una tarjeta

  if ( ! mfrc522.PICC_ReadCardSerial())     // si no puede obtener datos de la tarjeta
    return;           // retorna al loop esperando por otra tarjeta

  Serial.print("UID:");       // muestra texto UID:
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (mfrc522.uid.uidByte[i] < 0x10) {  // si el byte leido es menor a 0x10
      Serial.print(" 0");       // imprime espacio en blanco y numero cero
    }
    else {          // sino
      Serial.print(" ");        // imprime un espacio en blanco
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);    // imprime el byte del UID leido en hexadecimal
    LecturaUID[i] = mfrc522.uid.uidByte[i];   // almacena en array el byte del UID leido
  }

  Serial.print("\t");         // imprime un espacio de tabulacion

  if (comparaUID(LecturaUID, tarjeta)) {  // llama a funcion comparaUID con Usuario1
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acceso"); // si retorna verdadero muestra texto bienvenida
    lcd.setCursor(0, 1);
    lcd.print("Autorizado"); // si retorna verdadero muestra texto bienvenida
    delay(1000);
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, HIGH);
    delay(1000);
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, LOW);
    tone(buzzer, frecuencia2); // emite el tono
    delay(500); // lo mantiene 1/2 segundos
    noTone(buzzer); // para el tono
    delay(500); // espera medio segundo
    tone(buzzer, frecuencia2); // emite el tono
    delay(500); // lo mantiene 1/2 segundos
    noTone(buzzer); // para el tono
    delay(500); // espera medio segundo


  }
  else if (comparaUID(LecturaUID, llavero)) { // llama a funcion comparaUID con Usuario2
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bienvenido"); // si retorna verdadero muestra texto bienvenida
    delay(1000);
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, HIGH);
    delay(1000);
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, LOW);
  }
  else { // si retorna falso
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Accseso");    // muestra texto equivalente a acceso denegado
    lcd.setCursor(0, 1);
    lcd.print("Denegado");    // muestra texto equivalente a acceso denegado
    delay(1000);
    digitalWrite(ledrojo, HIGH);
    digitalWrite(ledverde, LOW);
    delay(1000);
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, LOW);
    tone(buzzer, frecuencia); // emite el tono
    delay(500); // lo mantiene 1/2 segundos
    noTone(buzzer); // para el tono
    delay(500); // espera medio segundo

    mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta
  }
}
boolean comparaUID(byte lectura[], byte usuario[]) // funcion comparaUID
{
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (lectura[i] != usuario[i])       // si byte de UID leido es distinto a usuario
      return (false);         // retorna falso
  }
  return (true);          // si los 4 bytes coinciden retorna verdadero

}

void ultrasonico () {
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  sensor = pulseIn(5, HIGH);
  distancia = sensor / 59;
  delay(1000);

  if (distancia < 4) {
    digitalWrite(ledazul, HIGH);
    delay(1000);
    digitalWrite(ledazul, LOW);
    delay(1000);
  }
}
bool alarma (DateTime date) {
  int dia = date.dayOfTheWeek();
  int hora = date.hour();
  int minuto = date.minute();

  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);

  bool CondicionH = (hora >= horasON1 && minuto >= minutosON1 && hora <= horasOFF1 && minuto <= minutosOFF1);
  if (CondicionH) {
    return true;
  }
  return false;
}

void ledstiempo () {
  DateTime now = RTC.now();
  if (alarma(now)) {
    digitalWrite (ledverde, HIGH);
    digitalWrite (ledrojo, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Abierto");
    delay(800);
    
    alarma(now);
  }
  else {
    digitalWrite (ledrojo, HIGH);
    digitalWrite (ledverde, LOW);
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cerrado");
    delay(800);
    
  }
}
