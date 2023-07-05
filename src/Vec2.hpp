#pragma once

struct Vec2 {
    float m_x;
    float m_y;

    Vec2();
    Vec2(float x, float y);

    ~Vec2() = default;

    void Add(const Vec2 &v);
    void Sub(const Vec2 &v);
    void Scale(const float n);
    Vec2 Rotate(const float angle) const;

    float Magnitude() const;
    float MagnitudeSquared() const;

    Vec2 &Normalize();
    Vec2 UnitVector() const;
    Vec2 Normal() const;

    float Dot(const Vec2 &v) const;
    float Cross(const Vec2 &v) const;
};
