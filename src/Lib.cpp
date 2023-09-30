/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

void ArcadeCore::fnlib(std::vector<std::string>& names, std::string& current, std::string& next)
{
    this->FLib();
    if (names.size() == 0)
        return;
    for (size_t i = 0; i < names.size(); i++) {
        if (LIB_PATH + names[i] == current && names.size() > i + 1) {
            next = LIB_PATH + names[i + 1];
            return;
        }
    }
    next = LIB_PATH + names[0];
}

void ArcadeCore::fdpreLib(std::vector<std::string>& names, std::string& current, std::string& next)
{
    this->FLib();
    if (names.size() == 0)
        return;
    for (size_t i = 0; i < names.size(); i++) {
        if (LIB_PATH + names[i] == current && i != 0) {
            next = LIB_PATH + names[i - 1];
            return;
        }
    }
    next = LIB_PATH + names.back();
}

void ArcadeCore::FNextDisp()
{
    fnlib(this->_DispName, this->_LibName, this->_NLib);
}

void ArcadeCore::FNextGame()
{
    fnlib(this->_NameGame, this->_GameName, this->_NGame);
}

void ArcadeCore::FPrevDisp()
{
    fdpreLib(this->_DispName, this->_LibName, this->_NLib);
}

void ArcadeCore::FPrevGame()
{
    fdpreLib(this->_NameGame, this->_GameName, this->_NGame);
}

void ArcadeCore::FLib() {
    DIR *directory;
    struct dirent *dir;

    this->_DispName.clear();
    this->_NameGame.clear();

    directory = opendir("./lib");
    if (directory == nullptr) {
        throw IError();
    }

    while ((dir = readdir(directory)) != nullptr) {
        DirectItem(dir);
    }

    closedir(directory);
}

bool isGameName(const std::string& name) {
    std::vector<std::string> gameNames = {
        "arcade_nibbler.so", "arcade_pacman.so", "arcade_qix.so", 
        "arcade_centipede.so", "arcade_solarfox.so"
    };

    return std::find(gameNames.begin(), gameNames.end(), name) != gameNames.end();
}

bool isDisplayName(const std::string& name) {
    std::vector<std::string> displayNames = {
        "arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so",
        "arcade_allegro5.so", "arcade_xlib.so", "arcade_gtk+.so", 
        "arcade_sfml.so", "arcade_irrlicht.so", "arcade_opengl.so", 
        "arcade_vulkan.so", "arcade_qt5.so", "arcade_ncurses.so", 
        "arcade_sdl2.so"
    };

    return std::find(displayNames.begin(), displayNames.end(), name) != displayNames.end();
}

void ArcadeCore::DirectItem(struct dirent* dir) {
    std::string name = dir->d_name;
    
    if (isGameName(name))
        this->_NameGame.push_back(dir->d_name);

    if (isDisplayName(name))
        this->_DispName.push_back(dir->d_name);
}
