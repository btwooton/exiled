#ifndef TILE_HPP_
#define TILE_HPP_
#include <vector>

class Item;

class Tile {
    public:
        enum TileType {
            EARTH,
            FLOOR,
            WALL,
            DOWN_STAIRS,
            UP_STAIRS
        };

        static short TILE_COLOR_INDEX;

        Tile(TileType type, int pos_x, int pos_y);
        ~Tile();

        int get_x() const;
        int get_y() const;
        TileType get_type() const;

        void set_type(TileType new_type);
        void display_tile() const;

        bool has_item() const;
        void add_item(Item *i);
        Item *get_item() const;

    private:

        int pos_x;
        int pos_y;
        TileType type;
        std::vector<Item*> items;
};
#endif