#include <Ultrasonic.h>
#include <toneAC.h>
#include <stdio.h>
#include <math.h>


#define TRIGGER_PIN  4         // sensor 1
#define ECHO_PIN     5        //sensor 1
#define TRIGGER 2            //sensor 2
#define ECHO   3            //sensor 2
#define TRIGGERsss 7     //sensor 3
#define ECHOsss   6       //sensor 3
#define Motor 9          //motor

int ledPin = 12;
int Tempo = 0;
int Ton = 0;
int motor = 0;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);         // Comunicação com bliblioteca para o primeiro sensor
Ultrasonic sonic(TRIGGER, ECHO);                     // Comunicação com bliblioteca para o segundo sensor
Ultrasonic ultra3(TRIGGERsss, ECHOsss);             // Comunicação com bliblioteca para o terceiro sensor




void setup()
  {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(Motor,OUTPUT);
  }

void loop()
  {
    int
      sensorF, inMsec ,                  // variavel para o primeiro sensor
      sensorE, IMsec,                   // variavel para o segundo sensor
      sensorD, TImec,                  // variavel para o terceiro sensor
     
      SensorF,                       // variavel para receber o valor depois da logica
      SensorE,                      // variavel para receber o valor depois da logica
      SensorD,                     // variavel para receber o valor depois da logia
     
    vl,                        // variavel de utilização publica(livre para testes)
    Ton,freq,le               // varivel de utlização do som
      ;
    
    long
    microsec = ultrasonic.timing(),         // variavel para o primeiro sensor
    Microsec = sonic.timing(),             // variavel para o segundo sensor
    TMicrosec = ultra3.timing();         // variavel para o terceiro sensor
    
    
      SensorF = 0;                        // colocando valores no sensor 1 para que não consuma valores aleatorios
      SensorE = 0;                       // colocando valores no sensor 2 para que não consuma valores aleatorios
      SensorD = 0;                      // colocando valores no sensor 3 para que não consuma valores aleatorios
     
    
      sensorF = ultrasonic.convert(microsec, Ultrasonic::CM);       // variavel para o primeiro sensor
      sensorE = sonic.convert(Microsec, Ultrasonic::CM);           // variavel para o segundo sensor
      sensorD = ultra3.convert(TMicrosec, Ultrasonic::CM);        // variavel para o terceiro sensor
      
    
    
    if (sensorF<100)                           // limitando o sensor1 a sua distancia de 3 metros
     SensorF = sensorF;  
    
    if (sensorE<100)                         // limitando o sensor2 a sua distancia de 3 metros
     SensorE = sensorE;
    
    if (sensorD<100)                       // limitando o sensor3 a sua distancia de 3 metros
     SensorD = sensorD;
    
  
    
    Serial.print(", CM do objeto a frente: ");               // leitura da frente
    Serial.println(SensorF);
    Serial.println( );
    Serial.println( );
    
    
    Serial.print(", CM do objeto a esquerda: ");              // leitura da esquerda
    Serial.println(SensorE);
    Serial.println( );
    Serial.println( );
    
    Serial.print(", CM do objeto a direita: ");           // leitura da direita
    Serial.println(SensorD);
    Serial.println( );
    Serial.println( );
    
   
    delay(2000);
    
             // Logica para a vibração dos motores de acordo com a distância
             
    //motor=digitalRead(sensorF);
    int mot=map(sensorF,0,1023,0,255);
    //motor=mot
   if(motor <=100&& motor>=80)                                     // Objeto a mais de 2 metros a frente
   {
    digitalWrite(Motor,mot);
    delay(500);
   }
   else if (motor <=80 && SensorF >50)             // Objeto a mais de 1 metro a frente
   {

    digitalWrite(Motor,mot);
    delay(500);
   }
   else if(SensorF<=50 && SensorF >20)               // Objeto a mais de 0,5 metros a frente
   {

     digitalWrite(Motor,mot);
     delay(500);
   }
   else                                               // Objeto a menos de 0,5 metros a frente
   {

    digitalWrite(Motor,LOW);
   }















    
    
   /* if (SensorF == SensorE && SensorF != SensorD  )                 // Obstaculo na esquerda
     {
    Ton = 0 ;                            // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 330;                         // frenquencia
    le = 300;                          // duração 
    
    Ton = SensorF;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa
    
    toneAC(freq, Ton, le);         // Codigo do ToneAC  em mi
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }
    
    if (SensorF == SensorD && SensorF != SensorE)           //Obstaculo  na direita
      {
    Ton = 0 ;                      // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 262;                   // frenquencia
    le = 200;                    // duração 
    
    Ton = SensorF;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa
    
    toneAC(freq, Ton, le);        // Codigo do ToneAC  em do
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }
    
    if (SensorF == SensorE && SensorD == SensorE && SensorF==SensorD) // obstaculo em frente  *******
     {
    Ton = 0 ;                  // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 440;               // frenquencia
    le = 200;                // duração 
    
    Ton = SensorF;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa     
    
    toneAC(freq, Ton, le);          // Codigo do ToneAC  em la
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }*/



}
