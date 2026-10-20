#include "Player.h"
#include "Character.h"
#include "Job.h"

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::runtime_error;
using std::stringstream;


unique_ptr<Job> Player::initializeJob(const string& jobName) {
    if (jobName == "Magician") return std::make_unique<Magician>();
    if (jobName == "Archer") return std::make_unique<Archer>();
    if (jobName == "Warrior") return std::make_unique<Warrior>();

    throw runtime_error("Invalid Players File");
}

unique_ptr<Character> Player::initializeCharacter(const string& characterType) {
    if (characterType == "Responsible") return std::make_unique<Responsible>();
    if (characterType == "RiskTaking") return std::make_unique<RiskTaking>();

    throw runtime_error("Invalid Players File");
}



Player::Player(const string& name, const string& characterType, const string& jobName):
name(name),
character(initializeCharacter(characterType)),
job(initializeJob(jobName)),
level(1),
coins(job -> initialsCoins()),
currentHP(job -> initialsMaxHp()),
force(5){
}




int Player::getCombatPower() const {
    return this -> job -> combatPower(*this);
}



string Player::getDescription() const {
    string jobName = this -> job -> getJob();
    string characterType = this -> character -> getCharacter();
    stringstream description;
    description << name << ", " << jobName << " with " << characterType << " character (level " << this -> level << ", force " << this -> force << ")";
    return description.str();
}




string Player::getName() const {
    return name;
}

int Player::getLevel() const {
    return level;
}

int Player::getForce() const {
    return force;
}

int Player::getHealthPoints() const {
    return currentHP;
}

int Player::getCoins() const {
    return coins;
}

int Player::getMaxHp() const {
    return this -> job -> initialsMaxHp();
}





bool Player::knockedOut() const {
    return currentHP <= 0;
}

bool Player::Won() const {
    return level == 10;
}

const Character& Player::getCharacter() const {
    return *character;
}

bool Player::buyPotion() {
    if (coins >= 5 && currentHP < this->getMaxHp()) {
        coins -=5;
        currentHP += 10;
        if (currentHP > getMaxHp()) {
            currentHP = getMaxHp();
        }
        return true;
    }
    return false;
}

const Job &Player::getJob() const {
    return *job;
}

int Player::changeForce(int forceToChange) {
    if (force + forceToChange < 0) {
        forceToChange = -force;
        force = 0;
        return forceToChange;
    }
    force += forceToChange;
    return forceToChange;
}



void Player::levelUp() {
    if (level == 10) {
        return;
    }
    this -> level += 1;
}

void Player::addCoins(int coinsAmount) {
    this -> coins += coinsAmount;
}

void Player::reduceHP(int reduceHPby) {
    if (currentHP - reduceHPby < 0) {
        currentHP = 0;
        return;
    }
    this -> currentHP -= reduceHPby;
}



void Player::endRoundWin() {
    int loseHP = this -> job -> loseHp();
    if (loseHP > this -> currentHP) {loseHP = this -> currentHP;}
    currentHP -= loseHP;
}






