#if !defined(COLORS)
#define COLORS


#include <iostream>

using namespace std;

class Color {
public:
    int colorID;

    Color(int colorID) {
        this->colorID = colorID;
    }

    friend std::ostream &operator<<(std::ostream &, Color &);
};

std::ostream &operator<<(std::ostream &stream, Color &c) {
    stream << c.colorID;
    return stream;
}

#endif // COLORS
