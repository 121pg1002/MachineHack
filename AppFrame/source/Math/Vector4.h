/**
 * @file   Vector4.h
 * @brief  �������W�n�̃x�N�g���N���X
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
        * @brief �R���X�g���N�^
        */
        Vector4();

        /*
        *  @brief �����ɂ��e�����̏�����
        *  @param x �������W�n�ɂ�����x����
        *  @param y �������W�n�ɂ�����y����
        *  @param z �������W�n�ɂ�����z����
        *
        */
        Vector4(const double x, const double y, const double z) : _x(x), _y(y), _z(z), _w(1.0) {}

        /*
        *  @brief �����ɂ��e�����̏�����
        *  @param x �������W�n�ɂ�����x����
        *  @param y �������W�n�ɂ�����y����
        *  @param z �������W�n�ɂ�����z����
        *  @param w �������W�n�ɂ�����w����(0 < w < 1)
        */
        Vector4(const double x, const double y, const double z, double w) : _x(x), _y(y), _z(z), _w(w) {}


        // �f�X�g���N�^
        ~Vector4() = default;

        /*
        *  @brief  �x�N�g�����m�̉��Z
        *  @return ���Z���ꂽ�x�N�g��
        */
        const Vector4 operator +(const Vector4& rhs) const;

        /*
        *  @brief  �x�N�g�����m�̌��Z
        *  @return ���Z���ꂽ�x�N�g��
        */
        const Vector4 operator -(const Vector4& rhs) const;

        /*
        *  @brief  �x�N�g���̃X�J���[�{(��Z)
        *  @return �v�Z���ꂽ�x�N�g�� 
        */
        const Vector4 operator *(const double rhs) const;

        /*
        *  @brief  �x�N�g���̃X�J���[�{(���Z)
        *  @return �v�Z���ꂽ�x�N�g�� 
        */
        const Vector4 operator /(const double rhs) const;

        /*
        *�@@brief �x�N�g���̉��Z���
        *  @return �v�Z���ꂽ�x�N�g��
        */
        //const Vector4 operator +=(const Vector4& rhs) const;




        /*
        *  @brief �x�N�g���ƍs��̐�
        */
        const Vector4 operator *(const Matrix44 rhs) const;

        /*
        *  @brief �������W�n�ɂ�����x�N�g���̊e������ۑ�
        */
        void Set(const Vector4& vector);

        /*
        *  @breif �������W�n�ɂ�����x�N�g���̊e������ۑ�
        */
        void Set(const double x, const double y, const double z);

        /*
        *  @brief �������W�n�ɂ�����x�N�g���̊e���������̍��W�ɉ��Z
        */
        /*void Add(const Vector4& vector);*/
        void Add(const double x, const double y, const double z);

        /*
        *  @brief  �������W�n�ɂ�����x�����̎擾
        *  @return x����
        */
        const double GetX() const { return _x; }

        /*
        *  @brief  �������W�n�ɂ�����y�����̎擾
        *  @return y����
        */
        const double GetY() const { return _y; }

        /*
        *  @brief  �������W�n�ɂ�����z�����̎擾
        *  @return z����
        */
        const double GetZ() const { return _z; }

        /*
        *  @brief  �������W�n�ɂ�����w�����̎擾
        *  @return w����
        */
        const double GetW() const { return _w; }

        /*
        *  @brief  �x�N�g���̒����̌v�Z 
        *  @return ����
        */
        const double Length() const;

        ////////////////////////�ǉ���12/01
        /*
        *  @brief  XZ���ʂ̃x�N�g���̒����̌v�Z 
        *  @return ����
        */
        const double Length_XZ() const;

        /////////////////////////////////////

        /*
        *@brief �P�ʃx�N�g���̌v�Z
        */
        void Normalized();

        /*
        *  @brief  �P�ʃx�N�g���̌v�Z
        *  @return �P�ʃx�N�g��
        */
        const Vector4 Normalize() const;


        /*
        *  @brief  �x�N�g���̓���
        *  @return �e���ς̐���
        */
        const double Dot(const Vector4& rhs) const;

        /*
        *  @brief  �x�N�g���̊O��
        *  @return �e�O�ς̐���
        */
        const Vector4 Cross(const Vector4& rhs) const;

    private:
        double _x;
        double _y;
        double _z;
        double _w;
    };
}



