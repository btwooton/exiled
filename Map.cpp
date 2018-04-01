#include "Map.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include <cstdlib>
#include <climits>

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;

    tiles = new Tile** [height];
    for (int i = 0; i < height; i++) {
        tiles[i] = new Tile* [width];
        for (int j = 0; j < width; j++) {
            tiles[i][j] = new Tile(Tile::TileType::WALL, j, i);
        }
    }
}

Map::~Map() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            delete tiles[i][j];
        }
        delete tiles[i];
    }
    delete tiles;
}

int Map::get_height() const {
    return height;
}

int Map::get_width() const {
    return width;
}

Tile *Map::get_tile(int x, int y) const {
    return tiles[y][x];
}

void Map::fill_map(int num_rooms) {

    int room_max_width = width / (num_rooms / 2);
    int room_max_height = height / (num_rooms / 2);

    int rooms_added = 0;

    while (rooms_added < num_rooms) {
        int room_width = rand() % room_max_width + 5;
        int room_height = rand() % room_max_height + 5;
        int room_x = rand() % width;
        int room_y = rand() % height;

        if (this->fill_rect(room_x, room_y, room_width, room_height)) {
            rooms_added++;
            this->rooms.push_back(Room(room_x, room_y, 
                                       room_x + room_width, room_y + room_height));
        }   
    }

    this->connect_rooms();
    this->add_earth();
    this->add_stairs();

}

bool Map::fill_rect(int start_x, int start_y, int w, int h) {

    // First make sure that we can place the room

    if (start_x + 1 + w >= width || start_y + 1 + h >= height ||
        start_x - 1 < 0 || start_y - 1 < 0) {
        return false;
    }
    for (int i = start_y - 1; i <= start_y + h + 1; i++) {
        for (int j = start_x - 1; j <= start_x + w + 1; j++) {
            if (tiles[i][j]->get_type() != Tile::TileType::WALL) {
                return false;
            }
        }
    }

    // Now we are safe to place the room

    for (int i = start_y; i <= start_y + h; i++) {
        for (int j = start_x; j <= start_x + w; j++) {
            if (i == start_y || i == start_y + h ||
                j == start_x || j == start_x + w) {
                    tiles[i][j]->set_type(Tile::TileType::FLOOR);
            }
            else {
                tiles[i][j]->set_type(Tile::TileType::FLOOR);
            }
        }
    }

    return true;
}

void Map::connect_rooms() {
    for (int i = 0; i < this->rooms.size() - 1; i++) {
        Room r1 = rooms[i];
        Room r2 = rooms[i + 1];
        int current_x = r1.get_x_center();
        int current_y = r1.get_y_center();
        int dest_x = r2.get_x_center();
        int dest_y = r2.get_y_center();

        int dx = 0;
        int dy = 0;

        if (current_x < dest_x) {
            dx = 1;
        }
        else if (current_x > dest_x) {
            dx = -1;
        }
        if (current_y < dest_y) {
            dy = 1;
        }
        else if (current_y > dest_y) {
            dy = -1;
        }
        
        while (current_x != dest_x) {
            Tile *current = this->get_tile(current_x, current_y);
            current->set_type(Tile::TileType::FLOOR);
            current_x += dx;
        }

        while (current_y != dest_y) {
            Tile *current = this->get_tile(current_x, current_y);
            current->set_type(Tile::TileType::FLOOR);
            current_y += dy;
        }


    }
}

void Map::display_map() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            tiles[i][j]->display_tile();
        }
    }
}

void Map::place_character(int *x, int *y) {
    int room_index = rand() % rooms.size();
    *x = rooms[room_index].get_x_center();
    *y = rooms[room_index].get_y_center();

}

int Map::get_num_neighbors(Tile *tile) {
    int tile_x = tile->get_x();
    int tile_y = tile->get_y();

    int start_x = tile_x > 0 ? tile_x - 1 : tile_x;
    int end_x = tile_x < width - 1 ? tile_x + 1 : tile_x;
    int start_y = tile_y > 0 ? tile_y - 1 : tile_y;
    int end_y = tile_y < height - 1 ? tile_y + 1 : tile_y;

    int num_neighbors = 0;

    for (int i = start_y; i <= end_y; i++) {
        for (int j = start_x; j <= end_x; j++) {
            if (i != tile_y || j != tile_x) {
                if (tiles[i][j]->get_type() != Tile::TileType::FLOOR) {
                    num_neighbors++;
                }
            }
        }
    }
    return num_neighbors;
}

void Map::add_earth() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Tile *current = get_tile(j, i);
            int neighbors = get_num_neighbors(current);
            if (neighbors == 8 && current->get_type() == Tile::TileType::WALL) {
                current->set_type(Tile::TileType::EARTH);
            }
        }
    }
}

void Map::add_stairs() {
    int random_index= rand() % rooms.size();
    Room random_room = rooms[random_index];
    int rx = random_room.get_startx();
    int ry = random_room.get_starty();
    int rex = random_room.get_endx();
    int rey = random_room.get_endy();

    int stair_x = rand() % (rex - rx) + rx;
    int stair_y = rand() % (rey - ry) + ry;
    Tile *up_stair = this->get_tile(stair_x, stair_y);
    up_stair->set_type(Tile::TileType::UP_STAIRS);

    random_index = rand() % rooms.size();
    random_room = rooms[random_index];
    rx = random_room.get_startx();
    ry = random_room.get_starty();
    rex = random_room.get_endx();
    rey = random_room.get_endy();

    stair_x = rand() % (rex - rx) + rx;
    stair_y = rand() % (rey - ry) + ry;

    Tile *down_stair = this->get_tile(stair_x, stair_y);
    down_stair->set_type(Tile::TileType::DOWN_STAIRS);
}






