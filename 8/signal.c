#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <stdint.h>

#define MAX_LENGTH 100


void getparams(int argc, char **argv, int *stripes);
void registerParentSignals();
void registerChildSignals();
void sendByte(uint8_t b, int toPid);
void sendSignal(int id, int sig);
void signal_ACK(int signum);
void signal_RECV(int signum);

int id = 0;
int pid;

//CHILD:
char status = 0;

//PARENT:
int recvCounter = 0;
char recvByte = 0;

void signal_ACK(int signum)
{
    registerChildSignals();
    status = 1;
}

void signal_RECV(int signum)
{
  registerParentSignals();
  int recvBit;
  if(signum==SIGUSR1){
    recvBit = 0;
  }
  if(signum==SIGUSR2){
    recvBit = 1;
  }
  recvByte |= recvBit << (7-recvCounter);
  recvCounter++;
  if(recvCounter%8==0){ //ganzes Byte empfangen:
    if(recvByte == 0){//Ende der Übertragung
      printf("\n");
      exit(0);
    }
    recvCounter=0;
    putchar(recvByte);
    recvByte = 0;
  }
  //Bereit für Übertragung nächstes bit:
  kill(id, SIGUSR1);
}

int main(int argc, char **argv)
{
  int fid = 0;
  registerChildSignals();
  fid = fork();
  
  if(fid == -1){
    fprintf(stderr, "Fehler bei Fork!\n");
    return EXIT_FAILURE;
  }

  if(fid == 0){//CHILD
    registerChildSignals();
    pid = getppid();//Diese Funktion ist immer erfolgreich
    char* sendstring="Hallo Welt";
    while(*sendstring!='\0')
      sendByte(*sendstring++, pid);
    sendByte('\0',pid);
  }else{//PARENT
    id = fid;
    registerParentSignals();
    kill(fid, SIGUSR1); //Bereit zum Empfangen
    while(1){
      while(status == 0){
        sleep(1);
      }
    }
  }
  return EXIT_SUCCESS;
}

void sendByte(uint8_t b, int toPid){
  for(int i = 7; i>=0;i--){
    int mask = 1 << i;
    int bit = (b & mask);
    sendSignal(toPid, bit);
  }
}

void sendSignal(int id, int sig){
  while(status == 0){
    sleep(1);
  }
  status = 0;
  if(sig == 0){
    kill(id, SIGUSR1);
  }else{
    kill(id, SIGUSR2);
  }
}

void registerParentSignals(){
  signal(SIGUSR1, signal_RECV);
  signal(SIGUSR2, signal_RECV);
}

void registerChildSignals(){
  signal(SIGUSR1, signal_ACK);
}
