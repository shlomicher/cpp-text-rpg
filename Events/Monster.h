
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <memory>

using std::string;
using std::vector;
using std::stringstream;
using std::istream;
using std::unique_ptr;

class Monster {
protected:
    string name;
    int power;
    int loot;
    int damage;

public:

    explicit Monster(const string& name, const int& power, const int& loot, const int& damage);

    virtual ~Monster() = default;

    virtual void EndRound();

    virtual string getDescription() const;

    string getName() const;
    int getPower() const;
    int getLoot() const;
    int getDamage() const;
};

class Snail : public Monster {
public:
    Snail();
};

class Slime : public Monster {
public:
    Slime();
};

class Balrog : public Monster {
public:
    Balrog();

    void EndRound() override;
};

class Pack : public Monster {
private:
    int monsterNumber;
    vector<unique_ptr<Monster>> monsters;

    static unique_ptr<Monster> InitializeMonster(istream& monsterName);
    void updateStats();

public:
    explicit Pack(istream& input);


    string getDescription() const override;

    void EndRound() override;
};
