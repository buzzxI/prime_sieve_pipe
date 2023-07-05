#include "prime.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s number\n", argv[0]);
        exit(1);
    }

    int top = atoi(argv[1]);
    
    PipePair pair;
    init_pair(&pair);

    char buff[MAXBUF];
    pid_t pid;
    if ((pid = Fork()) == 0) {
        // child process
        child_trim(&pair);

        char parent_2_child[FD_SIZE];
        char child_2_parent[FD_SIZE];
        sprintf(parent_2_child, "%d", pair.parent_2_child[0]);
        sprintf(child_2_parent, "%d", pair.child_2_parent[1]);
        char* const child_argv[] = {"./prime", parent_2_child, child_2_parent, 0};
        // Execve("./parallel_prime", NULL, NULL);
        Execve(child_argv[0], child_argv, environ);
    } else {
        // parent process
        parent_trim(&pair);

        int i;
        for (i = 2; i < top; i++) {
            sprintf(buff, "%d", i);
            Write(pair.parent_2_child[1], buff, strlen(buff));
            Read(pair.child_2_parent[0], buff, MAXBUF);
        }
        parent_close(&pair);
    }
    exit(0);
}