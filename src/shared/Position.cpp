#include "Position.h"

template<typename T, typename Enable>
Position<T, Enable>::Position(T x, T y, T z)
    : X(x), Y(y), Z(z) {
}

template<typename T, typename Enable>
Position<T, Enable>::Position(const Position<T>& pos)
    : Position<T>(pos.X, pos.Y, pos.Z) {
}

template<typename T, typename Enable>
Position<T, Enable>::Position()
    : Position(0, 0, 0) {
}

template<typename T, typename Enable>
void Position<T, Enable>::SetPosition(const Position<T>& pos) {
    X = pos.X;
    Y = pos.Y;
    Z = pos.Z;
}

template<typename T, typename Enable>
void Position<T, Enable>::SetPosition(T x, T y, T z) {
    X = x;
    Y = y;
    Z = z;
}

template<typename T, typename Enable>
Position<T> Position<T, Enable>::GetPosition() const {
    return Position<T>(X, Y, Z);
}

template<typename T, typename Enable>
std::tuple<T, T, T> Position<T, Enable>::GetPositionTuple() const {
    return std::make_tuple(X, Y, Z);
}

// Explicit instantiation for commonly used types if needed
template class Position<double>;
template class Position<float>;
template class Position<int>;
template class Position<Uint64>;
template class Position<Uint32>;
template class Position<Uint16>;
template class Position<Uint8>;
