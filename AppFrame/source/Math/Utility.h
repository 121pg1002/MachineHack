/*****************************************************************//**
 * @file  Utility.h
 * @brief 便利な機能クラス
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


        static constexpr float PI = 3.14159265358979f; //!< 円周率
        static constexpr float DEGREES_180 = 180.0f;   //!< 180度

        /*
        *  @breif  角度からラジアンに変換
        *  @return ラジアン
        */
        static double DegreeToRadian(const double degree) {return degree * PI / DEGREES_180;}

        /*
        *  @breif  ラジアンから角度に変換
        *  @return 角度
        */
        static double RadianToDegree(const double radian) {return radian * DEGREES_180 / PI;}

        // 面の法線を求める
        static Vector4 Normal(const Vector4& point0, const Vector4& point1, const Vector4& point2);

        /**
         * @brief 点と三角形の内外判定
         * @param trianglePoint0
         * @param trianglePoint1
         * @param trianglePoint2
         * @param point
         * @return 内か外か
         */
        static bool InsideTrianglePoint(const Vector4& trianglePoint0, const Vector4& trianglePoint1, const Vector4& trianglePoint2, const Vector4& point);


    private:
        Utility() = default;
    };
}


