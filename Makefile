objects = cryptography.o lib.o definition.o

launch : $(objects)
	gcc -o launch $(objects)

cryptography.o : lib.h
lib.o : definition.h

.PHONY : clean
clean :
	rm launch $(objects)
