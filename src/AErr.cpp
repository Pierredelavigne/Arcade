/*
** EPITECH PROJECT, 2023
** error
** File description:
** error
*/

#include "../include/Arcade.hpp"

const char *AErr::what() const noexcept
{
    return (this->errorMessage.c_str());
}

DLErr::DLErr(std::string error)
{
    this->errorMessage = "Dynamic library error: " + error;
}

DLErr::~DLErr()
{
}
