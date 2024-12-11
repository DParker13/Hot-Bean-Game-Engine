#pragma once

#include <SDL_stdinc.h>
#include <type_traits>
#include <tuple>
#include <iostream>

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Position {
public:
    T X, Y, Z;

    // Constructor with parameters
    Position(T x, T y, T z);

    // Copy constructor
    Position(const Position<T>& pos);

    // Default constructor
    Position();

    // Virtual destructor for polymorphic behavior
    virtual ~Position() = default;

    // Virtual function to set position from another Position object
    virtual void SetPosition(const Position<T>& pos);

    // Function to set position with individual coordinates
    virtual void SetPosition(T x, T y, T z);

    // Function to get a copy of the current position
    Position<T> GetPosition() const;

    // Function to get the position as a tuple
    std::tuple<T, T, T> GetPositionTuple() const;

    void Add(const Position<T>& pos) {
        X += pos.X;
        Y += pos.Y;
        Z += pos.Z;
    }

    void ToString() {
        std::cout << "Position: {" << X << ", " << Y << ", " << Z << "}";
    }
};