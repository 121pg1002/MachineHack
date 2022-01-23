/**
 * @file   Vector2.cpp
 * @brief  x•ûŒü‚Æz•ûŒü‚ÌAABB‚Ì•Ï”‚ğì¬‚·‚éƒNƒ‰ƒX
 *
 * @author Hikaru Goto
 * @date   2021/12/02
 */

#include "Vector2.h"
#include <cmath>

namespace AppFrame::Math {

    double Vector2::Dot(const Vector2& rhs) const{
        return _x * rhs.GetX() + _z * rhs.GetZ();
    }

    double Vector2::Cross(const Vector2& rhs) const{
        return _x * rhs.GetZ() - _z * rhs.GetX();
    }

    const Vector2 Vector2::operator +(const Vector2& rhs) const{
        return Vector2(_x + rhs.GetX(), _z + rhs.GetZ());
    }

    const Vector2 Vector2::operator -(const Vector2& rhs) const
    {
        return Vector2(_x - rhs.GetX(), _z - rhs.GetZ());
    }

    const Vector2 Vector2::operator *(const double rhs) const{
        return Vector2(_x * rhs, _z * rhs);
    }

    const Vector2 Vector2::operator /(const double rhs) const{
        return Vector2(_x / rhs, _z / rhs);
    }

    const double Vector2::Length()const {
        return std::sqrt(_x * _x + _z * _z);
    }

}


