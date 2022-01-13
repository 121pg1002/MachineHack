/**
 * @file   ToDx.h
 * @brief  DxLibのラッパークラス
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */


#include "DxLib.h"
#include "ToDx.h"
#include "Vector4.h"
#include "Matrix44.h"
#include <utility>

VECTOR ToDX(AppFrame::Math::Vector4& vector) {
    return VGet(static_cast<float>(vector.GetX()), static_cast<float>(vector.GetY()), static_cast<float>(vector.GetZ()));
}

MATRIX ToDX(AppFrame::Math::Matrix44& matrix) {
    MATRIX ret;

    for (auto i = 0; i < AppFrame::Math::row_max; ++i) {
        for (auto j = 0; j < AppFrame::Math::column_max; ++j) {
            ret.m[i][j] = static_cast<float>(matrix.GetValue(i, j));
        }
    }

    return ret;
}

AppFrame::Math::Matrix44 ToMath(MATRIX& matrix) {
    AppFrame::Math::Matrix44 ret;

    for (auto i = 0; i < AppFrame::Math::row_max; ++i) {
        for (auto j = 0; j < AppFrame::Math::column_max; ++j) {
            ret.SetValue(i, j, static_cast<double>(matrix.m[i][j]));
        }
    }

    return ret;
}

