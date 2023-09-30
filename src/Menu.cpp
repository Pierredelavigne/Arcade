/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

int ArcadeCore::Home()
{
    while (this->_Home) {
        this->_inp = this->_Lib->getevents();
        if (exevent()) return 1;

        try {
            objupmenu();
        } catch (const IError &error) {
            throw DLErr(error.what());
        }

        this->_Lib->dispupdate(this->GetObjHome());
        this->_Lib->dispclear();
        this->_Lib->printdraw();
    }
    return 0;
}

bool ArcadeCore::exevent()
{
    if (this->_inp == ArcadeObject::ECHAP || this->_inp == ArcadeObject::QUIT) {
        this->_Lib->stopdisp();
        return true;
    }
    return false;
}

void ArcadeCore::objupmenu()
{
    ArcadeObject::IObjects *cursor = fcursor();
    if (!cursor)
        cursor = new ArcadeAObject(ArcadeObject::HOME, 4, 6, "Cursor");

    this->FLib();
    this->_NumDisp = this->_DispName.size();
    this->_NumGame = this->_NameGame.size();
    this->_Obj.clear();

    poplibObj();
    pophomeObj();
    popscoreObj();

    this->_Obj.push_back(cursor);

    this->KeyHome();
}

ArcadeObject::IObjects* ArcadeCore::fcursor()
{
    for (std::size_t i = 0; i < this->_Obj.size(); i++) {
        if (this->_Obj.at(i)->get_val() == "Cursor" && this->_Obj.at(i)->get_type() == ArcadeObject::HOME)
            return this->_Obj.at(i);
    }
    return nullptr;
}

void ArcadeCore::poplibObj()
{
    std::string temp;
    int x = 5, y = 6;
    while (!this->_DispName.empty()) {
        temp = this->_DispName.back().data();
        this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, x, y, temp));
        y += 1;
        this->_DispName.pop_back();
    }

    x = 30, y = 6;
    while (!this->_NameGame.empty()) {
        temp = this->_NameGame.back().data();
        this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, x, y, temp));
        y += 1;
        this->_NameGame.pop_back();
    }
}

void ArcadeCore::pophomeObj()
{
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 18, 2, "HOME"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 5, 4, "Graphics"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 30, 4, "Games"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 18, 4, "Score"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 33, 18, "Start"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 18, 15, "Input"));
    this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 18, 15, this->_NamEntire));
}

void ArcadeCore::popscoreObj()
{
    std::size_t max = this->_score->scoreget().size() >= 5 ? 5 : this->_score->scoreget().size();

    for (std::size_t i = 0; i < max; i++) {
        this->_Obj.push_back(new ArcadeAObject(ArcadeObject::HOME, 18, 6 + i, this->_score->scoreget().at(i).nameget() + ": " + this->_score->scoreget().at(i).scoreget()));
    }
}

void ArcadeCore::libclaim(int x_value, std::string& lib_var)
{
    int y = this->_Obj.back()->y_get();

    for (std::size_t i = 0; i < this->_Obj.size(); i++) {
        if (this->_Obj.at(i)->x_get() == x_value && this->_Obj.at(i)->y_get() == y) {
            lib_var = "./lib/" + this->_Obj.at(i)->get_val();
        }
    }
}

void ArcadeCore::addscoreine()
{
    if (this->_NamEntire != "" && this->_poin != "0") {
        this->_score->scoradd(ValueScore(this->_NamEntire, this->_poin));
        this->_score->loadr();
    }
}

void ArcadeCore::LibLoad()
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

void ArcadeCore::Upname()
{
    this->_NamEntire = "";
    for (std::size_t i = 0; i < this->_User.size(); i++) {
        this->_NamEntire += this->_User.at(i);
    }
}

void ArcadeCore::UserName()
{
    if (this->_inp <= ArcadeObject::KEY_Z && this->_User.size() < 15) {
        this->_User.push_back(97 + this->_inp);
    }
    if (this->_inp == ArcadeObject::RETURN && this->_User.size() > 0)
        this->_User.pop_back();
    Upname();
}
