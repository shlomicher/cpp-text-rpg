
#include "Job.h"
#include "Player.h"
/** job methods  **/

int Job::initialsCoins() const {
    return 10;
}

int Job::initialsMaxHp() const {
    return 100;
}

int Job::combatPower(const Player &player) const {
    return player.getForce() + player.getLevel();
}

int Job::solarEclipse(const Player &player) const {
    return -1;
}

int Job::loseHp() const {
    return 0;
}

/** magician methods **/
string Magician::getJob() const {
    return "Magician";
}

int Magician::solarEclipse(const Player &player) const {
    return 1;
}

/** warrior methods **/

string Warrior::getJob() const {
    return "Warrior";
}


int Warrior::initialsMaxHp() const {
    return 150;
}

int Warrior::loseHp() const {
    return 10;
}

int Warrior::combatPower(const Player &player) const {
    return 2*player.getForce() + player.getLevel();
}

/** archer methods **/

string Archer::getJob() const {
    return "Archer";
}

int Archer::initialsCoins() const {
    return 20;
}

