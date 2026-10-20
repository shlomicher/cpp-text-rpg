
#pragma once

#include "../Players/Player.h"
#include "Monster.h"

class Event {
public:
    virtual string apply(Player& player) const = 0;
    virtual string getDescription() const = 0;
    virtual ~Event() = default;
};



class SpecialEvent : public Event {
public:
    virtual ~SpecialEvent() = default;
};


class PotionsMerchant : public SpecialEvent {
public:
    string apply(Player& player) const override;
    string getDescription() const override;
};

class SolarEclipse : public SpecialEvent {
public:
    string apply(Player& player) const override;
    string getDescription() const override;
};



class Encounter : public Event {
    std::unique_ptr<Monster> m_monster;

public:
    explicit Encounter(std::unique_ptr<Monster> monster);
    string apply(Player& player) const override;
    string getDescription() const override;
};