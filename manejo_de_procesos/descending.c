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
#include <sys/wait.h>


void level(int num, int start);

int main(int argc, char* argv[]) {
  int num, start=0;
  if (argc != 2) {
		fprintf(stderr, "usage: %s number\n", argv[0]);
		return -1;
	}
  num = atoi(argv[1]);
  if (num < 1) {
    fprintf(stderr, "%s: the parameter must be a positive integer number\n", argv[0]);
    return -2;
  }
  level(num,start);

  return 0;
}

void level(int num, int start){
  int pid,i,j;
  if(num==start){
      sleep(1);
      for (i = 0; i < start; i++) {
        printf("\t");
      }
      //printf("PPID = %i PID = %i NIVEL = %i\n",start,start, start);
      printf("PPID = %i PID = %i NIVEL = %i\n",getppid(),getpid(), start);
      exit(0);

  }else{
    for (j = 0; j < start; j++){
       printf("\t");
     }
     //printf("PPID = %i PID = %i NIVEL = %i\n",start,start, start);
    printf("PPID = %i PID = %i NIVEL = %i\n",getppid(),getpid(), start);
    for(i=0; i<start+1; i++){
      if((pid=fork())<0){
        perror("fork");
        exit(-3);

      }else if(pid==0){
        level(num, ++start);
      }else{
        sleep(1);
        wait(NULL);
      }
    }
    exit(0);
  }


}
