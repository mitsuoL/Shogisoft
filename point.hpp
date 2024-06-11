#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
public:
    int x;
    int y;
    Point(int x, int y);
    Point();
    bool operator==(const Point& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

#endif // POINT_HPP
