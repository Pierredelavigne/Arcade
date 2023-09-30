/*
** EPITECH PROJECT, 2023
** display
** File description:
** display
*/

#include "../../include/Display.hpp"

void Dispncurses::gameprint(int i)
{
    poscursor(i);
    switch (this->_ObjectVector.at(i)->get_type()) {
        case ArcadeObject::TEXTE:
            disptext(i);
            break;
        case ArcadeObject::BACKGROUND:
            groundisp();
            break;
        case ArcadeObject::POMME:
            appledisp();
            break;
        case ArcadeObject::DOWNHEAD:
        case ArcadeObject::UPHEAD:
        case ArcadeObject::LEFTHEAD:
        case ArcadeObject::RIGHTHEAD:
            headisp();
            break;
        case ArcadeObject::DOWNBOTTOM:
        case ArcadeObject::LESFTBOTTOM:
        case ArcadeObject::UPBOTTOM:
        case ArcadeObject::RIGHTBOTTOM:
            bottomdisp();
            break;
        default:
            snakeprint(i);
    }
}

void Dispncurses::poscursor(int i)
{
    move(LINES / 2 + (this->_ObjectVector.at(i)->y_get()) - 10, COLS / 2 + (this->_ObjectVector.at(i)->x_get()) - 20);
}

void Dispncurses::disptext(int i)
{
    move(LINES / 2 + (this->_ObjectVector.at(i)->y_get()) - 13, COLS / 2 + (this->_ObjectVector.at(i)->x_get()) - 20);
    printw(this->_ObjectVector.at(i)->get_val().c_str());
}

void Dispncurses::groundisp()
{
    printw(" ");
}

void Dispncurses::appledisp()
{
    printw("A");
}

void Dispncurses::headisp()
{
    printw("O");
}

void Dispncurses::bottomdisp()
{
    printw(".");
}

void Dispncurses::pacmanprint(int i)
{
    switch (this->_ObjectVector.at(i)->get_type()) {
        case ArcadeObject::DOWNPAC:
        case ArcadeObject::LEFTPAC:
        case ArcadeObject::RIGHTPAC:
        case ArcadeObject::UPAC:
            pacmandisp();
            break;
        case ArcadeObject::BULLE:
            bubbledisp();
            break;
        case ArcadeObject::BIGBULLE:
            bigbuldisp();
            break;
        case ArcadeObject::DEADGHOST:
            deadghostdisp();
            break;
        case ArcadeObject::GHOSTSCARE:
            ghostscradisp();
            break;
        default:
            ghostdisp(i);
    }
}

void Dispncurses::pacmandisp()
{
    printw("C");
}

void Dispncurses::bubbledisp()
{
    printw(".");
}

void Dispncurses::bigbuldisp()
{
    printw("O");
}

void Dispncurses::deadghostdisp()
{
    printw("_");
}

void Dispncurses::ghostscradisp()
{
    printw("S");
}

void Dispncurses::ghostdisp(int i)
{
    std::vector<std::string> phantom = {"R", "P", "B", "O"};
    std::string value = this->_ObjectVector.at(i)->get_val();

    for (const auto &ph : phantom) {
        if (value == ph) {
            printw(ph.c_str());
            return;
        }
    }
}

void Dispncurses::menuprint(int i)
{
    move(LINES / 2 + (this->_ObjectVector.at(i)->y_get()) - 10, COLS / 2 + (this->_ObjectVector.at(i)->x_get() * 3) - 60);
    std::string value = this->_ObjectVector.at(i)->get_val();
    if (value == "Input") {
        return;
    }
    if (value == "Cursor") {
        cursdisp();
    }
    else {
        printw(value.c_str());
    }
}

void Dispncurses::cursdisp()
{
    printw("*");
}

void Dispncurses::snakeprint(int i)
{
    switch (this->_ObjectVector.at(i)->get_type()) {
        case ArcadeObject::RIGHTBODY:
        case ArcadeObject::LEFTBODY:
        case ArcadeObject::BOTTOMLESFCORNER:
        case ArcadeObject::TOPLEFTCORNER:
        case ArcadeObject::BOTTOMRIGHTCORNER:
        case ArcadeObject::TOPRIGHTCORNER:
            snakedisp();
            break;
        case ArcadeObject::MUR:
            walldisp();
            break;
        default:
            this->pacmanprint(i);
    }
}

void Dispncurses::snakedisp()
{
    printw("o");
}

void Dispncurses::walldisp()
{
    printw("X");
}

Errorncurses::Errorncurses(std::string error)
{
    this->errorMessage = "Library error: " + error;
}

Errorncurses::~Errorncurses()
{
}

Dispncurses::Dispncurses()
{
    initarrayname();
    dimensioninit();
    this->_Inp = 0;
    this->windows = nullptr;
}

void Dispncurses::initarrayname()
{
    this->_name = {"arcade_ncurses.so", "arcade_sdl2.so", "arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so", "arcade_allegro5.so", "arcade_xlib.so", "arcade_gtk+.so", "arcade_sfml.so" , "arcade_irrlicht.so", "arcade_opengl.so", "arcade_vulkan.so", "arcade_qt5.so", "arcade_nibbler.so", "arcade_pacman.so", "arcade_qix.so", "arcade_centipede.so", "arcade_solarfox.so", "Games", "Graphics", "Menu", "Score", "Start", "Input", "Cursor"};
}

void Dispncurses::dimensioninit()
{
    this->_lenx = 0;
    this->_Leny = 0;
    this->_Xsizee = 0;
    this->_Ysizee = 0;
}


Dispncurses::~Dispncurses()
{
}

void Dispncurses::dispclear()
{
    wclear(this->windows);
}

void Dispncurses::gamesizeget()
{
    this->_lenx = 0;
    this->_Leny = 0;

    for (const auto& object : this->_ObjectVector) {
        this->_lenx = std::max(this->_lenx, object->x_get());
        this->_Leny = std::max(this->_Leny, object->y_get());
    }
    
    this->_lenx += 1;
    this->_Leny += 1;
}

bool Dispncurses::checkscreensize()
{
    std::string small = "Not enough large\n";
    std::string height = "Not enough height\n";

    if (this->_lenx > COLS) {
        messagedisp(small);
        return false;
    }
    if (this->_Leny > LINES) {
        messagedisp(height);
        return false;
    }
    return true;
}

void Dispncurses::messagedisp(const std::string& message)
{
    move(LINES / 2, COLS / 2 - (message.size() / 2));
    printw(message.c_str());
    usleep(2000);
}

void Dispncurses::objdisp()
{
    for (std::size_t i = 0; i < this->_ObjectVector.size(); i++) {
        if (this->_ObjectVector.at(i)->get_type() == ArcadeObject::HOME)
            this->menuprint(i);
        else
            this->gameprint(i);
    }
}

void Dispncurses::printdraw(void)
{
    this->gamesizeget();
    if (!checkscreensize()) {
        return;
    }
    this->objdisp();
    wrefresh(this->windows);
    curs_set(0);
    usleep(2000);
}

void Dispncurses::stopdisp()
{
    nodelay(this->windows, false);
    delwin(this->windows);
    endwin();
}

void Dispncurses::initialisation()
{
    this->windows = initscr();
    if (this->windows == NULL) {
        throw Errorncurses("Failed open");
    }
    nodelay(this->windows, true);
}


ArcadeObject::Touche Dispncurses::getevents()
{
    keypad(this->windows, TRUE);
    int ch = wgetch(this->windows);
    
    if (isalpha(ch)) {
        return alphakey(ch);
    } else if (ch == KEY_BACKSPACE || ch == 10 || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT || ch == 27 || ch == ' ') {
        return speckey(ch);
    } else {
        return ArcadeObject::NO_INPUT;
    }
}

ArcadeObject::Touche Dispncurses::alphakey(int ch)
{
    switch (ch) {
        case 'q':
            return ArcadeObject::KEY_Q;
        case 'n':
            return ArcadeObject::KEY_N;
        default:
            return ArcadeObject::NO_INPUT;
    }
}

ArcadeObject::Touche Dispncurses::speckey(int ch)
{
    switch (ch) {
        case KEY_BACKSPACE:
            return ArcadeObject::RETURN;
        case 10:
            return ArcadeObject::ENTER;
        case KEY_UP:
            return ArcadeObject::ARROW_UP;
        case KEY_DOWN:
            return ArcadeObject::ARROW_DOWN;
        case KEY_LEFT:
            return ArcadeObject::ARROW_LEFT;
        case KEY_RIGHT:
            return ArcadeObject::ARROW_RIGHT;
        case 27:
            return ArcadeObject::ECHAP;
        case ' ':
            return ArcadeObject::SPACE;
        default:
            return ArcadeObject::NO_INPUT;
    }
}


extern "C" IGraphic *entryPoint()
{
    return (new Dispncurses);
}