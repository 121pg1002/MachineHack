/*****************************************************************//**
 * @file  Utility.cpp
 * @brief �֗��ȋ@�\�N���X
 *
 * @author Hikaru Goto
 * @date   November 30 2021
*********************************************************************/


#include "../AppFrame/source/Math/Vector4.h"
#include "../AppFrame/source/Math/Vector2.h"
#include "../AppFrame/source/Math/Utility.h"

namespace AppFrame::Math {

    //�@���̌v�Z
    Vector4 Utility::Normal(const Vector4& point0, const Vector4& point1, const Vector4& point2)
    {
        
        const auto v0 = point1 - point0;
        const auto v1 = point2 - point0;
        auto cross = v0.Cross(v1);

        return cross.Normalize();
    }

    //�_�ƎO�p�`�̓��O����(3����)
    bool Utility::InsideTrianglePoint(const Vector4& trianglePoint0, const Vector4& trianglePoint1, const Vector4& trianglePoint2, const Vector4& point) {
        
        const auto v01 = trianglePoint1 - trianglePoint0;
        const auto v12 = trianglePoint2 - trianglePoint1;
        const auto v20 = trianglePoint0 - trianglePoint2;
        const auto v0p = point - trianglePoint0;
        const auto v1p = point - trianglePoint1;
        const auto v2p = point - trianglePoint2;

        auto c0 = v01.Cross(v1p);
        auto c1 = v12.Cross(v2p);
        auto c2 = v20.Cross(v0p);

        c0.Normalized();
        c1.Normalized();
        c2.Normalized();

        const auto dot01 = c0.Dot(c1);
        const auto dot02 = c0.Dot(c2);

        return (dot01 > 0.0) && (dot02 > 0.0);
    }

    //�_�ƎO�p�`�̓��O����(2����)
    bool Utility::InsideTrianglePoint(const Vector2& trianglePoint0, const Vector2& trianglePoint1, const Vector2& trianglePoint2, const Vector2& point) {

        const auto v01 = trianglePoint1 - trianglePoint0;
        const auto v12 = trianglePoint2 - trianglePoint1;
        const auto v20 = trianglePoint0 - trianglePoint2;

        const auto v0p = point - trianglePoint0;
        const auto v1p = point - trianglePoint1;
        const auto v2p = point - trianglePoint2;

        auto c0 = v01.Cross(v0p);
        auto c1 = v12.Cross(v1p);
        auto c2 = v20.Cross(v2p);

        //c0.Normalized();
        //c1.Normalized();
        //c2.Normalized();

        
        //const auto dot01 = c0.Dot(c1);
        //const auto dot02 = c0.Dot(c2);
        // 
        //�S�ĕ��Ȃ����
        if (c0 <= 0.0 && c1 <= 0.0 && c2 <= 0.0) {
        
            return true;
        }
        else {
            return false;
        }
        
        ////�S�ĕ����Ɠ����ɂ���
        //return (c0 < 0.0) && (c1 < 0.0) && (c2 < 0.0);
    }

}







