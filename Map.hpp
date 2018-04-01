#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>

class Tile;
class Room;
class Money;

class Map {
    public:

        enum Direction {
            NORTH,
            SOUTH,
            EAST,
            WEST
        };

        Map(int width, int height);
        ~Map();

        void fill_map(int num_rooms);
        int get_width() const;
        int get_height() const;

        Tile *get_tile(int x, int y) const;

        void display_map();
        void place_character(int *x, int *y);

    private:

        bool fill_rect(int start_x, int start_y, int w, int h);
        void connect_rooms();
        int get_num_neighbors(Tile *tile);
        void add_earth();
        void add_stairs();
        void add_money();

        Tile ***tiles;
        int width, height;
        std::vector<Room> rooms;
};

#endif