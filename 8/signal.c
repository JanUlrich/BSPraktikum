#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 100

void getparams(int argc, char **argv, int *stripes);
void registerParentSignals();
void registerChildSignals();
void sendByte(unsigned char b, int toPid);
void sendSignal(int id, int sig);
void signal_ACK(int signum);
void signal_RECV(int signum);
void registerStartUpSignals();

int id = 0;
int pid;

//CHILD:
volatile char status = 0;

//PARENT:
int recvCounter = 0;
char recvByte = 0;
char* recvData;

void signal_ACK(int signum)
{
  if(signum==SIGUSR1){
    status = 1;
  }
}

void signal_RECV(int signum)
{
  int recvBit;
  if(signum==SIGUSR1){
    recvBit = 0;
  }
  if(signum==SIGUSR2){
    recvBit = 1;
  }
  printf("%d\n", recvBit);
  recvByte += recvBit << recvCounter%8;
  recvCounter++;
  if(recvCounter%8==0){ //ganzes Byte empfangen:
    if(recvByte == 0){//Ende der Übertragung

    }
    recvData[recvCounter/8 - 1] = recvByte;
    recvByte = 0;
  }
  //Bereit für Übertragung nächstes bit:
  kill(id, SIGUSR1);
}

int main(int argc, char **argv)
{
  recvData = alloca(sizeof(char)*MAX_LENGTH);
  registerStartUpSignals();

  int fid = fork();
  if(fid == -1){
    fprintf(stderr, "Fehler bei Fork!\n");
    return EXIT_FAILURE;
  }

  if(fid == 0){//CHILD
    pid = getppid();//Diese Funktion ist immer erfolgreich
    registerChildSignals();
    sendByte(123,pid);
  }else{//PARENT
    id = fid;
    while(1);
  }

	return EXIT_SUCCESS;
}

void sendByte(unsigned char b, int toPid){
  for(int i = 0; i<8;i++){
    int mask = 1 << i;
    int bit = (b & i)/i;
    sendSignal(toPid, bit);
  }
}

void sendSignal(int id, int sig){
  while(status == 0);
  if(sig == 0){
    kill(id, SIGUSR1);
  }else{
    kill(id, SIGUSR2);
  }
  status = 0;
}

void registerParentSignals(){
  signal(SIGUSR1, signal_RECV);
  signal(SIGUSR2, signal_RECV);
  kill(id,SIGUSR1);
}

void registerChildSignals(){
  signal(SIGUSR1, signal_ACK);
  kill(pid,SIGUSR1);
}


void signal_START(int signum)
{
  if(signum==SIGUSR1){
    registerParentSignals();
  }
}


void registerStartUpSignals(){
  signal(SIGUSR1, signal_START);
}