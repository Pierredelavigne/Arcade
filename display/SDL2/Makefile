##
## EPITECH PROJECT, 2023
## make
## File description:
## make
##

SRC = 	../../Object/AObject.cpp			\
		../../src/AErr.cpp					\
		SDLDisplay.cpp						\

OBJ = 	AObject.o				\
		AErr.o					\
		SDLDisplay.o			\

NAME = arcade_sdl2.so

CFLAGS = -c -fPIC -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique
LDFLAGS = -shared -fPIC -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -lSDL2 -lSDL2_ttf
LIB_PATH = -L/usr/lib
INC_PATH = -I/usr/include/SDL2 -I/usr/include/SDL2_ttf

all: $(NAME)

$(NAME):
	g++ $(CFLAGS) $(INC_PATH) $(SRC)
	g++ $(LDFLAGS) $(LIB_PATH) $(OBJ) -o $(NAME)
	cp $(NAME) ../../lib

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f ../../lib/$(NAME)

re: fclean all
