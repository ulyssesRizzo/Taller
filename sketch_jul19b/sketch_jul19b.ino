#include <LiquidCrystal_I2C.h> //libreria de LCD con i2c
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //tamaño de lcd y dirección i2c
//variables utilizadas
int pinSensor = A0;
int valorirent = 0;
int led = 12;
int content = 0;
int content1 = 0;
int total = 0;
int buzzer = 13;
int frecuencia=250;
void setup()
{
  Serial.begin(9600); //inicializamos el monitor serial
  pinMode(pinSensor, INPUT);  //pin A0 iniciado como entrada (innecesario)
  lcd.begin(); //iniciamos el lcd
  pinMode (led, OUTPUT); //pin led salida
  pinMode(buzzer, OUTPUT); //pin buzzer salida
  lcd.setCursor(0, 0); //posicion del cursor
  lcd.print("personas: 0");

}

void loop()
{
  valorirent = digitalRead(pinSensor); //lector del sensor
  if (valorirent != 1) //condicionan si es diferente de 1
  {
    content++;
    total++;
    while (digitalRead(pinSensor) != 1) { //retraso
      delay(100);
    }
    lcd.setCursor(10, 0);
    lcd.print(content);
    lcd.setCursor(0, 1);
    lcd.println("TOTAL: ");
    lcd.setCursor(7, 1);
    lcd.print(total);
    if (content == 10) {
      tone(buzzer, frecuencia); // emite el tono
      delay(1500); // lo mantiene 1.5 segundos
      noTone(buzzer); // para el tono
      delay(500); // espera medio segundo
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.println(" LLENO   ");
      digitalWrite(led, 1);
      delay (2000);
      content = 0;
      lcd.clear();
      digitalWrite(led, 0);
      lcd.setCursor(0, 0);
      lcd.print("Personas: 0");
      lcd.setCursor(0, 1);
      lcd.print("TOTAL: ");
      lcd.setCursor(7, 1);
      lcd.print(total);

    }
  }
}
