#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED 

void mensagem_erro(char *mensagem);
void mensagem_amarela(char* mensagem);
void mensagem_sucesso(char*mensagem);
void fimFuncao();
User* searchTree(Tree *tree, int code);
User* findOlder(Root* root_tree, User* older) ;
User* findYounger(Root* root_tree, User* younger) ;
char* strupper(char* string);
int printRole(Root* root,char* role);
bool emptyTreeMessage(Tree *tree);
void trimTrailingSpaces(char *str);
void padWithSpaces(char *str, int length);
void insertUserInFile(Root* root, FILE *ARQ);
char* formatRow(User* user);
void clear();
char* setRole();
User* findUserByName(Tree* tree);

#endif // STRUCTS_H_INCLUDED