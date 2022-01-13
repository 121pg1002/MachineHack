/**
 * @file   Matrix44.h
 * @brief  4*4のマトリックスクラス
 *
 *
 * @author Hikaru Goto
 * @date   2021/11/30
 */

#include <cmath>
#include "Utility.h"
#include "Matrix44.h"
#include "Vector4.h"

using namespace math;

    Matrix44::Matrix44() {
        DiagonalValueToOne();
    }

    Matrix44::Matrix44(const matrix_array values) {
        this->row_column = values;
    }

    void Matrix44::ValueToZero(matrix_array& target) const {
        for (auto i = 0; i < row_max; ++i) {
            target[i].fill(0.0);
        }
    }

    void Matrix44::DiagonalValueToOne() {
        ValueToZero(row_column);

        for (auto i = 0; i < row_max; ++i) {
            row_column[i][i] = 1.0;
        }
    }

    // 本来はカメラに属する処理だが便宜上実装する
    void Matrix44::LookAt(const Vector4& position, const Vector4& target, const Vector4& up) {
        auto axis_z = target - position;
        auto axis_x = up.Cross(axis_z);
        auto axis_y = axis_z.Cross(axis_x);

        axis_x.Normalized();
        axis_y.Normalized();
        axis_z.Normalized();

        row_column[0][0] = axis_x.GetX();
        row_column[0][1] = axis_y.GetX();
        row_column[0][2] = axis_z.GetX();
        row_column[0][3] = 0.0;

        row_column[1][0] = axis_x.GetY();
        row_column[1][1] = axis_y.GetY();
        row_column[1][2] = axis_z.GetY();
        row_column[1][3] = 0.0;

        row_column[2][0] = axis_x.GetZ();
        row_column[2][1] = axis_y.GetZ();
        row_column[2][2] = axis_z.GetZ();
        row_column[2][3] = 0.0;

        row_column[3][0] = -axis_x.Dot(position);
        row_column[3][1] = -axis_y.Dot(position);
        row_column[3][2] = -axis_z.Dot(position);
        row_column[3][3] = 1.0;
    }

    void Matrix44::Perspective(const double angle, const double aspect, const double near_z, const double far_z) {
        auto ScaleY = 1.0 / tan(angle * 0.5);
        auto ScaleX = ScaleY/aspect;
        auto ScaleZ = 1/(far_z- near_z) / far_z;
        auto TransZ = -near_z / (far_z - near_z) * far_z;

        ValueToZero(row_column);

        row_column[0][0] = ScaleX;
        row_column[1][1] = ScaleY;
        row_column[2][2] = ScaleZ;
        row_column[2][3] = 1.0f;
        row_column[3][2] = TransZ;
    }

    void Matrix44::Viewport(const double screen_width, const double screen_height) {
        auto w = screen_width * 0.5;
        auto h = screen_height * 0.5;

        DiagonalValueToOne();

        row_column[0][0] = w;
        row_column[1][1] = -h;
        row_column[3][0] = w;
        row_column[3][1] = h;
    }

    const Matrix44 Matrix44::operator *(const Matrix44 rhs) const {
        matrix_array result{ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} };

        for (auto i = 0; i < row_max; ++i) {
            for (auto j = 0; j < column_max; ++j) {
                auto m = 0.0;

                for (auto k = 0; k < 4; ++k) {
                    m += row_column[i][k] * rhs.GetValue(k, j);
                }

                result[i][j] = m;
            }
        }

        return Matrix44(result);
    }

    void Matrix44::VectorToMatrix44(const double x, const double y, const double z) {
        
            DiagonalValueToOne();
        

        row_column[3][0] += x;
        row_column[3][1] += y;
        row_column[3][2] += z;
    }

    Vector4 Matrix44::VectorToTransform(const Vector4 vec, Matrix44 matrix) 
    {
       auto x = vec.GetX()* matrix.row_column[0][0] + vec.GetY() * matrix.row_column[1][0] + vec.GetZ() * matrix.row_column[2][0] + matrix.row_column[3][0];
       auto y = vec.GetX() * matrix.row_column[0][1] + vec.GetY() * matrix.row_column[1][1] + vec.GetZ() * matrix.row_column[2][1] + matrix.row_column[3][1];
       auto z = vec.GetX() * matrix.row_column[0][2] + vec.GetY() * matrix.row_column[1][2] + vec.GetZ() * matrix.row_column[2][2] + matrix.row_column[3][2];

       Vector4 v;
    
    return  v = { x, y, z };
    }

    void Matrix44::Scale(const double x, const double y, const double z, bool make) {
        
        if (make) 
        {
            DiagonalValueToOne();
        }
        

        row_column[0][0] *= x;
        row_column[1][1] *= y;
        row_column[2][2] *= z;
    }

    void Matrix44::Rotate_x(const double degree, bool make) {
        auto sin_cos = GetSinCos(degree);
        auto sin = sin_cos.first;
        auto cos = sin_cos.second;

        if (make) {
            DiagonalValueToOne();

            row_column[1][1] = cos;
            row_column[1][2] = sin;
            row_column[2][1] = -sin;
            row_column[2][2] = cos;
        }
        else {
            matrix_array array{ {{1, 0, 0, 0}, {0, cos, sin, 0}, {0, -sin, cos, 0}, {0, 0, 0, 1}} };
            Matrix44 rot_x(array);

            *this = *this * rot_x;
        }
    }

    void Matrix44::Rotate_y(const double degree, bool make) {
        auto sin_cos = GetSinCos(degree);
        auto sin = sin_cos.first;
        auto cos = sin_cos.second;

        if (make) {
            DiagonalValueToOne();

            row_column[0][0] = cos;
            row_column[0][2] = -sin;
            row_column[2][0] = sin;
            row_column[2][2] = cos;
        }
        else {
            matrix_array array{ {{cos, 0, -sin, 0}, {0, 1, 0, 0}, {sin, 0, cos, 0}, {0, 0, 0, 1}} };
            Matrix44 rot_y(array);

            *this = *this * rot_y;
        }
    }

    void Matrix44::Rotate_z(const double degree, bool make) {
        auto sin_cos = GetSinCos(degree);
        auto sin = sin_cos.first;
        auto cos = sin_cos.second;

        int j = 0;

        if (make) {
            DiagonalValueToOne();

            row_column[0][0] = cos;
            row_column[0][1] = sin;
            row_column[1][0] = -sin;
            row_column[1][1] = cos;
        }
        else {
            matrix_array array{ {{cos, sin, 0, 0}, {-sin, cos, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
            Matrix44 rot_z(array);

            *this = *this * rot_z;
        }
    }

    std::pair<double, double> Matrix44::GetSinCos(const double degree) const {
        auto radian = Utility::DegreeToRadian(degree);
        std::pair<double, double> _sin_cos = { std::sin(radian), std::cos(radian) };
        return _sin_cos;
    }

