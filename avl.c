#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tno {
	int chave;
	struct tno *esq;
	struct tno *dir;
    struct tno *pai;
	int bal;
} T_no;

void imprimelista(T_no* raiz,int i){
	if(raiz == NULL) 
		return; 
	imprimelista(raiz->esq, i+1);
	printf("%i , %i\n",raiz->chave, i);
	imprimelista(raiz->dir, i+1);
}

T_no* criaNodo(int chave)
{
    T_no *n = malloc(sizeof(T_no));
    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->bal = 0;
    return n;
}


T_no* insereFolha(T_no *n, int chave)
{
    if(n == NULL)
        n = criaNodo(chave);

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

//Tive q alterar a função de rotação, pra fazer a rotação no nodo corretamente
//Por enquanto isso é literalmente uma cópia do Didonet, tem q ver se tem como
//mudar ou fazer diferente alguma coisa
T_no *rotNodo_dir(T_no *no)
{
    T_no *aux = no->esq;
    no->esq = aux->dir;
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->dir != NULL)
        aux->dir->pai = no;
    aux->dir = no;
    return aux;
}

T_no *rotNodo_esq(T_no *no)
{
    T_no *aux = no->dir;
    no->dir = aux->esq;
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->esq != NULL)
        aux->esq->pai = no;
    aux->esq = no;
    return aux;
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
    return antecessor(n->esq);
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
    return antecessor(n->dir);
}

T_no *balanceiaAVL_esq(T_no *no, int *alterada){
    if(no->esq != NULL && no->esq->bal > 0) //caso 4: Esq-Dir
        no->esq = rotNodo_esq(no->esq);
    T_no *aux = rotNodo_dir(no->dir);//caso 1: Esq-Esq

    if(aux->pai != NULL){
        if(aux->pai->esq == no)
            no->pai->esq = aux;
        else
            no->pai->dir = aux;
    }

    aux->bal = 0;
    aux->esq->bal = altura(no->esq->esq) - altura(no->esq->dir);
    aux->dir->bal = altura(no->dir->esq) - altura(no->dir->dir);
    return aux;
}

T_no *balanceiaAVL_dir(T_no *no, int *alterada){
    if(no->dir != NULL && no->dir->bal < 0) //caso 3: Dir-Esq
        no->dir = rotNodo_dir(no->dir);
    T_no *aux = rotNodo_esq(no->esq);//caso 2: Dir-Dir
    
    if(aux->pai != NULL){
        if(aux->pai->esq == no)
            no->pai->esq = aux;
        else
            no->pai->dir = aux;
    }
    
    aux->bal = 0;
    aux->esq->bal = altura(no->esq->esq) - altura(no->esq->dir);
    aux->dir->bal = altura(no->dir->esq) - altura(no->dir->dir);
    return aux;
}

T_no* insere(T_no *n, int chave, int *alterada)
{
    if(n == NULL){
        n = criaNodo(chave);
        *alterada = 1;
    }
    //Realiza a inserção
    if(n->chave > chave){
        n->esq = insere(n->esq, chave, alterada);
        n->esq->pai = n;
        if(*alterada)
            n->bal -= 1;
            
        //Faz o balanceamento Esquerda
        if(n->bal == 0)
            *alterada = 0;
        else if (n->bal == -2){
            balanceiaAVL_esq(n, alterada);
            alterada = 0;
        }
    }
    else if(n->chave <= chave){
        n->dir = insere(n->dir, chave, alterada);
        n->dir->pai = n;
        if(*alterada) //se a estrura da subarvore foi alterada
            n->bal += 1;

        //Faz o balanceamento Direita
        if(n->bal == 0)
            *alterada = 0;
        else if (n->bal == 2){
            balanceiaAVL_dir(n, alterada);
            alterada = 0;
        }
    }
    return n;
}

int main()
{
    T_no *arv;
    char op[1];
    int chave;
    if(scanf("%s %d", op, &chave) != 2){
        fprintf(stderr,"Entrada inválida");
        exit(1);
    }
    arv = criaNodo(chave);
    //lê entrada    
    while(scanf("%s %d", op, &chave) == 2 && !feof(stdin)){
        if(!strcmp(op, "i")){
            printf("Inclui: %d\n", chave);
            insere(arv, chave, 0);
            printf("\ninserido\n");
        }
    }
    imprimelista(arv, 0);
    return 0;
}
