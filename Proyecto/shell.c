/*----------------------------------------------------------------
*
* Programación avanzada: Proyecto final
* Fecha: 2-Jun-2021
* Autor: Adrián Torres Hernández A01173530
*
*
*--------------------------------------------------------------*/
/**
* To compile: gcc shell.c -o shell
**/

#include "header.h"


void mini_shell();
void execute_file(char *filepath);


int main(int argc, char *argv[]){
    int src = 0;
    struct stat stat_buf;

    if(argc > 2){
        printf("usage: %s [batchFile]\n", argv[0]);
        return -1;

    }else if(argc == 2){

        if((src = open(argv[1], O_RDONLY)) < 0){
            printf("%s: No such file or directory\n",argv[1]);
            return -2;
        }

        stat(argv[1],&stat_buf);
        if(S_ISREG(stat_buf.st_mode)){
            execute_file(argv[1]);
        }else{
            printf("%s: File unavailable to open \n",argv[1]);
        }

    }else{
        mini_shell();
    }
    return 0;
}

void mini_shell()
{
    char cmd_argv[BUFFER_MAX];
    char dir[PATH_MAX];

    prompt();


    while(fgets(cmd_argv,BUFFER_MAX, stdin)){
        if(cmd_argv[0] == '\n'){
            prompt();
            continue;
        }else if(strcmp(cmd_argv,"quit\n") == 0){
            break;
        }
        get_pipe_cmd(cmd_argv);
        prompt();
    }
    exit(0);
}

void execute_file(char *filepath){

    FILE *filep = fopen(filepath, "r");
    char buffer[BUFFER_MAX];

    while(fgets(buffer,sizeof(buffer),filep) != NULL){
        if(strcmp(buffer,"quit\n") == 0){
            break;
        }

        fputs("\n\n<executing command: ",stdout);
        fputs(buffer,stdout);
        fputs("\n\n",stdout);
        get_pipe_cmd(buffer);
        fputs("\n\n",stdout);

        printf("\n\ncommand completed>");

    }
    printf("\n\nexecuting completed\n\n");
    fclose(filep);
    exit(0);
}
