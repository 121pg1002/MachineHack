/**
 * @file   Vector4.h
 * @brief  同次座標系のベクトルクラス
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

#pragma once

namespace AppFrame::Math
{

    class Matrix44;

    class Vector4 {
    public:
        /*
        * @brief コンストラクタ
        */
        Vector4();

        /*
        *  @brief 引数による各成分の初期化
        *  @param x 直交座標系におけるx成分
        *  @param y 直交座標系におけるy成分
        *  @param z 直交座標系におけるz成分
        *
        */
        Vector4(const double x, const double y, const double z) : _x(x), _y(y), _z(z), _w(1.0) {}

        /*
        *  @brief 引数による各成分の初期化
        *  @param x 同次座標系におけるx成分
        *  @param y 同次座標系におけるy成分
        *  @param z 同次座標系におけるz成分
        *  @param w 同次座標系におけるw成分(0 < w < 1)
        */
        Vector4(const double x, const double y, const double z, double w) : _x(x), _y(y), _z(z), _w(w) {}


        // デストラクタ
        ~Vector4() = default;

        /*
        *  @brief  ベクトル同士の加算
        *  @return 加算されたベクトル
        */
        const Vector4 operator +(const Vector4& rhs) const;

        /*
        *  @brief  ベクトル同士の減算
        *  @return 減算されたベクトル
        */
        const Vector4 operator -(const Vector4& rhs) const;

        /*
        *  @brief  ベクトルのスカラー倍(乗算)
        *  @return 計算されたベクトル 
        */
        const Vector4 operator *(const double rhs) const;

        /*
        *  @brief  ベクトルのスカラー倍(除算)
        *  @return 計算されたベクトル 
        */
        const Vector4 operator /(const double rhs) const;

        /*
        *　@brief ベクトルの加算代入
        *  @return 計算されたベクトル
        */
        //const Vector4 operator +=(const Vector4& rhs) const;




        /*
        *  @brief ベクトルと行列の積
        */
        const Vector4 operator *(const Matrix44 rhs) const;

        /*
        *  @brief 同次座標系におけるベクトルの各成分を保存
        */
        void Set(const Vector4& vector);

        /*
        *  @breif 直交座標系におけるベクトルの各成分を保存
        */
        void Set(const double x, const double y, const double z);

        /*
        *  @brief 同次座標系におけるベクトルの各成分を元の座標に加算
        */
        /*void Add(const Vector4& vector);*/
        void Add(const double x, const double y, const double z);

        /*
        *  @brief  同次座標系におけるx成分の取得
        *  @return x成分
        */
        const double GetX() const { return _x; }

        /*
        *  @brief  同次座標系におけるy成分の取得
        *  @return y成分
        */
        const double GetY() const { return _y; }

        /*
        *  @brief  同次座標系におけるz成分の取得
        *  @return z成分
        */
        const double GetZ() const { return _z; }

        /*
        *  @brief  同次座標系におけるw成分の取得
        *  @return w成分
        */
        const double GetW() const { return _w; }

        /*
        *  @brief  ベクトルの長さの計算 
        *  @return 長さ
        */
        const double Length() const;

        ////////////////////////追加分12/01
        /*
        *  @brief  XZ平面のベクトルの長さの計算 
        *  @return 長さ
        */
        const double Length_XZ() const;

        /////////////////////////////////////

        /*
        *@brief 単位ベクトルの計算
        */
        void Normalized();

        /*
        *  @brief  単位ベクトルの計算
        *  @return 単位ベクトル
        */
        const Vector4 Normalize() const;


        /*
        *  @brief  ベクトルの内積
        *  @return 各内積の成分
        */
        const double Dot(const Vector4& rhs) const;

        /*
        *  @brief  ベクトルの外積
        *  @return 各外積の成分
        */
        const Vector4 Cross(const Vector4& rhs) const;

    private:
        double _x;
        double _y;
        double _z;
        double _w;
    };
}



