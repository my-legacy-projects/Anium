#ifndef ANIUM_MATRIX_HPP
#define ANIUM_MATRIX_HPP

struct matrix3x4 {
private:
    float values[3][4];

public:
    matrix3x4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23) {
        this->values[0][0] = m00;	
        this->values[0][1] = m01;
        this->values[0][2] = m02; 
        this->values[0][3] = m03;
        
        this->values[1][0] = m10;	
        this->values[1][1] = m11; 
        this->values[1][2] = m12; 
        this->values[1][3] = m13;
        
        this->values[2][0] = m20; 
        this->values[2][1] = m21; 
        this->values[2][2] = m22;
        this->values[2][3] = m23;
    }

    float* operator[](int index) {
        return this->values[index];
    }

    const float* operator[](int index) const {
        return this->values[index];
    }

};

#endif  // ANIUM_MATRIX_HPP
