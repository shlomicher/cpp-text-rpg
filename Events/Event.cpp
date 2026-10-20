
#include "Event.h"

#include "Utilities.h"


string PotionsMerchant::apply(Player &player) const {
    int needed = player.getCharacter().potionsAmount(player);
    unsigned int amount = 0;
    for (int i = 0; i < needed; i++) {
        if (!player.buyPotion()) {
            break;
        }
        amount++;
    }
    return getPotionsPurchaseMessage(player, amount);
}
string PotionsMerchant::getDescription() const {
    return "PotionsMerchant";
}


string SolarEclipse::apply(Player &player) const {
    int forceToChange = player.getJob().solarEclipse(player);
    int effect = player.changeForce(forceToChange);
    return getSolarEclipseMessage(player, effect);
}

string SolarEclipse::getDescription() const {
    return "SolarEclipse";
}




string Encounter::apply(Player &player) const {
    string returnMessage;
    if (player.getCombatPower() > this -> m_monster -> getPower()) {
        player.addCoins(this -> m_monster -> getLoot());
        player.levelUp();

        player.endRoundWin();

        returnMessage = getEncounterWonMessage(player, this -> m_monster -> getLoot());
    }else {
        player.reduceHP(this -> m_monster -> getDamage());

        returnMessage = getEncounterLostMessage(player, this -> m_monster -> getDamage());
    }

    this -> m_monster->EndRound();

    return returnMessage;
}

string Encounter::getDescription() const {
    return this -> m_monster -> getDescription();
}

Encounter::Encounter(std::unique_ptr<Monster> monster)
    : m_monster(std::move(monster)){};


