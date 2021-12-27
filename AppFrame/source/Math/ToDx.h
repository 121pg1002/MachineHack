/**
 * @file   ToDx.h
 * @brief  DxLibのラッパー
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
*@brief Vector4クラスからDxLibのVECTORに変換
*@param vector ベクトル
*/
VECTOR ToDX(math::Vector4& vector);

/*
*@brief Matrix44クラスからDxLibのMATRIXに変換
*@param matrix 行列
*/
MATRIX ToDX(math::Matrix44& matrix);

/*
*@brief DxLibのMATRIXからMatrix44クラスに変換
*@param matrix 行列
*/
math::Matrix44 ToMath(MATRIX& matrix);
