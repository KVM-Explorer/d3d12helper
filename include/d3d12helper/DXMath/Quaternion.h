//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard
//

#pragma once
#include <DirectXMath.h>
#include "d3d12helper/DXMath/Vector.h"

namespace Math {
class alignas(16) Quaternion {
public:
    INLINE XM_CALLCONV Quaternion() { m_vec = XMQuaternionIdentity(); }
    INLINE XM_CALLCONV Quaternion(const Vector3 &axis, const Scalar &angle) { m_vec = XMQuaternionRotationAxis(axis, angle); }
    INLINE XM_CALLCONV Quaternion(float pitch, float yaw, float roll) { m_vec = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll); }
    INLINE explicit XM_CALLCONV Quaternion(const XMMATRIX &matrix) { m_vec = XMQuaternionRotationMatrix(matrix); }
    INLINE explicit XM_CALLCONV Quaternion(FXMVECTOR vec) { m_vec = vec; }
    INLINE explicit XM_CALLCONV Quaternion(EIdentityTag) { m_vec = XMQuaternionIdentity(); }

    INLINE XM_CALLCONV operator XMVECTOR() const { return m_vec; }

    INLINE Quaternion XM_CALLCONV operator~(void) const { return Quaternion(XMQuaternionConjugate(m_vec)); }
    INLINE Quaternion XM_CALLCONV operator-(void) const { return Quaternion(XMVectorNegate(m_vec)); }

    INLINE Quaternion XM_CALLCONV operator*(Quaternion rhs) const { return Quaternion(XMQuaternionMultiply(rhs, m_vec)); }
    INLINE Vector3 XM_CALLCONV operator*(Vector3 rhs) const { return Vector3(XMVector3Rotate(rhs, m_vec)); }

    INLINE Quaternion &XM_CALLCONV operator=(Quaternion rhs)
    {
        m_vec = rhs;
        return *this;
    }
    INLINE Quaternion &XM_CALLCONV operator*=(Quaternion rhs)
    {
        *this = *this * rhs;
        return *this;
    }

protected:
    XMVECTOR m_vec;
};

inline Vector3 catmullRom(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3, const float t) noexcept
{
    float t2 = t * t;
    float t3 = t2 * t;
    // clang-format off
	// return 0.5f * (( p1 * 2.0f) +
	// 	(-p0 + p2) * t +
	// 	(p0 * 2.0f - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
	// 	(-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
    // clang-format on
    return Vector3(DirectX::XMVectorCatmullRom(p0, p1, p2, p3, t));
}

inline Quaternion slerp(Quaternion q1, Quaternion q2, float t) noexcept
{
    return Quaternion(XMQuaternionSlerp(q1, q2, t));
}

} // namespace Math