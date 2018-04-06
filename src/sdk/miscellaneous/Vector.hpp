#ifndef ANIUM_VECTOR_HPP
#define ANIUM_VECTOR_HPP

#include <cfloat>
#include <cmath>

class Vector {
private:
    float x;
    float y;
    float z;

public:
    Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    [[deprecated("Use constructor to init Vector with values")]]
    void Init(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Normalize() {
        float radius = 1.0f / (this->Length() + FLT_EPSILON);

        this->SetX(this->GetX() * radius);
        this->SetY(this->GetY() * radius);
        this->SetZ(this->GetZ() * radius);
    }

    Vector Normalize(Vector& vector) {
        float length = this->Length();

        if (length != 0.0f) {
            vector.SetX(this->GetX() / length);
            vector.SetY(this->GetY() / length);
            vector.SetZ(this->GetZ() / length);
        }

        return vector;
    }

    bool IsZero(float tolerance = 0.01f) {
        return this->GetX() > -tolerance && this->GetX() < tolerance &&
               this->GetY() > -tolerance && this->GetY() < tolerance &&
               this->GetZ() > -tolerance && this->GetZ() < tolerance;
    }

    float Length() {
        return std::sqrt(this->GetX() * this->GetX() +
                         this->GetY() * this->GetY() +
                         this->GetZ() * this->GetZ());
    }

    float LengthSqrt() {
        return this->GetX() * this->GetX() +
               this->GetY() * this->GetY() +
               this->GetZ() * this->GetZ();
    }

    float Length2D() {
        return std::sqrt(this->GetX() * this->GetX() +
                         this->GetY() * this->GetY());
    }

    float Length2DSqrt() {
        return this->GetX() * this->GetX() +
               this->GetY() * this->GetY();
    }

    float GetX() const {
        return x;
    }

    float GetY() const {
        return y;
    }

    float GetZ() const {
        return z;
    }

    void SetX(float x) {
        this->x = x;
    }

    void SetY(float y) {
        this->y = y;
    }

    void SetZ(float z) {
        this->z = z;
    }

    void operator=(const Vector& input) {
        this->SetX(input.GetX());
        this->SetY(input.GetY());
        this->SetZ(input.GetZ());
    }

    bool operator==(const Vector& compare) {
        return this->GetX() == compare.GetX() &&
               this->GetY() == compare.GetY() &&
               this->GetZ() == compare.GetZ();
    }

    bool operator!=(const Vector& compare) {
        return this->GetX() != compare.GetX() &&
               this->GetY() != compare.GetY() &&
               this->GetZ() != compare.GetZ();
    }

    float& operator[](int index)
    {
        return ((float*) this)[index];
    }

    float operator[](int index) const
    {
        return ((float*) this)[index];
    }

    static Vector Zero() {
        return Vector(0.0f, 0.0f, 0.0f);
    }

};

#endif  // ANIUM_VECTOR_HPP
