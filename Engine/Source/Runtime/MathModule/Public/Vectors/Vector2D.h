#pragma once

template<typename T>
class Vector2D {
public:
    Vector2D(T x, T y)
    : m_x(x), m_y(y) { }

    Vector2D() = default;

    T m_x;
    T m_y;
};