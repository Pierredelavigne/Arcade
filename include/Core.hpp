/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#pragma once

#include <vector>
#include <string>
#include "iostream"
#include "Display.hpp"
#include "Game.hpp"
#include "Arcade.hpp"
#include <dirent.h>
#include <fstream>
#include <algorithm>
#include <dlfcn.h>

template<typename T>
class Lloader {
    public:
        Lloader()
        {
        };

        ~Lloader()
        {
        };

        void Errorhandle() {
            char *error;
            if ((error = dlerror()) != NULL) {
                throw DLErr("No entry point found");
            }
        }

        void* libloadinstance(std::string className) {
            void *instance = dlopen(className.c_str(), RTLD_LAZY);
            if (!instance) {
                throw DLErr("Failed to open");
            }
            return instance;
        }

        T* crealibinstance(void* instance) {
            T *(*maker)();
            *(void **)(&maker) = dlsym(instance, "entryPoint");
            Errorhandle();
            return maker();
        }

        void instanceopen(std::string className) {
            this->_Inst = libloadinstance(className);
            this->_Lib = crealibinstance(this->_Inst);
        }


        void instclose(T *lib)
        {
            delete lib;
            dlclose(_Inst);
        };

        T *instget()
        {
            return this->_Lib;
        };

    
    private:
        void *_Inst;
        T *_Lib;
};
class ValueScore {
    public:
        ValueScore(std::string name, std::string score) : _User(name), _Scoring(score) {};
        ~ValueScore(){};

        std::string nameget() const { return this->_User; }
        std::string scoreget() const { return this->_Scoring; }

    private:
        std::string _User;
        std::string _Scoring;
};

class classement {
    public:
        classement();
        ~classement();

        void openclassement();
        std::vector<ValueScore> scoreget() const;
        void scoradd(ValueScore score);
        void loadr();
        void scoread(std::ifstream& file);
        void scoradd(const std::string& line);

    private:
        std::vector<ValueScore> _val;
        std::ofstream _valfil;
};
class ArcadeCore {
    private:
        std::vector<std::string> _DispName;
        std::vector<std::string> _NameGame;
        std::vector<char> _User;
        std::string _NamEntire;
        IGraphic *_Lib;
        IGame *_Game;
        classement *_score;
        std::string _NGame;
        std::string _NLib;
        std::string _LibName;
        std::string _GameName;
        Lloader<IGame> *_LoadGame;
        Lloader<IGraphic> *_LoaDisp;
        ArcadeObject::Touche _inp;
        bool _Home;
        int _fin;
        int _NumDisp;
        int _NumGame;
        std::string _poin;
        std::vector<ArcadeObject::IObjects *> _Obj;

    public:

        ArcadeCore(std::string libName);
        ~ArcadeCore();
        static const std::string LIB_PATH;
        int boucle();
        void OpenLibDisp(std::string libName);
        void OpenLibGame(std::string libName);
        void verif_key(ArcadeObject::Touche input);
        void LibLoad();
        void FNextDisp();
        void FNextGame();
        void FPrevDisp();
        void FPrevGame();
        void UserName();
        void fScore();
        void FLib();
        int Home();
        std::vector<ArcadeObject::IObjects *> GetObjHome();
        void KeyHome();
        void DirectItem(struct dirent* dir);
        void InstClose(Lloader<IGraphic>* loader, IGraphic* instance);
        void InstClose(Lloader<IGame>* loader, IGame* instance);
        void scoradd();
        bool termshould();
        void gamerun();
        std::string extrascorev(const std::string& value);
        bool objscore(ArcadeObject::TypeObj type, const std::string& value);
        void closeCurrentLib();
        void gameclose();
        void fnlib(std::vector<std::string>& names, std::string& current, std::string& next);
        void fdpreLib(std::vector<std::string>& names, std::string& current, std::string& next);
        void changegraph();
        void changengraph();
        void changegame();
        void changengame();
        bool exevent();
        void objupmenu();
        ArcadeObject::IObjects* fcursor();

        void poplibObj();
        void pophomeObj();
        void popscoreObj();
        void libclaim(int x_value, std::string& lib_var);
        void addscoreine();
        void Upname();
        void mcursorup();
        void actionenter();
        void cursorleft();
        int getcursorX();
        int getcursorY();
        void Updcursor(int x, int y);
        void cursordown();
        void updlib();
};
