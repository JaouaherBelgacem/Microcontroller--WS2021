#define t10 1000
#define t20 2000
#define redState 1
#define yellowState 2
#define greenState 3

int trRED= 13;
int trYELLOW= 12;
int trGREEN= 11;
int pdRED= 10; 
int pdGREEN= 9; 
int pdBUTTON = 2; 

volatile byte buttonState= LOW; 

int state= redState; 
int lastState;



void setup()
{
  pinMode(trRED, OUTPUT);
  pinMode(trYELLOW, OUTPUT);
  pinMode(trGREEN, OUTPUT);
  pinMode(pdGREEN, OUTPUT);
  pinMode(pdRED, OUTPUT);
  pinMode(pdBUTTON, INPUT); 
  attachInterrupt(digitalPinToInterrupt(pdBUTTON), pdREQUEST, RISING);
  digitalWrite(pdRED, HIGH); 
  digitalWrite(pdGREEN, LOW);
}

void loop(){
  switch(buttonState){
  case LOW: carLANE();
    break; 
  case HIGH: pedastrianCROSS();
    break; 
    
  }
}

void carLANE(){ 
  
digitalWrite(pdGREEN, LOW);
digitalWrite(pdRED, HIGH);
  
switch (state){
    
 case redState:
  ledCONTROL(trRED, trYELLOW, trGREEN, HIGH, LOW, LOW, t20);
  lastState=redState;
  state= yellowState;
  break; 
 
 case yellowState:
  ledCONTROL(trRED, trYELLOW, trGREEN, LOW, HIGH, LOW, t10);
    
    switch (lastState){
      case redState: 
       state= greenState;
      break; 
      case greenState:
       state= redState; 
      break;
    }
      
   break;
  case greenState:
  ledCONTROL(trRED, trYELLOW, trGREEN, LOW, LOW, HIGH, t20);
  lastState= greenState;
  state= yellowState ;
  break;
}}

void pedastrianCROSS(){
  
digitalWrite(pdGREEN, HIGH);
digitalWrite(pdRED, LOW);
ledCONTROL(trRED, trYELLOW, trGREEN, HIGH, LOW, LOW, t20);
buttonState=!buttonState; 

}

void pdREQUEST(){
  buttonState=!buttonState; 
}

void ledCONTROL(int tL1,int tL2,int tL3, int s1,int s2,int s3, int time)
{ 
  digitalWrite(tL1,s1);
  digitalWrite(tL2,s2);
  digitalWrite(tL3,s3);
  delay(time);
}