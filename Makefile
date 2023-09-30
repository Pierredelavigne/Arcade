##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

NAME	=	arcade

all:	$(NAME)

$(NAME):
	make -C src
	make -C display
	make -C game

clean:
	make clean -C src
	make clean -C display
	make clean -C game

fclean: clean
	make fclean -C src
	make fclean -C display
	make fclean -C game

core:
	make -C src

graphicals:
	make -C display

games:
	make -C game

re:	fclean all
