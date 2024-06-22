#ifndef POSITION_H
#define POSITION_H

#include <type_traits>

template<typename T, typename = std::enable_if<std::is_arithmetic<T>::value, T>>
class Position {
public:
    T X, Y, Z;

    Position(T x, T y, T z);

    Position(const Position<T>& pos);

    Position();

    void virtual SetPosition(Position<T> pos);
    void virtual SetPosition(T x, T y, T z);
};

#endif // POSITION_H