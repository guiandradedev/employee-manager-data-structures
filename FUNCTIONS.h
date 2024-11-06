#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED 

User* searchTree(Tree *tree, int code) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    Root* current = tree->root;
    while (current != NULL) {
        if (code > current->user.code) {
            current = current->root_right;
        } else if (code < current->user.code) {
            current = current->root_left;
        } else {
            return &current->user;
        }
    }
    return NULL;
}

User* findOlder(Root* root_tree, User* older) {
    if (root_tree == NULL) {
        return older;
    }

    if (root_tree->user.age >= older->age) {
        older = &root_tree->user;
    }

    if (root_tree->root_left != NULL) {
        older = findOlder(root_tree->root_left, older);
    }
    if (root_tree->root_right != NULL) {
        older = findOlder(root_tree->root_right, older);
    }

    return older;
}

User* findYounger(Root* root_tree, User* younger) {
    if (root_tree == NULL) {
        return younger;
    }

    if (root_tree->user.age < younger->age) {
        younger = &root_tree->user;
    }

    if (root_tree->root_right != NULL) {
        younger = findYounger(root_tree->root_right, younger);
    }

    if (root_tree->root_left != NULL) {
        younger = findYounger(root_tree->root_left, younger);
    }

    return younger;
}

char* strupper(char* string){
    char* result = malloc((strlen(string)+1)* sizeof(char));

    if(result == NULL){
        printf("Alocating error");
        return NULL;
    }

    for (int i = 0; i < strlen(string); i++) {
        result[i] = toupper(string[i]);
    }
    result[strlen(string)] = '\0';

    return result;
}

int printRole(Root* root,char* role){
    int sum = 0;
    if(root == NULL){
        printf("Arvore Vazia\n");
        return 0;
    }

    if(strcmp(strupper(role),strupper(root->user.role)) == 0){
        printUser(&root->user);
        printf("---\n");
        sum++;
    }

    if(root->root_right != NULL){
        sum += printRole(root->root_right,role);
    }

    if(root->root_left != NULL) {
        sum += printRole(root->root_left,role);
    }
    return sum;
}

void mensagem_erro(char* mensagem) {
    vermelho();
    printf("%s\n", mensagem);
    resetcor();
}

void mensagem_sucesso(char*mensagem){
    verde();
    printf("%s\n", mensagem);
    resetcor();
}

void mensagem_amarela(char* mensagem){
    amarelho();
    printf("%s\n", mensagem);
    resetcor();
}

void fimFuncao() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    system("cls");
}

bool emptyTreeMessage(Tree *tree) {
    if(isEmptyTree(tree)) {
        mensagem_erro("A arvore esta vazia!");
        return true;
    }
    return false;
}

void trimTrailingSpaces(char *str) {
    int length = strlen(str);
    while (length > 0 && isspace((unsigned char)str[length - 1])) {
        str[length - 1] = '\0';
        length--;
    }
}

void padWithSpaces(char *str, int length) {
    int currentLength = strlen(str);
    while (currentLength < length) {
        str[currentLength] = ' ';
        currentLength++;
    }
    str[currentLength] = '\0';
}

char* formatRow(User* user) {
    static char row[200];

    padWithSpaces(user->name, 38);
    padWithSpaces(user->role, 23);
    // 3 a menos que o valor original
    // pq? nao sei

    snprintf(row, sizeof(row), "%d %s %d %s %.2f",
             user->code, user->name, user->age, user->role, user->salary);

    return row;
}

void insertUserInFile(Root* root, FILE *ARQ) {
    if(root == NULL){
        printf("Arvore Vazia\n");
        return;
    }
    fprintf(ARQ,"%s\n",formatRow(&root->user));//Grava os elementos do vetor
    if(root->root_right != NULL){
        insertUserInFile(root->root_right, ARQ);
    }
    if(root->root_left != NULL) {
        insertUserInFile(root->root_left, ARQ);
    }
}


#endif // ROOT_H_INCLUDED