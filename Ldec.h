#ifndef LDEC_H_INCLUDED
#define LDEC_H_INCLUDED
 
enum boolean
{
    true = 1, false = 0
};
typedef enum boolean bool;
 
typedef struct Node
{
    int info;
    struct Node *anterior;
    struct Node *proximo;
}No;
 
typedef struct LDEC
{
    No *cabeca;
    No *cauda;
    int tamanho;
}ldec;
 
ldec *criarLdec();//Cria uma nova lista encadeada;
 
void inserirInicio(int valor, ldec *l);//Insere um nó no começo da lista
 
void inserirFinal(int valor, ldec *l);//Insere um nó no final da lista
 
void inserirPosicao(int valor, int posicao, ldec *l);//Insere um nó em determinada posicao da lista
 
void removerPrimeiro(ldec *l);//Remove o primeiro nó da lista
 
void removerUltimo(ldec *l);//Remove o ultimo nó da Lista
 
void removerValor(int valor, ldec *l);//Remove os nós que contém determinado valor da lista
 
void removerPosicao(int posicao, ldec *l);//Remove o nó de determinada posição da lista
 
void imprimirLista(ldec *l);//Imprime todos os valores dos nós da lista
 
void deletarLista(ldec **l);//Remove todos os nós da lista e depois a deleta
 
int multiplos(int valor, ldec *l);//Retorna quantos nós da lista são multiplos de determinado valor
 
bool estaOrdenada(ldec *l);//Retorna true se a lista estiver crescentemente ordenada e false caso contrário
 
#endif // LDEC_H_INCLUDED