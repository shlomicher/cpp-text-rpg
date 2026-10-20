#include <exception>
#include <fstream>
#include <iostream>

#include "MatamStory.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: MatamStory <events_file_path> <players_file_path>\n";
        return 1;
    }

    std::ifstream events(argv[1]);
    if (!events) {
        std::cerr << "Invalid Events File\n";
        return 1;
    }

    std::ifstream players(argv[2]);
    if (!players) {
        std::cerr << "Invalid Players File\n";
        return 1;
    }

    try {
        MatamStory game(events, players);
        game.play();
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
