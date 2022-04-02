all:	main
main:	main.o 
		gcc -g -o main main.o /home/asus/CTdich/Bai_1/lib/libfdr.a -lm
main.o:	main.c 
	gcc -g -I/home/asus/CTdich/Bai_1/include -c main.c -lm
clean:	
	rm -f *.o *~
