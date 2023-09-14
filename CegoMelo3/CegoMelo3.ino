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


int ledPin = 12;
int Tempo = 0;
int Ton = 0;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);         // Comunicação com bliblioteca para o primeiro sensor
Ultrasonic sonic(TRIGGER, ECHO);                     // Comunicação com bliblioteca para o segundo sensor
Ultrasonic ultra3(TRIGGERsss, ECHOsss);             // Comunicação com bliblioteca para o terceiro sensor



void setup()
  {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
  }

void loop()
  {
    int
      sensor1, inMsec ,                  // variavel para o primeiro sensor
      sensor2, IMsec,                   // variavel para o segundo sensor
      sensor3, TImec,                  // variavel para o terceiro sensor
     
      Sensor1,                       // variavel para receber o valor depois da logica
      Sensor2,                      // variavel para receber o valor depois da logica
      Sensor3,                     // variavel para receber o valor depois da logia
     
    vl,                        // variavel de utilização publica(livre para testes)
    Ton,freq,le               // varivel de utlização do som
      ;
    
    long
    microsec = ultrasonic.timing(),         // variavel para o primeiro sensor
    Microsec = sonic.timing(),             // variavel para o segundo sensor
    TMicrosec = ultra3.timing();         // variavel para o terceiro sensor
    
    
      Sensor1 = 0;                        // colocando valores no sensor 1 para que não consuma valores aleatorios
      Sensor2 = 0;                       // colocando valores no sensor 2 para que não consuma valores aleatorios
      Sensor3 = 0;                      // colocando valores no sensor 3 para que não consuma valores aleatorios
     
    
      sensor1 = ultrasonic.convert(microsec, Ultrasonic::CM);       // variavel para o primeiro sensor
      sensor2 = sonic.convert(Microsec, Ultrasonic::CM);           // variavel para o segundo sensor
      sensor3 = ultra3.convert(TMicrosec, Ultrasonic::CM);        // variavel para o terceiro sensor
      
    
    
    if (sensor1<30)                           // limitando o sensor1 a sua distancia de 4 metros
     Sensor1 = sensor1;  
    
    if (sensor2<30)                         // limitando o sensor2 a sua distancia de 4 metros
     Sensor2 = sensor2;
    
    if (sensor3<30)                       // limitando o sensor3 a sua distancia de 4 metros
     Sensor3 = sensor3;
    
  
    
    Serial.print(", CM primeiro sensor: ");               // leitura do primeiro sensor
    Serial.println(Sensor1);
    Serial.println( );
    Serial.println( );
    
    
    Serial.print(", CM segundo sensor: ");              // leitura do segundo sensor
    Serial.println(Sensor2);
    Serial.println( );
    Serial.println( );
    
    Serial.print(", CM terceiro sensor: ");           // leitura do terceiro sensor
    Serial.println(Sensor3);
    Serial.println( );
    Serial.println( );
    
   
    delay(3000);
    
    
    if (Sensor1 == Sensor2 && Sensor1 != Sensor3  )                 // Obstaculo em cima e na esquerda
     {
    Ton = 0 ;                            // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 330;                         // frenquencia
    le = 300;                          // duração 
    
    Ton = Sensor1;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa
    
    toneAC(freq, Ton, le);         // Codigo do ToneAC  em mi
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }
    
    if (Sensor1 == Sensor3 && Sensor1 != Sensor2)           //Obstaculo em cima e na direita
      {
    Ton = 0 ;                      // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 262;                   // frenquencia
    le = 200;                    // duração 
    
    Ton = Sensor1;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa
    
    toneAC(freq, Ton, le);        // Codigo do ToneAC  em do
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }
    
    if (Sensor1 == Sensor2 && Sensor3 == Sensor2 && Sensor1==Sensor3) // obstaculo em frente
     {
    Ton = 0 ;                  // volume ( 0 a 10) default: 10, range: 0 to 10 [0 = off
    freq = 440;               // frenquencia
    le = 200;                // duração 
    
    Ton = Sensor1;                    // Ton recebe valor de sensor
    Ton = map(Ton, 0, 400, 10, 0);   //Ton e definido entre 0 e 10 pelo mapa     
    
    toneAC(freq, Ton, le);          // Codigo do ToneAC  em la
    Serial.print("Tonalidade: ");
    Serial.println(Ton);
    Serial.print("Tempo (ms): ");
    Serial.println(Tempo);
    delay(100);
    noTone(8);
     }



}
