all:
	gcc -Wall -pedantic ./src/fool.c -o fool

debug:
	gcc -Wall -pedantic -g ./src/fool.c -o fool

