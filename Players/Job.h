
#pragma once
#include <string>
using  std::string;
class Player;


class Job {
public:
    virtual string getJob() const = 0;
    virtual int initialsMaxHp() const;
    virtual int initialsCoins() const;
    virtual int combatPower(const Player& player)const;
    virtual int solarEclipse(const Player& player)const;
    virtual int loseHp()const;

    virtual ~Job() = default;
};

class Magician : public Job {
public:
    string getJob() const override;
    int solarEclipse(const Player& player) const override;
};

class  Archer : public Job {
public:
    string getJob() const override;
    int initialsCoins() const override;
};

class Warrior : public Job {
public:
    string getJob() const override;
    int initialsMaxHp() const override;
    int loseHp() const override;
    int combatPower(const Player& player) const override;
};
