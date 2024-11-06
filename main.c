#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "STRUCTS.h"
#include "ROOT.h"
#include "PROTOTIPOS.h"
#include "colors.h"
#include "FUNCTIONS.h"

// Para evitar problemas de compilador devido ao path
#define DATA_PATH "../Dados.txt"

void header();
void menu();
int readFile(Tree* tree); // ok
int newFile(Tree* tree, int N); // ok
void findUser(Tree* tree); // ok
User* findUserByCode(Tree* tree); // ok
void findOlderAndYounger(Tree* tree); // ok
void findUserByRole(Tree* tree); // ok
void printAllUsers(Tree *tree); // ok

void insertUser(Tree *tree, int *N); // not ok
void removeUser(Tree *tree, int *N); // ok
void updateUser(Tree *tree); // not ok

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Tree* tree = createTree();
    int N = 0;
    N = readFile(tree);
    int op;

    do{
        op=0;
        menu();
        scanf("%d",&op);

        switch (op){
        case 1:
            // inserir um funcionario
            break;
        case 2:
            // atualizar um funcionario
            break;
        case 3:
            // remover um funcionario
            removeUser(tree, &N);
            break;
        case 4:
            // buscar um funcionario pelo codigo
            findUser(tree);
            break;
        case 5:
            // buscar o mais novo e o mais velho
            findOlderAndYounger(tree);
            break;
        case 6:
            // buscar todos por cargo
            findUserByRole(tree);
            break;
        case 7:
            // imprimir todos
            printAllUsers(tree);
            break;
        case 8:
            // fim do codigo
            break;
        default:
            mensagem_erro("Comando incorreto.");
            break;
        }
    }while (op != 8);

    mensagem_sucesso("Obrigado por acessar o sistema.");

    newFile(tree, N);

    cleanTree(tree);

    return 0;
}

void header() {
    printf("-------\n");
    printf("Sistema de Funcionarios\n");
    printf("-------\n");
}

int readFile(Tree* tree){
    FILE *ARQ;
    int N=0;
    ARQ = fopen(DATA_PATH, "r");
    if(ARQ == NULL) {
        header();
        printf("Erro na abertura do arquivo, programa encerrando.\n");
        system("pause");
        exit(0);
    }
    fscanf(ARQ, "%d", &N);
    // printf("Quantidade de usuarios a serem cadastrados: %d\n", N);

    User aux;
    char line[200];
    for (int i = 0; i < N; i++) {
        fflush(stdin);
        if (fgets(line, sizeof(line), ARQ) != NULL) {
            // Le até encontrar um número
            fscanf(ARQ, "%d %40[^0-9] %d %49[^0-9] %f", &aux.code, aux.name, &aux.age, aux.role, &aux.salary);

            trimTrailingSpaces(aux.name);
            trimTrailingSpaces(aux.role);
            insertTree(tree, aux);
        }
    }

    fclose(ARQ);
    return N;
}
int newFile(Tree* tree, int N){
    FILE *ARQ;
    ARQ = fopen("../Dados2.txt", "w");
    if(ARQ == NULL) {
        header();
        printf("Erro na abertura do arquivo, programa encerrando.\n");
        system("pause");
        exit(0);
    }
    fprintf(ARQ,"%d\n",N);

    insertUserInFile(tree->root, ARQ);

    fclose(ARQ);
    return N;
}

void menu() {
    header();
    printf("O que deseja fazer?\n");
    printf("[1] - Inserir funcionario           [5] - Buscar mais novo e mais velho\n");
    printf("[2] - Atualizar funcionario         [6] - Buscar pelo cargo\n");
    printf("[3] - Remover funcionario           [7] - Imprimir todos\n");
    printf("[4] - Buscar pelo codigo            [8] - Sair do sistema\n");
    printf("\nOpcao: ");
}

void findUser(Tree* tree) {
    header();

    User* user = findUserByCode(tree);
    printf("Situacao da busca: ");
    if(user == NULL) {
        mensagem_erro("Usuario nao encontrado!");
        return;
    }
    mensagem_sucesso("Usuario encontrado!");
    printf("\n");
    printUser(user);

    fimFuncao();
}
User* findUserByCode(Tree* tree) {
    int code;
    printf("Insira o codigo que deseja buscar:\n");
    do {
        scanf("%d", &code);
        if(code < 1000 || code > 9999) {
            mensagem_erro("Insira um codigo entre 1000 e 9999!");
        }
    } while(code < 1000 || code > 9999);

    return searchTree(tree, code);
}

void findOlderAndYounger(Tree* tree) {
    header();

    printf("Buscar o funcionario mais velho e o mais novo\n");

    if(emptyTreeMessage(tree)) return;
    printf("\n");

    printf("Funcionario mais velho:\n");
    printUser(findOlder(tree->root, &tree->root->user));

    printf("\n");

    printf("Funcionario mais novo\n");
    printUser(findYounger(tree->root,&tree->root->user));

    fimFuncao();
}

void findUserByRole(Tree* tree) {
    char *role = (char*)malloc(50*sizeof(char));
    header();

    printf("Busca por cargo\n");

    if(emptyTreeMessage(tree)) return;
    printf("\n");

    fflush(stdin);
    printf("Qual cargo deseja buscar?\n");
    scanf("%[^\n]s",role);

    int n = printRole(tree->root, role);

    if(n == 0) {
        mensagem_erro("Nenhum usuario com este cargo foi encontrado!");
    }

    free(role);

    fimFuncao();
}

void printAllUsers(Tree *tree) {
    header();

    printInOrder(tree->root);

    fimFuncao();
}

void insertUser(Tree *tree, int *N) {
    header();
    printf("Inserir um usuario na arvore\n");
    fimFuncao();
}
void removeUser(Tree *tree, int *N) {
    header();
    printf("Remover um usuario da arvore\n");
    
    if(emptyTreeMessage(tree)) return;
    printf("\n");

    User* user = findUserByCode(tree);
        int remove = 0;

    if(user == NULL) {
        mensagem_erro("Usuario nao encontrado!");
        return;
    }
    mensagem_sucesso("Usuario encontrado!");
    printUser(user);
    printf("Deseja realmente remover este usuario? [1]: sim; [2]: nao\n");
    do {
        scanf("%d", &remove);
        if(remove != 1 && remove != 2) {
            mensagem_erro("Insira um valor valido entre 1 e 2");
        }
    } while(remove != 1 && remove != 2);

    if(remove == 1) {
        removeFromTree(tree, user->code);
        mensagem_sucesso("Usuario removido com sucesso!");
    }

    (*N)--;

    fimFuncao();
}
void updateUser(Tree *tree) {
    header();
    printf("Atualizar um usuario da arvore\n");
    
    if(emptyTreeMessage(tree)) return;
    printf("\n");

    User* user = findUserByCode(tree);
    fimFuncao();
}