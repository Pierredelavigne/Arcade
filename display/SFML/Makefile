##
## EPITECH PROJECT, 2023
## make
## File description:
## make
##

SRC	=	../../Object/AObject.cpp		\
		../../src/AErr.cpp				\
		SFMLDisplay.cpp					\

OBJ	= 	AObject.o				\
		AErr.o					\
		SFMLDisplay.o			\

NAME	=	arcade_sfml.so

all:	$(NAME)

$(NAME):
	g++ -c -fPIC $(SRC) -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -lsfml-graphics -lsfml-window -lsfml-system
	g++ -shared -fPIC $(OBJ) -o $(NAME) -std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -lsfml-graphics -lsfml-window -lsfml-system
	cp $(NAME) ../../lib

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f ../../lib/$(NAME)

re:	fclean all