/**
 * @file   Vector2.cpp
 * @brief  x������z������AABB�̕ϐ����쐬����N���X
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
		*@brief �R���X�g���N�^
		*/
		Vector2(double ax, double az) :_x(ax), _z(az) {}

		// �f�X�g���N�^
		~Vector2() = default;
	
		/*
        *  @brief  �x�N�g�����m�̉��Z
        *  @return ���Z���ꂽ�x�N�g��
        */
        const Vector2 operator +(const Vector2& rhs) const;

        /*
        *  @brief  �x�N�g�����m�̌��Z
        *  @return ���Z���ꂽ�x�N�g��
        */
        const Vector2 operator -(const Vector2& rhs) const;

        /*
        *  @brief  �x�N�g���̃X�J���[�{(��Z)
        *  @return �v�Z���ꂽ�x�N�g�� 
        */
        const Vector2 operator *(const double rhs) const;

        /*
        *  @brief  �x�N�g���̃X�J���[�{(���Z)
        *  @return �v�Z���ꂽ�x�N�g�� 
        */
        const Vector2 operator /(const double rhs) const;

        /**
         * @brief  ����         
         * @param  rhs
         * @return �v�Z�����l
         */
        double Dot(const Vector2& rhs) const;


        /**
         * @brief  �O��       
         * @param  rhs
         * @return �v�Z�����x�N�g��
         */
        double Cross(const Vector2& rhs) const;


		/*
		*@brief  x�̐��l���擾
		*@return _x
		*/
		const double GetX() const  { return _x; }

		/*
		*@brief  z�̐��l���擾
		*@return _z
		*/
		const double GetZ() const  { return _z; }

	private:
		double _x, _z; //!< x����, z����

	};


}
