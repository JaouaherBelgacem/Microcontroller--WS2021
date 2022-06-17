#define t10 1000
#define t20 2000
#define redState 1
#define yellowState 2
#define greenState 3

int RED= 4;
int YELLOW= 3;
int GREEN= 2;

volatile int state= redState; 
volatile int lastState;



void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop(){ 
  
switch (state){
    
 case redState:
  ledCONTROL(RED, YELLOW, GREEN, HIGH, LOW, LOW, t20);
  lastState=redState;
  state= yellowState;
  break; 
 
 case yellowState:
  ledCONTROL(RED, YELLOW, GREEN, LOW, HIGH, LOW, t10);
    
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
  ledCONTROL(RED, YELLOW, GREEN, LOW, LOW, HIGH, t20);
  lastState= greenState;
  state= yellowState ;
  break;
    
   
}  
}

void ledCONTROL(int tL1,int tL2,int tL3,int s1,int s2,int s3, int time)
{ 
  digitalWrite(tL1,s1);
  digitalWrite(tL2,s2);
  digitalWrite(tL3,s3);
  delay(time);
}