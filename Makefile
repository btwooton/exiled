CC = g++
CFLAGS = -std=c++11
LFLAGS = -lncurses
OBJS = main.out
SRC = main.cpp
DEPS = Character.cpp Map.cpp Tile.cpp Room.cpp Money.cpp

exiled:
		$(CC) $(CFLAGS) $(SRC) $(DEPS) $(LFLAGS) -o $(OBJS) -g

clean:
		rm *.out