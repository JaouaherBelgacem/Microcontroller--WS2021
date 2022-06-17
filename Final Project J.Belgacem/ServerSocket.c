#include <stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#include <stdbool.h>
#define red 100
#define yellow 101
#define green 110


#pragma comment(lib,"ws2_32.lib") //Winsock Library

/*

    TCP SOCKET

*/
int stateCar;
char SenderBuffer[512];
bool iAmGreen = false;

void carLine ( )
{
    switch (stateCar)
    {
        case red:
            printf("RED is on\n");
            printf ("YELLOW is off  \n");
            printf ("GREEN is off \n\n");
            SenderBuffer [512] = "red";

            stateCar = yellow;
        break;

       case yellow:

            printf("RED is off \n");
            printf ("YELLOW is on\n");
            printf ("GREEN is off \n\n");

            SenderBuffer[512] ="yellow";

            stateCar = green;

        break;

		case green:

            printf("RED is off\n");
            printf ("YELLOW is off\n");
            printf ("GREEN is on\n\n");

            SenderBuffer [512] = "green";
            stateCar = red;

        break;

       default:
        break;


    }
}
int main()
{

   printf("\t\t----TCP SERVER HERE----\n");


   WSADATA winsockdata;
   int iWsaStartup;
   int iWsaCleanup;

   SOCKET TCPServerSocket;
   int iCloseSocket;

   struct sockaddr_in TCPServerAdd;
   struct sockaddr_in TCPClientAdd;
   int iTCPClientAdd= sizeof (TCPClientAdd);

   int iBind;

   int iListen;

   SOCKET sAcceptSocket;

   int iSend;
   //char SenderBuffer = 'H';
   int iSenderBuffer = strlen (SenderBuffer)+1;

   int iRecv;
   char RecvBuffer[512];
   int iRecvBuffer = strlen(RecvBuffer)+1;

   //Step1 using WSAStartUp func
   iWsaStartup = WSAStartup(MAKEWORD (2,2), &winsockdata);
   if(iWsaStartup !=0)
   {
       printf(" WSAStartUp Failed\n");
   }
    else {
           printf(" WSAStartUp Success\n");
    }

   //Step2 Fill the structure

   TCPServerAdd.sin_family = AF_INET;
   TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
   TCPServerAdd.sin_port = htons(8000);

   //Step3 Socket Creation

   TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if(TCPServerSocket == INVALID_SOCKET)
   {
        printf("Could not create socket : %d\n" , WSAGetLastError());

   }
    else
    {
        printf(" TCP SOCKET CREATION SUCCESS \n");

    }

   //Step4 Bind Func
   iBind = bind(TCPServerSocket,(SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
   if(iBind == SOCKET_ERROR)
   {
       printf("Binding Failed and Error No : %d\n" , WSAGetLastError());
   }
    else
    {
           printf(" Binding Sucess\n");

    }

   //Step5 Listen Func
   iListen = listen(TCPServerSocket ,2);
   if(iListen == SOCKET_ERROR)
   {
       printf("Listening Failed and Eroor NO : %d\n" , WSAGetLastError());
   }
   else{

        printf(" Listening Success\n");
   }

    //step6 Accept Func
    sAcceptSocket = accept(TCPServerSocket,(SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if(sAcceptSocket == INVALID_SOCKET)
    {
        printf("Accept Failed : %d\n" , WSAGetLastError());
    }
    else
    {
            printf("Accept Success\n");
    }
//for (;;)
//{
    carLine();

    //Step7 Send Data to Client
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR )
    {
        printf("Sending Failed : %d\n" , WSAGetLastError());
    }
    else
    {
        printf("Sending Success\n", SenderBuffer);
    }


    //Step8 Recv Data from Client
    iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
    if(iRecv == SOCKET_ERROR)
    {
        printf("Receiving data Failed : %d\n" , WSAGetLastError());
    }
    else
    {
             printf("Data Received \t\n", RecvBuffer);
    }

//}

    //Step9 Close Socket
    iCloseSocket = closesocket(TCPServerSocket);
    if(iCloseSocket == SOCKET_ERROR)
    {
        printf("Closing Socket Failed : %d\n" , WSAGetLastError());
    }
    else
    {
            printf("Closing Socket Sucess\n");
    }
    //Step10 CleanUp Socket
    iWsaCleanup = WSACleanup();
    if(iWsaCleanup == SOCKET_ERROR)
    {
        printf("CleanUp Failed : %d\n" , WSAGetLastError());

    }
    else
    {
            printf("CleanUp Success\n");
    }
}

