/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de archivos
* Fecha: 2-Mar-2021
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
#include <time.h>
#include <pwd.h>
#include <grp.h>


void normal(char *directory, char*filename, char* program ){
  DIR* dir;
  struct dirent* entry;
  struct stat info;
  if ((dir=opendir(directory)) ==NULL) {
    perror(program);
    exit(-2);

  }

  while( (entry = readdir(dir)) != NULL){

    if(strstr( entry->d_name,filename)!=NULL){
      //printf("%s: %s\n", filename,directory);
      printf("Name: %s \nPath: %s\n\n", entry->d_name,directory);
      //break;

    }
  /*  if(strcmp(filename, entry->d_name)==0){
      printf("%s: %s\n", filename,directory);
      break;
    }*/
  }

  closedir(dir);

}


void recursiva(char *directory, char*filename , char* program ){
  DIR* dir;
  struct dirent* entry;
  struct stat info;
  char pathname[PATH_MAX + NAME_MAX + 1];


  if ((dir=opendir(directory)) ==NULL) {
    perror(program);
    exit(-2);

  }

  while( (entry = readdir(dir)) != NULL){
    if(strstr( entry->d_name,filename)!=NULL){
      //printf("%s: %s\n", filename,directory);
      printf("Name: %s \nPath: %s\n\n", entry->d_name,directory);
      //break;

    }
  }

  rewinddir(dir);

  while( (entry = readdir(dir)) != NULL){
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
      sprintf(pathname, "%s/%s",directory, entry->d_name );
      if(stat(pathname, &info)<0){
        perror("stat");
        printf("%s\n",entry->d_name);

      }
      //stat(entry->d_name, &info);
      if((info.st_mode & S_IFMT) == S_IFDIR){
        recursiva(pathname,filename, program );
      }
    }

  }


  closedir(dir);

}



int main(int argc, char* argv[]) {
  char directory[PATH_MAX + 1];
  if (argc <3  || argc > 4 ) {
    printf("usage: %s string initial_directory [-r]\n", argv[0]);
    return -1;
  }
  getcwd(directory, PATH_MAX);

  if (argc== 3) {
    strcpy(directory,argv[2]);
    normal(directory,argv[1], argv[0]);
  }

  if (argc == 4) {

		if (strcmp(argv[3], "-r") == 0) {
      strcpy(directory,argv[2]);
      recursiva(directory,argv[1], argv[0]);

		}else{
      printf("usage: %s string initial_directory [-r]\n", argv[0]);
      return -3;

    }
	}


  return 0;
}
