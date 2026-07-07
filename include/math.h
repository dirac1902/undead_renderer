#pragma once

class vec3f {
    public:
        vec3f() : x(0), y(0), z(0) {}
        vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

        float x, y, z;
};

class vec3i {
    public:
        vec3i() : x(0), y(0), z(0) {}
        vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

        int x, y, z;
};