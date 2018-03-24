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
        return r;
    }

    unsigned char GetGreen() const {
        return g;
    }

    unsigned char GetBlue() const {
        return b;
    }

    unsigned char GetAlpha() const {
        return a;
    }

};

#endif  // ANIUM_COLOR_HPP
