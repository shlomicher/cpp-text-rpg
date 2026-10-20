
#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Monster.h"
#include "Players/Player.h"
#include "Events/Event.h"
#include "Utilities.h"
#include <algorithm>


class MatamStory{
private:
    unsigned int m_turnIndex;
    std::vector<Player> m_players;
    std::vector<std::unique_ptr<Event>> m_events;
    std::size_t m_currentEvent = 0;

    static std::vector<std::unique_ptr<Event>> receiveEvents(std::istream& eventsStream);
    static std::vector<Player> receivePlayers(std::istream& playersStream);
    static void isNameValid(const std::string& name);

    /**
     * Plays a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    //
    std::vector<std::size_t> makeLeaderBoard() const;
};
