#ifndef ANIUM_COLOR_HPP
#define ANIUM_COLOR_HPP

class Color {
private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

public:
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    unsigned char& operator[](int index) {
        return ((unsigned char*) this)[index];
    }

    unsigned char operator[](int index) const {
        return ((unsigned char*) this)[index];
    }

    unsigned char GetRed() const {
        return this->r;
    }

    unsigned char GetGreen() const {
        return this->g;
    }

    unsigned char GetBlue() const {
        return this->b;
    }

    unsigned char GetAlpha() const {
        return this->a;
    }

};

struct ColorExp {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char exponent;

};

static Color WHITE = Color(255, 255, 255);
static Color BLUE = Color(0, 0, 255);
static Color GREEN = Color(0, 255, 0);
static Color RED = Color(255, 0, 0);
static Color YELLOW = Color(255, 255, 0);
static Color CYAN = Color(0, 139, 139);
static Color PINK = Color(255, 192, 203);
static Color PURPLE = Color(128, 0, 128);
static Color ORANGE = Color(255, 165, 0);
static Color GRAY = Color(128, 128, 128);
static Color BLACK = Color(0, 0, 0);

#endif  // ANIUM_COLOR_HPP
