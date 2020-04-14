output: driver.o defrag.o freelist.o listfunc.o managerial.o 
	gcc -o final.exe driver.o defrag.o freelist.o listfunc.o managerial.o
	./final.exe
	make clean

driver.o : driver.c
	gcc -c driver.c

defrag.o : defrag.c
	gcc -c defrag.c

freelist.o : freelist.o
	gcc -c freelist.c

listfunc.o : listfunc.c
	gcc -c listfunc.c

managerial.o : managerial.c
	gcc -c managerial.c

clean:
	rm *.o
	rm final.exe

