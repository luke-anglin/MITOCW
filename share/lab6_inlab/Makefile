# I want two different ones. One for the progrma with the normal tester, and one with LukeTests.cpp 

CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall -g -O2 -std=c++11 # I always like debug mode 

OBJECTS = hashTable.o timer.o timer_test.o worldPuzzle.o

run: $(OBJECTS)
	$(CXX) $(OBJECTS)


hashTable.o: hashTable.cpp
timer.o: timer.cpp timer.h
timer_test.o: timer_test.cpp timer.h
worldPuzzle.o: worldPuzzle.cpp timer.h



.PHONY: clean 
clean: 
	-rm -f *.o *~ a.out

