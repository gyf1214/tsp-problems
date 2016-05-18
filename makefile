CXX = g++
CXXFLAGS = -Wall -O2
TARGET = main
LIB = main.o city.o gene.o train.o

all: $(TARGET)

clean:
	rm -f *.o
	rm -f -r *.dSYM
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

$(TARGET): $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^
