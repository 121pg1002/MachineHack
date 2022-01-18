/*****************************************************************//**
 * @file  Utility.h
 * @brief �֗��ȋ@�\�N���X
 *
 * @author Hikaru Goto
 * @date   November 30 2021
*********************************************************************/


#pragma once

namespace AppFrame::Math
{
    class Vector4;

    class Utility {
    public:


        static constexpr float PI = 3.14159265358979f; //!< �~����
        static constexpr float DEGREES_180 = 180.0f;   //!< 180�x

        /*
        *  @breif  �p�x���烉�W�A���ɕϊ�
        *  @return ���W�A��
        */
        static double DegreeToRadian(const double degree) {return degree * PI / DEGREES_180;}

        /*
        *  @breif  ���W�A������p�x�ɕϊ�
        *  @return �p�x
        */
        static double RadianToDegree(const double radian) {return radian * DEGREES_180 / PI;}

        // �ʂ̖@�������߂�
        static Vector4 Normal(const Vector4& point0, const Vector4& point1, const Vector4& point2);

        /**
         * @brief �_�ƎO�p�`�̓��O����
         * @param trianglePoint0
         * @param trianglePoint1
         * @param trianglePoint2
         * @param point
         * @return �����O��
         */
        static bool InsideTrianglePoint(const Vector4& trianglePoint0, const Vector4& trianglePoint1, const Vector4& trianglePoint2, const Vector4& point);


    private:
        Utility() = default;
    };
}


