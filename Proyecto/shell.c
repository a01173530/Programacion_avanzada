#include "header.h"



void mini_shell()
{
    char command_argv[BUFFER_MAX];
    char dir[PATH_MAX];

    prompt();


    while(fgets(command_argv,BUFFER_MAX, stdin)){
        if(command_argv[0] == '\n'){
            prompt();
            continue;
        }else if(strcmp(command_argv,"quit\n") == 0){
            break;
        }
        pipe_get_cmd(command_argv);
        prompt();
    }
    exit(0);
}


void execute_file(char *filepath){

    FILE *fp = fopen(filepath, "r");
    char buffer[BUFFER_MAX];

    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        if(strcmp(buffer,"quit\n") == 0){
            break;
        }

        fputs("\n\n<<COMANDOS : ",stdout);
        fputs(buffer,stdout);
        fputs("\n\n",stdout);
        pipe_get_cmd(buffer);
        fputs("\n\n",stdout);

        printf("\n\nTERMINA>>");

    }
    printf("\n\nFIN De ejecucion\n\n");
    fclose(fp);
    exit(0);
}



int main(int argc, char *argv[]){
    int src = 0;
    struct stat statbuf;

    if(argc > 2){
        printf("ERROR: %s [nombre]\n", argv[0]);
        return -1;

    }else if(argc == 2){

        if((src = open(argv[1], O_RDONLY)) < 0){
            printf("%s: Archivo no encontrado\n",argv[1]);
            return -2;
        }

        stat(argv[1],&statbuf);
        if(S_ISREG(statbuf.st_mode)){
            execute_file(argv[1]);
        }else{
            printf("No se puede abrir el archivo: %s \n",argv[1]);
        }

    }else{
        mini_shell();
    }
    return 0;
}
