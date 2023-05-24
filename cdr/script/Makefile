CC = gcc
CFLAGS = -Wall -g -c
LDFLAGS = -o

INC = ./inc/
BIN = ./bin
SRC = ./src
OBJ = ./obj

IFLAGS = -I $(INC)

all: cdr
	
cdr: $(OBJ)/main.o $(OBJ)/myFunctions.o
	$(CC) $(LDFLAGS) $(BIN)/cdr $(OBJ)/main.o $(OBJ)/myFunctions.o
$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c $(IFLAGS)
	mv *.o $(OBJ)/

$(OBJ)/myFunctions.o: $(SRC)/myFunctions.c
	$(CC) $(CFLAGS) $(SRC)/myFunctions.c $(IFLAGS)
	mv *.o $(OBJ)/
clean: 
	rm -f $(OBJ)/*
	rm -f $(BIN)/*
	@echo "Cleaning Done!"


