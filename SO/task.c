#include "task.h"
#include "listaEncadeada.h"

TList * pTaskList;
int CountList;

//Função que inicializa nossa biblioteca
void task_init()
{ 
   
   numTasks = 0;
   
   pTaskList = CreateLista();
   
   //getcontext( &( Principal.ctxt ) );

   Principal.taskID = numTasks;

   numTasks++;

   Corrente = &Principal;
   
   CountList = 0;

   #ifdef DEBUG
      printf("task_init(): inicialização feita com sucesso.\n");
   #endif   

}

//Cria a tarefa
void task_create(void (*start_routine)(void*), void * arg, int ini_priority)
{
   
   char* pilha;
   
   task_t* task;
   
   task = malloc(sizeof(task_t*));
   
   //getcontext( &( task->ctxt ) );
   
   if( pilha = malloc( STACKSIZE ) )
   {
/*
	( task->ctxt ).uc_stack.ss_sp = pilha;
	
	( task->ctxt ).uc_stack.ss_size = STACKSIZE;
	
	( task->ctxt ).uc_stack.ss_flags = 0;
	
	( task->ctxt ).uc_link = 0;
   
    makecontext( &( task->ctxt ), (void*) start_routine, 1, arg );
*/
    task->taskID = numTasks;
    task->ini_priority = ini_priority;
    task->cur_priority = ini_priority;
	
    numTasks++;
    
	InsereNoFim(*task,pTaskList);    
   }
}
//Termina a tarefa corrente
void task_exit( int exit_code )
{
  // swapcontext( &( Corrente->ctxt ), &( (&Principal)->ctxt ) );
   
   task_yield();
}

//Suspende a tarefa corrente e ativa outra tarefa
void task_yield()
{
    No* aux;
    task_t * task; 
    task_t * task_aux; 
    int posicao;
    
    task_aux = Corrente;
    
    if ((pTaskList->tamanho - CountList) == 0)
    	CountList = 0;

    if (Corrente->taskID != 0)
        InsereNoFim(*Corrente,pTaskList);   

    Corrente = &Principal;

    if ( pTaskList != NULL) 
    {
        posicao = task_item_priority();
        
        aux = RemovePosicao(pTaskList, posicao);
        CountList++;
        task = &(aux->conteudo);
        Corrente = task;

        //swapcontext( &( task_aux->ctxt ), &( task->ctxt ) );
        
        control_priority(Corrente); 
        //free(task);
        free(aux);
    }
    //free(task_aux);

}

int task_id()
{
    
   return ( *Corrente ).taskID;

}

void control_priority(task_t * task)
{
    if (task->cur_priority == MIN_PRIORITY)
        task->cur_priority = task->ini_priority;
    else
        task->cur_priority = task->cur_priority - 1;
}

int task_item_priority()
{
	int i;
	int resultado;
	
	No * pFirst_Aux;
	task_t  task_max;
	task_t  task_atual;
	
	pFirst_Aux = pTaskList->cabeca;
	resultado = 0;
	i = 0;
	task_max = pFirst_Aux->conteudo;	
	
	while (pTaskList->tamanho-CountList != i)
	{
		task_atual = pFirst_Aux->conteudo;

		if (task_atual.cur_priority > task_max.cur_priority)
		{
			task_max = task_atual;
			resultado = i;
		}
		else if (task_atual.cur_priority == task_max.cur_priority)
		{
			if (task_atual.ini_priority > task_max.ini_priority)
			{
				task_max = task_atual;
				resultado = i;	
			}			
		}
		pFirst_Aux = pFirst_Aux->pProximo;
		i++;
			
	}
    return resultado;
}
