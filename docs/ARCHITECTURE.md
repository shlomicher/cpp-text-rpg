# Architecture

MatamStory is a small **console game**, structured around composition and
polymorphic behavior rather than a graphical engine.

```mermaid
classDiagram
    class MatamStory {
      -players
      -events
      +play()
    }
    class Player {
      -job
      -character
      +getCombatPower()
    }
    class Job
    class Warrior
    class Archer
    class Magician
    class Character
    class Responsible
    class RiskTaking
    class Event
    class Encounter
    class PotionsMerchant
    class SolarEclipse
    class Monster
    class Snail
    class Slime
    class Balrog
    class Pack

    MatamStory "1" o-- "*" Player
    MatamStory "1" o-- "*" Event
    Player "1" *-- "1" Job
    Player "1" *-- "1" Character
    Job <|-- Warrior
    Job <|-- Archer
    Job <|-- Magician
    Character <|-- Responsible
    Character <|-- RiskTaking
    Event <|-- Encounter
    Event <|-- PotionsMerchant
    Event <|-- SolarEclipse
    Encounter "1" *-- "1" Monster
    Monster <|-- Snail
    Monster <|-- Slime
    Monster <|-- Balrog
    Monster <|-- Pack
    Pack "1" *-- "*" Monster
```

## Responsibilities

- **Game loop** (`MatamStory`): parse input, advance turns, cycle through
  events, finish the game, sort and print the leaderboard.
- **Player**: mutable health, force, coins and level; owns a job and a
  character strategy.
- **Jobs** (`Warrior`, `Archer`, `Magician`): adjust initial player
  attributes, combat strength, and reactions to special events.
- **Characters** (`Responsible`, `RiskTaking`): change potion-buying
  decisions independently of a player's job.
- **Events**: provide a common interface for monster encounters and
  special events.
- **Monster packs**: recursively contain other monsters, including nested
  packs; their aggregate statistics change as members evolve.

Polymorphic objects are held by `std::unique_ptr`, which expresses ownership
and avoids manual `delete` calls.

## Scope

This is a coursework-scale model of a turn-based game. It deliberately has
no rendering loop, graphical UI, network play or save system.
