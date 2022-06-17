// C++ code
//
#define redLed 9
#define greenLed 7
#define yellowLed 8
 
volatile int t20= 0; // timer for red and green light
volatile int t10= 0; // timer for yellow light

enum lightState { redYellow, yellowGreen };

lightState state;

void setup()
{
	pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
	pinMode(greenLed, OUTPUT);

}



void loop()
{
  t20 = 3000;
  t10 = 1000;
  stateMachine();
  
}

void stateMachine()
{
	switch(state)
    { 
       case redYellow:
      
          digitalWrite(redLed, HIGH);
          delay (t20);
          digitalWrite(redLed, LOW);

          digitalWrite(yellowLed, HIGH);
          delay (t10);
          digitalWrite(yellowLed, LOW);
		  
      	  state = yellowGreen;
      
		  break;

       case yellowGreen:

          /*digitalWrite(yellowLed, HIGH);
          delay (t10);
          digitalWrite(yellowLed, LOW);*/

          digitalWrite(greenLed, HIGH);
          delay (t20);
          digitalWrite(greenLed, LOW);
          
          digitalWrite(yellowLed, HIGH);
          delay (t10);
      	  digitalWrite(yellowLed, LOW);

          state = redYellow;
      
        break;



       default:
        break;
    }
 }

