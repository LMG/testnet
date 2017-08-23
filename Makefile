SRCDIR = src

testnet: main.o
	gcc -o testnet main.o -lm

main.o: $(SRCDIR)/main.c
	gcc -o main.o -c $(SRCDIR)/main.c

