
#pragma once
#include "Player.h"

using std::string;

class  Player;

class Character {
public:
    virtual string getCharacter() const = 0;

    virtual int potionsAmount(const Player& player) const = 0;

    virtual ~Character() = default;
};

class Responsible : public Character {
public:
    string getCharacter() const override;
    int potionsAmount(const Player &player) const override;
};

class RiskTaking : public  Character {
    string getCharacter() const override;
    int potionsAmount(const Player &player) const override;
};























