##
## EPITECH PROJECT, 2022
## make
## File description:
## make
##

SRC	= 	pacman.cpp					\
		../../Object/AObject.cpp	\

OBJ	= 	pacman.o					\
		AObject.o					\

NAME	=	arcade_pacman.so

all:	$(NAME)

$(NAME):
	g++ -c -fPIC $(SRC)
	g++ -shared -fPIC $(OBJ) -o $(NAME) -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique
	cp $(NAME) ../../lib

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f ../../lib/$(NAME)

re:	fclean all