
#include "Character.h"
#include "Player.h"

int Responsible::potionsAmount(const Player &player) const {
    if (player.getMaxHp() - player.getHealthPoints() <= 0) {
        return 0;
    }
    return  (player.getMaxHp() - player.getHealthPoints() + 9)/10;
}

int RiskTaking::potionsAmount(const Player &player) const {
    int currentHp = player.getHealthPoints();
        if (currentHp < 50 &&  currentHp< player.getMaxHp()) {
            return 1;
        }
    return 0;
}

string  RiskTaking::getCharacter() const {
    return "RiskTaking";
}

string Responsible::getCharacter() const {
    return "Responsible";
}
