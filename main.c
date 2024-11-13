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
#define DATA_PATH "Dados.txt"
#define DATA2_PATH "Dados2.txt"

void header();
void menu();
int readFile(Tree* tree); // ok
int newFile(Tree* tree, int N); // ok
void findUser(Tree* tree); // ok
User* findUserByCode(Tree* tree); // ok
void findOlderAndYounger(Tree* tree); // ok
void findUserByRole(Tree* tree); // ok
void printAllUsers(Tree *tree); // ok

void insertUser(Tree *tree, int *N); // ok
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
            insertUser(tree,&N);
            break;
        case 2:
            updateUser(tree);
            break;
        case 3:
            // remover um funcionario
            removeUser(tree, &N);
            break;
        case 4:
            // buscar um funcionario pelo matricula
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
            // fim do matricula
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
    clear();
    printf("-------\n");
    printf("Sistema de Funcionarios\n");
    printf("-------\n");
}

void getLine(int *index,char* line_file, char* user){
    int j=0;
    bool space_count = false;
    while (line_file[*index] != '\0' && !space_count){
        if (line_file[*index] == ' ' && line_file[*index+1] == ' ') {
            space_count = true;
        } else {
            user[j++] = line_file[*index];
        }
        (*index)++;
    }
    user[j] = '\0';
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
    fscanf(ARQ, "%d\n", &N);
    // printf("Quantidade de usuarios a serem cadastrados: %d\n", N);

    User aux;
    char line[200];
    for (int i = 0; i < N; i++) {
        // flushStdin();
        if (fgets(line, sizeof(line), ARQ) != NULL) {
            // Le até encontrar um número
            line[strcspn(line, "\n")] = '\0';

            sscanf(line, "%d", &aux.code);

            int index = 0;
            
            while(line[index] != ' ') index++;
            index++;

            getLine(&index, line, aux.name);

            while (line[index] == ' '){
                index++;
            }   

            sscanf(&line[index],"%d", &aux.age);

            while(line[index] != ' ') index++;
            index++;

            getLine(&index, line, aux.role);

            while (line[index] == ' '){
                index++;
            } 
            sscanf(&line[index], "%lf\n", &aux.salary);
            // le como longfloat pra evitar bug da leitura da virgula

            insertTree(tree, aux,&N);
        }
    }

    fclose(ARQ);
    return N;
}
int newFile(Tree* tree, int N){
    FILE *ARQ;
    ARQ = fopen(DATA2_PATH, "w");
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
    printf("[2] - Atualizar funcionario         [6] - Imprimir de acordo com o cargo\n");
    printf("[3] - Remover funcionario           [7] - Imprimir todos\n");
    printf("[4] - Buscar funcionario            [8] - Sair do sistema\n");
    printf("\nOpcao: ");
}

void findUser(Tree* tree) {
    header();
    int op;
    User* user;

    do
    {
        printf("Como deseja realizaar a busca?\n");
        printf("[1] - Pela matricula do funcionario\n");
        printf("[2] - Pelo nome do funcionario\n");
        scanf("%d",&op);
    } while (op < 1 || op > 2);
    
    if(op == 1){
        user = findUserByCode(tree);
    }else{
        user = findUserByName(tree);
    }

    printf("Situacao da busca: ");
    if(user == NULL) {
        mensagem_erro("Usuario nao encontrado!");
        fimFuncao();
        return;
    }
    mensagem_sucesso("Usuario encontrado!");
    printf("\n");
    printUser(user);

    fimFuncao();
}

User* findUserByName(Tree* tree){
    char* name;
    do
    {
        printf("Diga o nome do funcionario(maximo de 40 caracteres): ");
        scanf(" %[^\n]s",name);
    } while (strlen(name) > 40);
    
    return searchTreeByName(tree->root,name);
}

int insertCode(){
    int code;
    do {
        scanf("%d", &code);
        if(code < 1000 || code > 9999) {
            mensagem_erro("Insira uma matricula entre 1000 e 9999!");
        }
    } while(code < 1000 || code > 9999);

    return code;
}

User* findUserByCode(Tree* tree) {
    printf("Insira a matricula que deseja buscar:\n");

    return searchTree(tree, insertCode());
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

    flushStdin();
    printf("Qual cargo deseja buscar?\n");
    role = setRole();

    int n = printRole(tree->root, role);

    if(n == 0) {
        mensagem_erro("Nenhum usuario com este cargo foi encontrado!");
    }

    fimFuncao();
}

void printAllUsers(Tree *tree) {
    header();

    printInOrder(tree->root);

    fimFuncao();
}

char* setRole(){
    int op;
    do
    {
        printf("[1]-ANALISTA DE SISTEMAS\n");
        printf("[2]-ANALISTA DE SUPORTE\n");
        printf("[3]-PROGRAMADOR\n");
        printf("[4]-CONTADOR\n");
        printf("[5]-ADMINISTRATIVO\n");
        printf("[6]-GERENTE\n");
        printf("Escolha: ");
        scanf("%d",&op);
        switch (op){
    
        case 1:
            return "ANALISTA DE SISTEMAS";
            break;

        case 2:
            return "ANALISTA DE SUPORTE";
            break;

        case 3:
            return "PROGRAMADOR";
            break;

        case 4:
            return "CONTADOR";
            break;

        case 5:
            return "ADMINISTRATIVO";
            break;

        case 6:
            return "GERENTE";
            break;

        default:
            mensagem_erro("Opcao invalida!\n");
            break;
        }
    } while (op<1 || op>6);
}    

void insertUser(Tree *tree, int *N){
    User aux;
    header();
    printf("Inserir um usuario na arvore\n");
    printf("insira a matricula\n");
    aux.code = insertCode();
    printf("Insira o nome\n");
    scanf(" %[^\n]s",aux.name);
    printf("Insira a idade\n");
    scanf("%d", &aux.age);
    printf("Insira o salario\n");
    scanf("%lf",&aux.salary);
    printf("Insira o cargo\n");
    strcpy(aux.role, setRole());

    (*N)++;

    insertTree(tree,aux,N);

    printf("\n");
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

void updateName(User* user){
    printf("Insira o novo nome de no maximo 40 caracteres: ");
    scanf(" %[^\n]s", user->name);
    mensagem_sucesso("Nome atualizado!");
}

void updateAge(User* user){
    printf("Insira a nova idade: ");
    scanf("%d", &user->age);
    mensagem_sucesso("Idade atualizada!");
}

void updateRole(User* user){
    printf("Diga qual a nova profissao:\n");
    strcpy(user->role,setRole());
    mensagem_sucesso("Profissao atualizada!");
}

void updateSalary(User* user){
    printf("Insira o novo salario: ");
    do
    {
        scanf("%lf", &user->salary);
    } while (user->salary < 0);
    mensagem_sucesso("Salario atualizado!");   
}

void updateUser(Tree *tree) {
    header();
    printf("Atualizar um usuario da arvore\n");
    
    if(emptyTreeMessage(tree)) return;
    printf("\n");

    User* user = findUserByCode(tree);

    if(user == NULL){
        mensagem_erro("usuario nao encontrado");
        fimFuncao();
        return;
    }

    int op;
    do
    {
        header();
        printUser(user);
        printf("-----------------------\n");
        printf("O que deseja atualizar?\n");
        printf("[1]-Nome\n");
        printf("[2]-Idade\n");
        printf("[3]-Profissao\n");
        printf("[4]-Salario\n");
        printf("[5]-Nao desejo atualizar mais\n");
        printf("opcao:");
        scanf("%d",&op);
    
        switch (op){
        case 1:
            updateName(user);
            break;

        case 2:
            updateAge(user);
            break;

        case 3:
            updateRole(user);
            break;

        case 4:
            updateSalary(user);
            break;

        case 5:
            fimFuncao();
            return;
            break;
        
        default:
            mensagem_erro("Opcao invalida");
            break;
        }

    } while (op != 5);
}