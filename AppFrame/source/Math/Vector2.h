/**
 * @file   Vector2.cpp
 * @brief  x方向とz方向のAABBの変数を作成するクラス
 *
 * @author Hikaru Goto
 * @date   2021/12/02
 */

#pragma once

namespace AppFrame::Math
{
	class Vector2
	{
	public:

		/*
		*@brief コンストラクタ
		*/
		Vector2(double ax, double az) :_x(ax), _z(az) {}

		// デストラクタ
		~Vector2() = default;
	
		/*
        *  @brief  ベクトル同士の加算
        *  @return 加算されたベクトル
        */
        const Vector2 operator +(const Vector2& rhs) const;

        /*
        *  @brief  ベクトル同士の減算
        *  @return 減算されたベクトル
        */
        const Vector2 operator -(const Vector2& rhs) const;

        /*
        *  @brief  ベクトルのスカラー倍(乗算)
        *  @return 計算されたベクトル 
        */
        const Vector2 operator *(const double rhs) const;

        /*
        *  @brief  ベクトルのスカラー倍(除算)
        *  @return 計算されたベクトル 
        */
        const Vector2 operator /(const double rhs) const;

        /**
         * @brief  内積         
         * @param  rhs
         * @return 計算した値
         */
        double Dot(const Vector2& rhs) const;


        /**
         * @brief  外積       
         * @param  rhs
         * @return 計算したベクトル
         */
        double Cross(const Vector2& rhs) const;


		/*
		*@brief  xの数値を取得
		*@return _x
		*/
		const double GetX() const  { return _x; }

		/*
		*@brief  zの数値を取得
		*@return _z
		*/
		const double GetZ() const  { return _z; }

	private:
		double _x, _z; //!< x成分, z成分

	};


}
