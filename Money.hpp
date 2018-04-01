#ifndef MONEY_HPP_
#define MONEY_HPP_
#include "Item.hpp"

class Money : public Item {
    public:

        enum Denomination {
            COPPER,
            SILVER,
            GOLD
        };
        
        static const int COPPER_VALUE;
        static const int SILVER_VALUE;
        static const int GOLD_VALUE;

        static const double COPPER_WEIGHT;
        static const double SILVER_WEIGHT;
        static const double GOLD_WEIGHT;

        Money(int pos_x, int pos_y);
        Money(Denomination denomination, int num_coins, int pos_x, int pos_y);
        ~Money() = default;

        double get_weight() const;
        int get_value() const;
        Denomination get_denomination() const;

        int get_x() const;
        int get_y() const;

        void set_x(int pos_x);
        void set_y(int pos_y);

        virtual std::string get_description() const override;
        virtual void display() const override;

    private:

        int num_coins;
        Denomination denomination;
        char sprite;
        int pos_x, pos_y;

    
};
#endif