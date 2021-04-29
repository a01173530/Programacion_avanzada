/*----------------------------------------------------------------
*
* Programación avanzada: Examen 2
* Fecha: 20-04-2021
* Autor: Adrián Torres Hernández A01173530
*
*
*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
typedef unsigned char uchar;
typedef unsigned long ulong;


void recursiva(char *directory, char*filename , char* program ){
  DIR* dir;
  struct dirent* entry;
  struct stat info;
  char pathname[PATH_MAX + NAME_MAX + 1];
  int pid;

  if ((dir=opendir(directory)) ==NULL) {
    perror(program);
    exit(-2);

  }

  while( (entry = readdir(dir)) != NULL){
    if(strcmp(filename, entry->d_name)== 0){
      //printf("%s: %s\n", filename,directory);
      //The process 278 found file file1 in directory dir1
      printf("The process %i found file %s in directory %s\n", getpid(), filename,directory);
      break;

    }
  }

  rewinddir(dir);

  while( (entry = readdir(dir)) != NULL){
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
      sprintf(pathname, "%s/%s",directory, entry->d_name );
      lstat(pathname, &info);
      //stat(entry->d_name, &info);
      if((info.st_mode & S_IFMT) == S_IFDIR){
        if((pid=fork())<0){
          exit(-1);
        }else if(pid==0){
          recursiva(pathname,filename, program);
        }else{
          wait(NULL);
        }
      }
    }

  }

  closedir(dir);

}


int main(int argc, char* argv[]) {
   char directory[PATH_MAX + 1];

  if (argc <2  || argc > 3 ) {
    printf("usage: %s file [directory]\n", argv[0]);
    return -1;
  }
  getcwd(directory, PATH_MAX);
  if (argc == 3) {
    strcpy(directory, argv[2]);
  }
  recursiva(directory, argv[1], argv[0]);
  return 0;
}
