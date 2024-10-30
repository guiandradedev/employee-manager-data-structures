#include <stdio.h>
#include <stdlib.h>
#include "STRUCTS.h"
#include "ROOT.h"

int main() {
    Tree* tree = createTree();
    
    printf("Vazia: %d\n", isEmptyTree(tree));

    insertTree(tree, (User){1234, "Guilherme", 19, "GAROTO DE PROGRAMA", 1251});
    insertTree(tree, (User){1235, "Joao", 19, "GAROTO DE PROGRAMA", 1250});
    insertTree(tree, (User){1236, "Pedro", 19, "GAROTO DE PROGRAMA", 1250});
    insertTree(tree, (User){1237, "Robson", 19, "GAROTO DE PROGRAMA", 1250});
    insertTree(tree, (User){1238, "Luigi", 20, "GAROTO DE PROGRAMA", 100});

    printf("Vazia: %d\n", isEmptyTree(tree));

    printf("Pre: ");
    printPreOrder(tree->root);

    // printUser(*findTree(tree, 1235));

    // printf("\n");
    // printf("In: ");
    // printInOrder(tree->root);
    // printf("\n");
    // printf("Pos: ");
    // printPosOrder(tree->root);
    // printf("\n");

    cleanTree(tree);
    printf("Vazia: %d\n", isEmptyTree(tree));
    

    return 0;
}