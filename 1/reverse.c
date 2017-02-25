#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void getparams(int argc, char **argv, char **inname);

void getfilehandles(char *inname, char *outname, int *infd, int *outfd);

void reverse(int infd, int outfd);

int main(int argc, char **argv)
{

  char *inname;
  int infd;
  int outfd;

  getparams(argc, argv, &inname);
  //Set Outname:
  char *suffix = ".rev";
  char outname[strlen(inname)+strlen(suffix)+1];
  strcpy(outname, inname);
  strcat(outname, suffix);

  getfilehandles(inname, outname, &infd, &outfd);
  
  reverse(infd, outfd);

  if (close(outfd) == -1) {
    //printf("%d %d",errno, EBADF);
    perror("Fehler beim Schließen der Ausgabedatei");
    exit(EXIT_FAILURE);
  }

  if (close(infd) == -1) {
    perror("Fehler beim Schließen der Eingabedatei");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, char **inname)
{
  int opterrflag = 0;
  int opt;

  if (optind < argc) {
    *inname = argv[optind++];
  } else {
    opterrflag = 1;
  }

  if (opterrflag) {
    fprintf(stderr,
            "Benutzung:\n"
            "\n"
            "  %s <Eingabedatei>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

void getfilehandles(char *inname, char *outname, int *infd, int *outfd)
{
	*infd = open(inname, O_RDONLY);
  *outfd = open(outname, O_WRONLY| O_APPEND);
  if(*outfd != -1){
    fprintf(stderr, "Zieldatei %s existiert bereits! UEberschreiben?\n[y] zum bestaetigen\n", outname);
    char x = ' ';
    scanf("%c", &x);
    if (x != 'y'){
      perror("Abbruch");
      exit(EXIT_FAILURE);
    }
    else {
      *outfd = open(outname, O_WRONLY | O_CREAT);
    }
  }
}

void reverse(int infd, int outfd)
{
  char Buf = '\0';
  lseek(infd,-1,SEEK_END);
  do{
    read(infd,&Buf,1);
    lseek(infd,-1,SEEK_CUR);
    printf("%c", Buf);
    write(outfd,&Buf,1);
  }while(0 != lseek(infd,-1,SEEK_CUR));
  read(infd,&Buf,1);
  write(outfd,&Buf,1);
}
