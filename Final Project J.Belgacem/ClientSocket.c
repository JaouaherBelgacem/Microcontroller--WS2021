#include <stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#include <stdbool.h>
#include <string.h>
#define red 100
#define yellow 101
#define green 110


#pragma comment(lib,"ws2_32.lib") //Winsock Library

/*

    TCP SOCKET ---- client-----

*/
int stateCar;
char RecvBuffer[512];
bool iAmGreen = false;
char greenLight [10]= "green";
char SenderBuffer[512];

void carLine ( )
{
    switch (stateCar)
    {
        case red:
            printf("RED is on\n");
            printf ("YELLOW is off  \n");
            printf ("GREEN is off \n\n");
            if (iAmGreen == true)
            {
            stateCar = yellow;
            }
        break;

       case yellow:

            printf("RED is off \n");
            printf ("YELLOW is on\n");
            printf ("GREEN is off \n\n");


            stateCar = green;

        break;

		case green:

            printf("RED is off\n");
            printf ("YELLOW is off\n");
            printf ("GREEN is on\n\n");

            stateCar = red;

        break;

       default:
        break;


    }
}
int main()
{
   printf("\t\t----TCP CLIENT HERE----\n");

   //local variables

   WSADATA winsockdata;
   int iWsaStartup;
   int iWsaCleanup;

   SOCKET TCPClientSocket;
   int iCloseSocket;

   struct sockaddr_in TCPServerAdd;
   //struct sockaddr_in TCPClientAdd;
  // int iTCPClientAdd= sizeof (TCPClientAdd);

   int iConnect;

   int iRecv;
//   char RecvBuffer[512];
   int iRecvBuffer = strlen(RecvBuffer)+1;

   int iSend;
   char SenderBuffer[512];
   //char SenderBuffer = 'L';
   int iSenderBuffer = strlen (SenderBuffer)+1;



   //Step1 using WSAStartUp func
   iWsaStartup = WSAStartup(MAKEWORD (2,2), &winsockdata);
   if(iWsaStartup !=0)
   {
       printf(" WSAStartUp Failed\n");
   }

   printf(" WSAStartUp Success\n");


   //Step2 Socket Creation

   TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(TCPClientSocket == INVALID_SOCKET)
   {
        printf("Could not create socket : %d\n" , WSAGetLastError());

   }
    else
    {
        printf(" TCP SOCKET CREATION SUCCESS \n");
    }
    //Step Fill the structure

   TCPServerAdd.sin_family = AF_INET;
   TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
   TCPServerAdd.sin_port = htons(8000);

   //Step4 Connect Func
   iConnect = connect(TCPClientSocket,(SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
   if(iConnect == SOCKET_ERROR)
   {
       printf("Connection Failed and Error No : %d\n" , WSAGetLastError());
   }
    else
   {
       printf(" Connection Sucess\n");
   }
   //for(;;)
 //  {
      carLine();
    //Step5 Recv Data from Client

    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
    if(iRecv == SOCKET_ERROR)
    {
        printf("Receiving data Failed : %d\n" , WSAGetLastError());
    }
    else
     {
         printf("Data Received \t\n", RecvBuffer);
     }
     if (strcmp(RecvBuffer, greenLight)!= 0)
     {
         iAmGreen = true;
         SenderBuffer [512]= "I am not allowed to switch";
     }
     else
     {
         SenderBuffer [512]="I am allowed to switch";
     }

    //Step6 Send Data to server
    iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR )
    {
        printf("Sending Failed : %d\n" , WSAGetLastError());
    }
    else
    {
        printf("Sending Success\n", SenderBuffer);
    }
   //}
    //Step7 Close Socket
    iCloseSocket = closesocket(TCPClientSocket);
    if(iCloseSocket == SOCKET_ERROR)
    {
        printf("Closing Socket Failed : %d\n" , WSAGetLastError());
    }
      else
       {
           printf("Closing Socket Success\n");
       }
    //Step8 CleanUp Socket
    iWsaCleanup = WSACleanup();
    if(iWsaCleanup == SOCKET_ERROR)
    {
        printf("CleanUp Failed : %d\n" , WSAGetLastError());

    }
    else
    {
        printf("CleanUp Success\n");
    }
	return 0;
}

