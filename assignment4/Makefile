CXX = g++
CXXFLAGS = -g -Wall

all: dog
#TARGET : Dependencies
#[TAB] Rule

dog: dog.o function.o
	$(CXX) $(CXXFLAGS) -o dog dog.o function.o

dog.o: dog.cc function.h
	$(CXX) $(CXXFLAGS) -c dog.cc

function.o: function.h

clean:
	rm *.o dog 
