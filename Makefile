all:
	gcc -pedantic ./src/fool.c -o fool

debug:
	gcc -pedantic -g ./src/fool.c -o fool

