/**
 * @file   Utility.h
 * @brief  便利な機能クラス
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

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
        static double DegreeToRadian(float degree) {return degree * PI / DEGREES_180;}

        /*
        *  @breif  ラジアンから角度に変換
        *  @return 角度
        */
        static double RadianToDegree(float radian) {return radian * DEGREES_180 / PI;}

        // 面の法線を求める
        static Vector4 Normal(const Vector4& point0, const Vector4& point1, const Vector4& point2);


    private:
        Utility() = default;
    };
}


