CXX = g++
CXXFLAGS = -Wall -O2
TARGET = main
LIB = main.o city.o gene.o train.o
HEADERS = city.hpp gene.hpp train.hpp

all: $(TARGET)

clean:
	rm -f *.o
	rm -f -r *.dSYM
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

$(TARGET): $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(HEADERS) makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<
