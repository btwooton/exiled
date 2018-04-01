#include "Money.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <string>

const int Money::COPPER_VALUE = 1;
const int Money::SILVER_VALUE = 5;
const int Money::GOLD_VALUE = 10;

const double Money::COPPER_WEIGHT = 0.1;
const double Money::SILVER_WEIGHT = 0.5;
const double Money::GOLD_WEIGHT = 0.8;

Money::Money(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;

    this->denomination = Denomination(rand() % 3);
    
    switch(denomination) {
        case Denomination::COPPER:
            this->num_coins = rand() % 50 + 1;
            break;
        case Denomination::SILVER:
            this->num_coins = rand() % 80 + 1;
            break;
        case Denomination::GOLD:
            this->num_coins = rand() % 10 + 1;
            break;
    }

    this->sprite = '$';
}

Money::Money(Denomination denomination, int num_coins, int pos_x, int pos_y) {
    this->denomination = denomination;
    this->num_coins = num_coins;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->sprite = '$';
}

double Money::get_weight() const {
    double weight;
    switch(denomination) {
        case Denomination::COPPER:
            weight = Money::COPPER_WEIGHT;
            break;
        case Denomination::SILVER:
            weight = Money::SILVER_WEIGHT;
            break;
        case Denomination::GOLD:
            weight = Money::GOLD_WEIGHT;
            break;
    }
    return weight * num_coins;
}

int Money::get_value() const {
    int value;
    switch(denomination) {
        case Denomination::COPPER:
            value = Money::COPPER_VALUE;
            break;
        case Denomination::SILVER:
            value = Money::SILVER_VALUE;
            break;
        case Denomination::GOLD:
            value = Money::GOLD_VALUE;
            break;
    }
    return value * num_coins;
}
Money::Denomination Money::get_denomination() const {
    return this->denomination;
}

int Money::get_x() const {
    return this->pos_x;
}

int Money::get_y() const {
    return this->pos_y;
}

void Money::set_x(int pos_x) {
    this->pos_x = pos_x;
}

void Money::set_y(int pos_y) {
    this->pos_y = pos_y;
}

void Money::display() const {
    attron(COLOR_PAIR(denomination));
    mvaddch(this->pos_y, this->pos_x, this->sprite);
    attroff(COLOR_PAIR(denomination));
}

std::string Money::get_description() const {
    std::ostringstream result;
    result << num_coins;
    switch(denomination) {
        case Money::Denomination::COPPER:
            result << " copper coins";
            break;
        case Money::Denomination::SILVER:
            result << " silver coins";
            break;
        case Money::Denomination::GOLD:
            result << " gold coins";
            break;
    }
    result << " of value " << this->get_value();
    return result.str();
}