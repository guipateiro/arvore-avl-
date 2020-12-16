#include <stdio.h>
#include <stdlib.h>

typedef struct tno {
	int chave;
	struct tno *esq;
	struct tno *dir;
	struct tno *pai;
	int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} T_no;

T_no* criano (int c){
	T_no *novo = (T_no* )malloc(sizeof(T_no));
	if (!novo)
		exit (1);
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = NULL;
	novo->chave = c;
	novo->bal = 0;
	printf("inserido com sucesso %i na arvore \n", c);
	return novo; 
}

int max(int a, int b){
	if (a>b)
		return a;
	return b;
}

int altura (T_no* no){
	if (!no)
		return -1;
	else 
		return 1 + max(altura(no->esq),altura(no->dir));
}

void imprimelista(T_no* raiz,int k){
	if(raiz == NULL) 
		return; 
	imprimelista(raiz->esq, k+1);
	printf("%i , %i\n",raiz->chave, k);
	imprimelista(raiz->dir, k+1);
}

void insereno(T_no** raiz, int c){
	T_no* novo = *raiz;
	if(novo == NULL){
		*raiz = criano(c);		
	}
	else{
		if (c <= novo->chave)
			insereno(&novo->esq,c);
		else
			insereno(&novo->dir,c);
	}
}

T_no *min(T_no *n){
    if(n->esq == NULL)
        return n;
    return min(n->esq);
}

T_no *sucessor(T_no *n){
    if(n->dir != NULL) 
    	return min(n->dir);
    T_no *sucessor = n->pai;
    while (sucessor != NULL && sucessor->dir == n){
        n = sucessor;
        sucessor = sucessor->pai;
    }
    return sucessor;
}

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

/* exclui a chave com valor igual a ch   */
int excluirAVL(T_no** raiz, int ch, int* alterou){
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
    	res = excluirAVL(&(atual->esq), ch, alterou);
    	if (*alterou){
     	    switch (atual->bal){
        		case -1: 
        			atual->bal = 0;
            		return 1;
            	case 0: 
            		atual->bal = 1;
            		*alterou = 0;
            		return 1;
            	case 1:
            	    *raiz = rotNodo_dir(atual);
            		if (atual->bal != 0){
            			*alterou = 0;
            		}
        			return 1;
        	}
    	}
    }	
  	else{
    	res = excluirAVL(&(atual->dir), ch, alterou);
    	if (*alterou){
    	    switch (atual->bal){
        		case 1: 
        			atual->bal = 0;
        	    	return 1;
        		case 0: 
        			atual->bal = -1;
         			*alterou = 1;
            		return 1;
          		case -1: 
          			*raiz = rotNodo_esq(atual);
          			if (atual->bal != 0)
          				 *alterou = 0;
          			return 1;
       		}
    	}
  	}
  	return res;
}

int main(){
	T_no *arvore = NULL;
	int i; 
	int j = 0;
	char codigo;
	while (i >= -1){
		scanf("%s",&codigo);
		if (codigo == 'i'){
			scanf("%i",&i);
			insereno(&arvore,i);
		}
		if (codigo == 'p')
			imprimelista(arvore,0);
		if (codigo == 'r'){
			scanf("%i",&i);
			excluirAVL(&arvore,i,&j);
			j = 0;
		}
	}
	return 0;
}	
