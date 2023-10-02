// CORRECÕES: -ajustar configuraçoes dos angulos;
//            -verificar qual o eixo da movimentação vertical do giroscopio;
//            -verificar necessidades de atualizações constantes do uso do map e das leituras dos sensores.


#include <MPU6050_tockn.h>
#include <Wire.h>
// necessidade de incluir uma library para o ultrasonic

#define pulseiraE 9
#define pulseiraD 11
#define ledAux 13 // ao piscar mostra que o arduino está funionando

#define MPU6050_ADDR 0x68 // no arduino uno, ligar o pino A4(arduin) ao pino SDA do MPU e o A5(arduino) no SCL do MPU 
                          // o pino AD0 do MPU deve ficar ligado no GND para o endereço 0x68 
#define DEBUG


const float calDist = 0.01723; // calibração de distância

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

long dista(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
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

  Serial.print("angulo: ");
  Serial.print(anguloX );
  Serial.println("cm");

  Serial.println("---------------------------------------------");
   
 }

 void vibra(){
  analogWrite(pulseiraD,255);
  analogWrite(pulseiraE,255);
  delay(200);
  analogWrite(pulseiraD,0);
  analogWrite(pulseiraE,0);
  delay(200);

 }

void setup() {
 
  Serial.begin(9600);
  pinMode(pulseiraE,OUTPUT);
  pinMode(pulseiraD,OUTPUT);

  vibra();
  vibra();
  vibra();
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);  // colocar o giroscopio  em uma superficie plana para calibrar

  #ifdef DEBUG
    Serial.println("Fim Setup");
  #endif 

}

void loop() {


  mpu6050.update();

  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  anguloZ = mpu6050.getAngleZ();

  cm1 = calDist * dista(triggerPin1, echoPin1);

  cm2 = calDist * dista(triggerPin2, echoPin2);
    
  cm3 = calDist * dista(triggerPin3, echoPin3);
  
  mediaSensor= (cm1+cm2+cm3)/3.0;

  
 // imprimir();
  

  Serial.print("anguloY: ");
  Serial.print(anguloY );
  Serial.println("cm");

if (mediaSensor >= 3 && mediaSensor <=100)
{ 
  xI = map(mediaSensor,3,100,255,0); // 255 = 5v ; 0 = 0v 
  
  // OBJETOS A FRENTE / GIROSCOPIO EM TORNO DE 90 GRAUS

  if (anguloZ >= 60 && anguloZ <=120 && mediaSensor <= 100 && mediaSensor >= 80 && anguloY >=60 && anguloY <= 120 ) 

  {
     analogWrite(pulseiraE,xI);
     analogWrite(pulseiraD,xI);

  }
  else if (anguloZ >= 60 && anguloZ <= 120 && mediaSensor < 80 && mediaSensor > 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraE,xI);
    analogWrite(pulseiraD,xI);

  }
  else if (anguloZ >= 60 && anguloZ <= 120 && mediaSensor <= 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraE,xI);
    analogWrite(pulseiraD,xI);

  }

  // OBJETOS A LATERAL ESQUERDA / GIROSCOPIO EM TORNO DE 150 GRAUS

  xI = map(mediaSensor,3,100,255,0);

  if (anguloZ > 120 && anguloZ <= 180 && mediaSensor <= 100 && mediaSensor >= 80 && anguloY >=60 && anguloY <= 120 ) 
  {
    analogWrite(pulseiraE,xI);

  }
  else if (anguloZ > 120 && anguloZ <= 180 && mediaSensor < 80 && mediaSensor > 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraE,xI);

  }
  else if (anguloZ > 120 && anguloZ <= 180 && mediaSensor <= 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraE,xI);

  }

  // OBJETOS A LATERAL DIREITA / GIROSCOPIO EM TORNO DE 30 GRAUS

   xI = map(mediaSensor,3,100,255,0);

   if (anguloZ < 60 && anguloZ >= 0 && mediaSensor <= 100 && mediaSensor >= 80 && anguloY >=60 && anguloY <= 120) 
  {
    analogWrite(pulseiraD,xI);
    
  }
  else if (anguloZ <60 && anguloZ >= 0 && mediaSensor < 80 && mediaSensor > 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraD,xI);

  }
  else if (anguloZ < 60 && anguloZ >= 0 && mediaSensor <= 40 && anguloY >=60 && anguloY <= 120)
  {
    analogWrite(pulseiraD,xI);

  }

}
else {

  analogWrite(pulseiraD,0);
  analogWrite(pulseiraE,0);

}
delay(2000);
}
