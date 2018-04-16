#include "Item.hpp"
#include <stdexcept>

Item::Item(Money other) {
    new (&money) Money(other);
    this->type = Item::ItemType::MONEY;
}

Item::Item(const Item& other) {
    switch(other.get_type()) {
        case Item::ItemType::MONEY:
            new (&money) Money(other.money);
            break;
    }
    this->type = other.type;
}

template<> Money& Item::get<Money>() {
    if (this->type != Item::ItemType::MONEY) {
        throw std::runtime_error("Unable to get Money from Item");
    }
    return money;
}

Item::ItemType Item::get_type() const {
    return this->type;
}

Item::~Item() {
    switch(this->type) {
        case Item::ItemType::MONEY:
            money.~Money();
            break;
    }
}

void Item::render() const {
    switch(this->type) {
        case Item::ItemType::MONEY:
            money.display();
            break;
    }
}

std::string Item::get_description() const {
    switch(this->type) {
        case Item::ItemType::MONEY:
            return money.get_description();
            break;
    }

    return std::string("");
}
