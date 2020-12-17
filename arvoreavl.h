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

void imprimelista(T_no* raiz,int i);

int max(int a, int b);

T_no* criaNodo(int chave);

int altura (T_no* no);

T_no *antecessor(T_no *n);

T_no *sucessor(T_no *n);

T_no *rotNodo_dir(T_no *no);

T_no *rotNodo_esq(T_no *no);

void arrumaBal(T_no *no, T_no *aux);

T_no *balanceiaAVL_esq(T_no *no, int *alterada);

T_no *balanceiaAVL_dir(T_no *no, int *alterada);

T_no* insere(T_no *n, int chave, int *alterada);

int excluino(T_no** raiz, int ch, int* alterou);

T_no *criaArvore();

#endif