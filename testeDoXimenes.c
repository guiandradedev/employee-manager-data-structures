#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
// #include "STRUCTS.h"
// #include "ROOT.h"
// #include "PROTOTIPOS.h"
#include "colors.h"
// #include "FUNCTIONS.h"

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
void removeFromTree(Arv* tree,int info);
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

    removeFromTree(arvore, 8);

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

NoArv* removeAux(NoArv* root, int info, int* alterou) {
    if(root == NULL) {
        printf("Usuario nao encontrado\n");
    } else {
        if(info > root->info) {
            root->noDir = removeAux(root->noDir, info, alterou);
            // direita
            if (*alterou) {
                root->bf--;
            }
        } else {
            if(info < root->info) {
                root->noEsq = removeAux(root->noEsq, info, alterou);
                // esquerda
                if (*alterou) {
                    root->bf++;
                }
            } else {
                // achou o no
                *alterou = 1;
                if(root->noDir == NULL && root->noEsq == NULL) {
                    free(root); // no sem filhos
                    root = NULL;
                } else {
                    if(root->noEsq == NULL) {
                        // so um filho da direita
                        NoArv* aux = root;
                        root = root->noDir;
                        free(aux);
                    } else {
                        if(root->noDir == NULL) {
                            // so tem filho da esquerda
                            NoArv* aux = root;
                            root = root->noEsq;
                            free(aux);
                        } else {
                            // tem os dois filhos
                            NoArv* aux = root->noEsq;
                            while(aux->noDir != NULL) {
                                aux = aux->noDir;
                            }
                            root->info = aux->info; // troca as informacoes
                            aux->info = info;
                            root->noEsq = removeAux(root->noEsq, info,alterou);
                        }
                    }
                }
            }
        }
    }
    root = balancear(root);

    if (root->bf == 0) {
        *alterou = 0;
    }

    return root;
}

void removeFromTree(Arv *tree, int info) {
    NoArv*aux = tree->raiz;
    if((aux->info == info) && (aux->noEsq == NULL) && (aux->noDir == NULL)) {
        free(aux);
        free(tree);
        return;
    }
    int alterou = 0;
    tree->raiz = removeAux(tree->raiz, info, &alterou);
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
    printf("%d fb %d\n",raiz->info, raiz->bf);
}
