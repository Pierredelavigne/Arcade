/*
** EPITECH PROJECT, 2022
** game
** File description:
** game
*/

#include "../../include/Game.hpp"

GamePacman::GamePacman()
    : gagne(0),
      vit(0),
      linelengt(0),
      _maping(""),
      _inp(ArcadeObject::Touche::NO_INPUT),
      _point(0),
      _gumesuper(0),
      timeur(0),
      ghostime(0),
      pactime(0),
      timegumsuper(0),
      redtime(0),
      bluetime(0),
      pinktime(0),
      orangetime(0),
      nombregum(0),
      backpink(' '),
      backred(' '),
      bachorange(' '),
      backblue(' '),
      nombreghost(0),
      nombrespawnghost(1),
      deadpink(0),
      deadorange(0),
      deadred(0),
      deadblue(0),
      sensred(0),
      sensblue(0),
      senspink(0),
      sensorange(0),
      _safinp(ArcadeObject::Touche::NO_INPUT)
{
}


GamePacman::~GamePacman()
{}

void GamePacman::inpsend(ArcadeObject::Touche inputs)
{
    this ->_inp = inputs;
}

void GamePacman::vargamerest() {
    if (gagne == 0)
        _point = 0;
    _gumesuper = timeur = ghostime = pactime = timegumsuper = 0;
    redtime = bluetime = pinktime = orangetime = 0;
    nombregum = 0;
    nombreghost = 0;
    nombrespawnghost = 1;
    _safinp = ArcadeObject::Touche::NO_INPUT;
    if (gagne == 1)
        vit = vit + 1;
    gagne = 0;
}

void GamePacman::ghostvarest() {
    deadpink = deadorange = deadred = deadblue = 0;
    sensred = sensblue = senspink = sensorange = 0;
    backpink = backred = bachorange = backblue = ' ';
}

void GamePacman::rescharpos() {
    for (int i = 0; _maping[i] != '\0'; i++) {
        if (_maping[i] == '\n' && linelengt == 0)
            linelengt = i + 1;
        switch (_maping[i]) {
            case 'C': pacpos = i; break;
            case 'P': pospink = i; break;
            case 'R': posred = i; ghospawn = i; break;
            case 'B': posblue = i; break;
            case 'O': posorange = i; break;
            default: break;
        }
    }
}

void GamePacman::crearray()
{
       std::ifstream file("game/Pacman/map_pacman.txt");
    std::string line;
    _maping = "";
    int i = 0;

    while (std::getline(file, line)) {
        _maping += line + '\n';
        for (char c : line) {
            switch (c) {
                case 'C': pacpos = i; break;
                case 'P': pospink = i; break;
                case 'R': posred = i; ghospawn = i; break;
                case 'B': posblue = i; break;
                case 'O': posorange = i; break;
                default: break;
            }
            i++;
        }
    }
    file.close();
    vargamerest();
    ghostvarest();
    rescharpos();
}

void GamePacman::pacmoveopt()
{
    switch (_inp) {
        case ArcadeObject::Touche::ARROW_DOWN:
            return downmove();
        case ArcadeObject::Touche::ARROW_LEFT:
            return leftmove();
        case ArcadeObject::Touche::ARROW_RIGHT:
            return rightmove();
        case ArcadeObject::Touche::ARROW_UP:
            return upmove();
        default:
            if (_safinp != ArcadeObject::Touche::NO_INPUT) {
                _inp = _safinp;
                pacmoveopt();
            }
    }
}


ArcadeAObject* GamePacman::creaghostObj(char mapChar, int sens, int x, int y) {
    switch (sens) {
        case 0:
            return new ArcadeAObject(ArcadeObject::GHOSTRIGHT, x, y, std::string(1, mapChar));
        case 1:
            return new ArcadeAObject(ArcadeObject::GHOSTUP, x, y, std::string(1, mapChar));
        case 2:
            return new ArcadeAObject(ArcadeObject::GHOSTDOWN, x, y, std::string(1, mapChar));
        case 3:
            return new ArcadeAObject(ArcadeObject::GHOSTLEFT, x, y, std::string(1, mapChar));
        default:
            return nullptr;
    }
}

void GamePacman::objclear()
{
    if (_Obj.size() != 0) {
        for (size_t i = 0; i < _Obj.size(); i++) {
            delete _Obj.at(i);
        }
        _Obj.clear();
    }
}

void GamePacman::pacmanhand(int x, int y)
{
    switch (_safinp) {
        case ArcadeObject::Touche::ARROW_RIGHT:
        case ArcadeObject::Touche::NO_INPUT:
            _Obj.push_back(new ArcadeAObject(ArcadeObject::RIGHTPAC, x, y));
            break;
        case ArcadeObject::Touche::ARROW_LEFT:
            _Obj.push_back(new ArcadeAObject(ArcadeObject::LEFTPAC, x, y));
            break;
        case ArcadeObject::Touche::ARROW_UP:
            _Obj.push_back(new ArcadeAObject(ArcadeObject::UPAC, x, y));
            break;
        case ArcadeObject::Touche::ARROW_DOWN:
            _Obj.push_back(new ArcadeAObject(ArcadeObject::DOWNPAC, x, y));
            break;
    }
}

void GamePacman::incrPos(int& x, int& y, char mapChar)
{
    x++;
    if (mapChar == '\n') {
        x = 0;
        y++;
    }
}

void GamePacman::casespecialhand(int i, int x, int y) 
{
    if (_gumesuper == 1 && (_maping[i] == 'O' || _maping[i] == 'P' || _maping[i] == 'R'|| _maping[i] == 'B')) {
        _Obj.push_back(new ArcadeAObject(ArcadeObject::GHOSTSCARE, x, y));
    }
    if ((deadred == 1 && _maping[i] == 'R') || (deadpink == 1 && _maping[i] == 'P')
    || (deadblue == 1 && _maping[i] == 'B') || (deadorange == 1 && _maping[i] == 'O')) {
        _Obj.push_back(new ArcadeAObject(ArcadeObject::DEADGHOST, x, y));
    }
}


std::vector<ArcadeObject::IObjects *> GamePacman::getObjs(void)
{
    int x = 0;
    int y = 0;

    objclear();

    std::string score = "Score: " + std::to_string(_point);
    for (int i = 0; _maping[i] != '\0'; i++) { 
        switch (_maping[i]) {
            case 'C':
                pacmanhand(x, y);
                break;
            case 'R':
                _Obj.push_back(creaghostObj('R', sensred, x, y));
                break;
            case 'P':
                _Obj.push_back(creaghostObj('P', senspink, x, y));
                break;
            case 'B':
                _Obj.push_back(creaghostObj('B', sensblue, x, y));
                break;
            case 'O':
                _Obj.push_back(creaghostObj('O', sensorange, x, y));
                break;
            case '#':
                _Obj.push_back(new ArcadeAObject(ArcadeObject::MUR, x, y));
                break;
            case ' ':
            case '%':
            case '!':
                _Obj.push_back(new ArcadeAObject(ArcadeObject::BACKGROUND, x, y));
                break;
            case '.':
                _Obj.push_back(new ArcadeAObject(ArcadeObject::BULLE, x, y));
                break;
            case 'D':
                _Obj.push_back(new ArcadeAObject(ArcadeObject::BIGBULLE, x, y));
                break;
        }

        casespecialhand(i, x, y);

        incrPos(x, y, _maping[i]);
    }
    
    _Obj.push_back(new ArcadeAObject(ArcadeObject::TEXTE, 1, 1, score));
    return _Obj;
}


void GamePacman::spawnghost(int& ghost_pos, char ghost_type) {
    _maping[ghost_pos] = ' ';
    ghost_pos = ghospawn;
    _maping[ghost_pos] = ghost_type;
}

void GamePacman::ghostspawn()
{
    if (ghostime > 1000 && nombrespawnghost < 2){
        spawnghost(pospink, 'P');
        nombrespawnghost = 2;
    }
    if (ghostime >  2000 && nombrespawnghost < 3){
        spawnghost(posblue, 'B');
        nombrespawnghost = 3;
    } 
    if (ghostime > 3000 && nombrespawnghost < 4){
        spawnghost(posorange, 'O');
        nombrespawnghost = 4;
    }
}

void GamePacman::respawnghost(int& ghost_time, int& ghost_dead, int& ghost_pos, char ghost_type) {
    if (ghost_time > 10000) {
        ghost_time = 0;
        ghost_dead = 0;
        spawnghost(ghost_pos, ghost_type);
    }
}

void GamePacman::ghostrespawn()
{
    respawnghost(redtime, deadred, posred, 'R');
    respawnghost(pinktime, deadpink, pospink, 'P');
    respawnghost(orangetime, deadorange, posorange, 'O');
    respawnghost(bluetime, deadblue, posblue, 'B');
}



long long int GamePacman::diffcalc(struct timeval *startPoint, struct timeval *stopPoint)
{
    long long startInMicroseconds, stopInMicroseconds;
    startInMicroseconds = startPoint->tv_sec * 1000000 + startPoint->tv_usec;
    stopInMicroseconds = stopPoint->tv_sec * 1000000 + stopPoint->tv_usec;
    return (startInMicroseconds - stopInMicroseconds);
}

void GamePacman::timeups(struct timeval& start, struct timeval& stop) {
    auto diffTime = diffcalc(&stop, &start);
    timeur = timeur + diffTime;
    ghostime = (ghostime + diffTime);
    pactime = pactime + diffTime;
    if (_gumesuper == 1)
        timegumsuper = timegumsuper + diffTime;
    if (deadred == 1)
        redtime = redtime + diffTime;
    if (deadpink == 1)
        pinktime = pinktime + diffTime;
    if (deadblue == 1)
        bluetime = bluetime + diffTime;
    if (deadorange == 1)
        orangetime = orangetime + diffTime;
}

void GamePacman::supergumhand() {
    if (timegumsuper > 1000) {
        timegumsuper = 0;
        nombreghost = 0;
        _gumesuper = 0;
    }
}

void GamePacman::handleGum() {
    if (nombregum == 150) {
        gagne = 1;
        crearray();
    }
}

void GamePacman::handsupergumGum() {
    supergumhand();
    handleGum();
}


void GamePacman::ghostcollision() {
    if ((pacpos == posred || pacpos == posorange || pacpos == pospink || pacpos == posblue) && _gumesuper == 0)
        crearray();
}

void GamePacman::handinmov() {
    switch(_inp) {
        case ArcadeObject::Touche::NO_INPUT:
            if (pactime > 8) {
                pactime = 0;
                pacmoveopt();
            }
            if (timeur > (30 - vit)) {
                timeur = 0;
                ghostspawn();
                ghostselect();
                ghostcollision();
            }
            break;
        default:
            if (_inp != _safinp) {
                pacmoveopt();
            }
            break;
    }
}


void GamePacman::start() {
    struct timeval start, stop;

    if (_maping == "" || _inp == ArcadeObject::Touche::SPACE)
        crearray();

    gettimeofday(&start, NULL);

    handinmov();

    if (pacpos == posred && _gumesuper == 0)
        crearray();

    gettimeofday(&stop, NULL);
    
    timeups(start, stop);
    
    ghostrespawn();
    
    handsupergumGum();
}


std::string GamePacman::nameget()
{
    return ("pacman");
}

void GamePacman::setname(std::string user)
{
    this->user = user;
}

extern "C" IGame *entryPoint()
{
    return (new GamePacman);
}

void GamePacman::gumtime() {
    _point = _point + 10;
    nombregum = nombregum + 1;
}

void GamePacman::supergumtime() {
    _point = _point + 50;
    nombregum = nombregum + 1;
    _gumesuper = 1;
    timegumsuper = 0;
}

void GamePacman::ghostcons(char ghostType, int &ghost_dead, int &ghost_pos, int direction) {
    nombreghost = nombreghost + 1;
    _point = _point + (200 * nombreghost);
    ghost_dead = 1;
    ghost_pos = ghospawn + direction;
    _maping[ghost_pos] = ghostType;
}

void GamePacman::movemptyspace(int direction) {
    _maping[pacpos + direction] = 'C';
    _maping[pacpos] = ' ';
    pacpos = pacpos + direction;
}

void GamePacman::pacmove(int direction, bool isTeleport, int teleportOffset) {
    if (isTeleport) {
        _maping[pacpos + teleportOffset] = 'C';
        _maping[pacpos] = ' ';
        pacpos = pacpos + teleportOffset;
    } else {
        char next_pos = _maping[pacpos + direction];

        switch(next_pos) {
            case ' ': 
                movemptyspace(direction);
                break;
            case '.': 
                gumtime();
                break;
            case 'D': 
                supergumtime();
                break;
            case 'R': 
                if (_gumesuper == 1) 
                    ghostcons('R', deadred, posred, direction);
                else if (_gumesuper == 0) 
                    crearray();
                break;
            case 'P': 
                if (_gumesuper == 1) 
                    ghostcons('P', deadpink, pospink, direction);
                else if (_gumesuper == 0) 
                    crearray();
                break;
            case 'O': 
                if (_gumesuper == 1) 
                    ghostcons('O', deadorange, posorange, direction);
                else if (_gumesuper == 0) 
                    crearray();
                break;
            case 'B': 
                if (_gumesuper == 1) 
                    ghostcons('B', deadblue, posblue, direction);
                else if (_gumesuper == 0) 
                    crearray();
                break;
            default: 
                return;
        }

        if (next_pos == '.' || next_pos == 'D' || 
            (next_pos == 'R' || next_pos == 'B' || next_pos == 'P' || next_pos == 'O') && _gumesuper == 1) {
            movemptyspace(direction);
        }
    }

    _safinp = _inp;
}

void GamePacman::upmove() {
    pacmove(-linelengt);
}

void GamePacman::downmove() {
    pacmove(linelengt);
}

void GamePacman::leftmove() {
    char next_pos = _maping[pacpos - 1];

    if (next_pos == '!') {
        pacmove(-1, true, linelengt - 4);
    } else {
        pacmove(-1);
    }
}

void GamePacman::rightmove() {
    char next_pos = _maping[pacpos + 1];

    if (next_pos == '%') {
        pacmove(1, true, -linelengt + 4);
    } else {
        pacmove(1); 
    }
}

bool GamePacman::canupmove(int pos) {
    return _maping[pos - linelengt] != '#' && _maping[pos - linelengt] != 'O'
           && _maping[pos - linelengt] != 'P' && _maping[pos - linelengt] != 'B'
           && _maping[pos - linelengt] != '%' && _maping[pos - linelengt] != '!';
}


void GamePacman::GhostUpmove(int &pos, char &back, char ghostChar, int &sens) {
    char temp = _maping[pos - linelengt];
    _maping[pos - linelengt] = ghostChar;
    _maping[pos] = back;
    pos = pos - linelengt;
    back = temp;
    sens = 1;
}

void GamePacman::moveupfantom(int i, int _ghost) {
    switch (_ghost) {
        case 1:
            if (canupmove(posred)) {
                GhostUpmove(posred, backred, 'R', sensred);
                return;
            }
            break;
        case 2:
            if (canupmove(pospink)) {
                GhostUpmove(pospink, backpink, 'P', senspink);
                return;
            }
            break;
        case 3:
            if (canupmove(posblue)) {
                GhostUpmove(posblue, backblue, 'B', sensblue);
                return;
            }
            break;
        case 4:
            if (canupmove(posorange)) {
                GhostUpmove(posorange, bachorange, 'O', sensorange);
                return;
            }
            break;
        default:
            break;
    }
    switch (i) {
        case 1:
            return movedownfantom(1, _ghost);
        case 2:
            return;
        case 3:
            return moverightfantom(3, _ghost);
        case 4:
            return moveleftfantom(4, _ghost);
        default:
            return;
    }
}



bool GamePacman::canRightMove(int pos) {
    return _maping[pos + 1] != '#' && _maping[pos + 1] != 'O'
           && _maping[pos + 1] != 'P' && _maping[pos + 1] != 'B'
           && _maping[pos + 1] != '%' && _maping[pos + 1] != '!';
}


void GamePacman::GhostRightmove(int &pos, char &back, char ghostChar, int &sens) {
    char temp = _maping[pos + 1];
    _maping[pos + 1] = ghostChar;
    _maping[pos] = back;
    pos = pos + 1;
    back = temp;
    sens = 0;
}

void GamePacman::moverightfantom(int i, int _ghost) {
    switch (_ghost) {
        case 1:
            if (canRightMove(posred)) {
                GhostRightmove(posred, backred, 'R', sensred);
                return;
            }
            break;
        case 2:
            if (canRightMove(pospink)) {
                GhostRightmove(pospink, backpink, 'P', senspink);
                return;
            }
            break;
        case 3:
            if (canRightMove(posblue)) {
                GhostRightmove(posblue, backblue, 'B', sensblue);
                return;
            }
            break;
        case 4:
            if (canRightMove(posorange)) {
                GhostRightmove(posorange, bachorange, 'O', sensorange);
                return;
            }
            break;
        default:
            break;
    }
    switch (i) {
        case 1:
            return;
        case 2:
            return moveupfantom(2, _ghost);
        case 3:
            return moveleftfantom(3, _ghost);
        case 4:
            return movedownfantom(4, _ghost);
        default:
            return;
    }
}


bool GamePacman::canDownmove(int pos) {
    return _maping[pos + linelengt] != '#' && _maping[pos + linelengt] != 'O'
           && _maping[pos + linelengt] != 'P' && _maping[pos + linelengt] != 'B'
           && _maping[pos + linelengt] != '!' && _maping[pos + linelengt] != '%';
}

void GamePacman::GhostDownmove(int &pos, char &back, char ghostChar, int &sens) {
    char temp = _maping[pos + linelengt];
    _maping[pos + linelengt] = ghostChar;
    _maping[pos] = back;
    pos = pos + linelengt;
    back = temp;
    sens = 2;
}

void GamePacman::movedownfantom(int i, int _ghost) {
    switch (_ghost) {
        case 1:
            if (canDownmove(posred)) {
                GhostDownmove(posred, backred, 'R', sensred);
                return;
            }
            break;
        case 2:
            if (canDownmove(pospink)) {
                GhostDownmove(pospink, backpink, 'P', senspink);
                return;
            }
            break;
        case 3:
            if (canDownmove(posblue)) {
                GhostDownmove(posblue, backblue, 'B', sensblue);
                return;
            }
            break;
        case 4:
            if (canDownmove(posorange)) {
                GhostDownmove(posorange, bachorange, 'O', sensorange);
                return;
            }
            break;
        default:
            break;
    }
    switch (i) {
        case 1:
            return moverightfantom(1, _ghost);
        case 2:
            return moveleftfantom(2, _ghost);
        case 3:
            return;
        case 4:
            return moveupfantom(4, _ghost);
        default:
            return;
    }
}

bool GamePacman::canLeftmove(int pos) {
    char mapValue = _maping[pos - 1];
    return mapValue != '#' && mapValue != 'O' && mapValue != 'P' 
           && mapValue != 'B' && mapValue != '!' && mapValue != '%';
}

void GamePacman::GhostLeftmove(int& pos, char& back, char ghostSymbol, int& sens) {
    char temp = _maping[pos - 1];
    _maping[pos - 1] = ghostSymbol;
    _maping[pos] = back;
    pos = pos - 1;
    back = temp;
    sens = 3;
}

void GamePacman::moveleftfantom(int i, int _ghost) {
    switch (_ghost) {
        case 1:
            if (canLeftmove(posred)) {
                GhostLeftmove(posred, backred, 'R', sensred);
                return;
            }
            break;
        case 2:
            if (canLeftmove(pospink)) {
                GhostLeftmove(pospink, backpink, 'P', senspink);
                return;
            }
            break;
        case 3:
            if (canLeftmove(posblue)) {
                GhostLeftmove(posblue, backblue, 'B', sensblue);
                return;
            }
            break;
        case 4:
            if (canLeftmove(posorange)) {
                GhostLeftmove(posorange, bachorange, 'O', sensorange);
                return;
            }
            break;
        default:
            break;
    }
    switch (i) {
        case 1:
            return moveupfantom(1, _ghost);
        case 2:
            return moverightfantom(2, _ghost);
        case 3:
            return movedownfantom(3, _ghost);
        case 4:
            return;
        default:
            return;
    }
}


int GamePacman::ghostdetermove(int ghostPos) {
    if ((pacpos / linelengt) <= (ghostPos / linelengt) &&
        (pacpos % linelengt) <= (ghostPos % linelengt)) {
        return _gumesuper == 1 ? 4 : 1;
    }
    if ((pacpos / linelengt) >= (ghostPos / linelengt) &&
        (pacpos % linelengt) <= (ghostPos % linelengt)) {
        return _gumesuper == 1 ? 3 : 2;
    }
    if ((pacpos / linelengt) <= (ghostPos / linelengt) &&
        (pacpos % linelengt) >= (ghostPos % linelengt)) {
        return _gumesuper == 1 ? 2 : 3;
    }
    if ((pacpos / linelengt) >= (ghostPos / linelengt) &&
        (pacpos % linelengt) >= (ghostPos % linelengt)) {
        return _gumesuper == 1 ? 1 : 4;
    }
    return 0;
}

int GamePacman::getRandomDirection() {
    return rand() % 5;
}

void GamePacman::movefantom(int _ghost) {
    int direction = 0;
    switch (_ghost) {
        case 1:
            direction = ghostdetermove(posred);
            break;
        case 2:
            direction = ghostdetermove(pospink);
            break;
        case 3:
            direction = ghostdetermove(posblue);
            break;
        case 4:
            direction = ghostdetermove(posorange);
            break;
        default:
            break;
    }
    
    if (direction == 0) return;

    int newDirection = direction;
    int attempts = 0;
    while (!canMove(newDirection, _ghost) && attempts < 10) {
        newDirection = getRandomDirection();
        attempts++;
    }

    if(newDirection == 0) return;

    switch (newDirection) {
        case 1:
            moveleftfantom(newDirection, _ghost);
            break;
        case 2:
            movedownfantom(newDirection, _ghost);
            break;
        case 3:
            moveupfantom(newDirection, _ghost);
            break;
        case 4:
            moverightfantom(newDirection, _ghost);
            break;
        default:
            break;
    }
}

bool GamePacman::canMove(int direction, int ghost) {
    if (direction == 0) return true;

    int pos;
    switch (ghost) {
        case 1:
            pos = posred;
            break;
        case 2:
            pos = pospink;
            break;
        case 3:
            pos = posblue;
            break;
        case 4:
            pos = posorange;
            break;
        default:
            return false;
    }
    switch (direction) {
        case 1:
            return canLeftmove(pos);
        case 2:
            return canDownmove(pos);
        case 3:
            return canupmove(pos);
        case 4:
            return canRightMove(pos);
        default:
            return false;
    }
}





void GamePacman::ghostselect() {
    std::vector<bool> ghost_states = {deadred == 0, deadpink == 0, deadblue == 0, deadorange == 0};

    for(int i = 0; i < nombrespawnghost; ++i) {
        if(ghost_states[i]) {
            movefantom(i + 1);
        }
    }
}