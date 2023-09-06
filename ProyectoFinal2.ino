#include <Servo.h>
const int sluz1 = A0;
const int sluz2 = A1;
const int LEDluz1= 2;
const int LEDluz2= 12;
int umbralNumber=800;
int valorLDR=0;
int valorLDR2=0;

const int stemp1 = A2;
const int stemp2 = A3;
const int stemp3 = A4;
const int stemp4 = A5;

const int PT1 = 3;
const int PE1 = 5;

const int PT2 = 6;
const int PE2 = 9;

Servo servo1;
Servo servo2;
int anguloInicial = 90;
int anguloInicial2 = 270;

void setup() {
  Serial.begin(9600);

  pinMode(PT1, OUTPUT);
  pinMode(PE1, INPUT);
  digitalWrite(PT1, LOW);

  pinMode(PT2, OUTPUT);
  pinMode(PE2, INPUT);
  digitalWrite(PT2, LOW);

  pinMode(LEDluz1, OUTPUT); 
  pinMode(LEDluz2, OUTPUT); 

  servo1.attach(10);
  servo1.write(anguloInicial);
  servo2.attach(11);
  servo2.write(anguloInicial);
}

void loop() {
  unsigned long t;
  float d;
  digitalWrite(PT1, HIGH);
  delayMicroseconds(10000);
  digitalWrite(PT1, LOW);
  t = pulseIn(PE1, HIGH);   
  d = t * 0.000001 * 34300.0 / 2.0;
  Serial.print("Distancia4:");
  Serial.println(d);
  delay(1000);

  unsigned long t1;
  float d1;
  digitalWrite(PT2, HIGH);
  delayMicroseconds(10000);
  digitalWrite(PT2, LOW);
  t1 = pulseIn(PE2, HIGH);   
  d1 = t1 * 0.000001 * 34300.0 / 2.0;
  Serial.print("Distancia5:");
  Serial.println(d1);
  delay(1000);


  valorLDR=analogRead(sluz1);
  valorLDR2=analogRead(sluz2);
  Serial.print("luz1:");
  Serial.println(valorLDR);
  Serial.print("luz2:");
  Serial.println(valorLDR2);
  if (valorLDR >= umbralNumber){ //Si primer led supera el umbral
    digitalWrite(LEDluz1, HIGH);
    digitalWrite(LEDluz2, HIGH);
  }
  else{
    digitalWrite(LEDluz1, LOW);
    digitalWrite(LEDluz2, LOW);
  }


  if (Serial.available() > 0) {  // Comprobamos si hay datos disponibles en el puerto serial
    int dato = Serial.parseInt();  // Leemos el dato enviado desde Python

    if (dato == 80) {
      int nuevoAngulo = anguloInicial + 90;  // Calcular el nuevo ángulo
      servo1.write(nuevoAngulo);  // Girar el servomotor al nuevo ángulo
      delay(2000);  // Esperar 4 segundo
      servo1.write(anguloInicial);  // Volver al ángulo inicial
    }
    if (dato == 90) {
      int nuevoAngulo2 = anguloInicial - 90;  // Calcular el nuevo ángulo
      servo2.write(nuevoAngulo2);  // Girar el servomotor al nuevo ángulo
      delay(2000);  // Esperar 4 segundo
      servo2.write(anguloInicial);  // Volver al ángulo inicial
    }
}
delay(5000);
}