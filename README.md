# MatamStory

A turn-based text RPG written in C++17 for a Technion programming assignment.

The game is played by 2-6 players. Each player chooses a job (Warrior, Archer or Magician) and a character type (Responsible or RiskTaking). Players take turns facing monsters and other events. A leaderboard is printed after every round, and the game ends when someone reaches level 10 or all players are knocked out.

## Build and run

Requires a C++17 compiler and CMake 3.16 or newer.

```bash
cmake -S . -B build
cmake --build build
./build/MatamStory tests/test1.events tests/test1.players
```

The program reads two files: an events file, followed by a players file. You can edit the files in `tests/` to try different games.

## Code

- `MatamStory.cpp`: loads the input, runs the turns and prints the leaderboard.
- `Players/`: player stats, jobs and character types.
- `Events/`: monsters, encounters and special events.
- `Utilities.cpp/.h`: output functions provided by the course staff.

Monster packs can contain other packs. The different jobs, character types and events are implemented using inheritance and polymorphism.

There's a class diagram in [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Tests

Three sample cases are included (one game and two invalid-input cases). After building, run:

```bash
ctest --test-dir build --output-on-failure
```

These are sample tests, not an exhaustive test suite. They also run in GitHub Actions.

## About

This started as Homework 4 in Introduction to Systems Programming (234124) at the Technion. I worked on it with Ofri Hacohen. The course staff supplied the assignment and some starter files. The game code was written as a pair assignment; the build, test setup and documentation were updated for this repository.
