#ifndef TILE_HPP_
#define TILE_HPP_

class Tile {
    public:
        enum TileType {
            EARTH,
            FLOOR,
            WALL,
            DOWN_STAIRS,
            UP_STAIRS
        };

        Tile(TileType type, int pos_x, int pos_y);
        ~Tile() = default;

        int get_x();
        int get_y();
        TileType get_type();

        void set_type(TileType new_type);
        void display_tile();

    private:

        int pos_x;
        int pos_y;
        TileType type;
};
#endif