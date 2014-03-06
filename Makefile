CC = clang++
STD = --std=c++11
CCARGS = -Wall -g
SRCS = src/*.cpp
LINKS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lSDL2
OUTFILE = bin/gameloop

all:
	$(CC) $(STD) $(CCARGS) $(SRCS) $(LINKS) -o $(OUTFILE)

clean:
	rm -rf bin/*
