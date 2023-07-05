LD_FLAGS := -lcsapp
CC := gcc

.PHONY: all
all: main prime

main: main.c
	${CC} -o $@ $^ ${LD_FLAGS}

prime: prime.c
	${CC} -o $@ $^ ${LD_FLAGS}

clean: 
	rm -rf main prime
