#include
#include
#include "ldec.h"
 
ldec *criarLdec()//Cria uma nova lista encadeada;
{
    ldec *l = (ldec*) malloc (sizeof(ldec));
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
    return l;
}
 
void inserirInicio(int valor, ldec *l)//Insere um nó no começo da lista l
{
    if (l != NULL)
    {
        No *no = (No*) malloc (sizeof(No));
        no->info = valor;
        if (l->tamanho == 0)
        {
            l->cabeca = no;
            l->cauda = no;
            no->anterior = no;
            no->proximo = no;
            l->tamanho++;
            return;
        }
        if (l->tamanho == 1)
        {
            l->cabeca->anterior = no;
            l->cabeca->proximo = no;
            no->proximo = l->cabeca;
            no->anterior = l->cauda;
            l->cabeca = no;
            l->tamanho++;
            return;
        }
        l->cabeca->anterior = no;
        l->cauda->proximo = no;
        no->anterior = l->cauda;
        no->proximo = l->cabeca;
        l->cabeca = no;
        l->tamanho++;
    }
}
 
void imprimirLista(ldec *l)//Imprime todos os valores dos nós da lista
{
    if ((l->tamanho == 0) || (l == NULL))
        return;
    No *no = l->cabeca;
    //imprime o primeiro
    printf("%d ", no->info);
    no = no->proximo;
    while (no != l->cabeca)
    {
        printf("%d ", no->info);
        no = no->proximo;
    }
}
 
void deletarLista(ldec **l)//Remove todos os nós da lista e depois a deleta;
{
    if (((*l)->tamanho == 0) || (*l) == NULL)
        return;
    if ((*l)->tamanho == 1)
    {
        No *no = (*l)->cabeca;
        free (no);
        free ((*l));
        (*l) = NULL;
        return;
    }
    while ((*l)->tamanho > 0)
        removerPrimeiro((*l));
    free ((*l));
    (*l) = NULL;
}
 
void removerPrimeiro(ldec *l)//Remove o primeiro nó da lista
{
   if ((l->tamanho == 0) || (l == NULL))
        return;
    if (l->tamanho == 1)
    {
        free (l->cabeca);
        l->cabeca = NULL;
        l->cauda = NULL;
        l->tamanho = 0;
        return;
    }
    No *no = l->cabeca->proximo;
    no->anterior = l->cauda;
    l->cauda->proximo = no;
    free(l->cabeca);
    l->cabeca = no;
    l->tamanho--;
}
 
void inserirFinal(int valor, ldec *l)//Insere um nó no final da lista l
{
    if (l == NULL)
        return;
    if (l->tamanho == 0)
    {
        inserirInicio(valor,l);
        return;
    }
    No *no = l->cabeca, *novo;
    while (no->proximo != l->cabeca)
    {
        no = no->proximo;
    }
    novo = (No*) malloc (sizeof(No));
    novo->info = valor;
    no->proximo = novo;
    novo->anterior = no;
    novo->proximo = l->cabeca;
    l->cauda = novo;
    l->tamanho++;
}
 
void inserirPosicao(int valor, int posicao, ldec *l)//Insere um nó em determinada posicao da lista l
{
    if ((l == NULL) || (posicao > l->tamanho))
        return;
    int i;
    No *no = l->cabeca, *novo;
    for (i = 1; i < posicao; i++)//i inicializa em 1 para parar na posicao correta         no = no->proximo;
    novo = (No*) malloc(sizeof(No));
    novo->info = valor;
    no->proximo->anterior = novo;
    novo->proximo = no->proximo;
    no->proximo = novo;
    novo->anterior = no;
    l->tamanho++;
}
 
void removerValor(int valor, ldec *l)//Remove os nós que contém determinado valor da lista l
{
   if ((l->tamanho == 0) || (l == NULL))
        return;
    No *no = l->cabeca, *aux;
    while (no->proximo != l->cabeca)
    {
        if (no == l->cabeca)
        {
            if (no->info == valor)
            {
                l->cabeca = no->proximo;
                l->cauda->proximo = l->cabeca;
                free (no);
                l->tamanho--;
                no = l->cabeca;
            }
        }
        else
        {
            if (no->info == valor)
            {
                no->anterior->proximo = no->proximo;
                no->proximo->anterior = no->anterior;
                aux = no;
                no = no->anterior;
                free(aux);
                l->tamanho--;
            }
        }
        no = no->proximo;
    }
    //condicao para o ultimo
    if (no->info == valor)
    {
        l->cauda = no->anterior;
        l->cauda->proximo = l->cabeca;
        l->cabeca->anterior = l->cauda;
        free(no);
        l->tamanho--;
    }
}
 
void removerUltimo(ldec *l)//Remove o ultimo nó da Lista
{
    if ((l->tamanho == 0) || (l == NULL))
        return;
    if (l->tamanho == 1)
    {
        removerPrimeiro(l);
        return;
    }
    No *no = l->cauda;
    l->cauda = no->anterior;
    l->cauda->proximo = l->cabeca;
    l->cabeca->anterior = l->cauda;
    free (no);
    l->tamanho--;
}
 
void removerPosicao(int posicao, ldec *l)//Remove o nó de determinada posição da lista
{
    if ((l->tamanho == 0) || (l == NULL))
        return;
    if (l->tamanho == 1)
    {
        removerPrimeiro(l);
        return;
    }
    if (posicao == l->tamanho-1)
    {
        removerUltimo(l);
        return;
    }
    int i;
    No *no = l->cabeca;
    for (i = 0; i < posicao; i++)     {         no = no->proximo;
    }
    no->anterior->proximo = no->proximo;
    no->proximo->anterior = no->anterior;
    free(no);
}
 
int multiplos(int valor, ldec *l)//Retorna quantos nós da lista são multiplos de determinado valor
{
    if ((l->tamanho == 0) || (l == NULL))
        return 0;
    if (l->tamanho == 1)
    {
        if ((l->cabeca->info % valor) == 0)
            return 1;
        return 0;
    }
    int cont = 0;
    No *no = l->cabeca;
    while (no->proximo != l->cabeca)
    {
        if ((no->info % valor) == 0)
            cont++;
        no = no->proximo;
    }
    //verifica o último
    if ((no->info % valor) == 0)
        cont++;
    return cont;
}
 
bool estaOrdenada(ldec *l)//Retorna true se a lista estiver crescentemente ordenada e false caso contrário
{
    if ((l->tamanho == 0) || (l->tamanho == 1) || (l == NULL))
        return true;
    No *no = l->cabeca;
    while (no->proximo != l->cabeca)
    {
        if (no->info > no->proximo->info)
            return false;
        no = no->proximo;
    }
    return true;