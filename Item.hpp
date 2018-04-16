#ifndef ITEM_HPP_
#define ITEM_HPP_
#include <string>
#include "Money.hpp"
#include "IRenderable.hpp"

class Money;

class Item : public IRenderable {
    public:
        enum ItemType {
            MONEY
        };

        union {
            Money money;
        };

        Item(Money other);
        Item(const Item& other);

        ~Item();

        template <typename T>
        T& get();

        ItemType get_type() const;
        
        virtual void render() const override;

        std::string get_description() const;
    private:
        ItemType type;
};

template<> Money& Item::get<Money>();

#endif
