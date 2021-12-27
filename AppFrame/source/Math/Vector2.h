/**
 * @file   Vector2.cpp
 * @brief  x方向とz方向のAABBの変数を作成するクラス
 *
 * @author Hikaru Goto
 * @date   2021/12/02
 */

#pragma once

namespace math 
{
	class Vector2
	{
	public:

		/*
		*@brief コンストラクタ
		*/
		Vector2(double ax, double az) :_x(ax), _z(az) {}


		/*
		*@brief  xの数値を取得
		*@return _x
		*/
		double GetX() { return _x; }

		/*
		*@brief  zの数値を取得
		*@return _z
		*/
		double GetZ() { return _z; }

	private:
		double _x, _z; //!< x成分, z成分

	};


}
