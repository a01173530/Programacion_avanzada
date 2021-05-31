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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#define BUFFER_MAX 512


struct command_t {
        char *name;
        int argc;
        char *argv[100];
};


struct command_t command_dir;


void prompt()
{
    char dir[PATH_MAX];

    if(getcwd(dir, sizeof(dir)) != NULL){
        printf("mini-shell> ");
    }

}



int execute_command(char *command_argv) {

    char *args[100], *args_exec;
    int contador = 0;

    args_exec = strtok(command_argv," ");
    if(args_exec == NULL){
        printf("\n!!No dejes comandos en blanco!!\n");
    }else{
        while(args_exec != NULL){
            args[contador] = args_exec;
            contador++;
            args_exec = strtok(NULL, " ");
        }
        args[contador] = NULL;

        if (execvp(args[0], args) == -1) {
            perror("Execution error");
            return -1;
        }
    }

    return 0;
}



void pipe_get_cmd(char *command_argv)
{
    char *command;
    int contador = 0, pid = 0;


    command = strtok(command_argv,"\n");
    command = strtok(command_argv,";");

    while(command != NULL){
        if((pid = fork()) == 0){
            execute_command(command);
            exit(0);

        }else{
            contador++;
            command = strtok(NULL, ";");
        }
    }

    while(contador-- > 0){
        wait(NULL);
    }
}
