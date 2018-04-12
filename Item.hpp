#ifndef ITEM_HPP_
#define ITEM_HPP_
#include <string>

class Item {
    public:
        virtual ~Item() = 0;
        virtual std::string get_description() const = 0;
        virtual void display() const = 0;
};

#endif
