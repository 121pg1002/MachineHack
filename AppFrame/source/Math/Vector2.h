/**
 * @file   Vector2.cpp
 * @brief  x������z������AABB�̕ϐ����쐬����N���X
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
		*@brief �R���X�g���N�^
		*/
		Vector2(double ax, double az) :_x(ax), _z(az) {}


		/*
		*@brief  x�̐��l���擾
		*@return _x
		*/
		double GetX() { return _x; }

		/*
		*@brief  z�̐��l���擾
		*@return _z
		*/
		double GetZ() { return _z; }

	private:
		double _x, _z; //!< x����, z����

	};


}
