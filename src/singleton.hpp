#ifndef ANIUM_SINGLETON_HPP
#define ANIUM_SINGLETON_HPP

class Singleton {
private:
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }

};

#endif  // ANIUM_SINGLETON_HPP
