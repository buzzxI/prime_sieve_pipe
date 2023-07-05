#include "prime.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "parallel prime error\n");
        exit(1);
    }

    int read_parent = atoi(argv[1]);
    int write_parent = atoi(argv[2]);

    char buff[MAXBUF];
    int p, n, rst;
    if ((rst = Read(read_parent, buff, MAXBUF))) {
        p = atoi(buff);
        fprintf(stdout, "prime: %d\n", p);
        Write(write_parent, buff, strlen(buff));
    }
    
    if (rst != 0) {
        PipePair pair;
        init_pair(&pair);

        pid_t pid;
        if ((pid = Fork())) {
            // child process
            child_trim(&pair);
             
            char parent_2_child[FD_SIZE];
            char child_2_parent[FD_SIZE];
            sprintf(parent_2_child, "%d", pair.parent_2_child[0]);
            sprintf(child_2_parent, "%d", pair.child_2_parent[1]);
            char* const child_argv[] = {"./prime", parent_2_child, child_2_parent, 0};        
            Execve(child_argv[0], child_argv, environ);
        } else {
            // parent process
            parent_trim(&pair);

            while (rst = Read(read_parent, buff, MAXBUF)) {
                Write(write_parent, buff, strlen(buff));
                n = atoi(buff);
                if (n % p != 0) {
                    Write(pair.parent_2_child[1], buff, strlen(buff));
                    Read(pair.child_2_parent[0], buff, MAXBUF); 
                }
            }
            parent_close(&pair);
            Close(read_parent);
            Close(write_parent);
        }
    }
    exit(0);
}