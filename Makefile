CC = g++
FLAGS = -std=c++11
TARGET = zre_proj_linux


all: $(TARGET)

$(TARGET): main.cpp filter.o synthesize.o
	$(CC) $(FLAGS) -o $(TARGET) main.cpp filter.o synthesize.o

synthesize.o: synthesize.cpp synthesize.h
	$(CC) $(FLAGS) -c synthesize.cpp 

filter.o: filter.cpp filter.h
	$(CC) $(FLAGS) -c filter.cpp

clean:
	rm $(TARGET)
	rm filter.o
	rm synthesize.o

