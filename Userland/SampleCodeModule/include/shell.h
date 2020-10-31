 #ifndef _SHELL_H_
#define _SHELL_H_

typedef struct{
    void(*command)(int args, char *arg[]);
    char *name;
    char *description;
}t_command;

void initializeShell();

#endif