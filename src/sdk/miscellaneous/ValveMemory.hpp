#ifndef ANIUM_VALVEMEMORY_HPP
#define ANIUM_VALVEMEMORY_HPP

template <typename T, typename I = int>
class ValveMemory {
private:
    T* memory;
    int allocationCount;
    int growSize;

public:
    T* GetMemory() const {
        return this->memory;
    }

    int GetAllocationCount() const {
        return this->allocationCount;
    }

    int GetGrowSize() const {
        return this->growSize;
    }

    void SetMemory(T* memory) {
        this->memory = memory;
    }

    T& operator[](I index) {
        return this->memory[index];
    }

    T operator[](I index) const {
        return this->memory[index];
    }

};

#endif  // ANIUM_VALVEMEMORY_HPP
