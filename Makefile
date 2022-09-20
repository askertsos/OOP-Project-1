School	:	Myclasses.o School.cpp
	g++  Myclasses.o -o School School.cpp

Myclasses.o	:	Myclasses.cpp
	g++ -c Myclasses.cpp

clean	:
	rm School Myclasses.o