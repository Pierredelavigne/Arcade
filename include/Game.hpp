/*
** EPITECH PROJECT, 2022
** game
** File description:
** game
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <map>
#include <unistd.h>
#include "Arcade.hpp"

class IGame {
    public:
        IGame() = default;
        virtual ~IGame() = default;
        virtual void stop() = 0;
        virtual void start() = 0;
        virtual std::vector<ArcadeObject::IObjects *> getObjs(void) = 0;
        virtual void inpsend(ArcadeObject::Touche) = 0;
        virtual void setname(std::string name) = 0;
        virtual std::string nameget(void) = 0;
};

class GameNibbler : public IGame{

    protected:
        int _taille;
        int _temps;
        int _play;
        int _other;
        int _point;
        int _linelen;
        int _totallen;
        int _position;
        std::string _maping;
        std::string _direc;
        std::map<int, int> _snakebody;
        std::vector<ArcadeObject::IObjects*> _obj;
        ArcadeObject::Touche _inp;
        ArcadeObject::Touche _savinp;
        std::string user;

    public:
        GameNibbler();
        ~GameNibbler();
        void stop() override;
        std::vector<ArcadeObject::IObjects *> getObjs() override;
        void inpsend(ArcadeObject::Touche) override;
        void setname(std::string name) override;
        std::string nameget(void) override;
        void start() override;

        void snakeposget();
        void crearray();
        void handinput();
        void leftmove();
        void rightmove();
        void upmove();
        void downmove();
        void straimove();
        void applepos();
        bool nbapple();
        void creavec();
        void maplace();
        void snakerase();
        void bodymove();
        void waitstart();
        bool queuecheck();
        void initre();
        long long int calculdiff(struct timeval *start, struct timeval *stop);
        int calcapples();
        void inputspace();
        void inputfleche();
        bool collicheck(int next_position);
        bool appleis(int position);
        void miamapple(int position);
        bool collibody(int head_position, int body_position);
        void mapreplacechar(char target_char);
        void bodysnake(int startPos);
        int snakepos() ;
        void clearbody();
        void resgame();
        void cretailObj(int x, int y);
        void creabodyObj(int x, int y);
        void creaheadObj(int x, int y);
        void creaobjmap(char mapChar, int x, int y);
        void delobj();
        void nextframe(timeval* start, timeval* stop);
        void gamecontinu();
        void gamestart();
        void initgame();
        void initmap();
};

class GamePacman : public IGame {
        protected:
        char backred;
        char backpink;
        char backblue;
        char bachorange;
        std::vector<ArcadeObject::IObjects *> _Obj;
        ArcadeObject::Touche _inp;
        ArcadeObject::Touche _safinp;
        std::string _maping;
        int _point;
        int _gumesuper;
        float timeur;
        float timegumsuper;
        int vit;
        int nombreghost;
        int nombrespawnghost;
        int nombregum;
        int linelengt;
        int pacpos;
        int posred;
        int deadred;
        int sensred;
        int pospink;
        int deadpink;
        int senspink;
        int posblue;
        int deadblue;
        int sensblue;
        int posorange;
        int deadorange;
        int sensorange;
        int gagne;
        int ghospawn;
        int ghostime;
        int pactime;
        int redtime;
        int bluetime;
        int pinktime;
        int orangetime;
        std::string user;

    public:
        GamePacman();
        ~GamePacman();

        void inpsend(ArcadeObject::Touche) override;
        void start() override;
        std::vector<ArcadeObject::IObjects *> getObjs(void) override;
        void stop(){};
        void setname(std::string name) override;
        std::string nameget(void) override;
        bool canMove(int direction, int ghost);
        int getRandomDirection();
        void crearray();
        void pacmoveopt();
        void upmove();
        void downmove();
        void rightmove();
        void leftmove();
        void movefantom(int);
        void moveleftfantom(int, int);
        void moverightfantom(int, int);
        void moveupfantom(int, int);
        void movedownfantom(int, int);
        void ghostspawn();
        void ghostselect();
        void ghostrespawn();
        long long int diffcalc(struct timeval *start, struct timeval *stop);
        void supergumtime();
        void gumtime();
        void pacmove(int direction, bool isTeleport = false, int teleportOffset = 0);
        void movemptyspace(int direction);
        void ghostcons(char ghostType, int &ghost_dead, int &ghost_pos, int direction);
        void handinmov();
        void ghostcollision();
        void handsupergumGum();
        void timeups(struct timeval& start, struct timeval& stop);
        void respawnghost(int& ghost_time, int& ghost_dead, int& ghost_pos, char ghost_type);
        void spawnghost(int& ghost_pos, char ghost_type);
        void supergumhand();
        void handleGum();
        ArcadeAObject* creaghostObj(char mapChar, int sens, int x, int y) ;
        void incrPos(int& x, int& y, char mapChar);
        void pacmanhand(int x, int y);
        void objclear();
        void casespecialhand(int i, int x, int y);
        void vargamerest() ;
        void ghostvarest();
        void rescharpos() ;
        void GhostUpmove(int &pos, char &back, char ghostChar, int &sens);
        bool canupmove(int pos);
        void GhostRightmove(int &pos, char &back, char ghostChar, int &sens);
        bool canRightMove(int pos);
        bool canDownmove(int pos);
        void GhostDownmove(int &pos, char &back, char ghostChar, int &sens);
        void GhostLeftmove(int& pos, char& back, char ghostSymbol, int& sens);
        bool canLeftmove(int pos);
        int ghostdetermove(int ghostPos);

};
