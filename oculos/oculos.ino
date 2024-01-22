// CORRECÕES: -ajustar configuraçoes dos angulos;
//            -verificar qual o eixo da movimentação vertical do giroscopio;
//            -verificar necessidades de atualizações constantes do uso do map e das leituras dos sensores.

//=========================//
// Versão com Arduino Nano //
//=========================//

#include <MPU6050_tockn.h>
#include <Wire.h>
// necessidade de incluir uma library para o ultrasonic

#define pulseiraE 7
#define pulseiraD 8


#define MPU6050_ADDR 0x68 // no arduino uno, ligar o pino A4(arduin) ao pino SDA do MPU e o A5(arduino) no SCL do MPU 
                          // o pino AD0 do MPU deve ficar ligado no GND para o endereço 0x68 
#define DEBUG


const float calDist = 0.01723; // calibração de distância

MPU6050 mpu6050(Wire);

int triggerPinE = 2; // sensor Esquerdo
int echoPinE = 3;  // sensor Esquerdo
int triggerPinD = 2;  // sensor Direito
int echoPinD = 4; // sensor Direito

int ledAux = 13; // ao piscar mostra que o arduino está funionando

float DistE = 0;    // distnacia sensor Esquerdo
float DistD = 0;   // distnacia sensor Direito

int xI= 0;      // intensidade no atuadores, com base na media 
float anguloX; // angulo em graus eixo x
float anguloY; // angulo em graus eixo y
float anguloZ; // angulo em graus eixo z
bool LED;

unsigned long Tled = millis();
void pisca(){  // tempos menores que 2s não funcionam devido ao delay causado pelo mpu6050
  int base = 2000; // pisca a cada 2 segundos
  unsigned long dT = millis()- Tled;
  LED = dT < base;
  digitalWrite(ledAux, LED);
  if(dT > 2*base){ Tled = millis();}
}

long distancia(int triggerPin, int echoPin){
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
   Serial.print("SENSOR Direito: ");
   Serial.print(DistD);
   Serial.println("cm");
   
   Serial.print("SENSOR Esquerdo: ");
   Serial.print(DistE);
   Serial.println("cm");

  Serial.print("anguloX: ");
  Serial.print(anguloX );
  Serial.println("o");

  Serial.print("anguloY: ");
  Serial.print(anguloY );
  Serial.println("o");

  Serial.print("anguloZ: ");
  Serial.print(anguloZ );
  Serial.println("o");

  Serial.println("---------------------------------------------");
  //LED = !LED;
  //digitalWrite(ledAux, LED);
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
  pinMode(ledAux,OUTPUT);

  vibra();
  vibra();
  vibra();
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);  // colocar o giroscopio  em uma superficie plana para calibrar

  #ifdef DEBUG
    Serial.println("Fim Setup");
  #endif 
  digitalWrite(ledAux, HIGH);
}

void loop() {

  pisca();

  mpu6050.update();

  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  anguloZ = mpu6050.getAngleZ();

  DistE = calDist * distancia(triggerPinE, echoPinE);

  DistE = calDist * distancia(triggerPinD, echoPinD);
  
  //imprimir();
  
/*
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
*/
//delay(500);
}
