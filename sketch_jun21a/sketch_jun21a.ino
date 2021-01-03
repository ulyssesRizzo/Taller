#include <Adafruit_NeoPixel.h>
//Designamos nuestro pin de datos
#define PIN 6
//Designamos cuantos pixeles tenemos en nuestra cinta led RGB
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Inicializamos nuestra cinta led RGB
  pixels.begin();
}
void loop() {
  //Definimos nuestras variables de tipo uint32 para cada color que utilizaremos
  // pixels.Color toma valores en RGB, desde 0,0,0 hasta 255,255,255
  uint32_t rojo = pixels.Color(150, 0, 0);
  uint32_t verde = pixels.Color(0, 150, 0);
  uint32_t azul = pixels.Color(0, 0, 150);
  int delayval = 50;

  //Variamos los colores de cada led en nuestra cinta RGB cada medio segundo
  uint32_t amarillo = pixels.Color(150, 150, 0);
  uint32_t morado = pixels.Color(150, 0, 150);
  uint32_t celeste = pixels.Color(0, 150, 150);
  uint32_t blanco = pixels.Color(150, 150, 150);
  uint32_t cafe = pixels.Color(78, 59, 49);
  uint32_t negro = pixels.Color(0,0,0);
  uint32_t anaranjado = pixels.Color(78, 59, 49);
  delayval = 500;
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(0, cafe);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(1, anaranjado);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(2, amarillo);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(3, negro);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(4, blanco);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(5, cafe);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(6, anaranjado);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(7, amarillo);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(8, negro);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(9, blanco);
    pixels.show();
    delay(delayval);
  }
}
