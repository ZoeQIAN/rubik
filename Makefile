CIBLE = main
SRCS =  main.cpp Button.cpp GameController.cpp rubik.cpp Camera.cpp basicfunction.cpp

OS = $(shell uname -s)

LIBS = -framework GLUT -framework OpenGL -framework Cocoa

CC = g++
CPP = g++

FLAGS = -Wall -O2 

LDFLAGS =
CFLAGS = $(FLAGS)
CXXFLAGS = $(FLAGS)

OBJS = $(SRCS:.cpp=.o)   

$(CIBLE): $(OBJS)
	g++ $(LDFLAGS) -o $(CIBLE) $(OBJS) $(LIBS)
clean:
	rm -f  *~  $(CIBLE) $(OBJS)

basicfunction.o: basicfunction.h
Camera.o: Camera.cpp Camera.h basicfunction.h
Button.o: Button.cpp Button.h
rubik.o: rubik.cpp rubik.h basicfunction.h
GameController.o: GameController.cpp GameController.h Button.h
main.o: main.cpp GameController.h Camera.h
