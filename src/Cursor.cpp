/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

void ArcadeCore::KeyHome()
{
    switch (this->_inp) {
        case ArcadeObject::ARROW_DOWN:
            cursordown();
            break;
        case ArcadeObject::ARROW_UP:
            mcursorup();
            break;
        case ArcadeObject::ENTER:
            actionenter();
            break;
        case ArcadeObject::ARROW_LEFT:
            cursorleft();
            break;
        default:
            UserName();
    }
}

void ArcadeCore::cursordown()
{
    int x = getcursorX();
    int y = getcursorY();
    
    if ((y < (6 + this->_NumDisp - 1) && x == 4) ||
        (y < 5 + this->_NumGame && x == 29)) {
            Updcursor(x, y + 1);
    }
}

void ArcadeCore::mcursorup()
{
    int x = getcursorX();
    int y = getcursorY();

    if (y > 6) {
        Updcursor(x, y - 1);
    }
}

void ArcadeCore::actionenter()
{
    int x = getcursorX();
    
    if (x == 4) {
        libclaim(5, this->_NLib);
        Updcursor(29, 6);
    }
    if (x == 29) {
        libclaim(30, this->_NGame);
        Updcursor(32, 18);
    }
    if (x == 32) {
        this->_Obj.clear();
        this->_Home = false;
        updlib();
    }
}

void ArcadeCore::updlib()
{
    if (this->_GameName != this->_NGame) {
        addscoreine();
        this->OpenLibGame(this->_NGame);
        this->_GameName = this->_NGame;
    }
    if (this->_LibName != this->_NLib) {
        this->OpenLibDisp(this->_NLib);
    }
}

void ArcadeCore::cursorleft()
{
    int x = getcursorX();
    
    if (x == 29) {
        Updcursor(4, 6);
    }
    if (x == 32) {
        Updcursor(29, 6);
    }
}

int ArcadeCore::getcursorX()
{
    return this->_Obj.back()->x_get();
}

int ArcadeCore::getcursorY()
{
    return this->_Obj.back()->y_get();
}

void ArcadeCore::Updcursor(int x, int y)
{
    this->_Obj.pop_back();
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, x, y, "Cursor"));
}

std::vector<ArcadeObject::IObjects *> ArcadeCore::GetObjHome()
{
    return (this->_Obj);
}
