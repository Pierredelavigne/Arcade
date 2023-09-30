##
## EPITECH PROJECT, 2023
## make
## File description:
## make
##

SRC	= 	NcursesDisplay.cpp					\
		../../Object/AObject.cpp			\
		../../src/AErr.cpp			\
		

OBJ	= 	NcursesDisplay.o		\
		AObject.o				\
		AErr.o					\

NAME	=	arcade_ncurses.so

all:	$(NAME)

$(NAME):
	g++ -c -fPIC $(SRC) -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -lncurses
	g++ -shared -fPIC $(OBJ) -o $(NAME) -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -lncurses
	cp $(NAME) ../../lib

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f ../../lib/$(NAME)

re:	fclean all