#include"arvoreavl.h"

/*****************************************************************/
/*                                                               */
/*                     FUNÇÕES BÁSICAS                           */
/*                                                               */
/*****************************************************************/
void imprimelista(T_no* raiz,int i){
	if(raiz == NULL) 
		return; 
	imprimelista(raiz->esq, i+1);
	printf("%i,%i\n",raiz->chave, i);
	imprimelista(raiz->dir, i+1);
}

int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

T_no* criaNodo(int chave)
{
    T_no *n = malloc(sizeof(T_no));
    if (!n)
        exit(1);
    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->bal = 0;
    return n;
}

int altura (T_no* no){
	if (!no)
		return -1;
	else 
		return 1 + max(altura(no->esq),altura(no->dir));
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

/*****************************************************************/
/*                                                               */
/*                     FUNÇÕES ROTAÇÃO                           */
/*                                                               */
/*****************************************************************/

T_no *rotNodo_dir(T_no *no){
    T_no *aux = no->esq;
    no->esq = aux->dir;
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->dir != NULL)
        aux->dir->pai = no;
    aux->dir = no;
    return aux;
}

T_no *rotNodo_esq(T_no *no){
    T_no *aux = no->dir;
    no->dir = aux->esq;
    aux->pai = no->pai;
    no->pai = aux;
    if (aux->esq != NULL)
        aux->esq->pai = no;
    aux->esq = no;
    return aux;
}

/*****************************************************************/
/*                                                               */
/*                     BALANCEAMENTO                             */
/*                                                               */
/*****************************************************************/
void arrumaBal(T_no *no, T_no *aux){
    //Arruma ponteiro do pai
    if(aux->pai != NULL){
        if(aux->pai->esq == no)
            aux->pai->esq = aux;
        else
            aux->pai->dir = aux;
    }
    //Arruma valor balanceamento
    aux->bal = 0;
    aux->esq->bal = altura(aux->esq->esq) - altura(aux->esq->dir);
    aux->dir->bal = altura(aux->dir->dir) - altura(aux->dir->esq);
}

T_no *balanceiaAVL_esq(T_no *no, int *alterada){
    if(no->esq != NULL && no->esq->bal > 0) {
        //caso 2: Esq-Dir
        no->esq = rotNodo_esq(no->esq);
    }
    //caso 1: Esq-Esq
    T_no *aux = rotNodo_dir(no);

    arrumaBal(no, aux);  

    return aux;
}

T_no *balanceiaAVL_dir(T_no *no, int *alterada){
    if(no->dir != NULL && no->dir->bal < 0){
        //caso 4: Dir-Esq
        no->dir = rotNodo_dir(no->dir);
    }         
    //caso 3: Dir-Dir
    T_no *aux = rotNodo_esq(no);

    arrumaBal(no, aux);    
    
    return aux;
}

/*****************************************************************/
/*                                                               */
/*                     INSERE                                    */
/*                                                               */
/*****************************************************************/

/*
* Insere chave na arvore (ou subarvore) n
* Variável "altera" deve começar em 0, e é setada para 1
* se a subarvore foi alterada, ou seja, se o nodo foi adicionado
*/
T_no* insere(T_no *n, int chave, int *alterada)
{
    if(n == NULL){
        //cria nodo e seta o valor de "alterada"
        //sinalizando que a suarvore foi alterada
        n = criaNodo(chave);
        *alterada = 1;
        return n;
    }
    //Realiza a inserção
    if(chave < n->chave){
        n->esq = insere(n->esq, chave, alterada);
        n->esq->pai = n;
        if(*alterada)
            n->bal -= 1;
        //Faz o balanceamento Esquerda
        if(n->bal == 0) *alterada = 0; // se a subarvore esta balanceada
        //caso contrário, verifica o fator de balanceamento
        else if (n->bal == -2){
            //se a suarvore esta desbalanceada
            //n recebe a raiz da subarvore após balanceamento
            n = balanceiaAVL_esq(n, alterada);
            *alterada = 0;
        }
    }
    //o processo para a inserção na direita é o "espelho" do da esquerda
    else if(chave >= n->chave){
        n->dir = insere(n->dir, chave, alterada);
        n->dir->pai = n;
        //se a estrura da subarvore foi alterada
        if(*alterada) 
            n->bal += 1;

        //Faz o balanceamento Direita
        if(n->bal == 0) *alterada = 0;
        else if (n->bal == 2){
            n = balanceiaAVL_dir(n, alterada);
            *alterada = 0;
        }
    }
    return n;
}

/*****************************************************************/
/*                                                               */
/*                     REMOVE                                    */
/*                                                               */
/*****************************************************************/
int excluino(T_no** raiz, int ch, int* alterou){
    T_no* atual = *raiz;
    if (!atual) {
        *alterou = 0;
        return 0;
    }
    if (atual->chave == ch){
        T_no* substituto;
        if(!atual->esq || !atual->dir) { // tem zero ou um filho
            if(atual->esq) {
                substituto = atual->esq;
            }   
            else{ 
                substituto = atual->dir;
            }   
            *raiz = substituto;
            free(atual);
            *alterou = 1;
            return 1;
        }
        else{   // tem dois filhos
            substituto = sucessor(atual);
            atual->chave = substituto->chave;
            ch = substituto->chave; // continua o codigo excluindo o substituto
        }
    }
    int res;
    if (ch < atual->chave){
        //recursao a esquerda
        res = excluino(&(atual->esq), ch, alterou); 
        if (*alterou){ // rebalanceia a arvore 
            atual->bal++;
            if (atual->bal == 1)
            	*alterou = 0;
            else if (atual->bal == 2){
            	*raiz = balanceiaAVL_dir(atual,alterou);
                if (atual->bal != 0)
                    *alterou = 0;
            }
            return 1;
        }
    }   
    else{
        //recursao a direita 
        res = excluino(&(atual->dir), ch, alterou);
        if (*alterou){ // rebalanceia a arvore 
            atual->bal--;
            if (atual->bal == -1)
            	*alterou = 1;
            else if (atual->bal == -2){
            	*raiz = balanceiaAVL_esq(atual, alterou);
                if (atual->bal != 0)
                    *alterou = 0;
            }
            return 1;
        }
    }
    return res;
}

T_no *criaArvore()
{
    T_no *arv;
    char op[1];
    int chave;
    if(scanf("%s %d", op, &chave) != 2){
        fprintf(stderr,"Entrada inválida");
        exit(1);
    }
    arv = criaNodo(chave);
    int altera = 0;
    //lê entrada    
    while(scanf("%s %d", op, &chave) == 2 && !feof(stdin)){
        if(!strcmp(op, "i")){
            altera = 0;
            arv = insere(arv, chave, &altera);
        }
        if(!strcmp(op, "r")){
            altera = 0;
            excluino(&arv, chave, &altera);
        }
    }
    
    return arv;
}
