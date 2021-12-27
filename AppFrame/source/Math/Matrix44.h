/**
 * @file   Matrix44.h
 * @brief  4*4�̃}�g���b�N�X�N���X
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
    *@brief ��d�C���N���[�h�h�~ 
    */
    class Vector4;


    constexpr unsigned int row_max = 4;         //!< �s��
    constexpr unsigned int column_max = 4;      //!< ��

    //�s��
    using matrix_array = std::array<std::array<double, column_max>, row_max>;

    /*
    * 4�~4�̍s��N���X
    */
    class Matrix44 {
    public:

        /*
        * @brief �R���X�g���N�^
        */
        Matrix44();

        /*
        * @brief �R���X�g���N�^
        * @param values �s��
        */
        Matrix44(const matrix_array values);

        // �f�X�g���N�^
        virtual ~Matrix44() = default;

        /*
        *@brief  �s�񓯎m�̐�
        *@param  rhs �s��
        *@return �ς̐��l
        */
        const Matrix44 operator *(const Matrix44 rhs) const;

        /*
        *@brief         �s��̎擾
        *@param  row    �s
        *@param  column ��
        *@return        �s��
        */
        const double GetValue(const unsigned int row, const unsigned int column) const { return row_column[row][column]; }
        
        /*
        *@brief        �s��̕ۑ�
        *@param row    �s
        *@param column ��
        *@param value  ���l
        */
        const void SetValue(const unsigned int row, const unsigned int column, const double value) { row_column[row][column] = value; }

        /*
        *@brief        �s��̐��l��S��0�ɂ���
        *@param target �s��
        */
        void ValueToZero(matrix_array& target) const;

        /*
        *@brief �s��̍s�Ɨ�̓��������̏ꏊ��1�ɂ���
        */
        void DiagonalValueToOne();

        /*
        *@brief          �r���[�ϊ��s��
        *@param position �J�����ʒu
        *@param target   �J�����̒����_
        *@param up       �J�����̏����
        */
        void LookAt(const Vector4& position, const Vector4& target, const Vector4& up);

        /*
        *@brief        �����ϊ��s��
        *@param angle  ����p  
        *@param aspect �A�X�y�N�g��
        *@param near_z �j�A�N���b�v
        *@param far_z  �t�@�[�N���b�v
        */
        void Perspective(const double angle, const double aspect, const double near_z, const double far_z);

        /*
        *@brief �r���[�|�[�g�ϊ��s��
        *@param screen_width  �X�N���[����
        *@param screen_height �X�N���[������
        */
        void Viewport(const double screen_width, const double screen_height);

        /*
        *@ brief �x�N�g����4�~4�s��ɕϊ�
        *@param  x �x�N�g����x����
        *@param  y �x�N�g����y����
        *@param  z �x�N�g����z����
        */
        void VectorToMatrix44(const double x, const double y, const double z);

        /*
        *@brief        �s���p�����x�N�g���̕ϊ�
        *@param vec    �x�N�g��
        *@param matrix �s��
        *@return       �ϊ���̃x�N�g��
        */
        Vector4 VectorToTransform(const Vector4 vec, Matrix44 matrix);

        /*
        *@brief �g��k���s��
        *@param  x    �x�N�g����x����
        *@param  y    �x�N�g����y����
        *@param  z    �x�N�g����z����
        *@param  make �s������邩�ǂ���
        */
        void Scale(const double x, const double y, const double z, bool make);
        
        
        /*
        *@brief ��]�s��(x��)
        *@param degree x���p�x
        *@param make   �s����쐬���邩�ǂ���
        * 
        */
        void Rotate_x(const double degree, bool make);

        /*
        *@brief ��]�s��(y��)
        *@param degree y���p�x
        *@param make   �s����쐬���邩�ǂ���
        */
        void Rotate_y(const double degree, bool make);

        /*
        *@brief ��]�s��(z��)
        *@param degree z���p�x
        *@param make   �s����쐬���邩�ǂ���
        */
        void Rotate_z(const double degree, bool make);


    private:

        /*
        *@brief Sin��Cos�̕ϐ����擾
        *@param degree �p�x
        *@return ��sin�̒l �Ecos�̒l
        */
        std::pair<double, double> GetSinCos(const double degree) const;

        matrix_array row_column;//!< �s��
    };


}



