
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
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

typedef unsigned char uchar;

uchar decripta( uchar alt_buffer);

int main(int argc, char* argv[]) {
  int byte, in, out;
  uchar alt_buffer;

  if (argc != 3) {
    printf("usage: %s origen destination\n", argv[0]);
    return -1;
  }

  if ( (in = open(argv[1], O_RDONLY)) < 0 ) {
    perror(argv[0]);
    return -2;
  }

  if ( (out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0 ) {
    perror(argv[0]);
    return -3;
  }


  while ( (byte = read(in, &alt_buffer, sizeof(uchar) )) != 0) {
    alt_buffer = decripta(alt_buffer);
    write(out, &alt_buffer, byte);
  }

	close(in);
	close(out);
  printf("done\n");

  return 0;
}

uchar decripta( uchar alt_buffer)
{
  uchar left = (alt_buffer & 0x000F) << 4;
  uchar right = (alt_buffer & 0xF0) >> 4;
  uchar result = left | right;
  return result;
}
