/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

const std::string ArcadeCore::LIB_PATH = "./lib/";

ArcadeCore::ArcadeCore(std::string libName)
{
    this->_Game = nullptr;
    this->_Lib = nullptr;
    this->_LoadGame = new Lloader<IGame>();
    this->_LoaDisp = new Lloader<IGraphic>();
    this->_score = new classement();
    this->_Home = true;
    this->_LibName = libName;
    this->_GameName = "";
    this->_NamEntire = "";
    this->_poin = "0";
    this->_score->openclassement();
}

ArcadeCore::~ArcadeCore()
{
    InstClose(_LoaDisp, _Lib);
    InstClose(_LoadGame, _Game);
    delete _LoadGame;
    delete _LoaDisp;
    scoradd();
    delete _score;
}

void ArcadeCore::InstClose(Lloader<IGraphic>* loader, IGraphic* instance) {
    if(instance != nullptr) {
        loader->instclose(instance);
    }
}

void ArcadeCore::InstClose(Lloader<IGame>* loader, IGame* instance) {
    if(instance != nullptr) {
        loader->instclose(instance);
    }
}

void ArcadeCore::closeCurrentLib()
{
    if (this->_Lib != nullptr) {
        this->_Lib->stopdisp();
        this->_LoaDisp->instclose(this->_Lib);
    }
}

void ArcadeCore::gameclose()
{
    if (this->_Game != nullptr)
        this->_LoadGame->instclose(this->_Game);
}

void ArcadeCore::OpenLibDisp(std::string libName)
{
    if (this->_LibName == this->_NLib && this->_Lib != nullptr)
        return;

    try {
        closeCurrentLib();

        this->_LoaDisp->instanceopen(libName);
        this->_Lib = this->_LoaDisp->instget();
        this->_Lib->initialisation();
        
        if (!this->_NLib.empty())
            this->_LibName = this->_NLib;
    } catch (const IError &error) {
        throw DLErr(error.what());
    }
}

void ArcadeCore::OpenLibGame(std::string libName)
{
    if (this->_GameName == this->_NGame && this->_Game != nullptr)
        return;

    try {
        gameclose();

        this->_LoadGame->instanceopen(libName);
        this->_Game = this->_LoadGame->instget();

        this->_GameName = this->_NGame;
    } catch (const IError &error) {
        throw DLErr(error.what());
    }
}

void ArcadeCore::verif_key(ArcadeObject::Touche input)
{
    switch (input) {
        case ArcadeObject::KEY_A:
            changegraph();
            break;
        case ArcadeObject::KEY_Z:
            changengraph();
            break;
        case ArcadeObject::KEY_O:
            changegame();
            break;
        case ArcadeObject::KEY_P:
            changengame();
            break;
        case ArcadeObject::ECHAP:
            this->_Home = true;
            break;
        default:
            return;
    }
}

void ArcadeCore::changegraph()
{
    this->FPrevDisp();
    this->OpenLibDisp(this->_NLib);
}

void ArcadeCore::changengraph()
{
    this->FNextDisp();
    this->OpenLibDisp(this->_NLib);
}

void ArcadeCore::changegame()
{
    this->FPrevGame();
    this->OpenLibGame(this->_NGame);
}

void ArcadeCore::changengame()
{
    this->FNextGame();
    this->OpenLibGame(this->_NGame);
}
