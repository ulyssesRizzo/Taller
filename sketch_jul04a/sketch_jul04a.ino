int LEDVermelho=3;
int LEDVerde=5;
int LEDAzul=6;

void setup() 
{
  // Inicializa os entradas digitais como saídas
  pinMode(LEDVermelho,OUTPUT);
  pinMode(LEDVerde,OUTPUT);
  pinMode(LEDAzul,OUTPUT);
}

void loop() 
{
  //Rotina é executada
  digitalWrite(LEDVermelho, HIGH); //vermelho
  digitalWrite(LEDVerde, LOW);
  digitalWrite(LEDAzul, LOW);
  
  delay(3000);

  digitalWrite(LEDVermelho, LOW); //verde
  digitalWrite(LEDVerde, HIGH);
  digitalWrite(LEDAzul, LOW);

  delay(1000);

  digitalWrite(LEDVermelho, LOW); //Azul
  digitalWrite(LEDVerde, LOW);
  digitalWrite(LEDAzul, HIGH);

  delay(1000);

  digitalWrite(LEDVermelho, HIGH); //Amarelo
  digitalWrite(LEDVerde, HIGH);
  digitalWrite(LEDAzul, LOW);

  delay(1000);

  analogWrite(LEDVermelho, 255); //Roxo
  analogWrite(LEDVerde, 0);
  analogWrite(LEDAzul, 207);

  delay(1000);

  digitalWrite(LEDVermelho, HIGH); //Branco
  digitalWrite(LEDVerde, HIGH);
  digitalWrite(LEDAzul, HIGH);
  delay(5000);
}
