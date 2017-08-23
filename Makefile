SRCDIR = src

testnet: main.o nnet.o
	gcc -o testnet main.o nnet.o -lm

main.o: $(SRCDIR)/main.c
	gcc -o main.o -c $(SRCDIR)/main.c

nnet.o: $(SRCDIR)/nnet.c
	gcc -o nnet.o -c $(SRCDIR)/nnet.c
