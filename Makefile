CC = gcc
SRC = main.c function.c
OBJ = $(SRC:.c=.o)
EXEC = sup_liv.exe

SDL2_INCLUDE = -IC:/SDL2/include
SDL2_LIB = -LC:/SDL2/lib -lSDL2main -lSDL2

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(SDL2_LIB)

%.o: %.c
	$(CC) -c $< -o $@ $(SDL2_INCLUDE)

clean:
	del *.o *.exe 2>nul || rm -f *.o *.exe
