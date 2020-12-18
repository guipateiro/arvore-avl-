# include "arvoreavl.h"

int main(){
    T_no *arv;
    arv = criaArvore();
    printf("Sua árvore é: \n");
    imprimelista(arv, 0);

    return 0;
}