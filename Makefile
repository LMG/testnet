SRCDIR = src

testnet: main.o nnet.o random.o
	gcc -o testnet main.o nnet.o random.o -lm

main.o: $(SRCDIR)/main.c
	gcc -o main.o -c $(SRCDIR)/main.c

nnet.o: $(SRCDIR)/nnet.c
	gcc -o nnet.o -c $(SRCDIR)/nnet.c

random.o: $(SRCDIR)/random.c
	gcc -o random.o -c $(SRCDIR)/random.c
