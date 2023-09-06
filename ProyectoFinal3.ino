#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int sensorAgua0 = A0;
const int sensorAgua1 = A1;
const int sensorTierra1 = A2;
const int sensorTierra2 = A3;
const int sensorTierra3 = A4;
const int sensorTierra4 = A5;


const int control = 7 ;
const int control2 = 6 ;

void setup() {
  Serial.begin(9600);
  pinMode(control, OUTPUT);
  pinMode(control2, OUTPUT);
  dht.begin();
}

void loop() 
{
  digitalWrite(control, HIGH);
  digitalWrite(control2, HIGH);
  int nivel = analogRead(sensorAgua0);
  int nivel2 = analogRead(sensorAgua1);
  Serial.print("n1:");
  Serial.println(nivel);
  Serial.print("n2:");
  Serial.println(nivel2);

  int humedad1 = analogRead(sensorTierra1);
  int humedad2 = analogRead(sensorTierra2);
  int humedad3 = analogRead(sensorTierra3);
  int humedad4 = analogRead(sensorTierra4);
  Serial.print("h1:");
  Serial.println(humedad1);
  Serial.print("h2:");
  Serial.println(humedad2);
  Serial.print("h3:");
  Serial.println(humedad3);
  Serial.print("h4:");
  Serial.println(humedad4);

  if (Serial.available() > 0) {  
    int dato = Serial.parseInt();  

    if (dato == 10) {
      digitalWrite(control, LOW);
      delay(3000);
      digitalWrite(control, HIGH);
      delay(4000);      
    } 
    if (dato == 20) {
      digitalWrite(control2, LOW);
    } 
    if (dato == 30) {
      digitalWrite(control2, HIGH);  
    } 
  }
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    delay(10000);
    return;
  }
 
  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  delay(10000);

}