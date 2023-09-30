##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

NAME	=	display

all:	$(NAME)

$(NAME):
	make -C ncurses
	make -C SDL2
	make -C SFML

clean:
	make clean -C ncurses
	make clean -C SDL2
	make clean -C SFML

fclean: clean
	make fclean -C ncurses
	make fclean -C SDL2
	make fclean -C SFML

re:	fclean all