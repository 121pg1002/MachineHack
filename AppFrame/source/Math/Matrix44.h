/**
 * @file   Matrix44.h
 * @brief  4*4のマトリックスクラス
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

#pragma once
#include <cstdint>
#include <array>
#include <tuple>
#include <DxLib.h>


namespace math 
{
    /*
    *@brief 二重インクルード防止 
    */
    class Vector4;


    constexpr unsigned int row_max = 4;         //!< 行数
    constexpr unsigned int column_max = 4;      //!< 列数

    //行列
    using matrix_array = std::array<std::array<double, column_max>, row_max>;

    /*
    * 4×4の行列クラス
    */
    class Matrix44 {
    public:

        /*
        * @brief コンストラクタ
        */
        Matrix44();

        /*
        * @brief コンストラクタ
        * @param values 行列
        */
        Matrix44(const matrix_array values);

        // デストラクタ
        virtual ~Matrix44() = default;

        /*
        *@brief  行列同士の積
        *@param  rhs 行列
        *@return 積の数値
        */
        const Matrix44 operator *(const Matrix44 rhs) const;

        /*
        *@brief         行列の取得
        *@param  row    行
        *@param  column 列
        *@return        行列
        */
        const double GetValue(const unsigned int row, const unsigned int column) const { return row_column[row][column]; }
        
        /*
        *@brief        行列の保存
        *@param row    行
        *@param column 列
        *@param value  数値
        */
        const void SetValue(const unsigned int row, const unsigned int column, const double value) { row_column[row][column] = value; }

        /*
        *@brief        行列の数値を全て0にする
        *@param target 行列
        */
        void ValueToZero(matrix_array& target) const;

        /*
        *@brief 行列の行と列の同じ数字の場所を1にする
        */
        void DiagonalValueToOne();

        /*
        *@brief          ビュー変換行列
        *@param position カメラ位置
        *@param target   カメラの注視点
        *@param up       カメラの上向き
        */
        void LookAt(const Vector4& position, const Vector4& target, const Vector4& up);

        /*
        *@brief        透視変換行列
        *@param angle  視野角  
        *@param aspect アスペクト比
        *@param near_z ニアクリップ
        *@param far_z  ファークリップ
        */
        void Perspective(const double angle, const double aspect, const double near_z, const double far_z);

        /*
        *@brief ビューポート変換行列
        *@param screen_width  スクリーン幅
        *@param screen_height スクリーン高さ
        */
        void Viewport(const double screen_width, const double screen_height);

        /*
        *@ brief ベクトルを4×4行列に変換
        *@param  x ベクトルのx成分
        *@param  y ベクトルのy成分
        *@param  z ベクトルのz成分
        */
        void VectorToMatrix44(const double x, const double y, const double z);

        /*
        *@brief        行列を用いたベクトルの変換
        *@param vec    ベクトル
        *@param matrix 行列
        *@return       変換後のベクトル
        */
        Vector4 VectorToTransform(const Vector4 vec, Matrix44 matrix);

        /*
        *@brief 拡大縮小行列
        *@param  x    ベクトルのx成分
        *@param  y    ベクトルのy成分
        *@param  z    ベクトルのz成分
        *@param  make 行列をつくるかどうか
        */
        void Scale(const double x, const double y, const double z, bool make);
        
        
        /*
        *@brief 回転行列(x軸)
        *@param degree x軸角度
        *@param make   行列を作成するかどうか
        * 
        */
        void Rotate_x(const double degree, bool make);

        /*
        *@brief 回転行列(y軸)
        *@param degree y軸角度
        *@param make   行列を作成するかどうか
        */
        void Rotate_y(const double degree, bool make);

        /*
        *@brief 回転行列(z軸)
        *@param degree z軸角度
        *@param make   行列を作成するかどうか
        */
        void Rotate_z(const double degree, bool make);


    private:

        /*
        *@brief SinとCosの変数を取得
        *@param degree 角度
        *@return 左sinの値 右cosの値
        */
        std::pair<double, double> GetSinCos(const double degree) const;

        matrix_array row_column;//!< 行列
    };


}



