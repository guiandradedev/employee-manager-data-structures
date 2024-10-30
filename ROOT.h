#ifndef ROOT_H_INCLUDED
#define ROOT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "STRUCTS.h"

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

Root* insertNode(Root *root, User user) {
    if(root == NULL) {
        return createNode(user);
    }
    if(user.code < root->user.code) {
        root->root_left = insertNode(root->root_left, user);
    } else if(user.code > root->user.code){
        root->root_right = insertNode(root->root_right, user);
    }
    return root;
}

void insertTree(Tree *tree, User user) {
    tree->root = insertNode(tree->root, user);
}

int isEmptyTree(Tree* tree) {
    return tree->root == NULL;
}

void printUser(User user) {
    printf("Codigo: %d\n", user.code);
    printf("Nome: %s\n", user.name);
    printf("Idade: %d\n", user.age);
    printf("Cargo: %s\n", user.role);
    printf("Salario: R$ %.2f\n", user.salary);
}

void printPreOrder(Root *root) {
    if(root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    printUser(root->user);
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
    printUser(root->user);
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
    printUser(root->user);
    printf("---\n");
    if(root->root_left != NULL) {
        printInOrder(root->root_left);
    }
}

User* searchTree(Root *root, int code) {
    if(code > root.user.code) {
        
    } else if(code < root->user.code){

    }
    return root;
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