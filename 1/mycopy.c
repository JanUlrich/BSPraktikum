#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void getparams(int argc, char **argv, size_t *buflen, char **inname,
               char **outname);

void getfilehandles(char *inname, char *outname, int *infd, int *outfd);

void copy(int infd, int outfd, size_t buflen);

int main(int argc, char **argv)
{

  char *inname;
  char *outname;
  size_t buflen;
  int infd;
  int outfd;

  getparams(argc, argv, &buflen, &inname, &outname);
  getfilehandles(inname, outname, &infd, &outfd);
  
  copy(infd, outfd, buflen);

  if (close(outfd) == -1) {
    perror("Fehler beim Schließen der Ausgabedatei");
    exit(EXIT_FAILURE);
  }

  if (close(infd) == -1) {
    perror("Fehler beim Schließen der Eingabedatei");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, size_t *buflen, char **inname,
               char **outname)
{
  int opterrflag = 0;
  int opt;

  /* Standard-Wert */
  *buflen = 1;

  /* Kommandozeilenoptionen verarbeiten */
  while ((opt = getopt(argc, argv, "b:")) != -1) {
    switch (opt) {
    case 'b':
      opterrflag = sscanf(optarg, "%zu", buflen) != 1 || *buflen <= 0
        || *buflen >= 1024 * 1024;
      break;
    case '?':
      opterrflag = 1;
      break;
    }
  }

  if (optind < argc) {
    *inname = argv[optind++];
  } else {
    opterrflag = 1;
  }

  if (optind < argc) {
    *outname = argv[optind];
  } else {
    opterrflag = 1;
  }

  if (opterrflag) {
    fprintf(stderr,
            "Benutzung:\n"
            "\n"
            "  %s [-b n] <Eingabedatei> <Ausgabedatei>\n"
            "\n" "b[=1]: Puffergröße mit 0 < n <= 1024^2\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

void getfilehandles(char *inname, char *outname, int *infd, int *outfd)
{
	*infd = open(inname, O_RDONLY);
	*outfd = open(outname, O_WRONLY);
  if(*outfd != -1){
    fprintf(stderr, "Zieldatei %s existiert bereits! Überschreiben?\n[y] zum bestätigen", outname);
    char x = ' ';
    scanf("%c", &x);
    if (x != 'y'){
      perror("Abbruch");
      exit(EXIT_FAILURE);
    }
    else {
      *outfd = open(outname, O_WRONLY | O_CREAT | O_APPEND);//Für die new file sind die Rechte notwendig
    }
  }
}

void copy(int infd, int outfd, size_t buflen)
{
	ssize_t numRead = 0;//init
	char buf[buflen];
	do{
		numRead = read(infd, buf, buflen); // Am Ende einer File steht die NULL, als 0 überschrieben
		write(outfd, buf, buflen);         // Dementsprechend solange in die neue File schreiben
	}while(numRead > 0);//solange es einen Bitstrom gibt, ist numRead > 0
}
