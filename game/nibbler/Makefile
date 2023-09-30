##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC	=	nibbler.cpp					\
		../../Object/AObject.cpp	\
		../../src/AErr.cpp	\

OBJ	=	nibbler.o				\
		AObject.o				\
		AErr.o				\

NAME	=	arcade_nibbler.so

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
