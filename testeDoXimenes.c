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
    int bf;
    struct no* noEsq;
    struct no* noDir;
} NoArv;

typedef struct Arv {
    NoArv* raiz;
} Arv;

NoArv* inserirNo(NoArv* raiz, int valor, int*alterou);
void inserirArvBalanceado(Arv* arvore,int valor);
void printPosOrderX(NoArv *raiz);
Arv* criarArvore();
NoArv* criarNo(int v);

// Função recursiva para construir a visualização ASCII.
void imprimirArvore(NoArv* raiz, int espaco, int nivel) {
    if (raiz == NULL) return;

    espaco += 4; // Define o espaçamento entre os níveis.

    // Primeiro, imprime o subárvore direita.
    imprimirArvore(raiz->noDir, espaco, nivel + 1);

    // Imprime o nó atual com o espaçamento correspondente.
    printf("\n");
    for (int i = 4; i < espaco; i++) printf(" ");
    printf("%d\n", raiz->info);

    // Por último, imprime o subárvore esquerda.
    imprimirArvore(raiz->noEsq, espaco, nivel + 1);
}

// Wrapper para a função imprimirArvore.
void imprimirArvoreASCII(NoArv* raiz) {
    imprimirArvore(raiz, 0, 0);
}


int main(){
    Arv* arvore = criarArvore();
    inserirArvBalanceado(arvore,9);
    inserirArvBalanceado(arvore,10);
    inserirArvBalanceado(arvore,18);
    inserirArvBalanceado(arvore,4);
    inserirArvBalanceado(arvore,1);
    inserirArvBalanceado(arvore,15);
    inserirArvBalanceado(arvore,16);
    inserirArvBalanceado(arvore, 7);
    inserirArvBalanceado(arvore, 5);
    inserirArvBalanceado(arvore, 8);
    printPosOrderX(arvore->raiz);
    imprimirArvoreASCII(arvore->raiz);
    // imprimirArvoreASCII(arvore->raiz);
    // inserirArvBalanceado(arvore,19);
    // inserirArvBalanceado(arvore,1);
    // inserirArvBalanceado(arvore,3);
    // inserirArvBalanceado(arvore,2);
    // inserirArvBalanceado(arvore,1);

    printf("\n\n");

    printPosOrderX(arvore->raiz);
    imprimirArvoreASCII(arvore->raiz);
}
NoArv* rotateRight(NoArv* root) {
    NoArv* newRoot = root->noEsq;
    root->noEsq = newRoot->noDir;
    newRoot->noDir = root;

    root->bf = 0;
    newRoot->bf = 0;

    return newRoot;
}

NoArv* rotateLeft(NoArv* root) {
    NoArv* newRoot = root->noDir;
    root->noDir = newRoot->noEsq;
    newRoot->noEsq = root;

    root->bf = 0;
    newRoot->bf = 0;

    return newRoot;
}

NoArv* rotateLeftRight(NoArv* root) {
    root->noEsq = rotateLeft(root->noEsq);
    return rotateRight(root);
}

NoArv* rotateRightLeft(NoArv* root) {
    root->noDir = rotateRight(root->noDir);
    return rotateLeft(root);
}

NoArv* balancear(NoArv* noRaiz) {
    if (noRaiz->bf < -1) {
        if (noRaiz->noEsq->bf > 0) {
            noRaiz = rotateLeftRight(noRaiz);
        } else {
            noRaiz = rotateRight(noRaiz);
        }
    } else if (noRaiz->bf > 1) {
        if (noRaiz->noDir->bf < 0) {
            noRaiz = rotateRightLeft(noRaiz);
        } else { 
            noRaiz = rotateLeft(noRaiz);
        }
    }
    return noRaiz;
}

NoArv* inserirNo(NoArv* noRaiz, int valor, int* alterou) {
    if (noRaiz == NULL) {
        *alterou = 1;
        return criarNo(valor);
    }

    if (valor < noRaiz->info) {
        noRaiz->noEsq = inserirNo(noRaiz->noEsq, valor, alterou);

        if (*alterou) {
            noRaiz->bf--;
        }
    } else if (valor > noRaiz->info) {
        noRaiz->noDir = inserirNo(noRaiz->noDir, valor, alterou);

        if (*alterou) {
            noRaiz->bf++;
        }
    } else {
        *alterou = 0;
        return noRaiz;
    }

    noRaiz = balancear(noRaiz);

    if (noRaiz->bf == 0) {
        *alterou = 0;
    }

    return noRaiz;
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
    no->bf = 0;
    return no;
}

void inserirArvBalanceado(Arv* arvore,int valor){
    int alterou = 0;
    arvore->raiz = inserirNo(arvore->raiz, valor, &alterou);
} 

// NoArv* rotateRight(NoArv* y){
//     NoArv* x = y->root_left;
//     NoArv* t2 = x->root_right;

//     x->root_right = y;
//     y->root_left = t2;

//     updateBalance(y);
//     updateBalance(x);
// }



// NoArv* rotateLeft(NoArv* root) {
//     NoArv* newRoot = root->noDir;
//     root->noDir = newRoot->noEsq; // Reatribui o filho esquerdo da nova raiz.
//     newRoot->noEsq = root;       // Faz a antiga raiz virar o filho esquerdo da nova raiz.

//     // Atualiza os fatores de balanceamento.
//     root->bf = 0;
//     newRoot->bf = 0;

//     return newRoot;              // Retorna a nova raiz.
// }
// NoArv* rotateRight(NoArv* root) {
//     NoArv* newRoot = root->noEsq;
//     root->noEsq = newRoot->noDir; // Reatribui o filho direito da nova raiz.
//     newRoot->noDir = root;       // Faz a antiga raiz virar o filho direito da nova raiz.

//     // Atualiza os fatores de balanceamento.
//     root->bf = 0;
//     newRoot->bf = 0;

//     return newRoot;              // Retorna a nova raiz.
// }


// NoArv* inserirNo(NoArv* noRaiz, int valor) {
//     if (noRaiz == NULL)
//         return criarNo(valor); // Cria um novo nó se a raiz for NULL.

//     if (valor < noRaiz->info) {
//         // Inserir à esquerda.
//         noRaiz->noEsq = inserirNo(noRaiz->noEsq, valor);

//         // Balanceamento da subárvore esquerda.
//         if (noRaiz->bf == 1) {
//             noRaiz->bf = 0;
//         } else if (noRaiz->bf == 0) {
//             noRaiz->bf = -1;
//         } else if (noRaiz->bf == -1) {
//             // Rotação à esquerda, pois o fator ficou desbalanceado.
//             noRaiz = rotateRight(noRaiz);
//         }
//     } else if (valor > noRaiz->info) {
//         // Inserir à direita.
//         noRaiz->noDir = inserirNo(noRaiz->noDir, valor);

//         // Balanceamento da subárvore direita.
//         if (noRaiz->bf == -1) {
//             noRaiz->bf = 0;
//         } else if (noRaiz->bf == 0) {
//             noRaiz->bf = 1;
//         } else if (noRaiz->bf == 1) {
//             noRaiz = rotateLeft(noRaiz);
//         }
//     }

//     return noRaiz; // Retorna a raiz atualizada.
// }


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
    printf("%d fb %d\n",raiz->info, raiz->bf);
}
