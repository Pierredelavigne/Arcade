/*
** EPITECH PROJECT, 2023
** display
** File description:
** display
*/

#include "../../include/Display.hpp"

sf::Vector2f DispSFML::posset(int i) {
    sf::Vector2f pos;
    pos.x = this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40) + 10;
    pos.y = this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20) + 5;
    return pos;
}

void DispSFML::detailtextset(int i, const sf::Vector2f &pos) {
    this->_texte.setString(this->_ObjectVector.at(i)->get_val());
    this->_texte.setFont(this->_fonte);
    this->_texte.setCharacterSize(20);
    this->_texte.setPosition(pos);
    this->_texte.setFillColor(sf::Color(0, 0, 0));
}

void DispSFML::textdraw(int i) {
    sf::Vector2f pos = posset(i);
    detailtextset(i, pos);
    this->_Windows->draw(this->_texte);
}

int DispSFML::posfind(int i) {
    for (std::size_t y = 0; y < this->_name.size(); y++) {
        if (this->_name.at(y).compare(this->_ObjectVector.at(i)->get_val()) == 0)
            return y;
    }
    return 0;
}

void DispSFML::detailspritset(int pos, int i) {
    this->_tailimg = {0, pos * 40, 200, 40};
    this->_Spr.setTexture(this->_texmenu);
    this->_Spr.setTextureRect(this->_tailimg);
    this->_Spr.setPosition(this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40), this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20));
}

void DispSFML::scalespritset() {
    this->_tailX = this->_tail.x / 40;
    this->_tailX /= 200;
    this->_tailX *= 5;
    this->_tailY = this->_tail.y / 20;
    this->_tailY /= 40;
    this->_Spr.setScale(this->_tailX, this->_tailY);
}

void DispSFML::menudisp(int i) {
    int pos = posfind(i);

    if (pos == 0 && this->_ObjectVector.at(i)->get_val() != this->_name.at(0)) {
        this->textdraw(i);
        return;
    }

    detailspritset(pos, i);
    scalespritset();
    this->_Windows->draw(this->_Spr);
}


void DispSFML::grassizetexture() {
    this->_tailimg = {48, 48, 16, 16};
    this->_Spr.setTexture(this->_Tex);
    this->_Spr.setTextureRect(this->_tailimg);
}

void DispSFML::posgrassset(int i) {
    this->_Spr.setPosition(
        this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40) + (this->_tail.x / 40 * (40 / 2 - this->_LenX / 2)),
        this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20) + (this->_tail.y / 20 * (20 / 2 - this->_LenY / 2))
    );
}

void DispSFML::scalgrass() {
    this->_tailX = this->_tail.x / 40;
    this->_tailX /= 16;
    this->_tailY = (this->_tail.y / 20);
    this->_tailY /= 16;
    this->_Spr.setScale(this->_tailX, this->_tailY);
}

void DispSFML::grassdisp(int i) {
    grassizetexture();
    posgrassset(i);
    scalgrass();
    this->_Windows->draw(this->_Spr);
}

void DispSFML::imgsizeset(const sf::IntRect &rect) {
    this->_tailimg = rect;
}

void DispSFML::spritedispsetup(int i) {
    this->_Spr.setTexture(this->_Tex);
    this->_Spr.setTextureRect(this->_tailimg);
    this->_Spr.setPosition(this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40) + (this->_tail.x / 40 * (40 / 2 - this->_LenX / 2)),
    this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20) + (this->_tail.y / 20 * (20 / 2 - this->_LenY / 2)));
    this->_tailX = this->_tail.x / 40;
    this->_tailX /= 16;
    this->_tailY = (this->_tail.y / 20);
    this->_tailY /= 16;
    this->_Spr.setScale(this->_tailX, this->_tailY);
    this->_Windows->draw(this->_Spr);
}

void DispSFML::bottomsnakedisp(int i) {
    static const std::array<sf::IntRect, 6> imgSizes = {
        sf::IntRect{0, 48, 16, 16},
        sf::IntRect{16, 48, 16, 16},
        sf::IntRect{0, 32, 16, 16},
        sf::IntRect{16, 32, 16, 16},
        sf::IntRect{48, 32, 16, 16},
        sf::IntRect{32, 32, 16, 16}
    };

    static const std::array<ArcadeObject::TypeObj, 6> types = {
        ArcadeObject::RIGHTBODY,
        ArcadeObject::LEFTBODY,
        ArcadeObject::BOTTOMLESFCORNER,
        ArcadeObject::TOPLEFTCORNER,
        ArcadeObject::BOTTOMRIGHTCORNER,
        ArcadeObject::TOPRIGHTCORNER
    };

    auto type = this->_ObjectVector.at(i)->get_type();
    auto it = std::find(types.begin(), types.end(), type);
    if (it != types.end()) {
        this->grassdisp(i);
        imgsizeset(imgSizes[std::distance(types.begin(), it)]);
        spritedispsetup(i);
    } else {
        this->pacgamedisp(i);
    }
}

std::size_t DispSFML::ghostfind(int i) {
    std::array<std::string, 4> phantom = {"R", "P", "B", "O"};

    auto iterator = std::find(phantom.begin(), phantom.end(), this->_ObjectVector.at(i)->get_val());

    return (iterator != phantom.end()) ? std::distance(phantom.begin(), iterator) : 0;
}

void DispSFML::pacgamedisp(int i) {
    int x = this->ghostfind(i);

    struct ActionPacman {
        bool drawGrassBefore;
        sf::IntRect imgSize;
    };

    std::map<ArcadeObject::TypeObj, ActionPacman> actionsPacman = {
        {ArcadeObject::MUR, {false, {102, 0, 16, 16}}},
        {ArcadeObject::BIGBULLE, {true, {80, 0, 16, 16}}},
        {ArcadeObject::BULLE, {true, {80, 16, 16, 16}}},
        {ArcadeObject::DEADGHOST, {true, {80, 48, 16, 16}}},
        {ArcadeObject::GHOSTSCARE, {true, {80, 32, 16, 16}}},
        {ArcadeObject::RIGHTPAC, {true, {0, 0, 16, 16}}},
        {ArcadeObject::LEFTPAC, {true, {0, 16, 16, 16}}},
        {ArcadeObject::UPAC, {true, {0, 32, 16, 16}}},
        {ArcadeObject::DOWNPAC, {true, {0, 48, 16, 16}}},
        {ArcadeObject::GHOSTRIGHT, {true, {16 + (x * 16), 0, 16, 16}}},
        {ArcadeObject::GHOSTLEFT, {true, {16 + (x * 16), 16, 16, 16}}},
        {ArcadeObject::GHOSTUP, {true, {16 + (x * 16), 32, 16, 16}}},
        {ArcadeObject::GHOSTDOWN, {true, {16 + (x * 16), 48, 16, 16}}},
    };

    auto type = this->_ObjectVector.at(i)->get_type();

    if (actionsPacman.count(type)) {
        auto actionPacman = actionsPacman[type];
        if (actionPacman.drawGrassBefore) {
            this->grassdisp(i);
        }
        this->_tailimg = actionPacman.imgSize;
    }

    this->defdisppacman(i);
}

void DispSFML::defdisppacman(int i) {
    this->_Spr.setTexture(this->_pactex);
    this->_Spr.setTextureRect(this->_tailimg);
    this->_Spr.setPosition(this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40) + (this->_tail.x / 40 * (40 / 2 - this->_LenX / 2)),
    this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20) + (this->_tail.y / 20 * (20 / 2 - this->_LenY / 2)));
    this->_tailX = this->_tail.x / 40;
    this->_tailX /= 16;
    this->_tailY = (this->_tail.y / 20);
    this->_tailY /= 16;
    this->_Spr.setScale(this->_tailX, this->_tailY);
    this->_Windows->draw(this->_Spr);
}

void DispSFML::dispheadsnake(int i, int textureOffsetX, int textureOffsetY) {
    this->grassdisp(i);
    this->_tailimg = {textureOffsetX, textureOffsetY, 16, 16};
}

void DispSFML::dispsnakbottom(int i, int textureOffsetX, int textureOffsetY) {
    this->grassdisp(i);
    this->_tailimg = {textureOffsetX, textureOffsetY, 16, 16};
}

void DispSFML::appeledisp(int i) {
    this->grassdisp(i);
    this->_tailimg = {32, 48, 16, 16};
}

void DispSFML::defdisprite(int i) {
    this->_Spr.setTexture(this->_Tex);
    this->_Spr.setTextureRect(this->_tailimg);
    this->_Spr.setPosition(this->_ObjectVector.at(i)->x_get() * (this->_tail.x / 40) + (this->_tail.x / 40 * (40 / 2 - this->_LenX / 2)),
    this->_ObjectVector.at(i)->y_get() * (this->_tail.y / 20) + (this->_tail.y / 20 * (20 / 2 - this->_LenY / 2)));
    this->_tailX = this->_tail.x / 40;
    this->_tailX /= 16;
    this->_tailY = (this->_tail.y / 20);
    this->_tailY /= 16;
    this->_Spr.setScale(this->_tailX, this->_tailY);
    this->_Windows->draw(this->_Spr);
}

void DispSFML::gamedraw(int i) {
    struct Action {
        void (DispSFML::*func)(int, int, int);
        int offsetX;
        int offsetY;
    };

    std::map<ArcadeObject::TypeObj, Action> actions = {
        {ArcadeObject::DOWNHEAD, {&DispSFML::dispheadsnake, 32, 0}},
        {ArcadeObject::UPHEAD, {&DispSFML::dispheadsnake, 0, 0}},
        {ArcadeObject::LEFTHEAD, {&DispSFML::dispheadsnake, 48, 0}},
        {ArcadeObject::RIGHTHEAD, {&DispSFML::dispheadsnake, 16, 0}},
        {ArcadeObject::DOWNBOTTOM, {&DispSFML::dispsnakbottom, 0, 16}},
        {ArcadeObject::LESFTBOTTOM, {&DispSFML::dispsnakbottom, 16, 16}},
        {ArcadeObject::UPBOTTOM, {&DispSFML::dispsnakbottom, 32, 16}},
        {ArcadeObject::RIGHTBOTTOM, {&DispSFML::dispsnakbottom, 48, 16}},
    };

    auto type = this->_ObjectVector.at(i)->get_type();

    if (type == ArcadeObject::TEXTE) {
        this->textdraw(i);
        return;
    }
    else if (type == ArcadeObject::BACKGROUND) {
        this->_tailimg = {48, 48, 16, 16};
    }
    else if (type == ArcadeObject::POMME) {
        this->appeledisp(i);
    }
    else if (actions.count(type)) {
        auto action = actions[type];
        (this->*action.func)(i, action.offsetX, action.offsetY);
    }
    else {
        this->bottomsnakedisp(i);
        return;
    }
    
    this->defdisprite(i);
}

Errorsfml::Errorsfml(std::string error)
{
    this->errorMessage = "Library error: " + error;
}

Errorsfml::~Errorsfml()
{
}

DispSFML::DispSFML()
    : _tail{0, 0},
    _LenX(0), 
    _LenY(0), 
    _name({
        "arcade_ncurses.so", "arcade_sdl2.so", "arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so", "arcade_allegro5.so",
        "arcade_xlib.so", "arcade_gtk+.so", "arcade_sfml.so" , "arcade_irrlicht.so", "arcade_opengl.so", "arcade_vulkan.so", "arcade_qt5.so",
        "arcade_nibbler.so", "arcade_pacman.so", "arcade_qix.so", "arcade_centipede.so", "arcade_solarfox.so", "Games", "Graphics", "Menu", "Score", "Start",
        "Input", "Cursor"
    }) 
{
    mapkey[sf::Keyboard::Enter] = ArcadeObject::ENTER;
    mapkey[sf::Keyboard::Q] = ArcadeObject::KEY_Q;
    mapkey[sf::Keyboard::A] = ArcadeObject::KEY_A;
    mapkey[sf::Keyboard::Z] = ArcadeObject::KEY_Z;
    mapkey[sf::Keyboard::O] = ArcadeObject::KEY_O;
    mapkey[sf::Keyboard::P] = ArcadeObject::KEY_P;
    mapkey[sf::Keyboard::E] = ArcadeObject::KEY_E;
    mapkey[sf::Keyboard::R] = ArcadeObject::KEY_R;
    mapkey[sf::Keyboard::T] = ArcadeObject::KEY_T;
    mapkey[sf::Keyboard::Y] = ArcadeObject::KEY_Y;
    mapkey[sf::Keyboard::U] = ArcadeObject::KEY_U;
    mapkey[sf::Keyboard::I] = ArcadeObject::KEY_I;
    mapkey[sf::Keyboard::S] = ArcadeObject::KEY_S;
    mapkey[sf::Keyboard::D] = ArcadeObject::KEY_D;
    mapkey[sf::Keyboard::F] = ArcadeObject::KEY_F;
    mapkey[sf::Keyboard::G] = ArcadeObject::KEY_G;
    mapkey[sf::Keyboard::H] = ArcadeObject::KEY_H;
    mapkey[sf::Keyboard::J] = ArcadeObject::KEY_J;
    mapkey[sf::Keyboard::K] = ArcadeObject::KEY_K;
    mapkey[sf::Keyboard::L] = ArcadeObject::KEY_L;
    mapkey[sf::Keyboard::M] = ArcadeObject::KEY_M;
    mapkey[sf::Keyboard::W] = ArcadeObject::KEY_W;
    mapkey[sf::Keyboard::X] = ArcadeObject::KEY_X;
    mapkey[sf::Keyboard::C] = ArcadeObject::KEY_C;
    mapkey[sf::Keyboard::V] = ArcadeObject::KEY_V;
    mapkey[sf::Keyboard::B] = ArcadeObject::KEY_B;
    mapkey[sf::Keyboard::N] = ArcadeObject::KEY_N;
    mapkey[sf::Keyboard::Escape] = ArcadeObject::ECHAP;
    mapkey[sf::Keyboard::Space] = ArcadeObject::SPACE;
    mapkey[sf::Keyboard::Up] = ArcadeObject::ARROW_UP;
    mapkey[sf::Keyboard::Down] = ArcadeObject::ARROW_DOWN;
    mapkey[sf::Keyboard::Left] = ArcadeObject::ARROW_LEFT;
    mapkey[sf::Keyboard::Right] = ArcadeObject::ARROW_RIGHT;
    mapkey[sf::Keyboard::BackSpace] = ArcadeObject::RETURN;
}

DispSFML::~DispSFML()
{

}

void DispSFML::dispclear()
{
    this->_Windows->clear(sf::Color(96, 128, 255, 255));
}

void DispSFML::stopdisp()
{
    this->_Windows->close();
}

void DispSFML::widthgame()
{
    this->_LenX = 0;
    for (const auto& object : this->_ObjectVector) {
        this->_LenX = std::max(this->_LenX, object->x_get());
    }
    this->_LenX += 1;
}

void DispSFML::heightgame() 
{
    this->_LenY = 0;
    for (const auto& object : this->_ObjectVector) {
        this->_LenY = std::max(this->_LenY, object->y_get());
    }
    this->_LenY += 1;
}

void DispSFML::sizegetgame() {
    widthgame();
    heightgame();
}

void DispSFML::printdraw(void)
{
    this->sizeup();
    this->sizegetgame();
    this->dispobjs();
    this->_Windows->display();
}

void DispSFML::sizeup()
{
    this->_tail = this->_Windows->getSize();
}

void DispSFML::dispobjs()
{
    for (std::size_t i = 0; i < this->_ObjectVector.size(); i++) {
        this->dispobj(i);
    }
}

void DispSFML::dispobj(std::size_t i)
{
    if (this->_ObjectVector.at(i)->get_type() == ArcadeObject::HOME) {
        this->menudisp(i);
    } else {
        this->gamedraw(i);
    }
}


void DispSFML::initialisation()
{
    this->initwindow();
    this->texload();
    this->fontload();
}

void DispSFML::initwindow()
{
    this->_Windows = new sf::RenderWindow(sf::VideoMode(1280, 720), "ArcadeObject");
    if (!this->_Windows)
        throw Errorsfml("Failed to load window");
}

void DispSFML::texload()
{
    if (!this->_Tex.loadFromFile("Object/Snake.png"))
        throw Errorsfml("Failed to load snake texture");
    if (!this->_texmenu.loadFromFile("Object/Menu.png"))
        throw Errorsfml("Failed to load menu texture");
    if (!this->_pactex.loadFromFile("Object/pacman.png"))
        throw Errorsfml("Failed to load pacman texture");
}

void DispSFML::fontload()
{
    if (!this->_fonte.loadFromFile("Object/font.otf"))
        throw Errorsfml("Failed to load font");
}


ArcadeObject::Touche DispSFML::getevents()
{
    if (this->_Windows->pollEvent(this->_Ev)) {
        if (this->_Ev.type == sf::Event::Closed)
            return (ArcadeObject::QUIT);
        if (this->_Ev.type == sf::Event::KeyPressed) {
            auto key = this->_Ev.key.code;
            if (mapkey.find(key) != mapkey.end()) {
                return mapkey[key];
            }
        }
    }
    return (ArcadeObject::NO_INPUT);
}


extern "C" IGraphic *entryPoint()
{
    return (new DispSFML);
}