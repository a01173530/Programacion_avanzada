#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

/*----------------------------------------------------------------
*
* Programación avanzada: Examen 1
* Fecha: 2-Sep-2015
* Autor: A01173530 Adrián Torres Hernández
*
*--------------------------------------------------------------**/

typedef unsigned char uchar;
char buffer[1028];

int main(int argc, char* argv[]) {
  int bytes, source, destination, num1=0, num2;

  //if ((argc != 3) || (argc != 5 ))
  if (argc < 3 || argc > 5 ) {
    printf("usage: %s source destination [start] [end]\n", argv[0]);
    return -1;
  }

  if ( (source = open(argv[1], O_RDONLY)) < 0 ) {
    perror(argv[0]);
    return -2;
  }
  num2=lseek(source,0,SEEK_END);
  lseek(source,0,SEEK_SET);

  if ( (destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0 ) {
    perror(argv[0]);
    return -3;
  }
  if(argc==4){
    num1=atoi(argv[3]);
  }
  if(argc==5){
    num2=atoi(argv[4]);
  }

  if (num1 < 0) {
  printf("%s: start must be a positive number\n", argv[0]);
  return -4;
  }

  if (num2 < 1) {
  printf("%s: end must be a positive number\n", argv[0]);
  return -5;
  }
  int size=num2-num1;
  while (size>0 && (bytes = read(source, buffer, 1028)) != 0) {
    write(destination, buffer, bytes);
    size=size-bytes;
  }

  printf("copying from position %i to position %i\n", num1, num2);

  close(source);
  close(destination);

  return 0;
}
