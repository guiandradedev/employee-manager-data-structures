#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED 

// Structs
typedef struct user {
    int code;
    char name[81];
    int age;
    char role[31];
    float salary;
} User;

typedef struct node {
    User user;
    struct node* root_left;
    struct node* root_right;
} Root;

typedef struct tree {
    Root* root;
} Tree;

#endif // STRUCTS_H_INCLUDED