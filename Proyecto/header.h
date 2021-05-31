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



int execute_command(char *cmd_argv) {

    char *args[100], *exec_args;
    int count = 0;

    exec_args = strtok(cmd_argv," ");
    if(exec_args == NULL){
        printf("\nunexpected empty command\n");
    }else{
        while(exec_args != NULL){
            args[count] = exec_args;
            count++;
            exec_args = strtok(NULL, " ");
        }
        args[count] = NULL;

        if (execvp(args[0], args) == -1) {
            perror("execution error");
            return -1;
        }
    }

    return 0;
}



void pipe_get_cmd(char *cmd_argv)
{
    char *cmd;
    int count = 0, pid = 0;


    cmd = strtok(cmd_argv,"\n");
    cmd = strtok(cmd_argv,";");

    while(cmd != NULL){
        if((pid = fork()) == 0){
            execute_command(cmd);
            exit(0);

        }else{
            count++;
            cmd = strtok(NULL, ";");
        }
    }

    while(count-- > 0){
        wait(NULL);
    }
}
