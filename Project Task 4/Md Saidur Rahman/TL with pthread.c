#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


void* trafficLight (void* buttonState);
void* pedastrianLight(void* buttonState);




int main()
{
    srand(time(NULL));
    int buttonState = rand()%2 ;

    pthread_t traffic, pedestrian;
    pthread_create (&traffic, NULL, trafficLight, buttonState);
    pthread_create (&pedestrian, NULL, pedastrianLight, buttonState);
    pthread_join(traffic, NULL);
    pthread_join(pedestrian, NULL);

}

void* trafficLight (void* buttonState)
{
  int state;
  state= (int) buttonState;

 while (state==0)
  {
  printf("Traffic GREEN\n");
  sleep (2);
  printf("Traffic YELLOW\n");
  sleep (2);
  printf("Traffic RED\n");
  sleep (2);
  printf("Traffic YELLOW\n");
  sleep (2);
  }

 while (state==1)
  {
  printf("Traffic RED\n");
  sleep (2);
  }

}

void* pedastrianLight(void* buttonState)
{
  int state;
  state= (int) buttonState;

 while (state==0)
  {
  printf("Pedestrian RED\n");
  sleep (2);
  }

 while (state==1)
  {
  printf("Pedestrian GREEN\n");
  sleep (2);
  }

}
