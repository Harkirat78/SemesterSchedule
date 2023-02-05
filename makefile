soomalHarkiratA1: soomalHarkiratA1.o soomalHarkiratA1Main.o
	gcc -Wall -std=c99 soomalHarkiratA1.o soomalHarkiratA1Main.c -o soomalHarkiratA1

soomalHarkiratA1.o: soomalHarkiratA1.c givenA1.h
	gcc -Wall -std=c99 -c soomalHarkiratA1.c

soomalHarkiratA1Main.o: soomalHarkiratA1Main.c givenA1.h
	gcc -Wall -std=c99 -c soomalHarkiratA1Main.c

clean:
	rm *.o soomalHarkiratA1

