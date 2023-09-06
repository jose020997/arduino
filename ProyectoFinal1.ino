const int PT1 = 10;
const int PE1 = 11;

const int PT2 = 3;
const int PE2 = 5;

const int PT3 = 6;
const int PE3 = 9;

const int ledVerde = 7;
const int ledRojo = 4;

void setup() {
  Serial.begin(9600);

  pinMode(PT1, OUTPUT);
  pinMode(PE1, INPUT);
  digitalWrite(PT1, LOW);

  pinMode(PT2, OUTPUT);
  pinMode(PE2, INPUT);
  digitalWrite(PT2, LOW);

  pinMode(PT3, OUTPUT);
  pinMode(PE3, INPUT);
  digitalWrite(PT3, LOW);

  pinMode(ledVerde, OUTPUT); 
  pinMode(ledRojo, OUTPUT); 
}

void loop() {
  unsigned long t;
  float d;
  digitalWrite(PT1, HIGH);
  delayMicroseconds(10000);
  digitalWrite(PT1, LOW);
  t = pulseIn(PE1, HIGH);   
  d = t * 0.000001 * 34300.0 / 2.0;
  Serial.print("Distancia1:");
  Serial.println(d);
  delay(1000);

  unsigned long t1;
  float d1;
  digitalWrite(PT2, HIGH);
  delayMicroseconds(10000);
  digitalWrite(PT2, LOW);
  t1 = pulseIn(PE2, HIGH);   
  d1 = t1 * 0.000001 * 34300.0 / 2.0;
  Serial.print("Distancia2:");
  Serial.println(d1);
  delay(1000);

  unsigned long t2;
  float d2;
  digitalWrite(PT3, HIGH);
  delayMicroseconds(10000);
  digitalWrite(PT3, LOW);
  t2 = pulseIn(PE3, HIGH);   
  d2 = t2 * 0.000001 * 34300.0 / 2.0;
  Serial.print("Distancia3:");
  Serial.println(d2);
  Serial.println("Sobra");
  delay(1000);

   if (Serial.available() > 0) {  
    int dato = Serial.parseInt();  

    if (dato == 10) {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledRojo, LOW);
    } 
    else if (dato == 20) {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);
    }
   }
}
