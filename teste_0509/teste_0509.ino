int triggerPinF = 5; // sensor frente
int echoPinF = 4;  // sensor frente
int triggerPinE = 2;  // sensor esquerda
int echoPinE = 3; // sensor esquerda
int triggerPinD = 7;  // sensor direita
int echoPinD = 6; // sensor direita
float cmF = 0;
float cmE = 0;
float cmD = 0;
int xF=0;
int xE=0;
int xD=0;
#define pulseiraE 9
#define pulseiraD 11


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
    //delay(600);
  
    Serial.println("---------------------------------------------");
  
  if (cmF >= 3 && cmF<= 100)
  {
        xF = map(cmF,3,100,168,30);
      
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
   } else if (cmE >= 3 && cmE<= 100)
  {
      xE = map(cmE,3,100,168,30);
  
     if (cmE <=100.0 && cmE >=30)
       {
         analogWrite(pulseiraE,xE);
          //Serial.print("modo 3     ");
       }
      else if (cmE <80.0 && cmE >40)
      {
           analogWrite(pulseiraE,xE);
          //Serial.print("modo 2    ");
      }
       else if (cmE<=40)
       {
        analogWrite(pulseiraE,xE);
          //Serial.print("modo 1    ");
      }
      else {
      Serial.println("OBJETO A ESQUERDA INDECTAVEL!");
      }
  }
  
 else if (cmD >= 3 && cmD<= 100 )
  {
      xD = map(cmD,3,100,168,30);
    

      if (cmD <=100.0 && cmD >=80)
      {
        analogWrite(pulseiraD,xD);
          //Serial.print("modo 3     ");
      }
      else if (cmD <80.0 && cmD >40)
      {
         analogWrite(pulseiraD,xD);
         //Serial.print("modo 2    ");
      }
       else if (cmD<=40)
       {
          analogWrite(pulseiraD,xD);
          //Serial.print("modo 1    ");
      }
      else {
      Serial.println("OBJETO A DIREITA INDECTAVEL!");
      }
  }

else
  {
    analogWrite(pulseiraD,0);
    analogWrite(pulseiraE,0);
  }
 
}
