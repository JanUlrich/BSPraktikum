#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <time.h>

void getFileSizes(char *dirname, int* stats);
int isDirectory(char* name);
void printFileStats(char* dir, char *filename);
char getFileType(mode_t fileMode);
void updateFileSizeStats(char* fileName, int* stats);

void getparams(int argc, char **argv, char **startDir)
{
  if (optind < argc) {
    *startDir = argv[optind++];
  } else {
    *startDir = ".";
  }
}

int main(int argc, char **argv)
{
  char *inname;

  getparams(argc, argv, &inname);

  int stats[8];
  int i;
  for(i = 0; i<8; i++){
    stats[i]=0;
  }
  getFileSizes(inname, stats);

  printf("%d Dateien kleiner als 512 Bytes\n", stats[0]);
  printf("%d Dateien kleiner als %d KiB\n", stats[1], 1);
  printf("%d Dateien kleiner als %d KiB\n", stats[2], 2);
  printf("%d Dateien kleiner als %d KiB\n", stats[3], 4);
  printf("%d Dateien kleiner als %d KiB\n", stats[4], 8);
  printf("%d Dateien kleiner als %d KiB\n", stats[5], 64);
  printf("%d Dateien kleiner als 1 MiB\n", stats[6]);
  printf("%d Dateien größer als 1 MiB\n", stats[7]);

  return EXIT_SUCCESS;
}

void getFileSizes(char *dirname, int* stats){
  DIR* directory = opendir(dirname);
  if(errno == ENOTDIR){ //Just a single file:
    updateFileSizeStats(dirname, stats);
  }else if(errno){
    //Other error. Just ignore!
    fprintf(stderr, "Error %d\n", errno);
  }else{
    struct dirent* d;
    while(1){
      d = readdir(directory);
      if(d == NULL)break;
    
      char* sep = "/";
      char subDirName[strlen(dirname)+strlen(sep)+strlen(d->d_name)];
      strcpy(subDirName, dirname);
      strcat(subDirName, sep);
      strcat(subDirName, d->d_name);

      updateFileSizeStats(subDirName, stats);
      
      if(strcmp(d->d_name,".")!=0 && strcmp(d->d_name,"..")!=0){
        if(isDirectory(subDirName)){
          getFileSizes(subDirName, stats);
        }
      }
    }

    closedir(directory);
  }
}

int isDirectory(char* name){
  struct stat s;
  stat(name, &s);
  if(errno)return 0;
  if(S_ISDIR(s.st_mode))return 1;
  return 0;
}

void updateFileSizeStats(char* fileName, int* stats){
  struct stat s;
  stat(fileName, &s);
  int size = s.st_size;
  if(! S_ISREG(s.st_mode))return; //nur reguläre Dateien
  if(size < 512){
    stats[0]++;
  }else if(size < 1024){
    stats[1]++;
  }else if(size < 2048){
    stats[2]++;
  }else if(size < 1024*4){
    stats[3]++;
  }else if(size < 1024*8){
    stats[4]++;
  }else if(size < 1024*64){
    stats[5]++;
  }else if(size < 1024*1024){
    stats[6]++;
  }else{
    stats[7]++;
  }
}