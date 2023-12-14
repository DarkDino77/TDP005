# target: prerequisites
#    recipe

CXXFLAGS = -std=c++17 -g -Wall

prog: foo.o main.o
    g++ $(CXXFLAGS) foo.o main.o -o prog

foo.o: foo.cpp foo.h
    g++ -c -std=c++17 -g -Wall foo.cpp -o foo.o
    
main.o: main.cpp foo.h
    g++ -c -std=c++17 -g -Wall main.cpp -o main.o

.PHONY: clean
clean:
    rm *.o prog

# gnu.org/software/make/manual
