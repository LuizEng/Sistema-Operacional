#include <stdio.h>
#include <stdlib.h>
#include "listaEncadeada.h"

TList * CreateLista()
{
    TList *pList = (TList*) malloc (sizeof(TList));
    pList->cabeca = NULL;
    pList->cauda = NULL;
    pList->tamanho = 0;
    
	return pList;	
}

No * CriaNode(task_t task)
{
	No * Node = (No *) malloc(sizeof(No));
	Node->conteudo = task;
	Node->pProximo = NULL;
	Node->pAnterior = NULL;
	
	return Node;
}

void InsereNoInicio(task_t  valor, TList * pLista)
{
	if (pLista != NULL)
	{
		No* pNode = (No *) malloc(sizeof(No));
		pNode->conteudo = valor;
		if (pLista->tamanho == 0)
		{
			pLista->cabeca   = pNode;
			pLista->cauda    = pNode;
			pNode->pProximo  = pNode;
			pNode->pAnterior = pNode;
			pLista->tamanho++;
		}
		else
		{
			pLista->cabeca->pAnterior = pNode;
			pLista->cauda->pProximo = pNode;
			pNode->pAnterior = pLista->cauda;
			pNode->pProximo = pLista->cabeca;
			pLista->tamanho++;	
		} 
		
	}
}

void InsereNoFim(task_t valor, TList * pLista)
{
	if (pLista == NULL)
		return;
	if (pLista->tamanho == 0)
		InsereNoInicio(valor, pLista);
	else
	{
		No * pNode = pLista->cabeca;
		No* pNovoNo = (No *) malloc(sizeof(No));
		while( pNode->pProximo != pLista->cabeca)
			pNode = pNode->pProximo;

		pNovoNo->conteudo = valor;
		pNode->pProximo = pNovoNo;
		pNovoNo->pAnterior = pNode;
		pNovoNo->pProximo = pLista->cabeca;
		pLista->cauda = pNovoNo;
		pLista->tamanho++;	
	}		
	
}

No * RemoveNoInicio(TList * pLista)
{
	No * pNodeReturn;
	if ((pLista->tamanho == 0) || (pLista == NULL))
		return;
	if (pLista->tamanho == 1)
	{
		pNodeReturn = pLista->cabeca;
		free (pLista->cabeca);
		pLista->cabeca = NULL;
		pLista->cauda = NULL;
		pLista->tamanho = 0;
	}
	else
	{
		No * pNode = pLista->cabeca->pProximo;
		pNode->pAnterior = pLista->cauda;
		pLista->cauda->pProximo = pNode;
		pNodeReturn = pLista->cabeca;
		free(pLista->cabeca);
		pLista->cabeca = pNode;
		pLista->tamanho--;
	}
	
	return pNodeReturn;
}

No * RemoveNoFim(TList * pLista)
{
	if ((pLista->tamanho == 0) || (pLista == NULL))	
		return;
	if (pLista->tamanho == 1)
	{
		return RemoveNoInicio(pLista);		
	}
	else
	{
		No * pNode = pLista->cauda;
		pLista->cauda = pNode->pAnterior;
		pLista->cauda->pProximo = pLista->cabeca;
		pLista->cabeca->pAnterior = pLista->cauda;
		pLista->tamanho--;
		return pNode;	
	}	
}

No * RemovePosicao(TList * pLista, int posicao)
{
	if ((pLista->tamanho == 0) || (pLista == NULL))	
		return;
	if (pLista->tamanho == 1)
		return RemoveNoInicio(pLista);
	else if (posicao == pLista->tamanho - 1)
		return RemoveNoFim(pLista);
	else
	{
		int i;
		No *pNode = pLista->cabeca;
		
		for (i = 0; i < posicao; i++)
			pNode = pNode->pProximo;
		
		pNode->pAnterior->pProximo = pNode->pProximo;
		pNode->pProximo->pAnterior = pNode->pAnterior;	
		return pNode;
	}
		
}

void Destroy(TList ** pLista)
{
    if (((*pLista)->tamanho == 0) || (*pLista) == NULL)
        return;
    if ((*pLista)->tamanho == 1)
    {
        No *pNode = (*pLista)->cabeca;
        free (pNode);
        free ((*pLista));
        (*pLista) = NULL;
    }
    else
    {
    	while ((*pLista)->tamanho > 0)
        	RemoveNoInicio((*pLista));
    	free ((*pLista));
    	(*pLista) = NULL;
	}	
}
