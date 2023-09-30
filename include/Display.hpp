/*
** EPITECH PROJECT, 2023
** sfml
** File description:
** sfml
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "Arcade.hpp"

class IGraphic {
    public:
        IGraphic() = default;
        virtual ~IGraphic() = default;
        virtual void printdraw(void) = 0;
        virtual void dispclear() = 0;
        virtual void dispupdate(const std::vector<ArcadeObject::IObjects*>& objects) = 0;
        virtual void stopdisp() = 0;
        virtual void initialisation() = 0;
        virtual ArcadeObject::Touche getevents() = 0;
    protected:
    private:
};

class AGraphic : public IGraphic {
public:
    
    AGraphic()
    {
        _isOpen = true;
    }

    ~AGraphic()
    {
    }

    void dispupdate(const std::vector<ArcadeObject::IObjects*>& objects)
    {
        _ObjectVector = objects;
    }

protected:
    std::vector<ArcadeObject::IObjects*> _ObjectVector;
    bool _isOpen;
};

class Errorncurses : public AErr {
    public:
        Errorncurses(std::string error);
        ~Errorncurses();
};
class Dispncurses : public AGraphic {
    public:
        Dispncurses();
        ~Dispncurses();
        void printdraw(void);
        void dispclear();
        void stopdisp();
        void initialisation() override;
        ArcadeObject::Touche getevents() override;
        void menuprint(int i);
        void gameprint(int i);
        void snakeprint(int i);
        void pacmanprint(int i);
        void gamesizeget();
        void poscursor(int i);
        void disptext(int i);
        void groundisp();
        void appledisp();
        void headisp();
        void bottomdisp();
        void initarrayname();
        void dimensioninit();
        void pacmandisp();
        void bubbledisp();
        void bigbuldisp();
        void deadghostdisp();
        void ghostscradisp();
        void ghostdisp(int i);
        void snakedisp();
        void walldisp();
        void cursdisp();
        ArcadeObject::Touche alphakey(int ch);
        ArcadeObject::Touche speckey(int ch);
        bool checkscreensize();
        void messagedisp(const std::string& message);
        void objdisp();
        
    private:
        int _Inp;
        int _Xsizee;
        int _Ysizee;
        int _lenx;
        int _Leny;
        WINDOW *windows;
        std::array<std::string, 25> _name;
};

class Errorsfml : public AErr {
    public:
        Errorsfml(std::string error);
        ~Errorsfml();
};

class DispSFML : public AGraphic {
    private:
        sf::RenderWindow *_Windows;
        sf::Event _Ev;
        sf::Vector2u _tail;
        sf::IntRect _tailimg;
        int _LenX;
        int _LenY;
        double _tailX;
        double _tailY;
        sf::Texture _Tex;
        sf::Texture _texmenu;
        sf::Texture _pactex;
        sf::Sprite _Spr;
        sf::Text _texte;
        sf::Font _fonte;
        std::array<std::string, 25> _name;
        std::map<sf::Keyboard::Key, ArcadeObject::Touche> mapkey;

    public:
        DispSFML();
        ~DispSFML();
        void printdraw(void);
        void dispclear();
        ArcadeObject::Touche getevents() override;
        void stopdisp();
        void initialisation() override;
        void grassdisp(int i);
        void menudisp(int i);
        void gamedraw(int i);
        void bottomsnakedisp(int i);
        void pacgamedisp(int i);
        void textdraw(int i);
        void sizegetgame();
        std::size_t ghostfind(int i);
        

        void dispheadsnake(int i, int textureOffsetX, int textureOffsetY);
        void dispsnakbottom(int i, int textureOffsetX, int textureOffsetY);
        void appeledisp(int i);
        void defdisprite(int i);
        void defdisppacman(int i);
        void scalgrass();
        void posgrassset(int i);
        void grassizetexture();
        void scalespritset();
        void detailspritset(int pos, int i);
        int  posfind(int i);
        void detailtextset(int i, const sf::Vector2f &pos);
        sf::Vector2f posset(int i);
        void spritedispsetup(int i);
        void imgsizeset(const sf::IntRect &rect);
        void fontload();
        void texload();
        void initwindow();
        void dispobj(std::size_t i);
        void dispobjs();
        void sizeup();
        void heightgame();
        void widthgame();
};

class Errursdl : public AErr {
    public:
        Errursdl(std::string error);
        ~Errursdl();
};
class DispSDL : public AGraphic {
    private:
        SDL_Window *_Windowe;
        SDL_Renderer *_Rend;
        SDL_Event _Ev;
        int _tailleX;
        int _tailleY;
        int _LenX;
        int _LenY;
        SDL_Rect _imgpos;
        SDL_Rect _sizeimag;
        SDL_Texture * _Tex;
        SDL_Texture *_texpacman;
        SDL_Texture *_texmenu;
        TTF_Font *_Fontex;
        SDL_Color _Col;
        SDL_Surface *_surf;
        SDL_Texture *_Texture;
        std::array<std::string, 25> _arrayname;
        std::map<SDL_Keycode, ArcadeObject::Touche> mapkey;

    public:
        DispSDL();
        ~DispSDL();
        void printdraw(void);
        void dispclear();
        void stopdisp();
        void initialisation() override;
        ArcadeObject::Touche getevents() override;
        void grassdisp(void);
        void menudisp(int i);
        void gamedisp(int i);
        void snakedisp(int i);
        void pacmandisp(int i);
        void sizegame();
        void textdraw(int i);
        int ghostfind(int i);
        void initfont();
        void inittext();
        SDL_Texture* texturload(const std::string& filePath);
        void initwindow();
        void initsdl();
        void compdestroy();
        void objdisp(std::size_t index);
        void maxyget();
        void maxgetx();
        void textrend(int i);
        void createxturtext(int i);
        int posarrayname(int i);
        bool arrayname(int i, int pos);
        void texturemenudisp(int pos);
        void texturedisp(int textureX, int textureY, int textureWidth, int textureHeight);
        void snakedisptexture(int i, ArcadeObject::TypeObj type, int textureX, int textureY);
        void ghostdisp(int x, int y_offset);
        void pacmandispe(int y_offset);
        void bigbulldisp();
        void bulldisp();
        void objdisp();
        void imgsizeset(int x, int y, int w, int h);
        void appledisp();
        void headisp(int x, int y);
        void bottomdisp(int x, int y);
};
