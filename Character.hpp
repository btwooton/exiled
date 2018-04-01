#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_
#include "Map.hpp"

class Character {
    public:

        enum CharacterClass {
            FOOTMAN,
            ARCHER,
            WIZARD
        };

        Character(CharacterClass cclass, int pos_x, int pos_y);
        ~Character() = default;

        int get_x();
        int get_y();

        void move(Map::Direction dir, const Map& map);

        char get_sprite();
        void display();
        void display_stats(int screen_height);
    
    private:

        void move_east();
        void move_west();
        void move_south();
        void move_north();

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