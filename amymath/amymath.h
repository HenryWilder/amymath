/*******************
* Inspired by Godot, meant to operate alongside Raylib
*******************/
#ifndef AMYMATH_H
#define AMYMATH_H

#define RL_RECT2_TYPE
#define RL_RECT2I_TYPE
#define RL_VECTOR2I_TYPE
#define RL_VECTOR3I_TYPE
#define RL_VECTOR4I_TYPE

typedef enum Axis {
    AXIS_X = 0,
    AXIS_Y = 1,
} Axis;

#if !defined(RL_VECTOR2_TYPE)
typedef struct Vector2 {
    float x;
    float y;
} Vector2;
#define RL_VECTOR2_TYPE
#endif

#if !defined(RL_VECTOR3_TYPE)
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;
#define RL_VECTOR3_TYPE
#endif

#if !defined(RL_VECTOR4_TYPE)
typedef struct Vector4 {
    float x;
    float y;
    float z;
    float w;
} Vector4;
#define RL_VECTOR4_TYPE
#endif

#if !defined(RL_QUATERNION_TYPE)
typedef Vector4 Quaternion;
#define RL_QUATERNION_TYPE
#endif

typedef struct Vector2i {
    int x;
    int y;
} Vector2i;

typedef struct Vector3i {
    int x;
    int y;
    int z;
} Vector3i;

typedef struct Vector4i {
    int x;
    int y;
    int z;
    int w;
} Vector4i;

#if !defined(RL_RECTANGLE_TYPE)
typedef struct Rectangle {
    float x;
    float y;
    float width;
    float height;
} Rectangle;
#define RL_RECTANGLE_TYPE
#endif

typedef Rectangle Rect2;

typedef struct Rect2i {
    Vector2i position;
    Vector2i size;
} Rect2i;

typedef struct Transform2D {
    float xx, yx, ox;
    float xy, yy, oy;
} Transform2D;

Transform2D Transform2DIdentity(float rotation, Vector2 position)
{
    const Transform2D result = {
        1, 0, 0,
        0, 1, 0
    };

    return result;
}

Transform2D GenTransform2DV(float rotation, Vector2 position)
{
    // todo
}

Transform2D GenTransform2DEx(float rotation, Vector2 scale, float skew, Vector2 position)
{
    // todo
}

Transform2D GenTransform2D(Vector2 xAxis, Vector2 yAxis, Vector2 origin)
{
    Transform2D result = {
        xAxis.x, yAxis.x, origin.x,
        xAxis.y, yAxis.y, origin.y
    };

    return result;
}

// Get the origin of the transform
Vector2 Transform2DOrigin(Transform2D trans)
{
    Vector2 result = { trans.ox, trans.oy };

    return result;
}

typedef struct Transform3D {
    float xx, yx, zx, ox;
    float xy, yy, zy, oy;
    float xz, yz, zz, oz;
} Transform3D;

Transform3D GenTransform3D(Vector3 x, Vector3 y, Vector3 z, Vector3 origin)
{
    Transform3D result = {
        x.x, y.x, z.x, origin.x,
        x.y, y.y, z.y, origin.y,
        x.z, y.z, z.z, origin.z
    };

    return result;
}

#endif // AMYMATH_H