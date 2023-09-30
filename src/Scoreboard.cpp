/*
** EPITECH PROJECT, 2023
** core
** File description:
** core
*/

#include "../include/Core.hpp"

classement::classement() {}

classement::~classement() {
    this->_valfil.open("Object/Score.csv");

    auto scoreIterator = _val.begin();
    while (scoreIterator != _val.end()) {
        this->_valfil << scoreIterator->nameget() + "," + scoreIterator->scoreget() + "\n";
        ++scoreIterator;
    }

    this->_valfil.close();
}


void classement::scoradd(ValueScore score) { this->_val.push_back(score); }


bool CompareScore(const ValueScore &leftScore, const ValueScore &rightScore)
{
    return std::stoi(leftScore.scoreget()) < std::stoi(rightScore.scoreget());
}

void classement::scoread(std::ifstream& file) {
    std::string line;
    for (; std::getline(file, line); ) {
        scoradd(line);
    }
}

void classement::scoradd(const std::string& line) {
    std::string name = line.substr(0, line.find(','));
    std::string score = line.substr(line.find(',') + 1);
    _val.push_back(ValueScore(name, score));
}

void classement::openclassement() {
    std::ifstream file("Object/Score.csv");

    if (!file) {
        std::cerr << "Failed to open score file." << std::endl;
        return;
    }

    scoread(file);
    std::sort(_val.rbegin(), _val.rend(), CompareScore);

    file.close();
}


void classement::loadr() {
    if (_val.empty()) {
        std::cout << "No scores to sort." << std::endl;
        return;
    }
    std::sort(this->_val.rbegin(), this->_val.rend(), CompareScore);
}


std::vector<ValueScore> classement::scoreget() const {
    return this->_val;
}
