/**
 * @file   Utility.h
 * @brief  �֗��ȋ@�\�N���X
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

#include "../AppFrame/source/Math/Vector4.h"
#include "../AppFrame/source/Math/Utility.h"

using namespace math;

    // �ʂ̖@�������߂�
    Vector4 Utility::Normal(const Vector4& point0, const Vector4& point1, const Vector4& point2) 
    {
        // �ʂ̖@�������߂�
        const auto v0 = point1 - point0;
        const auto v1 = point2 - point0;
        auto cross = v0.Cross(v1);

        return cross.Normalize();
    }





