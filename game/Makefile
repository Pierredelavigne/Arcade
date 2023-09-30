##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

NAME	=	game

all:	$(NAME)

$(NAME):
	make -C nibbler
	make -C Pacman

clean:
	make clean -C nibbler
	make clean -C Pacman

fclean: clean
	make fclean -C nibbler
	make fclean -C Pacman

re:	fclean all