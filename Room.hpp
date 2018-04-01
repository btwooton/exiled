#ifndef ROOM_HPP_
#define ROOM_HPP_

class Room {
    public:
        Room(int start_x, int start_y, int end_x, int end_y);
        Room(const Room& other);
        ~Room() = default;
        
        int get_startx() const;
        int get_starty() const;
        int get_endx() const;
        int get_endy() const;
        int get_x_center() const;
        int get_y_center() const;

    private:
        int start_x;
        int start_y;
        int end_x;
        int end_y;
};
#endif