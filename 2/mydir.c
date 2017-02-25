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


void getparams(int argc, char **argv, char **dir);
void printDir(char *dirname);
int isDirectory(char* name);
void printFileStats(char* dir, char *filename);
char getFileType(mode_t fileMode);

int main(int argc, char **argv)
{

  char *inname;

  getparams(argc, argv, &inname);
  //getfilehandles(inname, outname, &infd, &outfd);
  
  printDir(inname);

  return EXIT_SUCCESS;
}

void printDir(char *dirname){
  DIR* directory = opendir(dirname);
  if(errno == ENOTDIR){ //Just show a single file:
      printFileStats("", dirname);
  }else if(errno){
    //Other error. Just ignore!
    fprintf(stderr, "Error %d\n", errno);
  }else{
    fprintf(stderr, "\n%s:\n", dirname);
    struct dirent* d;
    while(1){
      d = readdir(directory);
      if(d == NULL)break;
    
      char* sep = "/";
      char subDirName[strlen(dirname)+strlen(sep)+strlen(d->d_name)+1];
      strcpy(subDirName, dirname);
      strcat(subDirName, sep);
      strcat(subDirName, d->d_name);
      //fprintf(stderr, "Dir: %s\n", subDirName);

      printFileStats(dirname, d->d_name);
      
      if(strcmp(d->d_name,".")!=0 && strcmp(d->d_name,"..")!=0){
        if(isDirectory(subDirName))printDir(subDirName);
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

char *getUserNameForId(uid_t uid)
{
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}

void printFileStats(char* dirname, char *filename){
  char* sep = "/";
  char fullName[strlen(dirname)+strlen(sep)+strlen(filename)];
  strcpy(fullName, dirname);
  if(strlen(dirname)>0)strcat(fullName, sep);
  strcat(fullName, filename);

  struct stat s;
  stat(fullName, &s);

  char fileRights[100];
  if(isDirectory(fullName)){
    strcpy(fileRights, "d");
  }else{
    strcpy(fileRights, "-");
  }
  int multiplier;
  for(multiplier = 8*8;multiplier>=1;multiplier/=8){
    if(s.st_mode & (S_IROTH*multiplier)){
      strcat(fileRights, "r");
    }else{
      strcat(fileRights, "-");
    }
    if(s.st_mode & (S_IWOTH*multiplier)){
      strcat(fileRights, "w");
    }else{
      strcat(fileRights, "-");
    }
    if(s.st_mode & (S_IXOTH*multiplier)){
      strcat(fileRights, "x");
    }else{
      strcat(fileRights, "-");
    }
  }

  char* lastUsed = ctime(&s.st_mtime);
  if (lastUsed[strlen(lastUsed) - 1] == '\n') {
    //Chop of trailing \n :
    lastUsed[strlen(lastUsed) - 1] = '\0';
  }

  fprintf(stderr, "%s %s %s %8ld %s %s%c\n",
    fileRights, getUserNameForId(s.st_uid),
    getUserNameForId(s.st_gid), s.st_size,
    lastUsed,filename, getFileType(s.st_mode));
}

char getFileType(mode_t fileMode){
  if(S_ISSOCK(fileMode))return 's';
  if(S_ISLNK(fileMode))return '@';
  if(S_ISREG(fileMode))return ' ';
  if(S_ISFIFO(fileMode))return '|';
  if(S_ISDIR(fileMode))return '/';
  return ' ';
}

void getparams(int argc, char **argv, char **startDir)
{
  if (optind < argc) {
    *startDir = argv[optind++];
  } else {
    *startDir = ".";
  }
}
