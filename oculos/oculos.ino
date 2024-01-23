// CORRECÕES: -ajustar configuraçoes dos angulos;
//            -verificar qual o eixo da movimentação vertical do giroscopio;
//            -verificar necessidades de atualizações constantes do uso do map e das leituras dos sensores.

//=========================//
// Versão com Arduino Nano //
//=========================//

// para doisacelerometros trabalahremos apenas com wire.h que gerencia o barrameto I2C
//#include <MPU6050_tockn.h>
#include <Wire.h>
#include "Ultrasonic.h" // https://www.robocore.net/tutoriais/primeiros-passos-com-sensor-ultrassonico
//#include "Vibra.h"

#define pulseiraE 7
#define pulseiraD 8


//#define MPU6050_ADDR 0x68 // no arduino uno, ligar o pino A4(arduin) ao pino SDA do MPU e o A5(arduino) no SCL do MPU 
                          // o pino AD0 do MPU deve ficar ligado no GND para o endereço 0x68 
#define DEBUG


//const float calDist = 0.01723; // calibração de distância

//MPU6050 mpu6050(Wire);

int triggerPinE = 2; // sensor Esquerdo
int echoPinE = 3;  // sensor Esquerdo
int triggerPinD = 2;  // sensor Direito
int echoPinD = 4; // sensor Direito


HC_SR04 sensorE(triggerPinE,echoPinE); //Configura os pinos sensor ultrassonico (Trigger,Echo)
HC_SR04 sensorD(triggerPinD,echoPinD); //Configura os pinos sensor ultrassonico (Trigger,Echo)

const int MPU_H = 0x68; // Endereço do sensor da cabeça (Head)
const int MPU_B = 0x69; // Endereço do sensor do corpo (Body)

int16_t AcXB,AcYB,AcZB,TmpB,GyXB,GyYB,GyZB; //Variaveis para pegar os valores medidos
int16_t AcXH,AcYH,AcZH,TmpH,GyXH,GyYH,GyZH; //Variaveis para pegar os valores medidos

//VIBRA motorE(pulseiraE);
//VIBRA motorD(pulseiraD);

int ledAux = 13; // ao piscar mostra que o arduino está funionando

float DistE = 0;    // distnacia sensor Esquerdo
float DistD = 0;   // distnacia sensor Direito

int salvas; // numero de salvas  aserem executaddas pelo motor
int espaco; // espaço de tempo, em ms, entre salvas

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

void imprimir(){
   Serial.print("SENSOR Direito: ");
   Serial.print(DistD);
   Serial.println("cm");
   
   Serial.print("SENSOR Esquerdo: ");
   Serial.print(DistE);
   Serial.println("cm");

/*
  Serial.print("anguloX: ");
  Serial.print(anguloX );
  Serial.println("o");

  Serial.print("anguloY: ");
  Serial.print(anguloY );
  Serial.println("o");

  Serial.print("anguloZ: ");
  Serial.print(anguloZ );
  Serial.println("o");
*/

// Agora escreve os valores no monitor serial
  // Sensor cabeça
  Serial.print("AcXH = "); Serial.print(AcXH);
  Serial.print(" | AcYH = "); Serial.print(AcYH);
  Serial.print(" | AcZH = "); Serial.print(AcZH);
  Serial.print(" | TmpH = "); Serial.print(TmpH/340.00+36.53); // Equação da temperatura em Cº de acordo com o datasheet
  Serial.print(" | GyXH = "); Serial.print(GyXH);
  Serial.print(" | GyYH = "); Serial.print(GyYH);
  Serial.print(" | GyZH = "); Serial.println(GyZH);
  // Sensor corpo
  Serial.print("AcXB = "); Serial.print(AcXB);
  Serial.print(" | AcYB = "); Serial.print(AcYB);
  Serial.print(" | AcZB = "); Serial.print(AcZB);
  Serial.print(" | TmpB = "); Serial.print(TmpB/340.00+36.53); // Equação da temperatura em Cº de acordo com o datasheet
  Serial.print(" | GyXB = "); Serial.print(GyXB);
  Serial.print(" | GyYB = "); Serial.print(GyYB);
  Serial.print(" | GyZB = "); Serial.println(GyZB);
  Serial.println("---------------------------------------------");
  //LED = !LED;
  //digitalWrite(ledAux, LED);
 }
/*
 void vibra(){
  analogWrite(pulseiraD,255);
  analogWrite(pulseiraE,255);
  delay(200);
  analogWrite(pulseiraD,0);
  analogWrite(pulseiraE,0);
  delay(200);

 }
*/

class Vibra{
  // Variáveis membro da classe
    // São inicializadas no startup do programa
    int motorPin;      // número do pino do motor

    public:
    Vibra(int pin){
      motorPin = pin;
      pinMode(motorPin, OUTPUT);
    }

    void vibra(int nSalvas, int espaco){ // numero de salvas e milisegundos entre salvas
      int dt = 10;
      for (int i = 0; i < nSalvas; i++){
        digitalWrite(motorPin,HIGH);
        delay(dt);
        digitalWrite(motorPin,LOW);
        delay(dt);
        
        delay(espaco);
      }
    }

    void calcVibra(int distancia){ // sequencia de salvas em função da distância (em cm)
      int nSalvas, espaco;
      if (distancia >= 300 && distancia < 350 ){ // 300cm -> 3m
        nSalvas = 1;
        espaco = 900;
      } else if (distancia >= 250 && distancia < 200 ){ 
        nSalvas = 2;
        espaco = 800;
      } else if (distancia >= 200 && distancia < 150 ){ 
        nSalvas = 3;
        espaco = 700;
      } else if (distancia >= 150 && distancia < 100 ){ 
        nSalvas = 4;
        espaco = 600;
      } else if (distancia >= 100 && distancia < 50 ){ 
        nSalvas = 5;
        espaco = 500;
      } else if (distancia >= 50 && distancia < 40 ){ 
        nSalvas = 6;
        espaco = 400;
      } else if (distancia >= 40 && distancia < 30 ){ 
        nSalvas = 7;
        espaco = 300;
      } else if (distancia >= 30 && distancia < 20 ){ 
        nSalvas = 8;
        espaco = 200;
      } else if (distancia >= 20 && distancia < 10 ){ 
        nSalvas = 9;
        espaco = 100;
      } else{
        nSalvas = 10;
        espaco = 0;
      }
      vibra(nSalvas, espaco);
    }


};

Vibra motorE(pulseiraE);
Vibra motorD(pulseiraD);


void setup() {
  Wire.begin(); // Inicia a comunicação I2C
  Wire.beginTransmission(MPU_H); //Começa a transmissao de dados para o sensor cabeça
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 1
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_B); //Começa a transmissao de dados para o sensor corpo
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 2
  Wire.endTransmission(true);

  Serial.begin(9600); //Inicia a comunicaçao serial (para exibir os valores lidos)

  //pinMode(pulseiraE,OUTPUT);
  //pinMode(pulseiraD,OUTPUT);
  pinMode(ledAux,OUTPUT);

  motorE.vibra(3,100); // 3 salvas com espaço de 100ms
  motorD.vibra(3,100);
  
  
  Wire.begin();
  //mpu6050.begin();
  //mpu6050.calcGyroOffsets(true);  // colocar o giroscopio  em uma superficie plana para calibrar

  #ifdef DEBUG
    Serial.println("Fim Setup");
  #endif 
  digitalWrite(ledAux, HIGH);
}

void loop() {

  pisca();

  //mpu6050.update();

  //anguloX = mpu6050.getAngleX();
  //anguloY = mpu6050.getAngleY();
  //anguloZ = mpu6050.getAngleZ();

// Sensor cabeça
  Wire.beginTransmission(MPU_H); //Começa a transmissao de dados do sensor 1
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_H,14,true); // Faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcXH = Wire.read()<<8|Wire.read();
  AcYH = Wire.read()<<8|Wire.read();
  AcZH = Wire.read()<<8|Wire.read();
  TmpH = Wire.read()<<8|Wire.read();
  GyXH = Wire.read()<<8|Wire.read();
  GyYH = Wire.read()<<8|Wire.read();
  GyZH = Wire.read()<<8|Wire.read();
  Wire.endTransmission(true); // Se der erro tente tirar esta linha

  // Sensor corpo
  Wire.beginTransmission(MPU_B); // Começa a transmissao de dados do sensor 2
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_B,14,true); // Faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcXB = Wire.read()<<8|Wire.read();
  AcYB = Wire.read()<<8|Wire.read();
  AcZB = Wire.read()<<8|Wire.read();
  TmpB = Wire.read()<<8|Wire.read();
  GyXB = Wire.read()<<8|Wire.read();
  GyYB = Wire.read()<<8|Wire.read();
  GyZB = Wire.read()<<8|Wire.read();
  Wire.endTransmission(true); // Se der erro tente tirar esta linha


  DistE = sensorE.distance(); // distancia em cm

  DistD = sensorD.distance(); // distancia em cm
  
  motorE.calcVibra(DistE); // 3 salvas com espaço de 100ms
  motorD.calcVibra(DistD);

  imprimir();
  
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
