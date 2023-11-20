#include <stdio.h>
#include <stdlib.h>
#include "task.h"

void BodyPang (void * arg)
{
   char* name = (char *) arg ;
   printf ("%s \n", name) ;
   task_yield();
   task_exit (0) ;
}

void BodyPeng (void * arg)
{
   char* name = (char *) arg ;
   printf ("%s \n", name) ;
   task_yield();
   task_exit (0) ;
}

void BodyPing (void * arg)
{
   char* name = (char *) arg ;
   printf ("%s \n", name) ;
   task_yield();
   task_exit (0) ;
}

void BodyPong (void * arg)
{
   char* name = (char *) arg ;
   printf ("%s \n", name) ;
   task_yield();
   task_exit (0) ;
}

void BodyPung (void * arg)
{
   char* name = (char *) arg ;
   printf ("%s \n", name) ;
   task_yield();
   task_exit (0) ;
}

int main (int argc, char *argv[])
{
   int i;
   printf ("Main INICIO\n");
   //chamada da função para inicializar a biblioteca
   task_init () ;
   
   for (i = 0; i < 2; i++)
   {
        //Criação dos processos
        task_create(BodyPang, "    Pang", 0);
        task_create(BodyPeng, "        Peng", 3);
        task_create(BodyPing, "            Ping", -5);
        task_create(BodyPong, "                Pong", 1);
        task_create(BodyPung, "                    Pung",-2);
   }
    //o task yield é reponsavel por executar os processos
   //adicionando e removendo da lista global
   task_yield();    
   printf ("Main FIM\n");

   exit (0);
}
