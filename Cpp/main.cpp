#include <iostream>
#include <array>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Rectangle {
    public:

        int Area() {
            return height_ * width_;
        }

        int height_;
        int width_;
};

int main() {

    Rectangle r;
    r.height_ = 10;
    r.width_ = 20;
    r.Area();

    return 0;
}
