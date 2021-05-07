CC = g++
CFLAGS = -std=c++17 -g -O -Wall -Werror -pedantic
SFML = -lsfml-graphics -lsfml-window -lsfml-system
OBJ = main.o
EXE = bubbleSort

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(SFML)

clean:
	rm -f $(EXE) $(OBJ)