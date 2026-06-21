#pragma once

template<typename T>
class Vector3D {
public:
    Vector3D(T x, T y, T z)
    : m_x(x), m_y(y), m_z(z) { }

    T m_x;
    T m_y;
    T m_z;
};