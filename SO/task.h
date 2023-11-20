#ifndef _TASKLIB_
    #define _TASKLIB_
#include <stdio.h>
#include <stdlib.h>
//#include <ucontext.h>
#define STACKSIZE 16000
#define MIN_PRIORITY -20
#define MAX_PRIORITY  20

static int numTasks ;

typedef struct task_t
{
   //ucontext_t ctxt ;
   int taskID ;
   int ini_priority;
   int cur_priority;
} task_t ;

task_t Principal, *Corrente;

//Inicializa a tasklib
void task_init(); 

//Cria a tarefa
void task_create(void (*start_routine)(void*), void * arg, int ini_priority);

//Termina a tarefa corrente
void task_exit( int exit_code );

//Suspende a tarefa corrente e ativa outra tarefa
void task_yield();

void control_priority(task_t * task);

int task_item_priority();
//Informa o identificador da tarefa corrente
int task_id();

#endif
