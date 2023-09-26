// CORRECÕES: -ajustar configuraçoes dos angulos;
//            -verificar qual o eixo da movimentação vertical do giroscopio;
//            -verificar necessidades de atualizações constantes do uso do map e das leituras dos sensores.


#include <MPU6050_tockn.h>
#include <Wire.h>
// necessidade de incluir uma library para o ultrasonic

#define pulseiraE 9
#define pulseiraD 11
#define ledAux 7 // ao piscar mostra que o giroscopio está calibrado

#define MPU6050_ADDR         0x68 
#define DEBUG

MPU6050 mpu6050(Wire);

int triggerPin1 = 5; // sensor 1
int echoPin1 = 4;  // sensor 1
int triggerPin2 = 2;  // sensor 2
int echoPin2 = 3; // sensor 2
int triggerPin3 = 7;  // sensor 3
int echoPin3 = 6; // sensor 3
float cm1 = 0;    // centimetro sensor 1
float cm2 = 0;   // centimetro sensot 2
float cm3 = 0;  // centimetro sensor 3 
float mediaSensor; // media das distancias de todos os sensores
int xI= 0;      // intensidade no atuadores, com base na media 
float anguloX; // angulo em graus eixo x
float anguloY; // angulo em graus eixo y
float anguloZ; // angulo em graus eixo z

long dista1(int SomPin, int echoPin){
  pinMode(triggerPin1, OUTPUT); 
  digitalWrite(triggerPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin1, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
long dista2(int SomPin, int echoPin){
  pinMode(triggerPin2, OUTPUT);
  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
long dista3(int SomPin, int echoPin){
  pinMode(triggerPin3, OUTPUT);
  digitalWrite(triggerPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin3, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void imprimir(){
   Serial.print("SENSOR 1: ");
   Serial.print(cm1);
   Serial.println("cm");
   
   Serial.print("SENSOR 2: ");
   Serial.print(cm2);
   Serial.println("cm");

   Serial.print("SENSOR 3: ");
   Serial.print(cm3);
   Serial.println("cm");

  Serial.print("Média sensores: ");
  Serial.print(mediaSensor);
  Serial.println("cm");

  Serial.println("---------------------------------------------");
   
 }

void setup() {
 
  Serial.begin(9600);
  pinMode(pulseiraE,OUTPUT);
  pinMode(pulseiraD,OUTPUT);
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  digitalWrite(ledAux,HIGH);
  delay(500);
  digitalWrite(ledAux,LOW);

  #ifdef DEBUG
    Serial.println("Fim Setup");
  #endif 

}

void loop() {

  mpu6050.update();

  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  anguloZ = mpu6050.getAngleZ();

  cm1 = 0.01723 * dista1(triggerPin1, echoPin1);

  
  cm2 = 0.01723 * dista2(triggerPin2, echoPin2);
    
  
  cm3 = 0.01723 * dista3(triggerPin3, echoPin3);

  
  mediaSensor= (cm1+cm2+cm3)/3.0;

  
  //imprimir();
  
 

if (mediaSensor >= 3 && mediaSensor <=100)
{ 
  xI = map(mediaSensor,3,100,255,0); // 255 = 5v ; 0 = 0v 
  
  // OBJETOS A FRENTE / GIROSCOPIO EM TORNO DE 90 GRAUS

  if (anguloX >= 60 && anguloX <=120 && mediaSensor <= 100 && mediaSensor >= 80) 
  {
     analogWrite(pulseiraE,xI);
     analogWrite(pulseiraD,xI);

  }
  else if (anguloX >= 60 && anguloX <= 120 && mediaSensor < 80 && mediaSensor > 40)
  {
    analogWrite(pulseiraE,xI);
    analogWrite(pulseiraD,xI);

  }
  else if (anguloX >= 60 && anguloX <= 120 && mediaSensor <= 40)
  {
    analogWrite(pulseiraE,xI);
    analogWrite(pulseiraD,xI);

  }

  // OBJETOS A LATERAL ESQUERDA / GIROSCOPIO EM TORNO DE 150 GRAUS

  xI = map(mediaSensor,3,100,255,0);

  if (anguloX > 120 && anguloX <= 180 && mediaSensor <= 100 && mediaSensor >= 80) 
  {
    analogWrite(pulseiraE,xI);

  }
  else if (anguloX > 120 && anguloX <= 180 && mediaSensor < 80 && mediaSensor > 40)
  {
    analogWrite(pulseiraE,xI);

  }
  else if (anguloX > 120 && anguloX <= 180 && mediaSensor <= 40)
  {
    analogWrite(pulseiraE,xI);

  }

  // OBJETOS A LATERAL DIREITA / GIROSCOPIO EM TORNO DE 30 GRAUS

   xI = map(mediaSensor,3,100,255,0);

   if (anguloX < 60 && anguloX >= 0 && mediaSensor <= 100 && mediaSensor >= 80) 
  {
    analogWrite(pulseiraD,xI);
    
  }
  else if (anguloX <60 && anguloX >= 0 && mediaSensor < 80 && mediaSensor > 40)
  {
    analogWrite(pulseiraD,xI);

  }
  else if (anguloX < 60 && anguloX >= 0 && mediaSensor <= 40)
  {
    analogWrite(pulseiraD,xI);

  }

}
else {

  analogWrite(pulseiraD,0);
  analogWrite(pulseiraE,0);

}

}
