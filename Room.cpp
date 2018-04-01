#include "Room.hpp"
#include <cmath>

Room::Room(int start_x, int start_y, int end_x, int end_y) : 
    start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y) {}

Room::Room(const Room& other) : 
    start_x(other.start_x), start_y(other.start_y),
    end_x(other.end_x), end_y(other.end_y) {}

int Room::get_startx() const {
    return this->start_x;
}
int Room::get_starty() const {
    return this->start_y;
}
int Room::get_endx() const {
    return this->end_x;
}
int Room::get_endy() const {
    return this->end_y;
}

int Room::get_x_center() const {
    return (this->end_x - this->start_x) / 2 + this->start_x;
}

int Room::get_y_center() const {
    return (this->end_y - this->start_y) / 2 + this->start_y;
}
