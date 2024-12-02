#ifndef ROOT_H_INCLUDED
#define ROOT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "STRUCTS.h"
#include <string.h>
#include <ctype.h>

Tree* createTree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

Root* createNode(User user) {
    Root* node = (Root*)malloc(sizeof(Root));
    node->user = user;
    node->root_left = NULL;
    node->root_right = NULL;
    return node;
}

Root* insertNode(Root *root, User user,int *N) {
    if(root == NULL) {
        return createNode(user);
    }
    if(user.code < root->user.code) {
        root->root_left = insertNode(root->root_left, user,N);
    } else if(user.code > root->user.code){
        root->root_right = insertNode(root->root_right, user,N);
    }else if (user.code == root->user.code){
        (*N)--;
        return root;
    }
    return root;
}

void insertTree(Tree *tree, User user,int *N) {
    tree->root = insertNode(tree->root, user,N);
}

int isEmptyTree(Tree* tree) {
    return tree->root == NULL;
}

void printUser(User* user) {
    if(user != NULL) {
        printf("Codigo: %d\n", user->code);
        printf("Nome: %s\n", user->name);
        printf("Idade: %d\n", user->age);
        printf("Cargo: %s\n", user->role);
        printf("Salario: R$ %.2f\n", user->salary);
    } else {
        printf("Usuario nao encontrado\n");
    }
}

void printPreOrder(Root *root) {
    if(root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    printUser(&root->user);
    printf("---\n");
    if(root->root_right != NULL){
        printPreOrder(root->root_right);
    }
    if(root->root_left != NULL) {
        printPreOrder(root->root_left);
    }
}
void printPosOrder(Root *root) {
    if(root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    if(root->root_right != NULL){
        printPosOrder(root->root_right);
    }
    if(root->root_left != NULL) {
        printPosOrder(root->root_left);
    }
    printUser(&root->user);
    printf("---\n");
}
void printInOrder(Root *root) {
    if(root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    if(root->root_right != NULL){
        printInOrder(root->root_right);
    }
    printUser(&root->user);
    printf("---\n");
    if(root->root_left != NULL) {
        printInOrder(root->root_left);
    }
}

Root* removeAux(Root* root, int code) {
    if(root == NULL) {
        printf("Usuario nao encontrado\n");
    } else {
        if(code > root->user.code) {
            root->root_right = removeAux(root->root_right, code);
        } else {
            if(code < root->user.code) {
                root->root_left = removeAux(root->root_left, code);
            } else {
                // achou o no
                if(root->root_right == NULL && root->root_left == NULL) {
                    free(root); // no sem filhos
                    root = NULL;
                } else {
                    if(root->root_left == NULL) {
                        // so um filho da direita
                        Root* aux = root;
                        root = root->root_right;
                        free(aux);
                    } else {
                        if(root->root_right == NULL) {
                            // so tem filho da esquerda
                            Root* aux = root;
                            root = root->root_left;
                            free(aux);
                        } else {
                            // tem os dois filhos
                            Root* aux = root->root_left;
                            while(aux->root_right != NULL) {
                                aux = aux->root_right;
                            }
                            root->user = aux->user; // troca as informacoes
                            aux->user.code = code;
                            root->root_left = removeAux(root->root_left, code);
                        }
                    }
                }
            }
        }
    }
    return root;
}

User* removeFromTree(Tree *tree, int code) {
    Root*aux = tree->root;
    if((aux->user.code == code) && (aux->root_left == NULL) && (aux->root_right == NULL)) {
        free(aux);
        free(tree);
        return NULL;
    }
    tree->root = removeAux(tree->root, code);
    return &tree->root->user;
}

Root *cleanRoot(Root *root){
    if(root->root_right != NULL){
        root->root_right = cleanRoot(root->root_right);
    }else if(root->root_left != NULL){
        root->root_left = cleanRoot(root->root_left);
    }
    free(root);
    return NULL;
}

void cleanTree(Tree *tree){
    if(isEmptyTree(tree)){
        printf("tree is already empty!\n");
    }else{
        cleanRoot(tree->root);
        free(tree);
    }
}



#endif // ROOT_H_INCLUDED
