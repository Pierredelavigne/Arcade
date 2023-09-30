/*
** EPITECH PROJECT, 2023
** objet
** File description:
** objet
*/

#include "../include/Arcade.hpp"

ArcadeAObject::ArcadeAObject(ArcadeObject::TypeObj type, int x, int y, std::string value): _typ(type), x(x), y(y), val(value)
{
}

ArcadeAObject::~ArcadeAObject()
{
}

ArcadeObject::TypeObj ArcadeAObject::get_type(void)
{
    return this->_typ;
}

int ArcadeAObject::x_get(void)
{
    return this->x;
}

int ArcadeAObject::y_get(void)
{
    return this->y;
}

std::string ArcadeAObject::get_val(void)
{
    return this->val;
}