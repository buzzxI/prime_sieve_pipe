# prime sieve with pipes

## desc

this repo is implement a prime sieve with linux pipe mechanism, the mean idea is introduced in [this page](https://swtch.com/~rsc/thread/#1)

the repo need to be run with csapp environment(or you can change prime.h and include std library yourself)

it should be pointed out that: pipes does not make prime sieve run faster, this program is way slower than [Euler sieve](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)

> the main reason is when the range is too large, the program will create too many child process, each child get less work than their parent, making this parallel computing imbalanced

## run

to run this repo, run `make all` first, and run `./main <base>`, where base limit the range of prime sieve

if you change the source code, remember to run `make clean` before `make all`