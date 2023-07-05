#include <csapp.h>
#define FD_SIZE 8

typedef struct PipePair {
    int parent_2_child[2];
    int child_2_parent[2];
} PipePair;

void init_pair(PipePair* pair) {
    int rst = pipe(pair->parent_2_child); 
    if (rst < 0) {
        fprintf(stderr, "parent to child pipe error\n");
        exit(1);
    }
    rst = pipe(pair->child_2_parent);
    if (rst < 0) {
        fprintf(stderr, "child to parent pipe error\n");
        exit(1);
    }
}

void child_trim(PipePair* pair) {
    Close(pair->parent_2_child[1]);
    Close(pair->child_2_parent[0]);
}

void child_close(PipePair* pair) {
    Close(pair->parent_2_child[0]);
    Close(pair->child_2_parent[1]);
}

void parent_trim(PipePair* pair) {
    Close(pair->parent_2_child[0]);
    Close(pair->child_2_parent[1]);
}

void parent_close(PipePair* pair) {
    Close(pair->parent_2_child[1]);
    Close(pair->child_2_parent[0]);
}