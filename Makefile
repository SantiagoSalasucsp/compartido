CC = gcc
CXX = g++ 

all: init.exe px.exe r.exe px-cpp.exe

init.exe: init.o
	$(CC) -o init.exe init.o

px.exe: px.o
	$(CC) -o px.exe px.o

r.exe: r.o
	$(CC) -o r.exe r.o

px-cpp.exe: px-cpp.o  
	$(CXX) -o px-cpp.exe px-cpp.o

init.o: init.c
	$(CC) -c init.c

px.o: px.c
	$(CC) -c px.c

r.o: r.c
	$(CC) -c r.c

px-cpp.o: px-cpp.cpp  
	$(CXX) -c px-cpp.cpp

clean:
	rm -f *.exe *.o
