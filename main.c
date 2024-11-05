#include <stdio.h>
#include <stdlib.h>
#include "STRUCTS.h"
#include "ROOT.h"
#include <string.h>
#include <ctype.h>


int main() {
    Tree* tree = createTree();
    
    printf("Vazia: %d\n", isEmptyTree(tree));

    insertTree(tree, (User){1236, "Pedro", 62, "Eletricista", 1252});
    insertTree(tree, (User){1239, "Guilherme2", 17, "GAROTO DE PROGRAMA", 1251});
    insertTree(tree, (User){1235, "Joao", 21, "GAROTO DE PROGRAMA", 1250});
    insertTree(tree, (User){1234, "Guilherme", 19, "GAROTO DE PROGRAMA", 1251});
    insertTree(tree, (User){1240, "Joao3", 1, "Eletricista", 1250});
    insertTree(tree, (User){1241, "Pedro4", 22, "GAROTO DE PROGRAMA", 1252});
    insertTree(tree, (User){1243, "Luigi6", 10, "GAROTO DE PROGRAMA", 100});
    insertTree(tree, (User){1237, "Robson", 40, "eletricista", 1240});
    insertTree(tree, (User){1238, "Luigi", 21, "GAROTO DE PROGRAMA", 100});
    insertTree(tree, (User){1242, "Robson5", 20, "GAROTO DE PROGRAMA", 1240});

    // printf("Vazia: %d\n", isEmptyTree(tree));

    // printf("Pre: ");
    // printPreOrder(tree->root);

    // printf("Buscaar 1240\n");
    // printUser(searchTree(tree, 1240));

    // printf("Usuario 1240 removido\n");

    // removeFromTree(tree, 1240);
    // printf("Buscar 1240\n");
    // printUser(searchTree(tree, 1240));

    // cleanTree(tree);
    // printf("Vazia: %d\n", isEmptyTree(tree));

    User* older = findOlder(tree->root, &tree->root->user);

    printf("mais velho:\n\n");
    printUser(older);

    User* younger = findYounger(tree->root,&tree->root->user);
    
    printf("mais novo:\n\n");
    printUser(younger);
    printf("\n\n");
 
    printRole(tree->root,"Eletricista");

    cleanTree(tree);

    return 0;
}