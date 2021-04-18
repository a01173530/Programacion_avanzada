/*----------------------------------------------------------------
*
* Programación avanzada: Manejo de señales
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
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
typedef unsigned char uchar;
typedef unsigned long ulong;

char *buf1;
char *buf2;
char *buf3;


char *cmd11;
char *cmd12;
char *cmd21;
char *cmd22;
char *cmd31;
char *cmd32;


void handler_sigusr1(int sig) {
  int pid;
  //printf("ejecutando SIGUSR1\n");
  if((pid=fork())<0){
    exit(-8);
  }
  else if(pid==0){
    execlp(cmd11,cmd12,NULL);
    printf("\n");

  }else{
    wait(NULL);

  }

}

void handler_sigusr2(int sig) {
  int pid;
  if((pid=fork())<0){
    exit(-9);
  }
  else if(pid==0){
    execlp(cmd21,cmd22,NULL);

    printf("\n");

  }else{
    wait(NULL);

  }

}

void handler_sigpwr(int sig) {
  int pid;
  if((pid=fork())<0){
    exit(-10);
  }
  else if(pid==0){
    execlp(cmd31,cmd32,NULL);
    printf("\n");

  }else{
    wait(NULL);

  }

}

void handler_sigint(int sig) {
   fprintf(stderr, "Ending...\n");
   free(buf1);
   free(buf2);
   free(buf3);
   exit(0);
}


int main(int argc, char* argv[]) {
	int f1,f2,f3;
  ulong tam;
  struct stat info;

	if (argc != 4) {
		fprintf(stderr, "usage: %s file1 file2 file3\n", argv[0]);
		return -1;
	}
  if ( (f1 = open(argv[1], O_RDONLY)) < 0 ) {
    fprintf(stderr, "%s: the file %s does not exist\n", argv[0],argv[1]);
    return -2;
  }

  if ( (f2 = open(argv[2], O_RDONLY)) < 0 ) {
    fprintf(stderr, "%s: the file %s does not exist\n", argv[0],argv[2]);
    return -3;
  }

  if ( (f3 = open(argv[3], O_RDONLY)) < 0 ) {
    fprintf(stderr, "%s: the file %s does not exist\n", argv[0],argv[3]);
    return -4;
  }

  tam= lseek(f1,0,SEEK_END);
  //printf("%li \n", tam);
  if ( tam <= 0 ) {
    fprintf(stderr, "%s: the file %s is empty\n", argv[0],argv[1]);
    return -5;
  }
  lseek(f1,0, SEEK_SET);
  buf1= (char*) malloc(sizeof(char)*tam);
  read(f1,buf1,tam);
  //printf("%s \n", buf1);
  cmd11=strtok(buf1, ",");
  cmd12=strtok(NULL, ",");
  //printf("%s %s \n", cmd11,cmd12);

  tam= lseek(f2,0,SEEK_END);
  //printf("%li \n", tam);
  if ( tam <= 0 ) {
    fprintf(stderr, "%s: the file %s is empty\n", argv[0],argv[2]);
    return -6;
  }
  lseek(f2,0, SEEK_SET);
  buf2= (char*) malloc(sizeof(char)*tam);
  read(f2,buf2,tam);
  //printf("%s \n", buf2);
  cmd21=strtok(buf2, ",");
  cmd22=strtok(NULL, ",");
  //printf("%s %s \n", cmd21,cmd22);


  tam= lseek(f3,0,SEEK_END);
  //printf("%li \n", tam);
  if ( tam <= 0 ) {
    fprintf(stderr, "%s: the file %s is empty\n", argv[0],argv[3]);
    return -6;
  }
  lseek(f3,0, SEEK_SET);
  buf3= (char*) malloc(sizeof(char)*tam);
  read(f3,buf3,tam);
  //printf("%s \n", buf3);
  cmd31=strtok(buf3, ",");
  cmd32=strtok(NULL, ",");
  //printf("%s %s \n", cmd31,cmd32);







  signal(SIGUSR1,handler_sigusr1);
  signal(SIGUSR2,handler_sigusr2);
  signal(SIGPWR,handler_sigpwr);
  signal(SIGINT, handler_sigint);

  //printf("ok\n");

  fprintf(stderr, "Waiting for a signal...\n");

  while(1){
    pause();
  }

/*  close(f1);
	close(f2);
	close(f3);*/

	return 0;
}
