#include <infrarrojo.h>

const int rojo = 6;
const int amarillo = 5;
const int verde = 4;
 
void setup() {
  Serial.begin(9600);    //iniciar puerto serie
  pinMode(rojo , OUTPUT);  //definir pin como salidaç
  pinMode(amarillo , OUTPUT);  //definir pin como salida
  pinMode(verde , OUTPUT);  //definir pin como salida
}
 
void loop(){
  digitalWrite(rojo , HIGH);   // poner el Pin en HIGH
  delay(1000);                   // esperar un segundo
  digitalWrite(rojo , LOW);    // poner el Pin en LOW
  delay(1000); 
  digitalWrite(amarillo , HIGH);
  delay(1000);                   // esperar un segundo
  digitalWrite(amarillo , LOW);
  delay(1000);  
  digitalWrite(amarillo , HIGH);
  delay(1000);  
  digitalWrite(amarillo , LOW);
  delay(1000);  
  digitalWrite(amarillo , HIGH);
  delay(1000);  
  digitalWrite(amarillo , LOW);
  delay(1000); 
  digitalWrite(verde , HIGH);   // poner el Pin en HIGH
  delay(1000);                   // esperar un segundo
  digitalWrite(verde , LOW);
  delay(1000);
  digitalWrite(verde , HIGH);
  digitalWrite(amarillo , HIGH);
  digitalWrite(rojo , HIGH);
  delay(5000);
  digitalWrite(verde , LOW);
  digitalWrite(amarillo , LOW);
  digitalWrite(rojo , LOW);
}