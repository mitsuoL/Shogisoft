#include "point.hpp"

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point() : x(0), y(0) {}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}