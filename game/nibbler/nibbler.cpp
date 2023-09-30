/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** GameNibbler
*/

#include "../../include/Game.hpp"

GameNibbler::GameNibbler() : _temps(0), _play(0), _totallen(0), _linelen(0), 
                     _position(0), _direc("left"), _point(0), _other(4), _taille(3)
{
    srand(time(NULL));
    initgame();
}

void GameNibbler::initgame() 
{
    initmap();
    snakeposget();
}

void GameNibbler::initmap() 
{
    crearray();
}


GameNibbler::~GameNibbler()
{
}


void GameNibbler::crearray()
{
    std::string mapFilePath = "game/nibbler/map.txt";
    std::ifstream mapFile(mapFilePath);
    if (!mapFile) {
        throw std::runtime_error("Could not open map file: " + mapFilePath);
    }
    _maping.assign(std::istreambuf_iterator<char>{mapFile}, {});
    _totallen = _maping.size();
    _linelen = _maping.find('\n') + 1;
}




int GameNibbler::snakepos() 
{
    for (int i = 0; _maping[i] != '\0'; i++) 
    {
        if (_maping[i] == 'S')
            return i;
    }
    return -1;
}

void GameNibbler::bodysnake(int startPos)
{
    for(int i = 0; i < 4; i++)
    {
        _snakebody.insert(std::make_pair(i, startPos + i));
    }
}

void GameNibbler::snakeposget()
{
    int startPos = snakepos();
    if(startPos == -1) 
    {
        throw std::runtime_error("Snake position not found in map!");
    }
    bodysnake(startPos);
}


long long int GameNibbler::calculdiff(struct timeval *start, struct timeval *stop)
{
    return ((start->tv_sec * 1000000 + start->tv_usec) - (stop->tv_sec * 1000000 + stop->tv_usec));
}


void GameNibbler::start()
{    
    struct timeval start, stop;

    gettimeofday(&start, NULL);

    if (_play == 0) {
        gamestart();
    }
    else {
        gamecontinu();
        nextframe(&start, &stop);
    }
}

void GameNibbler::gamestart() {
    waitstart();
    applepos();
    creavec();
}

void GameNibbler::gamecontinu() {
    applepos();
    handinput();
    creavec();
}

void GameNibbler::nextframe(timeval* start, timeval* stop) {
    while(calculdiff(stop, start) < 80000) {
        gettimeofday(stop, NULL);
    }
}




void GameNibbler::waitstart()
{
    switch (_inp) {
        case ArcadeObject::Touche::ARROW_LEFT:
            _play = 1;
            break;
        default:
            break;
    }
}


void GameNibbler::clearbody()
{
    int i = 0;
    while (_snakebody.count(i)) {
        _snakebody.erase(_snakebody.find(i));
        i++;
    }
}

void GameNibbler::resgame()
{
    _temps = 0;
    _play = 0;
    _totallen = 0;
    _linelen = 0;
    _position = 0;
    _direc = "left";
    _point = 0;
    _other = 4;
    _taille = 3;
}

void GameNibbler::initre()
{
    clearbody();
    resgame();
    crearray();
    snakeposget();
    start();
}


void GameNibbler::delobj()
{
    if (!_obj.empty()) {
        for (ArcadeObject::IObjects* object : _obj) {
            ArcadeAObject* concreteObject = dynamic_cast<ArcadeAObject*>(object);
            if(concreteObject) {
                delete concreteObject;
                concreteObject = nullptr;
            }
        }
        _obj.clear();
    }
}


void GameNibbler::creaobjmap(char mapChar, int x, int y)
{
    switch (mapChar) {
        case '#':
            _obj.push_back(new ArcadeAObject(ArcadeObject::MUR, x, y));
            break;
        case 'A':
            _obj.push_back(new ArcadeAObject(ArcadeObject::POMME, x, y));
            break;
        case ' ':
            _obj.push_back(new ArcadeAObject(ArcadeObject::BACKGROUND, x, y));
            break;
        case 'S':
            creaheadObj(x, y);
            break;
        case 'q':
            creabodyObj(x, y);
            break;
        case 'Q':
            cretailObj(x, y);
            break;
        default:
            break;
    }
}

void GameNibbler::creaheadObj(int x, int y)
{
    switch (_direc[0]) {
        case 'l':
            _obj.push_back(new ArcadeAObject(ArcadeObject::LEFTHEAD, x, y));
            break;
        case 'r':
            _obj.push_back(new ArcadeAObject(ArcadeObject::RIGHTHEAD, x, y));
            break;
        case 'u':
            _obj.push_back(new ArcadeAObject(ArcadeObject::UPHEAD, x, y));
            break;
        case 'd':
            _obj.push_back(new ArcadeAObject(ArcadeObject::DOWNHEAD, x, y));
            break;
    }
}

void GameNibbler::creabodyObj(int x, int y)
{
    switch (_direc[0]) {
        case 'l':
        case 'r':
            _obj.push_back(new ArcadeAObject(ArcadeObject::LEFTBODY, x, y));
            break;
        case 'u':
        case 'd':
            _obj.push_back(new ArcadeAObject(ArcadeObject::RIGHTBODY, x, y));
            break;
    }
}

void GameNibbler::cretailObj(int x, int y)
{
    if (_snakebody.find(_taille - 1)->second == _snakebody.find(_taille)->second - 1)
        _obj.push_back(new ArcadeAObject(ArcadeObject::RIGHTBOTTOM, x, y));
    if (_snakebody.find(_taille - 1)->second == _snakebody.find(_taille)->second + 1)
        _obj.push_back(new ArcadeAObject(ArcadeObject::LESFTBOTTOM, x, y));
    if (_snakebody.find(_taille - 1)->second == _snakebody.find(_taille)->second - _linelen)
        _obj.push_back(new ArcadeAObject(ArcadeObject::DOWNBOTTOM, x, y));
    if (_snakebody.find(_taille - 1)->second == _snakebody.find(_taille)->second + _linelen)
        _obj.push_back(new ArcadeAObject(ArcadeObject::UPBOTTOM, x, y));
}

void GameNibbler::creavec()
{
    delobj();

    int x = 0;
    int y = 0;
    for (int i = 0; _maping[i] != '\0'; i++) {
        creaobjmap(_maping[i], x, y);
        x++;
        if (_maping[i] == '\n') {
            x = 0;
            y++;
        }
    }

    std::string score = "Score: " + std::to_string(_point);
    _obj.push_back(new ArcadeAObject(ArcadeObject::TEXTE, 1, 1, score));
}


extern "C" IGame *entryPoint()
{
return (new GameNibbler);
}

void GameNibbler::inpsend(ArcadeObject::Touche in)
{
    _inp = in;
    switch (in) {
        case ArcadeObject::Touche::NO_INPUT:
            break;
        default:
            _savinp = _inp;
            break;
    }
}


std::vector<ArcadeObject::IObjects *> GameNibbler::getObjs()
{
    return (_obj);
}

void GameNibbler::setname(std::string user)
{
    this->user = user;
}

std::string GameNibbler::nameget()
{
    return ("nibbler");
}

void GameNibbler::stop()
{   
    return;
}

void GameNibbler::inputfleche()
{
    if (_direc == "left" || _direc == "right") {
        if (_savinp == ArcadeObject::Touche::ARROW_UP) {
            upmove();
        } else if (_savinp == ArcadeObject::Touche::ARROW_DOWN) {
            downmove();
        } else {
            straimove();
        }
    } else if (_direc == "up" || _direc == "down") {
        if (_savinp == ArcadeObject::Touche::ARROW_LEFT) {
            leftmove();
        } else if (_savinp == ArcadeObject::Touche::ARROW_RIGHT) {
            rightmove();
        } else {
            straimove();
        }
    }
}

void GameNibbler::inputspace()
{
    if (_savinp == ArcadeObject::Touche::SPACE) {
        initre();
    }
}

void GameNibbler::handinput()
{
    inputfleche();
    inputspace();
}


void GameNibbler::leftmove()
{
    int next_position = _snakebody.find(0)->second - 1;

    if (collicheck(next_position)) {
        initre();
        return;
    }

    if (appleis(next_position)) {
        miamapple(next_position);
    }

    bodymove();
    _snakebody.find(0)->second = next_position;
    _direc = "left";
    maplace();
}

bool GameNibbler::collicheck(int next_position)
{
    return (_maping[next_position] == '#' || queuecheck() == false);
}

bool GameNibbler::appleis(int position)
{
    return (_maping[position] == 'A');
}

void GameNibbler::miamapple(int position)
{
    _snakebody.insert(std::make_pair(_other, _position + _other));
    _other++;
    _taille++;
    _point += 10;
}


void GameNibbler::rightmove()
{
    int next_position = _snakebody.find(0)->second + 1;

    if (collicheck(next_position)) {
        initre();
        return;
    }

    if (appleis(next_position)) {
        miamapple(next_position);
    }

    bodymove();
    _snakebody.find(0)->second = next_position;
    _direc = "right";
    maplace();
}


void GameNibbler::upmove()
{
    int next_position = _snakebody.find(0)->second - _linelen;

    if (collicheck(next_position)) {
        initre();
        return;
    }

    if (appleis(next_position)) {
        miamapple(next_position);
    }

    bodymove();
    _snakebody.find(0)->second = next_position;
    _direc = "up";
    maplace();
}

void GameNibbler::downmove()
{
    int next_position = _snakebody.find(0)->second + _linelen;

    if (collicheck(next_position)) {
        initre();
        return;
    }

    if (appleis(next_position)) {
        miamapple(next_position);
    }

    bodymove();
    _snakebody.find(0)->second = next_position;
    _direc = "down";
    maplace();
}


bool GameNibbler::collibody(int head_position, int body_position) {
    return head_position == body_position;
}

bool GameNibbler::queuecheck() {
    int head_position = _snakebody.find(0)->second;
    auto it = _snakebody.begin();
    while (it != _snakebody.end()) {
        if (it->first != 0 && collibody(head_position, it->second)) {
            return false;
        }
        ++it;
    }
    return true;
}


void GameNibbler::straimove()
{
    static const std::map<std::string, void (GameNibbler::*)()> direction_map = {
        {"left", &GameNibbler::leftmove},
        {"right", &GameNibbler::rightmove},
        {"up", &GameNibbler::upmove},
        {"down", &GameNibbler::downmove}
    };
    auto direction_it = direction_map.find(_direc);
    if (direction_it != direction_map.end()) {
        (this->*(direction_it->second))();
    }
}

void GameNibbler::bodymove()
{
    auto it = _snakebody.rbegin();
    auto next_it = std::next(it);

    while (next_it != _snakebody.rend()) {
        it->second = next_it->second;
        it = next_it;
        ++next_it;
    }
}

void GameNibbler::mapreplacechar(char target_char)
{
    std::replace(_maping.begin(), _maping.end(), target_char, ' ');
}

void GameNibbler::snakerase()
{
    mapreplacechar('S');
    mapreplacechar('q');
    mapreplacechar('Q');
}

void GameNibbler::maplace()
{
    auto it = std::next(_snakebody.begin());
    snakerase();
    _maping[_snakebody.begin()->second] = 'S';
    while (it != _snakebody.end()) {
        _maping[it->second] = 'q';
        ++it;
    } _maping[_snakebody.rbegin()->second] = 'Q';
}

int GameNibbler::calcapples()
{
    int count = 0;
    int i = 0;

    while (_maping[i] != '\0') {
        if (_maping[i] == 'A')
            count++;
        i++;
    }

    return count;
}


bool GameNibbler::nbapple()
{
    int appleCount = calcapples();
    
    return appleCount < 3;
}


void GameNibbler::applepos()
{
    if (nbapple() == false)
        return;

    const int MAX_TRIES = _totallen;
    int tries = 0;
    while(tries < MAX_TRIES) {
        int randNum = rand()%(_totallen + 1);
        if (_maping[randNum] == ' ') {
            _maping[randNum] = 'A';
            return;
        }
        ++tries;
    }
}