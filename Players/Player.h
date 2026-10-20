
#pragma once

#include <memory>
#include <string>
#include "Character.h"
#include "Job.h"

class Character;


using std::string;
using std::unique_ptr;

class Player {
private:
    string name;
    unique_ptr<Character> character;
    unique_ptr<Job> job;
    int level;
    int coins;
    int currentHP;
    int force;

    static unique_ptr<Job> initializeJob(const string& jobName);
    static unique_ptr<Character> initializeCharacter(const string& characterName);
public:

    Player(const string& name, const string& character, const string& job);





    int getCombatPower() const;

    string getDescription() const;


    string getName() const;

    int getLevel() const;

    int getForce() const;

    int getHealthPoints() const;

    int getCoins() const;

    int getMaxHp() const;


    bool knockedOut() const;


    /* note: Won does not check if the player won, it checks if the player is level 10,
    this means that the rounds are over and the player can win, but it is possible that another player will
    have more coins, so that player will win instead. */
    bool Won() const;

    const Character& getCharacter() const;


    bool buyPotion();

    const Job& getJob() const;

    int changeForce(int forceToChange);

    void addCoins(int coinsAmount);

    void reduceHP(int reduceHPby);

    void levelUp();

    void endRoundWin();
};


