#include <NewPing.h>
//#include <toneAC.h>
#include <stdio.h>
#include <math.h>


#define TRIGGER_PIN  4         // sensor 1
#define ECHO_PIN     5        //sensor 1
#define TRIGGER 2           //sensor 2
#define ECHO   3         //sensor 2
#define TRIGGERsss 7     //sensor 3
#define ECHOsss   6       //sensor 3
#define PulseiraD 9       //Vibracall da pulseira direita
#define PulseiraE 11       //Vibracall da pulseira esquerda

int motor = 0;
int motF =0;
int motE=0;
int motD =0;
long temppas=0;
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN);         // Comunicação com bliblioteca para o primeiro sensor
NewPing sonic(TRIGGER, ECHO);                     // Comunicação com bliblioteca para o segundo sensor
NewPing ultra3(TRIGGERsss, ECHOsss);             // Comunicação com bliblioteca para o terceiro sensor
long
    microsec = 0,
    Microsec = 0,
    TMicrosec = 0;
int
      sensorF, inMsec ,                  // variavel para o primeiro sensor
      sensorE, IMsec,                   // variavel para o segundo sensor
      sensorD, TImec,                  // variavel para o terceiro sensor
     
      SensorF,                       // variavel para receber o valor depois da logica
      SensorE,                      // variavel para receber o valor depois da logica
      SensorD;                     // variavel para receber o valor depois da logia
      

void concertaTudo (){
     
    microsec = ultrasonic.ping_cm(),         // variavel para o primeiro sensor
    Microsec = sonic.ping_cm(),             // variavel para o segundo sensor
    TMicrosec = ultra3.ping_cm(); 
    sensorF= microsec;
    sensorE= Microsec;
    sensorD =TMicrosec;

    if (sensorF > 50){
        sensorF = 50;

    }
      else if (sensorF <3){
        sensorF = 3;
    }
     if (sensorD > 50){
        sensorD = 50;
     }
      else if (sensorD <3){
        sensorD = 3;
      }
     if (sensorE > 50){
        sensorE = 50;
     }
      else if (sensorE <3){
        sensorE = 3;
      }

    motF=map(sensorF,3,50,120,20); //modulação sensor da frente
    motD=map(sensorD,3,50,120,20); //modulação sensor da direita
    motE=map(sensorE,3,50,120,20); //modulação sensor da esquerda

     
}

void setup()
  {
Serial.begin(9600);
pinMode(PulseiraD,OUTPUT);
pinMode(PulseiraE,OUTPUT);
  }

void loop()
  {
    microsec = ultrasonic.ping_cm(),         // variavel para o primeiro sensor
    Microsec = sonic.ping_cm(),             // variavel para o segundo sensor
    TMicrosec = ultra3.ping_cm();         // variavel para o terceiro sensor
    
    //SensorF = 0;                        // colocando valores no sensor 1 para que não consuma valores aleatorios
    //SensorE = 0;                       // colocando valores no sensor 2 para que não consuma valores aleatorios
    //SensorD = 0;                      // colocando valores no sensor 3 para que não consuma valores aleatorios
     
    sensorF= microsec;
    sensorE= Microsec;
    sensorD =TMicrosec;
    //sensorF = ultrasonic.convert(microsec, Ultrasonic::CM);       // variavel para o primeiro sensor
    //sensorE = sonic.convert(Microsec, Ultrasonic::CM);           // variavel para o segundo sensor
    // sensorD = ultra3.convert(TMicrosec, Ultrasonic::CM);        // variavel para o terceiro sensor
      
    
    
    if (sensorF<50)                           // limitando o sensor1 a sua distancia de 3 metros
     SensorF = sensorF;  
    
    if (sensorE<50)                         // limitando o sensor2 a sua distancia de 3 metros
     SensorE = sensorE;
    
    if (sensorD<50)                       // limitando o sensor3 a sua distancia de 3 metros
     SensorD = sensorD;
    
    
    if (millis()-temppas>=1000)
    {

    temppas=millis();
    Serial.print("SENSOR FRENTE: ");               // leitura da frente
    Serial.println(SensorF);
    Serial.println( );
    Serial.println( );
    
    
    Serial.print("SENSOR ESQUERDA: ");              // leitura da esquerda
    Serial.println(SensorE);
    Serial.println( );
    Serial.println( );
    
    Serial.print("SENSOR DIREITA: ");           // leitura da direita
    Serial.println(SensorD);
    Serial.println( );
    Serial.println( );

    Serial.println("----------------------------------------------------------------------------------------------");
    
   
    //delay(1000);
    }
    
    // Logica para a vibração dos motores de acordo com a distância
             
     motF=map(sensorF,3,100,120,20); //modulação sensor da frente
     motD=map(sensorD,3,100,120,20); //modulação sensor da direita
     motE=map(sensorE,3,100,120,20); //modulação sensor da esquerda

  // --------------------------- SENSOR ESQUERDA ABAIXO -------------------------------

    if(sensorE <=50 && sensorE>=35)                                     // Objeto a mais de 2 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraE,motE);
     }
    else if (sensorE <35 && sensorE >10)             // Objeto a mais de 1 metro a frente
    {
      concertaTudo();
      analogWrite(PulseiraE,motE);
    }
    else                                               // Objeto a menos de 0,5 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraE,motE);
    }

  // --------------------------- SENSOR DIREITA ABAIXO -------------------------------

    if(sensorD <=50 && sensorD>=35)                                     // Objeto a mais de 2 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motD);
    }
    else if (sensorD <35 && sensorD >10)             // Objeto a mais de 1 metro a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motD);
    }
    else                                               // Objeto a menos de 0,5 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motD);
    }
  //------------------------------ SENSOR DA FRENTE ABAIXO --------------------------------------

    if(sensorF <=50 && sensorF>=35)                        // Objeto a mais de 2 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motF);
      analogWrite(PulseiraE,motF);
     }
    else if (sensorF <35 && sensorF >10)             // Objeto a mais de 1 metro a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motF);
      analogWrite(PulseiraE,motF);
    }
    else                                               // Objeto a menos de 0,5 metros a frente
    {
      concertaTudo();
      analogWrite(PulseiraD,motF);
      analogWrite(PulseiraE,motF);
    }
  }




