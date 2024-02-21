#ifndef __VECTORS__
#define __VECTORS__

#include <math.h>

template <class T>
class Vector2
{
    public:
    Vector2() {}
    explicit Vector2(T a) : x(a), y(a) {}
    explicit Vector2(T x, T y) : x(x), y(y) {}

    inline Vector2<T> operator+(const Vector2<T> &v) const
    { return Vector2(x + v.x, y + v.y); }
    inline Vector2<T> operator-(const Vector2<T> &v) const
    { return Vector2<T>(x - v.x, y - v.y); }
    inline Vector2<T> operator*(const Vector2<T> &v) const
    { return Vector2<T>(x * v.x, y * v.y); }
    inline Vector2<T> operator/(const Vector2<T> &v) const
    { return Vector2<T>(x / v.x, y / v.y); }

    inline Vector2<T> operator+(T a) const
    { return Vector2<T>(x + a, y + a); }
    inline Vector2<T> operator-(T a) const
    { return Vector2<T>(x - a, y - a); }
    inline Vector2<T> operator*(T a) const
    { return Vector2<T>(x * a, y * a); }
    inline Vector2<T> operator/(T a) const
    { return Vector2<T>(x / a, y / a); }

    inline void operator+=(const Vector2<T> &v)
    { x += v.x; y += v.y; }
    inline void operator-=(const Vector2<T> &v)
    { x -= v.x; y -= v.y; }
    inline void operator*=(const Vector2<T> &v)
    { x *= v.x; y *= v.y; }
    inline void operator/=(const Vector2<T> &v)
    { x /= v.x; y /= v.y; }

    inline void operator+=(T a)
    { x += a; y += a; }
    inline void operator-=(T a)
    { x -= a; y -= a; }
    inline void operator*=(T a)
    { x *= a; y *= a; }
    inline void operator/=(T a)
    { x /= a; y /= a; }

    inline bool operator>(const Vector2<T> &v) const
    { return mag() > v.mag(); }
    inline bool operator<(const Vector2<T> &v) const
    { return mag() < v.mag(); }
    inline bool operator>=(const Vector2<T> &v) const
    { return mag() >= v.mag(); }
    inline bool operator<=(const Vector2<T> &v) const
    { return mag() <= v.mag(); }

    inline bool operator>(T a) const
    { return mag() > a; }
    inline bool operator<(T a) const
    { return mag() < a; }
    inline bool operator>=(T a) const
    { return mag() >= a; }
    inline bool operator<=(T a) const
    { return mag() <= a; }

    inline bool operator==(const Vector2<T> &v) const
    { return x == v.x && y == v.y; }
    inline bool operator!=(const Vector2<T> &v) const
    { return x != v.x || y != v.y; }

    inline bool operator==(T a) const
    { return mag() == a; }
    inline bool operator!=(T a) const
    { return mag() != a; }

    inline void operator=(T a)
    { x = a; y = a; }

    inline void negate()
    { x *= T(-1); y *= T(-1); }

    inline Vector2<T> negated() const
    { return Vector2<T>(x * T(-1), y * T(-1)); }

    inline void flip()
    { T t = x; x = y; y = t; }

    inline Vector2<T> flipped() const
    { return Vector2<T>(y, x); }

    inline void invert()
    { x = T(1) / x; y = T(1) / y; }

    inline Vector2<T> inverted() const
    { return Vector2<T>(T(1) / x, T(1) / y); }

    inline T sq() const
    { return (x * x + y * y); }
    inline T mag() const
    { return std::sqrt(sq()); }

    inline T dot(const Vector2<T> &v) const
    { return (x * v.x + y * v.y); }

    inline void abs() const
    { std::abs(x); std::abs(y); }

    inline Vector2<T> getAbs() const
    { return Vector2<T>(std::abs(x), std::abs(y)); }

    inline void normalize()
    { (*this) /= mag(); }

    inline Vector2<T> normalized() const
    { return ((*this) / mag()); }

    T x;
    T y;
};

template <class T>
class Vector3
{
public:
    T x;
    T y;
    T z;
    Vector3() {}
    Vector3(T a) : x(a), y(a), z(a) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
};

// INFO: Typedefs to simplify the names of datatypes (but Vector2 or vector3 is allowed but must be included with <datatype>)
typedef Vector2<int> Vec2i;
typedef Vector2<size_t> Vec2s;
typedef Vector2<float> Vec2f;
typedef Vector2<double> Vec2d;
typedef Vector3<int> Vec3i;
typedef Vector3<float> Vec3f;
typedef Vector3<double> Vec3d;

#endif
