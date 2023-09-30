/*
** EPITECH PROJECT, 2023
** error
** File description:
** error
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>

namespace ArcadeObject {
    enum TypeObj {
        BULLE,
        BIGBULLE,
        GHOSTUP,
        UPBOTTOM,
        DOWNBOTTOM,
        RIGHTBOTTOM,
        LESFTBOTTOM,
        TEXTE,
        GHOSTRIGHT,
        RIGHTHEAD,
        LEFTHEAD,
        LEFTBODY,
        RIGHTBODY,
        UPAC,
        RIGHTPAC,
        HOME,
        GHOSTLEFT,
        GHOSTDOWN,
        GHOSTSCARE,
        DEADGHOST,
        POMME,
        BACKGROUND,
        MUR,
        BOTTOMRIGHTCORNER,
        TOPRIGHTCORNER,
        BOTTOMLESFCORNER,
        TOPLEFTCORNER,
        UPHEAD,
        DOWNHEAD,
        LEFTPAC,
        DOWNPAC,
    };
    enum Touche {
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        QUIT,
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        SPACE,
        ECHAP,
        NO_INPUT,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        RETURN,
        ENTER
    };

    class IObjects {
        public:
            virtual ArcadeObject::TypeObj get_type(void) = 0;
            virtual std::string get_val(void) = 0;
            virtual int x_get(void) = 0;
            virtual int y_get(void) = 0;
    };
}

class IError : public std::exception {
    public:
        virtual ~IError() = default;
};

class AErr : public IError {
    public:
        const char *what() const noexcept override;

    protected:
        std::string errorMessage;
};

class DLErr : public AErr {
    public:
        DLErr(std::string error);
        ~DLErr();
};

class ArcadeAObject : public ArcadeObject::IObjects {
    public:
        ArcadeAObject(ArcadeObject::TypeObj type, int x, int y, std::string value = "");
        ~ArcadeAObject();

        ArcadeObject::TypeObj get_type(void) override;
        int x_get(void) override;
        int y_get(void) override;
        std::string get_val(void) override;
    
    private:
        ArcadeObject::TypeObj _typ;
        int x;
        int y;
        std::string val;
};
