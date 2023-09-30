##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC	=	main.cpp				\
		AErr.cpp				\
		Core.cpp				\
		Lib.cpp 				\
		Menu.cpp				\
		game.cpp				\
		Cursor.cpp				\
		../Object/AObject.cpp	\
		Scoreboard.cpp			\

NAME	=	arcade

CPPFLAGS	=	-std=c++20 -W -Wall -Wextra -Werror -fno-gnu-unique -ldl

all:	$(NAME)

OBJ	=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $(NAME)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all
