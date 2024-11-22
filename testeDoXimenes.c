#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
// #include "STRUCTS.h"
#include "ROOT.h"
#include "PROTOTIPOS.h"
#include "colors.h"
#include "FUNCTIONS.h"

// Structs
typedef struct no {
    int info;
    int fb;
    struct no* noEsq;
    struct no* noDir;
} NoArv;

typedef struct Arv {
    NoArv* raiz;
} Arv;

NoArv* inserirNo(NoArv* raiz, int valor);
void inserirArvBalanceado(Arv* arvore,int valor);
void printPosOrderX(NoArv *raiz);
Arv* criarArvore();
NoArv* criarNo(int v);




int main(){
    Arv* arvore = criarArvore();
    inserirArvBalanceado(arvore,9);
    inserirArvBalanceado(arvore,10);
    inserirArvBalanceado(arvore,18);
    inserirArvBalanceado(arvore,2);
    inserirArvBalanceado(arvore,4);

    printPosOrderX(arvore->raiz);
}




Arv* criarArvore(){
    Arv* arv = (Arv*)malloc(sizeof(Arv));
    arv->raiz = NULL;
    return arv;
}

NoArv* criarNo(int v){
    NoArv* no = (NoArv*)malloc(sizeof(NoArv));
    no->info = v;
    no->noEsq = NULL;
    no->noDir = NULL;
    return no;
}

void inserirArvBalanceado(Arv* arvore,int valor){
    arvore->raiz = inserirNo(arvore->raiz, valor);
} 

NoArv* inserirNo(NoArv* noRaiz, int valor){
    if(noRaiz == NULL)
        return criarNo(valor);
    if(noRaiz->info < valor)
        noRaiz->noEsq = inserirNo(noRaiz->noEsq,valor); 
    if(noRaiz->info > valor)
        noRaiz->noDir = inserirNo(noRaiz->noDir,valor); 
    return noRaiz;

}

void printPosOrderX(NoArv *raiz) {
    if(raiz == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    if(raiz->noDir != NULL) {
        printPosOrderX(raiz->noDir);
    }
    if(raiz->noEsq != NULL){
        printPosOrderX(raiz->noEsq);
    }
    printf("%d |",raiz->info);
}
