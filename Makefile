CC = gcc

all: init.exe px.exe r.exe
init.exe: init.o
	$(CC) -o init.exe init.o

px.exe: px.o
	$(CC) -o px.exe px.o

r.exe: r.o
	$(CC) -o r.exe r.o

init.o: init.c
	$(CC) -c init.c

px.o: px.c
	$(CC) -c px.c

r.o: r.c
	$(CC) -c r.c

clean:
	rm -f *.exe *.o