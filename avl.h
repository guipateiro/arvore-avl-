#ifndef __AVL__
#define __AVL__

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

T_no* insere(T_no *n, int chave, int *alterada);

T_no* criaArvore();

void imprimelista(T_no* raiz,int i);

#endif