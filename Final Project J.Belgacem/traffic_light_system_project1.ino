// C++ code
// Arduino 1 send and receive  signals

#define redLed 9
#define greenLed 7
#define yellowLed 8
#define pedGreenLed 5 
#define pedRedLed 6 
#define button 2
#define checkLed 10
#define	greenFlag 100 // switch is Allowed
#define redFlag 200 // switch is Not Allowed

volatile bool pedButton;
volatile int  checkChange;

//int x;
char signal[10];
bool iAmGreen;

volatile int t20= 2000; // timer for red and green light
volatile int t10= 1000; // timer for yellow light
volatile int pedTime= 2000; // timer for ped crossing

enum trafLightState {trafGreen, trafRed,   trafYellow1,  trafYellow2};

trafLightState tState;

enum pedLightState {pedRed, pedGreen};

pedLightState pState;

void setup()
{ 	
    Serial.begin(9600);// communication
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

}

void loop()
{
    communication();

    if (pedButton == true)
    {
      pState = pedGreen;
      tState = trafRed; // case red traffic light
      
      trafStateMachine();
      pedStateMachine();
      
      pedButton = false;
    } 
  
   else
  {
	if (tState == trafGreen)  
    {
/* for the sake of a fast transition i replaced 10 times by 2 and 5 times by 1s */
      t20=2000;
      t10= 1000;	
      pState = pedRed;
	  trafStateMachine();
      pedStateMachine();
    } 
     
      trafStateMachine();
      pedStateMachine();
   }
}
void communication()
{
 if(Serial.available()>0)
      {
        Serial.readBytes(signal,1);  
      }
        if(signal[0] == 'g' || signal[0] == 'r'|| signal[0] == 'y'|| signal[0] == 'Y')
          {
            Serial.print(" the other arduino state is:\t ");
            Serial.println(signal);
        }

        if(signal[0] == 'g'|| signal[0] == 'y')
         {
              iAmGreen = true;
              Serial.println(redFlag);
              tState = trafRed;
             
          }
          else
          {
            if(signal[0] == 'r' || signal[0] == 'Y')
            {
              iAmGreen = false;
              Serial.println(greenFlag);

            }
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
      
          Serial.write('r');
          Serial.println();
    	  Serial.println("I am red now");
          delay (t20);

          digitalWrite(redLed, LOW);

      	 if (pedButton == false && iAmGreen == false)
          {
            tState = trafYellow1;
          }
      
      break;

       case trafYellow1:

          digitalWrite(redLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
      
          Serial.write('y');
          Serial.println();
          Serial.println(" I am switching to green");
      
          delay (t10);
      	  digitalWrite(yellowLed, LOW);

          

          tState = trafGreen;
      

        break;

		case trafGreen:
		  digitalWrite(pedRedLed, HIGH);
      
          digitalWrite(yellowLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(greenLed, HIGH);
      
          Serial.write('g'); 
          Serial.println();
          Serial.println(" I am green now");

          delay (t20);

          digitalWrite(pedRedLed, LOW);
      	  digitalWrite(greenLed, LOW);
                   
      	  tState = trafYellow2;
      
        break;
      
      case trafYellow2:

          digitalWrite(redLed, LOW);
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
          
      
          Serial.write('Y');
          Serial.println();
          Serial.println(" I am switching to red");
      
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
          delay(pedTime);
          digitalWrite(pedRedLed, LOW);
          
        if(pedButton == true)
        {  
          pState = pedGreen;
        }
		  break;
      
       case pedGreen:
          
          digitalWrite(redLed, HIGH);
      
          Serial.write('r');
          Serial.println();
    	  Serial.println("I am red now");

          digitalWrite(pedRedLed, LOW);
          digitalWrite(pedGreenLed, HIGH);
          delay(pedTime);
      	  digitalWrite(redLed, LOW);
          digitalWrite(pedGreenLed, LOW);
          
      	 
      	  
      	  pState = pedRed ;
      
		  break;
       default:
        break;
    }

}