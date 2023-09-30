/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

bool ArcadeCore::termshould() {
    return ((_Home && (_fin = Home())) || _inp == ArcadeObject::KEY_Q || _inp == ArcadeObject::QUIT || _fin == 1);
}

void ArcadeCore::gamerun() {
    _inp = _Lib->getevents();
    verif_key(_inp);
    _Game->inpsend(_inp);
    _Game->start();
    _Obj = _Game->getObjs();
    _Lib->dispupdate(_Obj);
    fScore();
    _Lib->dispclear();
    _Lib->printdraw();
}

int ArcadeCore::boucle() {
    FLib();

    while (!termshould()) {
        gamerun();
    }

    return 0;
}

void ArcadeCore::scoradd() {
    if(_NamEntire != "" && _poin != "0") {
        _score->scoradd(ValueScore(_NamEntire, _poin));
    }
}

bool ArcadeCore::objscore(ArcadeObject::TypeObj type, const std::string& value) {
    return (type == ArcadeObject::TEXTE && value.find("Score") == 0 && value.find(":") != std::string::npos);
}

std::string ArcadeCore::extrascorev(const std::string& value) {
    return value.substr(value.find(':') + 2);
}

void ArcadeCore::fScore() {
    for (const auto& object : _Obj) {
        if (objscore(object->get_type(), object->get_val())) {
            _poin = extrascorev(object->get_val());
        }
    }
}
