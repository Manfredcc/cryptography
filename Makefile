objects = cryptography.o lib.o reverse.o

launch : $(objects)
	gcc -o launch $(objects)

cryptography.o : lib.h
lib.o : reverse.h

.PHONY : clean
clean :
	rm launch $(objects)
