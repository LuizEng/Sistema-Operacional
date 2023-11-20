#ifndef _NODELIB_
    #define _NODELIB_
#include <stdio.h>
#include <stdlib.h>
#include "task.h"
typedef struct _No
{
    task_t conteudo;
    struct _No * pProximo;
    struct _No * pAnterior;
} No;

typedef struct _Lista
{
	No * cabeca;
	No * cauda;
	int  tamanho;
}TList;

TList * CreateLista();

No * CriaNode(task_t task);

void InsereNoInicio(task_t valor, TList * pLista);

void InsereNoFim(task_t valor, TList * pLista);

No * RemoveNoInicio(TList * pLista);

No * RemoveNoFim(TList * pLista);

No * RemovePosicao(TList * pLista, int posicao);

void Destroy(TList ** pLista); 

#endif
