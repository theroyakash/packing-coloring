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

    bool operator==(const Color& other) const {
        return colorID == other.colorID;
    }


    friend std::ostream &operator<<(std::ostream &, Color &);
};

std::ostream &operator<<(std::ostream &stream, Color &c) {
    stream << c.colorID;
    return stream;
}

#endif // COLORS
