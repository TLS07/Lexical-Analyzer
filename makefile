a.out : main.o functions.o lexical_analyze.o  sample.o 
	gcc -o a.out main.o functions.o lexical_analyze.o  sample.o 

main.o:main.c
	gcc -c main.c

functions.o:functions.c
	gcc -c functions.c

lexical_analyze.o:lexical_analyze.c
	gcc -c lexical_analyze.c

sample.o:sample.c
	gcc -c sample.c

clean :  
	rm -f *.exe *.o



