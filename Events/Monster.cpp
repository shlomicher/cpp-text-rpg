#include "Monster.h"

using std::runtime_error;
using std::make_unique;
using std::string;
using std::stringstream;

Monster::Monster(const string& name, const int& power, const int& loot, const int& damage) : name(name), power(power), loot(loot), damage(damage) {}

Snail::Snail() : Monster("Snail", 5, 2, 10) {}

Slime::Slime() : Monster("Slime", 12, 5, 25) {}

Balrog::Balrog() : Monster("Balrog", 15, 100, 9001) {}


Pack::Pack(istream& input) : Monster("Pack", 0, 0, 0), monsterNumber(0) {
    if (!(input >> this -> monsterNumber) || monsterNumber < 2) {
        throw runtime_error("Invalid Events File");
    }
    for (int i = 0; i < this -> monsterNumber; i++) {
        monsters.push_back(InitializeMonster(input));
    }
    this -> updateStats();
}


unique_ptr<Monster> Pack::InitializeMonster(istream& input) {
    string monsterName;
    input >> monsterName;
    if (monsterName == "Snail") {
        return make_unique<Snail>();
    }
    if (monsterName == "Slime") {
        return make_unique<Slime>();
    }
    if (monsterName == "Balrog") {
        return make_unique<Balrog>();
    }
    if (monsterName == "Pack") {
        return make_unique<Pack>(input);
    }

    throw runtime_error("Invalid Events File");
}



void Pack::updateStats() {
    this -> power = 0;
    this -> loot = 0;
    this -> damage = 0;
    for (const auto& monster : monsters) {
        this -> power += monster->getPower();
        this -> loot += monster->getLoot();
        this -> damage += monster->getDamage();
    }
}





string Monster::getDescription() const {
    stringstream description;
    description << this -> name << " (power " << this -> power << ", loot " << this -> loot << ", damage " << this -> damage << ")";
    return description.str();
}

string Pack::getDescription() const {
    stringstream description;
    description << "Pack of " << this -> monsterNumber << " members (power " << this -> power << ", loot " << this -> loot << ", damage " << this -> damage << ")";
    return description.str();
}




string Monster::getName() const {
    return this -> name;
}

int Monster::getPower() const {
    return this -> power;
}
int Monster::getLoot() const {
    return this -> loot;
}
int Monster::getDamage() const {
    return this -> damage;
}


void Monster::EndRound() {}

void Balrog::EndRound() {
    this -> power += 2;
}

void Pack::EndRound() {
    for (auto& monster : monsters) {
        monster -> EndRound();
    }
    this -> updateStats();
}


