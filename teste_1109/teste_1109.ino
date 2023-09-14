
//teste com os tres sensores na frente
#define pulseiraE 9
#define pulseiraD 11
#define pinX A0
#define pinY A1
#define pinZ A2

int triggerPinF = 5; // sensor frente
int echoPinF = 4;  // sensor frente
int triggerPinE = 2;  // sensor esquerda
int echoPinE = 3; // sensor esquerda
int triggerPinD = 7;  // sensor direita
int echoPinD = 6; // sensor direita
float cmF = 0;    // centimetro na frente 
float cmE = 0;   // centimetro na esquerda
float cmD = 0;  // centimetro na direita 
int xF=0;      // intensidade na frente 
int xE=0;     // intensidade na esquerda
int xD=0;    // intensidade na direita 
float mediaSensor; // media das distancias de todos os sensores


long distaF(int SomPin, int echoPin){
  pinMode(triggerPinF, OUTPUT);
  digitalWrite(triggerPinF, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinF, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
long distaE(int SomPin, int echoPin){
  pinMode(triggerPinE, OUTPUT);
  digitalWrite(triggerPinE, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinE, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinE, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
long distaD(int SomPin, int echoPin){
  pinMode(triggerPinD, OUTPUT);
  digitalWrite(triggerPinD, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinD, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPinD, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}


void setup(){
 pinMode(pulseiraE,OUTPUT);
 pinMode(pulseiraD,OUTPUT);
 Serial.begin(9600);

}

void loop(){


   
  int eixoX=analogRead(pinX);
  int eixoY=analogRead(pinY);
  int eixoZ=analogRead(pinZ);

  Serial.print("X: ");
  Serial.print(eixoX);
  Serial.print("Y: ");
  Serial.print(eixoY);
  Serial.print("Z: ");
  Serial.print(eixoZ);



  cmF = 0.01723 * distaF(triggerPinF, echoPinF);
    Serial.print("SENSOR FRENTE: ");
    Serial.print(cmF);
    Serial.println("cm");
  
  cmE = 0.01723 * distaE(triggerPinE, echoPinE);
    Serial.print("SENSOR ESQUERDA: ");
    Serial.print(cmE);
    Serial.println("cm");
  
    cmD = 0.01723 * distaD(triggerPinD, echoPinD);
    Serial.print("SENSOR DIREITA: ");
    Serial.print(cmD);
    Serial.println("cm");


    mediaSensor= (cmF+cmE+cmD)/3.0;
    Serial.print("SENSOR UNICO: ");
    Serial.print(mediaSensor);
    Serial.println("cm");
    //delay(600);
  
    Serial.println("---------------------------------------------");
   //IREI TENTAR TRANSFORMAR OS TRES SENSORERS EM APENAS UM,PARA ISSO IREI FAZER A MEDIA DAS DISTANCIAS DOS TRES.

    mediaSensor= (cmF+cmE+cmD)/3.0;
    Serial.print("SENSOR UNICO: ");
    Serial.print(mediaSensor);
    Serial.println("cm");

    //ABAIXO VAMOS TENTAR USAR OS TRES SENSORES NA PARTE DA FRENTE DO ÓCULOS, VOU COLOCAR TODOS FUNCIONANCO DA MESMA FORMA DO DA FRENTE.
    // COLOCAMOS O EIXO X DO ACELEROMETRO


  if (cmF >= 3 && cmF<= 100 && eixoX>=320 && eixoX<=340 )
  {
        xF = map(cmF,3,100,255,120);
      
        if (cmF <=100.0 && cmF >=80)
       {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 3     ");
       }
        else if (cmF <80.0 && cmF >40)
      {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 2    ");
  
      }
        else if (cmF<=40)
      {
        analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 1    ");
      
      }
      else {
      Serial.println("OBJETO A FRENTE INDECTAVEL!");
      }  
   } 

  else if (cmE >= 3 && cmE<= 100 && eixoX>=320 && eixoX<=340)
  {
        xF = map(cmE,3,100,255,120);
      
        if (cmE <=100.0 && cmE >=80)
       {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 3     ");
       }
        else if (cmE <80.0 && cmE >40)
      {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 2    ");
  
      }
        else if (cmE<=40)
      {
        analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 1    ");
      
      }
      else {
      Serial.println("OBJETO A FRENTE INDECTAVEL!");
      }  
   } 
   
  else if (cmD>= 3 && cmD<= 100 && eixoX>=320 && eixoX<=340)
  {
        xF = map(cmF,3,100,255,120);
      
        if (cmD <=100.0 && cmD >=80)
       {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 3     ");
       }
        else if (cmD <80.0 && cmD >40)
      {
          analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 2    ");
  
      }
        else if (cmD<=40)
      {
        analogWrite(pulseiraE,xF);
          analogWrite(pulseiraD,xF);
          //Serial.print("modo 1    ");
      
      }
      else {
      Serial.println("OBJETO A FRENTE INDECTAVEL!");
      }  
   } 
  else
  {
    analogWrite(pulseiraD,0);
    analogWrite(pulseiraE,0);
  }
   
}
