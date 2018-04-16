#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_
#include "Map.hpp"
#include "IRenderable.hpp"

class Item;

class Character: public IRenderable {
    public:

        enum CharacterClass {
            FOOTMAN,
            ARCHER,
            WIZARD
        };

        Character(CharacterClass cclass, int pos_x, int pos_y);
        int get_x();
        int get_y();

        void move(Map::Direction dir, const Map& map);

        char get_sprite();
        virtual void render() const override;
        void display_stats(int screen_height);
    
    private:

        void move_east();
        void move_west();
        void move_south();
        void move_north();
        void inspect(Item *i);

        int pos_x, pos_y;
        char sprite;
        CharacterClass cclass;
        int hp;
        int max_hp;
        int attack;
        int level;
        double exp;
};

#endif