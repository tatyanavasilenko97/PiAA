all: lab1 clean

lab1: seti_3.o 
	g++ seti_3.o -o lab

seti_3.o: seti_3.cpp
	g++ -std=c++11 -c seti_3.cpp

		
clean:
	rm -rf *.o lab1

