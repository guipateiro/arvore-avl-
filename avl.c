#include<stdio.h>
#include<stdlib.h>

typedef struct T_no {
    int chave;
    int altura;
    struct T_no *esq, *dir, *pai;
} T_no;

void printTree(T_no *n)
{
    if(n == NULL) return;
    printTree(n->esq);
    printf("%d ", n->chave);
    printTree(n->dir);
}

T_no* criaNodo(int chave)
{
    T_no *n = malloc(sizeof(T_no));
    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->altura = 0;
    return n;
}

T_no* insereFolha(T_no *n, int chave)
{
    if(n == NULL)
        return criaNodo(chave);

    if(n->chave > chave){
        n->esq = insereFolha(n->esq, chave);
        n->esq->pai = n;
    }
    else if(n->chave <= chave){
        n->dir = insereFolha(n->dir, chave);
        n->dir->pai = n;
    }
    return n;
}

void rot_esq(T_no *tree, T_no *x)
{
    T_no * y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL)
        y->esq->pai = x;
    y->pai = x->pai;
    if(x->pai == NULL)
        tree = y;
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else 
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

void rot_dir(T_no *tree, T_no *x)
{
    T_no * y = x->esq;
    x->esq = y->dir;
    if(y->dir != NULL)
        y->dir->pai = x;
    y->pai = x->pai;
    if(x->pai == NULL)
        tree = y;
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else 
        x->pai->dir = y;
    y->dir = x;
    x->pai = y;
}

int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

int altura(T_no * n){
    if(n == NULL)
        return -1;
    int alturaEsq = altura(n->esq);
    int alturaDir = altura(n->dir);
    return max(alturaEsq, alturaDir);
}

T_no *antecessor(T_no *n){
    if(n->esq == NULL)
        return n;
    minimo(n->esq);
}

T_no *sucessor(T_no *n){
    if(n->dir == NULL){ 
        T_no *sucessor = n->pai;
        while (sucessor->pai != NULL && sucessor->dir == n){
            n = sucessor;
            sucessor = n->pai;
        }
        return sucessor;
    }
    return minimo(n->dir);
}

T_no *balanceiaAVL(T_no *no){
    //caso 1: Esq-Esq
        // rotação a direita
    //caso 2: Dir-Dir
        //rotação a esquerda
    //caso 3: Dir-Esq
        //rotacão dir (em no->dir)
        //rotação esquerda em no
    //caso 4: Esq-Dir
        //rotação esquerda (em no->esq)
        //rotação direita em no
}

T_no *inclui(T_no *no){
    //Inclui na folha
    
    // percorre a árvore do nodo inserido, até raiz:
        // calcula fator de balanceamento
        // calcula altura
        // arruma AVl
}

//links uteis: https://github.com/Ekan5h/AVLtree
//https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

int main()
{
    T_no *arv2;
    
    arv2 = malloc(sizeof(T_no));
    arv2->esq = NULL;
    arv2->dir = NULL;
    arv2->chave = 40;
   
    for(int i = 0; i < 10; i++)
        insereFolha(arv2, rand()%100);

    return 0;
}
