CFLAGS = -Wall
LFLAGS = -lGL -lGLU -lglut
C_SOURCES = $(wildcard ./*c)
OBJ = $(C_SOURCES:.c=.o)
CC = gcc
P_NAME = AnimatedSprit
RM = rm -rf

all: $(P_NAME)

$(P_NAME): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

clean:
	@ $(RM) $(OBJ) $(P_NAME)

.PHONY: all clean
