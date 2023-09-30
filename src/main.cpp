/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "iostream"
#include "../include/Core.hpp"

void print_usage()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "    ./arcade lib" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "    lib    dynamic library in lib folder" << std::endl << std::endl;
}

void print_menu_controls()
{
    std::cout << "MENU" << std::endl;
    std::cout << "    ENTER = valid selection" << std::endl;
    std::cout << "    ESCAPE = leave" << std::endl;
    std::cout << "    UP/DOWN KEY = change selection" << std::endl;
    std::cout << "    LEFT KEY = back to previous choice" << std::endl;
    std::cout << "    LETTERS = write username" << std::endl;
    std::cout << "    RETURN = delete an username letter" << std::endl << std::endl;
}

void print_game_controls()
{
    std::cout << "GAME" << std::endl;
    std::cout << "    LEFT/UP/RIGHT/DOWN KEYS = move" << std::endl;
    std::cout << "    SPACE = restart game" << std::endl;
    std::cout << "    Q = quit arcade" << std::endl;
    std::cout << "    ESCAPE = return to menu" << std::endl;
    std::cout << "    A = previous graphic lib" << std::endl;
    std::cout << "    Z = next graphic lib" << std::endl;
    std::cout << "    O = previous game lib" << std::endl;
    std::cout << "    P = next game lib" << std::endl;
}

void print_help()
{
    print_usage();
    print_menu_controls();
    print_game_controls();
}

int check_args(int ac, char **av)
{
    if (ac != 2) {
        print_help();
        return 84;
    }
    
    std::string str = av[1];
    if (str == "-h" || str.find("lib/") == std::string::npos) {
        print_help();
        return 84;
    }

    return 0;
}

int execute_arcade(char* library_path)
{
    try {
        ArcadeCore core = ArcadeCore(library_path);
        core.OpenLibDisp(library_path);
        core.boucle();
    } catch (IError const &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }

    return 0;
}

int main(int ac, char **av)
{
    int arg_check = check_args(ac, av);
    if(arg_check != 0) return arg_check;
    
    return execute_arcade(av[1]);
}
