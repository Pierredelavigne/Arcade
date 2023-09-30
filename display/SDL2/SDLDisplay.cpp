/*
** EPITECH PROJECT, 2023
** display
** File description:
** display
*/

#include "../../include/Display.hpp"

void DispSDL::createxturtext(int i) {
    this->_surf = TTF_RenderText_Solid(this->_Fontex, this->_ObjectVector.at(i)->get_val().c_str(), this->_Col);
    this->_Texture = SDL_CreateTextureFromSurface(this->_Rend, this->_surf);
}

void DispSDL::textrend(int i) {
    this->_imgpos = {this->_ObjectVector.at(i)->x_get() * (this->_tailleX / 40), this->_ObjectVector.at(i)->y_get() * (this->_tailleY / 20), this->_tailleX / 40 * 5, this->_tailleY / 20};
    SDL_RenderCopy(this->_Rend, this->_Texture, NULL, &this->_imgpos);
}

void DispSDL::textdraw(int i)
{
    createxturtext(i);
    textrend(i);
}


int DispSDL::posarrayname(int i) {
    for (std::size_t y = 0; y < this->_arrayname.size(); y++) {
        if (this->_arrayname.at(y).compare(this->_ObjectVector.at(i)->get_val()) == 0)
            return y;
    }
    return 0;
}

bool DispSDL::arrayname(int i, int pos) {
    return pos != 0 || this->_ObjectVector.at(i)->get_val() == this->_arrayname.at(0);
}

void DispSDL::texturemenudisp(int pos) {
    this->_sizeimag = {0, pos * 40, 200, 40};
    SDL_RenderCopy(this->_Rend, this->_texmenu, &this->_sizeimag, &this->_imgpos);
}

void DispSDL::menudisp(int i) {
    this->_imgpos = {this->_ObjectVector.at(i)->x_get() * (this->_tailleX / 40), this->_ObjectVector.at(i)->y_get() * (this->_tailleY / 20), this->_tailleX / 40 * 5, this->_tailleY / 20};
    int pos = posarrayname(i);
    if (arrayname(i, pos)) {
        texturemenudisp(pos);
    } else {
        this->textdraw(i);
    }
}



void DispSDL::texturedisp(int textureX, int textureY, int textureWidth, int textureHeight) 
{
    this->_sizeimag = {textureX, textureY, textureWidth, textureHeight};
    SDL_RenderCopy(this->_Rend, this->_Tex, &this->_sizeimag, &this->_imgpos);
}

void DispSDL::grassdisp() {
    texturedisp(48, 48, 16, 16);
}


void DispSDL::snakedisptexture(int i, ArcadeObject::TypeObj type, int textureX, int textureY)
{
    if (type != this->_ObjectVector.at(i)->get_type())
        return;
    this->grassdisp();
    this->_sizeimag = {textureX, textureY, 16, 16};
    SDL_RenderCopy(this->_Rend, this->_Tex, &this->_sizeimag, &this->_imgpos);
}

void DispSDL::snakedisp(int i)
{
    snakedisptexture(i, ArcadeObject::RIGHTBODY, 0, 48);
    snakedisptexture(i, ArcadeObject::LEFTBODY, 16, 48);
    snakedisptexture(i, ArcadeObject::BOTTOMLESFCORNER, 0, 32);
    snakedisptexture(i, ArcadeObject::TOPLEFTCORNER, 16, 32);
    snakedisptexture(i, ArcadeObject::BOTTOMRIGHTCORNER, 48, 32);
    snakedisptexture(i, ArcadeObject::TOPRIGHTCORNER, 32, 32);

    if (this->_ObjectVector.at(i)->get_type() == ArcadeObject::UPHEAD ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::DOWNHEAD ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::RIGHTHEAD ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::LEFTHEAD ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::RIGHTBODY ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::LEFTBODY ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::BOTTOMLESFCORNER ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::TOPLEFTCORNER ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::BOTTOMRIGHTCORNER ||
        this->_ObjectVector.at(i)->get_type() == ArcadeObject::TOPRIGHTCORNER) {
        return;
    }

    this->pacmandisp(i);
}



int DispSDL::ghostfind(int i)
{
    std::array<std::string, 4> phantom = {"R", "P", "B", "O"};

    auto iterator = std::find(phantom.begin(), phantom.end(), this->_ObjectVector.at(i)->get_val());
    
    return (iterator != phantom.end()) ? std::distance(phantom.begin(), iterator) : 0;
}


void DispSDL::imgsizeset(int x, int y, int w, int h)
{
    this->_sizeimag = {x, y, w, h};
}

void DispSDL::objdisp()
{
    SDL_RenderCopy(this->_Rend, this->_texpacman, &this->_sizeimag, &this->_imgpos);
}

void DispSDL::bulldisp()
{
    this->grassdisp();
    imgsizeset(80, 16, 16, 16);
}

void DispSDL::bigbulldisp()
{
    this->grassdisp();
    imgsizeset(80, 0, 16, 16);
}

void DispSDL::pacmandispe(int y_offset)
{
    this->grassdisp();
    imgsizeset(0, y_offset, 16, 16);
}

void DispSDL::ghostdisp(int x, int y_offset)
{
    this->grassdisp();
    imgsizeset(16 + (x * 16), y_offset, 16, 16);
}

void DispSDL::pacmandisp(int i)
{
    int x = this->ghostfind(i);
    ArcadeObject::TypeObj type = this->_ObjectVector.at(i)->get_type();

    if (type == ArcadeObject::MUR) {
        imgsizeset(102, 0, 16, 16);
    } else if (type == ArcadeObject::BULLE) {
        bulldisp();
    } else if (type == ArcadeObject::BIGBULLE) {
        bigbulldisp();
    } else if (type == ArcadeObject::RIGHTPAC) {
        pacmandispe(0);
    } else if (type == ArcadeObject::LEFTPAC) {
        pacmandispe(16);
    } else if (type == ArcadeObject::UPAC) {
        pacmandispe(32);
    } else if (type == ArcadeObject::DOWNPAC) {
        pacmandispe(48);
    } else if (type == ArcadeObject::GHOSTRIGHT) {
        ghostdisp(x, 0);
    } else if (type == ArcadeObject::GHOSTLEFT) {
        ghostdisp(x, 16);
    } else if (type == ArcadeObject::GHOSTUP) {
        ghostdisp(x, 32);
    } else if (type == ArcadeObject::GHOSTDOWN) {
        ghostdisp(x, 48);
    }
    
    objdisp();
}


void DispSDL::appledisp()
{
    this->grassdisp();
    imgsizeset(32, 48, 16, 16);
}

void DispSDL::headisp(int x, int y)
{
    this->grassdisp();
    imgsizeset(x, y, 16, 16);
}

void DispSDL::bottomdisp(int x, int y)
{
    this->grassdisp();
    imgsizeset(x, y, 16, 16);
}

void DispSDL::gamedisp(int i)
{
    this->_imgpos = {this->_ObjectVector.at(i)->x_get() * (this->_tailleX / 40) + (this->_tailleX / 40 * (40 / 2 - this->_LenX / 2)),
    this->_ObjectVector.at(i)->y_get() * (this->_tailleY / 20) + (this->_tailleY / 20 * (20 / 2 - this->_LenY / 2)),
    this->_tailleX / 40, this->_tailleY / 20};

    ArcadeObject::TypeObj type = this->_ObjectVector.at(i)->get_type();
    
    if (type == ArcadeObject::TEXTE) {
        this->textdraw(i);
    } else if (type == ArcadeObject::BACKGROUND) {
        imgsizeset(48, 48, 16, 16);
    } else if (type == ArcadeObject::POMME) {
        appledisp();
    } else if (type == ArcadeObject::DOWNHEAD) {
        headisp(32, 0);
    } else if (type == ArcadeObject::UPHEAD) {
        headisp(0, 0);
    } else if (type == ArcadeObject::LEFTHEAD) {
        headisp(48, 0);
    } else if (type == ArcadeObject::RIGHTHEAD) {
        headisp(16, 0);
    } else if (type == ArcadeObject::DOWNBOTTOM) {
        bottomdisp(0, 16);
    } else if (type == ArcadeObject::LESFTBOTTOM) {
        bottomdisp(16, 16);
    } else if (type == ArcadeObject::UPBOTTOM) {
        bottomdisp(32, 16);
    } else if (type == ArcadeObject::RIGHTBOTTOM) {
        bottomdisp(48, 16);
    } else {
        this->snakedisp(i);
        return;
    }
    
    if (type != ArcadeObject::TEXTE)
        SDL_RenderCopy(this->_Rend, this->_Tex, &this->_sizeimag, &this->_imgpos);
}

Errursdl::Errursdl(std::string error)
{
    this->errorMessage = "Library error: " + error;
}

Errursdl::~Errursdl()
{
}

DispSDL::DispSDL() 
    : _tailleX(0), _tailleY(0), _LenX(0), _LenY(0), 
    _arrayname{
        "arcade_ncurses.so", "arcade_sdl2.so", "arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so", "arcade_allegro5.so",
        "arcade_xlib.so", "arcade_gtk+.so", "arcade_sfml.so" , "arcade_irrlicht.so", "arcade_opengl.so", "arcade_vulkan.so", "arcade_qt5.so",
        "arcade_nibbler.so", "arcade_pacman.so", "arcade_qix.so", "arcade_centipede.so", "arcade_solarfox.so", "Games", "Graphics", "Menu", "Score", "Start",
        "Input", "Cursor"}, 
    mapkey{
        {SDLK_q, ArcadeObject::KEY_Q},
        {SDLK_a, ArcadeObject::KEY_A},
        {SDLK_z, ArcadeObject::KEY_Z},
        {SDLK_o, ArcadeObject::KEY_O},
        {SDLK_p, ArcadeObject::KEY_P},
        {SDLK_e, ArcadeObject::KEY_E},
        {SDLK_r, ArcadeObject::KEY_R},
        {SDLK_t, ArcadeObject::KEY_T},
        {SDLK_y, ArcadeObject::KEY_Y},
        {SDLK_u, ArcadeObject::KEY_U},
        {SDLK_i, ArcadeObject::KEY_I},
        {SDLK_s, ArcadeObject::KEY_S},
        {SDLK_d, ArcadeObject::KEY_D},
        {SDLK_f, ArcadeObject::KEY_F},
        {SDLK_g, ArcadeObject::KEY_G},
        {SDLK_h, ArcadeObject::KEY_H},
        {SDLK_j, ArcadeObject::KEY_J},
        {SDLK_k, ArcadeObject::KEY_K},
        {SDLK_l, ArcadeObject::KEY_L},
        {SDLK_m, ArcadeObject::KEY_M},
        {SDLK_w, ArcadeObject::KEY_W},
        {SDLK_x, ArcadeObject::KEY_X},
        {SDLK_c, ArcadeObject::KEY_C},
        {SDLK_v, ArcadeObject::KEY_V},
        {SDLK_b, ArcadeObject::KEY_B},
        {SDLK_n, ArcadeObject::KEY_N},
        {SDLK_ESCAPE, ArcadeObject::ECHAP},
        {SDLK_UP, ArcadeObject::ARROW_UP},
        {SDLK_DOWN, ArcadeObject::ARROW_DOWN},
        {SDLK_LEFT, ArcadeObject::ARROW_LEFT},
        {SDLK_RIGHT, ArcadeObject::ARROW_RIGHT},
        {SDLK_RETURN, ArcadeObject::ENTER},
        {SDLK_SPACE, ArcadeObject::SPACE},
        {SDLK_BACKSPACE, ArcadeObject::RETURN},
    }
{
}


DispSDL::~DispSDL()
{
}

void DispSDL::dispclear()
{
    SDL_RenderClear(this->_Rend);
}

void DispSDL::maxgetx() 
{
    this->_LenX = 0;
    for (std::size_t i = 0; i < this->_ObjectVector.size(); i++) 
    {
        if (this->_ObjectVector.at(i)->x_get() > this->_LenX)
            this->_LenX = this->_ObjectVector.at(i)->x_get();
    }
    this->_LenX += 1;
}

void DispSDL::maxyget() 
{
    this->_LenY = 0;
    for (std::size_t i = 0; i < this->_ObjectVector.size(); i++) 
    {
        if (this->_ObjectVector.at(i)->y_get() > this->_LenY)
            this->_LenY = this->_ObjectVector.at(i)->y_get();
    }
    this->_LenY += 1;
}

void DispSDL::sizegame() 
{
    maxgetx();
    maxyget();
}

void DispSDL::objdisp(std::size_t index) {
    if (this->_ObjectVector.at(index)->get_type() == ArcadeObject::HOME)
        this->menudisp(index);
    else
        this->gamedisp(index);
}

void DispSDL::printdraw() {
    SDL_SetRenderDrawColor(this->_Rend, 96, 128, 255, 255);
    SDL_GetWindowSize(this->_Windowe, &this->_tailleX, &this->_tailleY);

    this->sizegame();
    for (std::size_t i = 0; i < this->_ObjectVector.size(); i++) {
        objdisp(i);
    }
    SDL_RenderPresent(this->_Rend);
}

void DispSDL::compdestroy() {
    SDL_DestroyWindow(this->_Windowe);
    TTF_CloseFont(this->_Fontex);
}

void DispSDL::stopdisp() {
    compdestroy();
    SDL_Quit();
    TTF_Quit();
}


void DispSDL::initsdl() {
    std::string error;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        error = SDL_GetError();
        throw Errursdl("Could not load SDL " + error);
    }
    if (TTF_Init() < 0) {
        error = SDL_GetError();
        throw Errursdl("Could not load SDL TTF" + error);
    }
}

void DispSDL::initwindow() {
    std::string error;
    this->_Windowe = SDL_CreateWindow("ArcadeObject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_RENDERER_ACCELERATED);
    if (!this->_Windowe) {
        error = SDL_GetError();
        throw Errursdl("Window create failed " + error);
    }
    this->_Rend = SDL_CreateRenderer(this->_Windowe, -1, SDL_RENDERER_ACCELERATED);
    if (!this->_Rend) {
        error = SDL_GetError();
        throw Errursdl("renderer failed " + error);
    }
}

SDL_Texture* DispSDL::texturload(const std::string& filePath) {
    SDL_Surface *image = SDL_LoadBMP(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_Rend, image);
    SDL_FreeSurface(image);
    return texture;
}

void DispSDL::inittext() {
    this->_Tex = texturload("Object/Snake.bmp");
    this->_texmenu = texturload("Object/Menu.bmp");
    this->_texpacman = texturload("Object/pacman.bmp");
}

void DispSDL::initfont() {
    this->_Fontex = TTF_OpenFont("Object/font.ttf", 20);
    this->_Col.r = 0;
    this->_Col.g = 0;
    this->_Col.b = 0;
}

void DispSDL::initialisation() {
    initsdl();
    initwindow();
    inittext();
    initfont();
}


ArcadeObject::Touche DispSDL::getevents()
{
    if (SDL_PollEvent(&this->_Ev) != 0) {
        if (this->_Ev.type == SDL_QUIT) {
            return (ArcadeObject::QUIT);
        }
        if (this->_Ev.type == SDL_KEYDOWN) {
            auto it = mapkey.find(this->_Ev.key.keysym.sym);
            if (it != mapkey.end()) {
                return it->second;
            }
        }
    }
    return (ArcadeObject::NO_INPUT);
}


extern "C" IGraphic *entryPoint()
{
    return (new DispSDL);
}