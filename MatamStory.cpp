#include "MatamStory.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    // Validate and load the events before loading the players.
    m_events = receiveEvents(eventsStream);
    m_players = receivePlayers(playersStream);
    m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {
    Event& event = *m_events.at(m_currentEvent % m_events.size());
    printTurnDetails(m_turnIndex, player, event);
    printTurnOutcome(event.apply(player));
    ++m_currentEvent;
    ++m_turnIndex;
}

void MatamStory::playRound() {
    printRoundStart();
    for (Player& player : m_players) {
        if (!player.knockedOut()) {
            playTurn(player);
        }
    }
    printRoundEnd();
    printLeaderBoardMessage();

    const auto ranking = makeLeaderBoard();
    unsigned int position = 1;
    for (const std::size_t index : ranking) {
        printLeaderBoardEntry(position++, m_players[index]);
    }
    printBarrier();
}

bool MatamStory::isGameOver() const {
    bool everyoneKnockedOut = true;
    for (const Player& player : m_players) {
        if (player.Won()) {
            return true;
        }
        if (!player.knockedOut()) {
            everyoneKnockedOut = false;
        }
    }
    return everyoneKnockedOut;
}

void MatamStory::play() {
    printStartMessage();
    for (std::size_t index = 0; index < m_players.size(); ++index) {
        printStartPlayerEntry(static_cast<unsigned int>(index + 1), m_players[index]);
    }
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    const bool levelCapReached = std::any_of(
        m_players.begin(), m_players.end(),
        [](const Player& player) { return player.Won(); });
    if (levelCapReached) {
        printWinner(m_players[makeLeaderBoard().front()]);
    } else {
        printNoWinners();
    }
}

std::vector<std::size_t> MatamStory::makeLeaderBoard() const {
    std::vector<std::size_t> ranking;
    ranking.reserve(m_players.size());
    for (std::size_t index = 0; index < m_players.size(); ++index) {
        ranking.push_back(index);
    }

    std::sort(ranking.begin(), ranking.end(),
              [this](std::size_t left, std::size_t right) {
                  const Player& a = m_players[left];
                  const Player& b = m_players[right];
                  if (a.getLevel() != b.getLevel()) {
                      return a.getLevel() > b.getLevel();
                  }
                  if (a.getCoins() != b.getCoins()) {
                      return a.getCoins() > b.getCoins();
                  }
                  return a.getName() < b.getName();
              });
    return ranking;
}

std::vector<std::unique_ptr<Event>> MatamStory::receiveEvents(
    std::istream& eventsStream) {
    std::vector<std::unique_ptr<Event>> events;
    std::string type;

    while (eventsStream >> type) {
        if (type == "PotionsMerchant") {
            events.push_back(std::make_unique<PotionsMerchant>());
            continue;
        }
        if (type == "SolarEclipse") {
            events.push_back(std::make_unique<SolarEclipse>());
            continue;
        }

        std::unique_ptr<Monster> monster;
        if (type == "Pack") {
            monster = std::make_unique<Pack>(eventsStream);
        } else if (type == "Snail") {
            monster = std::make_unique<Snail>();
        } else if (type == "Slime") {
            monster = std::make_unique<Slime>();
        } else if (type == "Balrog") {
            monster = std::make_unique<Balrog>();
        } else {
            throw std::runtime_error("Invalid Events File");
        }
        events.push_back(std::make_unique<Encounter>(std::move(monster)));
    }

    // Count actual events, not individual tokens inside a nested Pack.
    if (events.size() < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    return events;
}

void MatamStory::isNameValid(const std::string& name) {
    if (name.size() < 3 || name.size() > 15) {
        throw std::runtime_error("Invalid Players File");
    }
    for (const char character : name) {
        const bool upper = character >= 'A' && character <= 'Z';
        const bool lower = character >= 'a' && character <= 'z';
        if (!upper && !lower) {
            throw std::runtime_error("Invalid Players File");
        }
    }
}

std::vector<Player> MatamStory::receivePlayers(std::istream& playersStream) {
    std::vector<Player> players;
    std::string name;
    std::string job;
    std::string character;

    while (playersStream >> name) {
        if (!(playersStream >> job >> character)) {
            throw std::runtime_error("Invalid Players File");
        }
        isNameValid(name);
        players.emplace_back(name, character, job);
        if (players.size() > 6) {
            throw std::runtime_error("Invalid Players File");
        }
    }

    if (players.size() < 2) {
        throw std::runtime_error("Invalid Players File");
    }
    return players;
}
