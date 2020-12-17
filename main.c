# include "avl.h"

int main(){
    T_no *arv;
    arv = criaArvore();
    printf("[ÁRVORE CRIADA]: \n");
    imprimelista(arv, 0);
    return 0;
}