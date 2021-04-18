#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

typedef unsigned char uchar;

char decripta( char alt_buffer);

int main(int argc, char* argv[]) {
  int byte, in, out;
  char alt_buffer;

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
  in = open(argv[1],O_RDONLY);
  out = open(argv[2],O_WRONLY);

  while ( (byte = read(in, &alt_buffer, sizeof(char) )) != 0) {
    alt_buffer = decripta(alt_buffer);
    write(out, &alt_buffer, byte);
  }

	close(in);
	close(out);
  printf("done\n");

  return 0;
}

char decripta( char alt_buffer)
{
   int left_arg=4;
   int right_arg=4;
    return ( (alt_buffer & 0x0F)<<left_arg | (alt_buffer & 0xF0)>>right_arg );
}
