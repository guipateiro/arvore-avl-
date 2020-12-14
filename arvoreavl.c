#include <stdio.h>
#include <stdlib.h>

typedef struct tno {
	int chave;
	struct tno *esq;
	struct tno *dir;
	int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} T_no;

T_no* criano (int c){
	T_no *novo = (T_no* )malloc(sizeof(T_no));
	if (!novo)
		exit (1);
	novo->esq = NULL;
	novo->dir = NULL;
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

void imprimelista(T_no* raiz,int i){
	if(raiz == NULL) 
		return; 
	imprimelista(raiz->esq, i+1);
	printf("%i , %i\n",raiz->chave, i);
	imprimelista(raiz->dir, i+1);
}

void insereno(T_no** no, int c){
	T_no* novo = *no;
	if(novo == NULL){
		*no = criano(c);		
	}
	else{
		if (c <= novo->chave)
			insereno(&novo->esq,c);
		else
			insereno(&novo->dir,c);
	}
}


int main(){
	T_no *arvore = NULL;
	int i; 
	char codigo;
	while (i != 0){
		scanf("%s",&codigo);
		if (codigo == 'i'){
			scanf("%i",&i);
			insereno(&arvore,i);
		}
		if (codigo == 'p')
			imprimelista(arvore,0);
	}	
}