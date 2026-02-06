//***************************************************************************************
// MathHelper.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Helper math class.
//***************************************************************************************

#pragma once

#include <cstdint>
#include <d3d12helper/DXMath/DXMath.h>

class MathHelper {
public:
    // Returns random float in [0, 1).
    static float RandF()
    {
        return (float)(rand()) / (float)RAND_MAX;
    }

    // Returns random float in [a, b).
    static float RandF(float a, float b)
    {
        return a + RandF() * (b - a);
    }

    static int32_t Rand(int32_t a, int32_t b)
    {
        return a + rand() % ((b - a) + 1);
    }

    template <typename T>
    static T Min(const T &a, const T &b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    static T Max(const T &a, const T &b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    static T Lerp(const T &a, const T &b, float t)
    {
        return a + (b - a) * t;
    }

    template <typename T>
    static T Clamp(const T &x, const T &low, const T &high)
    {
        return x < low ? low : (x > high ? high : x);
    }

    // Returns the angle theta in [0, 2*PI) defined by the vector (x, y).]
    template <typename T>
    static T NormalizeAngle(T theta)
    {
        T twoPi = 6.28318530718f;
        theta = fmod(theta, twoPi);
        if (theta < 0.0f) theta += twoPi;
        return theta;
    }

    template <typename T>
    static T SlerpRadians(const T &a, const T &b, T t)
    {
        // 1. 预处理：确保输入在 [0, 2*PI] 或其他统一范围内
        T start = MathHelper::NormalizeAngle(a);
        T end = MathHelper::NormalizeAngle(b);

        // 2. 计算原始差值
        T diff = end - start;

        // 3. 寻找最短路径：核心逻辑
        // 如果差值绝对值超过了 PI，说明走另一边更近
        const T PI = 3.1415926535f;
        const T TWO_PI = PI * 2.0f;

        if (diff > PI) {
            // 顺时针太远了，逆时针走
            diff -= TWO_PI;
        } else if (diff < -PI) {
            // 逆时针太远了，顺时针走
            diff += TWO_PI;
        }

        // 4. 执行插值并重新规范化结果
        T result = start + diff * t;
        return MathHelper::NormalizeAngle(result);
    }

    // Returns the polar angle of the point (x,y) in [0, 2*PI).
    static float AngleFromXY(float x, float y);

    static DirectX::XMVECTOR SphericalToCartesian(float radius, float theta, float phi);

    static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M);

    static float4x4 Identity4x4();

    static Math::Vector3 Vec3Max();

    static DirectX::XMVECTOR RandUnitVec3();
    static DirectX::XMVECTOR RandHemisphereUnitVec3(DirectX::XMVECTOR n);

    static const float Infinity;
    static const float Pi;
};