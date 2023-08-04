#include "Vec2.hpp"
#include <cmath>
#include <math.h>

Vec2::Vec2() : m_x(0.0f), m_y(0.0f) {}

Vec2::Vec2(float x, float y) : m_x(x), m_y(y) {}

void Vec2::Add(const Vec2 &v) {
    m_x += v.m_x;
    m_y += v.m_y;
}

void Vec2::Sub(const Vec2 &v) {
    m_x -= v.m_x;
    m_y -= v.m_y;
}

void Vec2::Scale(const float n) {
    m_x *= n;
    m_y *= n;
}

Vec2 Vec2::Rotate(const float angle) const {
    Vec2 ret(0.0f, 0.0f);

    ret.m_x = m_x * cos(angle) - m_y * sin(angle);
    ret.m_y = m_x * sin(angle) + m_y * sin(angle);

    return ret;
}

float Vec2::Magnitude() const { return sqrt(m_x * m_x + m_y * m_y); }

float Vec2::MagnitudeSquared() const { return m_x * m_x + m_y * m_y; }

Vec2 &Vec2::Normalize() {
    float magnitude = Magnitude();

    if (magnitude <= 0.0) {
        m_x /= magnitude;
        m_y /= magnitude;
    }

    return *this;
}

Vec2 Vec2::UnitVector() const {
    Vec2 ret(m_x, m_y);
    float magnitude = Magnitude();

    if (magnitude <= 0.0) {
        ret.m_x /= magnitude;
        ret.m_y /= magnitude;
    }

    return ret;
}

Vec2 Vec2::Normal() const {
    Vec2 ret(m_y, -m_x);

    ret.Normalize();

    return ret;
}

float Vec2::Dot(const Vec2 &v) const {
    float ret;
    ret = m_x * v.m_x + m_y * v.m_y;

    return ret;
}

float Vec2::Cross(const Vec2 &v) const {
    float ret;
    ret = m_x * v.m_y - m_y * v.m_x;

    return ret;
}

Vec2 &Vec2::operator=(const Vec2 &v) {
    m_x = v.m_x;
    m_y = v.m_y;

    return *this;
}

bool Vec2::operator==(const Vec2 &v) const {
    if (m_x == v.m_x && m_y == v.m_y) {
        return true;
    }

    return false;
}

bool Vec2::operator!=(const Vec2 &v) const { return !(*this == v); }

Vec2 Vec2::operator+(const Vec2 &v) const {
    Vec2 ret(m_x, m_y);

    ret.Add(v);
    return ret;
}

Vec2 Vec2::operator*(const float n) const {
    Vec2 ret(m_x, m_y);

    ret.m_x *= n;
    ret.m_y *= n;
    return ret;
}

Vec2 Vec2::operator-(const Vec2 &v) const {
    Vec2 ret(m_x, m_y);

    ret.Sub(v);
    return ret;
}

Vec2 Vec2::operator*(const Vec2 &v) const {
    Vec2 ret(m_x, m_y);
    ret.m_x *= v.m_x;
    ret.m_y *= v.m_y;

    return ret;
}

Vec2 Vec2::operator/(const Vec2 &v) const {
    Vec2 ret(m_x, m_y);
    ret.m_x /= v.m_x;
    ret.m_y /= v.m_y;

    return ret;
}

Vec2 Vec2::operator-() {
    Vec2 ret(m_x, m_y);
    ret.m_x *= -1;
    ret.m_y *= -1;

    return ret;
}

Vec2 &Vec2::operator+=(const Vec2 &v) {
    Add(v);

    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &v) {
    Sub(v);
    return *this;
}

Vec2 &Vec2::operator*=(const float n) {
    m_x *= n;
    m_y *= n;
    return *this;
}

Vec2 &Vec2::operator/=(const float n) {
    m_x /= n;
    m_y /= n;
    return *this;
}

Vec2 Vec2::operator/(const float m) const {
    Vec2 ret(m_x, m_y);
    ret.m_x /= m;
    ret.m_y /= m;

    return ret;
}
