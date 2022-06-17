// C++ code
//
#define redLed 9
#define greenLed 7
#define yellowLed 8
#define pedGreenLed 5 
#define pedRedLed 6 
#define button 2
#define checkLed 10

volatile bool pedButton;
volatile int  checkChange;

volatile int t20= 0; // timer for red and green light
volatile int t10= 0; // timer for yellow light
volatile int pedTime= 0; // timer for ped crossing
volatile int pedRedTimer = 0;

enum trafLightState { trafRed, trafYellow1, trafGreen, trafYellow2};

trafLightState tState;

enum pedLightState {pedRed, pedGreen};

pedLightState pState;

void setup()
{ 	Serial.begin(9600);
	pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
	pinMode(greenLed, OUTPUT);
  	pinMode(pedGreenLed, OUTPUT);
	pinMode(pedRedLed, OUTPUT);
  	pinMode(button, INPUT);
    pinMode (checkLed, OUTPUT);
  
 	attachInterrupt(digitalPinToInterrupt(button), pressPedButton, RISING);

 	
 
}

void pressPedButton()
{
  
  pedButton = true;
  checkChange = 1;
  digitalWrite(checkLed, HIGH);// to notify that a change happened
  delay(2000);
  digitalWrite(checkLed, LOW);
   // shared variable between two sate machines

}

void loop()
{
  pedRedTimer= 2000;
  pedTime= 2000;
  t20 = 3000;
  t10 = 1000;
  if (pedButton == true)
  {
    pState = pedGreen;
    pedTime = 4000; // increase crossing time
    pedStateMachine();// case Green pedestrian light
	tState = trafRed; // case red traffic light
    trafStateMachine();
	pedButton = false;
  }
  else
  {
	if (tState == trafGreen)  
    {
      	t20 = 10000;
      	t10 = 5000;
        trafStateMachine();
        pState = pedRed;
      	pedRedTimer = t20 + t10;
      	pedStateMachine();

    }
    
      trafStateMachine();
      pedStateMachine();

  }

}

void trafStateMachine()
{
	switch(tState)
    { 
       case trafRed:
      	
      	  digitalWrite(yellowLed, LOW);
		  digitalWrite(greenLed, LOW);
          digitalWrite(redLed, HIGH);
          delay (t20);
          digitalWrite(redLed, LOW);
          
      	  tState = trafYellow1;
      
		  break;

       case trafYellow1:

          digitalWrite(redLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
          delay (t10);
      	  digitalWrite(yellowLed, LOW);

          tState = trafGreen;
      
        break;

		case trafGreen:

          digitalWrite(yellowLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(greenLed, HIGH);
          delay (t20);
      	  digitalWrite(greenLed, LOW);

          tState = trafYellow2;
      
        break;
      
      case trafYellow2:

          digitalWrite(redLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
          delay (t10);
      	  digitalWrite(yellowLed, LOW);

          tState = trafRed;
      
        break;


       default:
        break;
    }
 }

void pedStateMachine()
{
	switch(pState)
    { 
       case pedRed:
 
          digitalWrite(pedGreenLed, LOW);
          digitalWrite(pedRedLed, HIGH);
          delay(pedRedTimer);
          digitalWrite(pedRedLed, LOW);
          
      	  pState = pedGreen;
      
		  break;
      
       case pedGreen:
 
          digitalWrite(pedRedLed, LOW);
          digitalWrite(pedGreenLed, HIGH);
          delay(pedTime);
          digitalWrite(pedGreenLed, LOW);
          
      	  pState = pedRed ;
      
		  break;
       default:
        break;
    }

}
