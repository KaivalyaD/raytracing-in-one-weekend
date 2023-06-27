#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>
#include<random>

using std::sqrt;

// utils
inline float random_float() {
    // returns a random float in [0, 1)
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    static std::mt19937 gen;
    return dist(gen);
}

inline float random_float(float min, float max) {
    // returns a random float in [min, max)
    return min + (max - min) * random_float();
}

// class
class vec3 {
private:
    float e[3];
public:
    vec3() : e{0.0f, 0.0f, 0.0f} {}
    vec3(float x, float y, float z) : e{x, y, z} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    float r() const { return x(); }
    float g() const { return y(); }
    float b() const { return z(); }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    vec3& operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3& operator/=(const float t) {
        return *this *= (1.0f / t);
    }

    float length() const {
        return sqrt(length_squared());
    }
    float length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline static vec3 random() {
        return vec3(random_float(), random_float(), random_float());
    }

    inline static vec3 random(float min, float max) {
        return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
    }
};

// utils
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

inline vec3 operator/(vec3 v, float t) {
    return (1.0f / t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.x() * v.z() - u.z() * v.x(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// type aliases for vec3
using point3 = vec3;  // 3D points
using color3 = vec3;   // RGB colors

#endif  // VEC3_H
