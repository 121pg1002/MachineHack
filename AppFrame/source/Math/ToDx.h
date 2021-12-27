/**
 * @file   ToDx.h
 * @brief  DxLib�̃��b�p�[
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */


#pragma once

struct tagVECTOR;
struct tagMATRIX;

namespace math {
    class Vector4;
    class Matrix44;
}
/*
*@brief Vector4�N���X����DxLib��VECTOR�ɕϊ�
*@param vector �x�N�g��
*/
VECTOR ToDX(math::Vector4& vector);

/*
*@brief Matrix44�N���X����DxLib��MATRIX�ɕϊ�
*@param matrix �s��
*/
MATRIX ToDX(math::Matrix44& matrix);

/*
*@brief DxLib��MATRIX����Matrix44�N���X�ɕϊ�
*@param matrix �s��
*/
math::Matrix44 ToMath(MATRIX& matrix);
