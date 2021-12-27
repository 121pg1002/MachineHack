/**
 * @file   Vector4.h
 * @brief  同次座標系のベクトルクラス
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */


#include <cmath>
#include "../AppFrame/source/Math/Vector4.h"
#include "../AppFrame/source/Math/Matrix44.h"

using namespace math;
    Vector4::Vector4() : _x(0.0), _y(0.0), _z(0.0), _w(1.0)
    {
    }

    void Vector4::Set(const Vector4& vector) 
    {
        _x = vector.GetX();
        _y = vector.GetY();
        _z = vector.GetZ();
        _w = vector.GetW();
    }

    void Vector4::Set(const double x, const double y, const double z) 
    {
        _x = x;
        _y = y;
        _z = z;
    }

    void Vector4::Add(const double x, const double y, const double z) 
    {
        _x += x;
        _y += y;
        _z += z;
    }

    const double Vector4::Length() const 
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }

    /// //////////////////////////追加分 12/01
    const double Vector4::Length_XZ() const 
    {
        return sqrt(_x * _x + _z * _z);
    }
    //////////////////////////////////////


    void Vector4::Normalized() {
        auto len = Length();

        _x /= len;
        _y /= len;
        _z /= len;
    }


    const Vector4 Vector4::Normalize() const 
    {
        auto len = Length();
        auto nx = _x / len;
        auto ny = _y / len;
        auto nz = _z / len;

        return Vector4(nx, ny, nz);
    }

    const double Vector4::Dot(const Vector4& rhs) const 
    {
        return _x * rhs.GetX() + _y * rhs.GetY() + _z * rhs.GetZ();
    }

    const Vector4 Vector4::Cross(const Vector4& rhs) const 
    {
        auto cx = _y * rhs.GetZ() - _z * rhs.GetY();
        auto cy = _z * rhs.GetX() - _x * rhs.GetZ();
        auto cz = _x * rhs.GetY() - _y * rhs.GetX();

        return Vector4(cx, cy, cz);
    }

    const Vector4 Vector4::operator +(const Vector4& rhs) const 
    {
        return Vector4(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
    }

    const Vector4 Vector4::operator -(const Vector4& rhs) const 
    {
        return Vector4(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
    }

    const Vector4 Vector4::operator *(const double rhs) const 
    {
        return Vector4(_x * rhs, _y * rhs, _z * rhs);
    }

    const Vector4 Vector4::operator /(const double rhs) const 
    {
        return Vector4(_x / rhs, _y / rhs, _z / rhs);
    }

    //const Vector4 Vector4::operator += (const Vector4& rhs) const
    //{
    //    return Vector4(_x + rhs._x, _y + rhs._y, _z + rhs._z);
    //
    //}


    const Vector4 Vector4::operator *(const Matrix44 rhs) const 
    {
        auto mx = _x * rhs.GetValue(0, 0)
                + _y * rhs.GetValue(1, 0)
                + _z * rhs.GetValue(2, 0)
                + rhs.GetValue(3, 0);

        auto my = _x * rhs.GetValue(0, 1)
                + _y * rhs.GetValue(1, 1)
                + _z * rhs.GetValue(2, 1)
                + rhs.GetValue(3, 1);

        auto mz = _x * rhs.GetValue(0, 2)
                + _y * rhs.GetValue(1, 2)
                + _z * rhs.GetValue(2, 2)
                + rhs.GetValue(3, 2);

        auto mw = _x * rhs.GetValue(0, 3)
                + _y * rhs.GetValue(1, 3)
                + _z * rhs.GetValue(2, 3)
                + rhs.GetValue(3, 3);

        return Vector4(mx, my, mz, mw);
    }

