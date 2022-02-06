/*****************************************************************//**
 * @file   ModelAnimComponent.cpp
 * @brief  アニメーションモデル用のコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "ModelAnimComponent.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/Actor.h"
//#include <numbers>


namespace MachineHuck::Model {
    ModelAnimeComponent::ModelAnimeComponent(Actor::Actor& owner) : ModelComponent{ owner } {
    }

    ModelAnimeComponent::~ModelAnimeComponent() {
        MV1DetachAnim(_handle, _attachIndex);
    }

    ///
    /// 初期化.
    ///
    void ModelAnimeComponent::Init() {
    }
    void ModelAnimeComponent::Register(std::string_view key, int animIndex) {
        if (_registry.count(key.data()) != 0) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, animIndex);
    }
    /// 更新
    void ModelAnimeComponent::Update() {
        // 再生時間をセットする
        MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);

        // ワールド行列更新
        ModelComponent::Update();

        // 再生時間を進める
        _playTime += (1.f * _timeRate);

        if (_playTime >= _totalTime) {
            if (_repeate) {
                // リピート再生あり
                _playTime = 0.0f;
                ++_repeatedCount;
            }
            else {
                // リピート再生なし
                _repeatedCount = 1;
                _playTime = _totalTime;
            }
        }
    }
    ///
    /// 描画.
    ///
    void ModelAnimeComponent::Draw() {
        MV1DrawModel(_handle);
    }

    void ModelAnimeComponent::Draw(const Actor::Actor& owner, bool _isHit, double range, bool select)
    {
#ifdef _DEBUG
        Math::Vector4 lmax = owner.GetLMax() + owner.GetPosition();
        Math::Vector4 lmin = owner.GetLMin() + owner.GetPosition();

        DrawLine3D(ToDX(lmin), ToDX(lmax), GetColor(255, 0, 0));

        auto pos = owner.GetPosition();

        auto dir = owner.GetRotation();

        //atan2は、時計回りを正として実装しているため、向きが逆となるため符号をマイナスにしている
        auto rotY = -dir.GetY();

        //z軸を0度とするため
        auto nine = DX_PI / 180.0 * 90.0;

        auto nineReverse = DX_PI / 180.0 * 270.0;


        //ハッキングのみ180度回転させる
       /* auto reverse = DX_PI / 180.0 * 180.0;*/

        ////円弧の方向ベクトル
        //double endAngle = 45.0;
        //double halfAngle = endAngle / 2.0;
        //double Rad = DX_PI / 180.0 * endAngle;
        ////auto   halfRad = DX_PI / 180.0 * halfAngle;

        //Math::Vector4 _move = { std::cos(Rad), 0.0, std::sin(Rad) };
        //auto pos = owner.GetPosition();
        //auto target = pos + _move * owner.GetR() * 2.0;
        //DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));

        //
        //auto zero = 0.0;
        //_move = { std::cos(zero), 0.0, std::sin(zero) };
        //target = pos + _move * owner.GetR() * 2.0;
        //DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));


       // auto pos1 = act1.GetPosition();
       //DrawLine3D(ToDX(pos1), ToDX(pos), GetColor(255, 255, 0));
        ///円のあたりはんてい　
        //if (_isHit == true) 
        //{
        //    for (double i = 0.0; i < 720.0; i++)
        //    {
        //        double radian = DX_PI / 180.0 * i/2.0;
        //        double x = owner.GetR() * std::cos(radian);
        //        double z = owner.GetR() * std::sin(radian);
        //        Math::Vector4 t = { x, 0.0, z };
        //        Math::Vector4 newpos = owner.GetPosition() + t;
        //        DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));

        //    }
        //
        //}
        //else 
        //{
        //    for (double i = 0.0; i < 720.0; i++)
        //    {
        //        double radian = DX_PI / 180.0 * i/2.0;
        //        double x = owner.GetR() * std::cos(radian);
        //        double z = owner.GetR() * std::sin(radian);
        //        Math::Vector4 t = { x, 0.0, z };
        //        Math::Vector4 newpos = owner.GetPosition() + t;
        //        DrawPixel3D(ToDX(newpos), GetColor(255, 255, 0));

        //    }
        //
        //}


            //円の描画(一つ目が索敵範囲, 二つ目がハッキング範囲)
        for (double i = 0.0; i < 720.0; i++)
        {
            double radian = DX_PI / 180.0 * i / 2.0;
            double x = owner.GetR() * std::cos(radian);
            double z = owner.GetR() * std::sin(radian);
            double huckX = owner.GetHuckR() * std::cos(radian);
            double huckZ = owner.GetHuckR() * std::sin(radian);

            Math::Vector4 move = { x, 0.0, z };

            Math::Vector4 newpos = owner.GetPosition() + move;
            DrawPixel3D(ToDX(newpos), GetColor(0, 255, 0));

            move = { huckX, 0.0, huckZ };

            newpos = owner.GetPosition() + move;
            DrawPixel3D(ToDX(newpos), GetColor(0, 255, 0));

        }

        //hucking成功時
        if (_isHit)
        {

            //角度

            auto angle = range;
            auto rad = DX_PI / 180.0 * angle;

            auto sRad = 0.0; auto eRad = 0.0;

            if (select) {
                sRad = -rad + rotY + nine;
                eRad = rad + rotY + nine;
            }
            else {
                sRad = -rad + rotY + nineReverse;
                eRad = rad + rotY + nineReverse;
            }

            //double endAngle = 120.0;
            //double Rad = DX_PI / 180.0 * endAngle;
            //Rad = Rad + _rot_y;
            ////弧の左側の線
            Math::Vector4 move = { std::cos(eRad), 0.0, std::sin(eRad) };

            Math::Vector4 target;
            //索敵範囲は赤色
            if (select) {
                target = owner.GetPosition() + move * owner.GetR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 0, 0));
            }
            else {
                target = owner.GetPosition() + move * owner.GetHuckR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 255, 255));
            }

            //auto startAngle = 30.0;
            //Rad = DX_PI / 180.0 * startAngle;
            //Rad = Rad + _rot_y;
            ////弧の右側の線
            move = { std::cos(sRad), 0.0, std::sin(sRad) };
            target = owner.GetPosition() + move * owner.GetR();
            //索敵範囲は赤色
            if (select) {
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 0, 0));
            }
            else {
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 255, 255));
            }

            // auto yAngle = 180.0 / DX_PI * rotY;
             //円弧
            //for(double i = yAngle; i < abs(yAngle + Angle); i++)
            //{
            //        double radian = DX_PI / 180.0 * i/2.0;
            //        radian = radian + _rot_y;
            //        double x = owner.GetR() * std::cos(radian);
            //        double z = owner.GetR() * std::sin(radian);
            //        Math::Vector4 t = { x, 0.0, z };
            //        Math::Vector4 newpos = owner.GetPosition() + t;
            //        DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));
            //}

            //for (double i = yAngle; i < abs(yAngle - Angle); i--)
            //{
            //    double radian = DX_PI / 180.0 * i / 2.0;
            //    radian = radian + _rot_y;
            //    double x = owner.GetR() * std::cos(radian);
            //    double z = owner.GetR() * std::sin(radian);
            //    Math::Vector4 t = { x, 0.0, z };
            //    Math::Vector4 newpos = owner.GetPosition() + t;
            //    DrawPixel3D(ToDX(newpos), GetColor(255, 0, 0));
            //}

        }
        else //ハッキング失敗時
        {
            //角度

            auto angle = range;
            auto rad = DX_PI / 180.0 * angle;

            auto sRad = 0.0; auto eRad = 0.0;

            //索敵範囲(true), ハッキング範囲(false)
            if (select) {
                sRad = -rad + rotY + nine;
                eRad = rad + rotY + nine;
            }
            else {
                sRad = -rad + rotY + nineReverse;
                eRad = rad + rotY + nineReverse;
            }

            //double endAngle = 120.0;
            //double Rad = DX_PI / 180.0 * endAngle;
            //Rad = Rad + _rot_y;
            ////弧の左側の線
            Math::Vector4 move = { std::cos(eRad), 0.0, std::sin(eRad) };
            Math::Vector4 target;

            //索敵範囲(true), ハッキング範囲(false)
            if (select) {
                target = owner.GetPosition() + move * owner.GetR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 255, 0));
            }
            else {
                target = owner.GetPosition() + move * owner.GetHuckR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 0, 255));
            }

            //auto startAngle = 30.0;
            //Rad = DX_PI / 180.0 * startAngle;
            //Rad = Rad + _rot_y;
            ////弧の右側の線
            move = { std::cos(sRad), 0.0, std::sin(sRad) };

            //索敵範囲(true), ハッキング範囲(false)
            if (select) {
                target = owner.GetPosition() + move * owner.GetR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 255, 0));
            }
            else {
                target = owner.GetPosition() + move * owner.GetHuckR();
                DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 0, 255));
            }

            /*auto yAngle = 180.0 / DX_PI * rotY;*/
            //for (double i = startAngle; i < endangle; (endAngle- startAngle/100)を1ずつ足す) 
            //{
            // //auto target = _pos + GetR() * std::cos(i);
            //   auto target2 = _pos + GetR() * std::cos(i-1);
            //    DrawTriangle3D(ToDX(_pos), ToDX(target), ToDX(target2), GetColor(255, 255, 0), true);
            //}
        }




#endif
    }

    void ModelAnimeComponent::Draw(const Actor::Actor& owner, Math::Vector4 position) {
#ifdef _DEBUG

        auto pos = owner.GetPosition();

        auto target = position;

        auto dif = pos - target;

        //auto rotYYY = std::atan2(dif.GetZ(), dif.GetX());

        auto dir = owner.GetRotation();

        //atan2は、時計回りを正として実装しているため、向きが逆となるため符号をマイナスにしている
        auto rotY = -dir.GetY();

        //z軸を0度とするため
        auto nine = DX_PI / 180.0 * 90.0;

        auto rad = rotY + nine;

        //auto radian = rotYYY + nine;

        auto min = owner.GetMin();
        auto max = owner.GetMax();

        Math::Vector4 move = { std::cos(rad), 0.0, std::sin(rad) };

        //Math::Vector4 leftUp    = { min.GetX() + pos.GetX(), pos.GetY(), max.GetZ() + pos.GetZ() };
        //Math::Vector4 leftDown  = { min.GetX() + pos.GetX(), pos.GetY(), min.GetZ() + pos.GetZ() };
        //Math::Vector4 rightUp   = { max.GetX() + pos.GetX(), pos.GetY(), max.GetZ() + pos.GetZ() };
        //Math::Vector4 rightDown = { max.GetX() + pos.GetX(), pos.GetY(), min.GetZ() + pos.GetZ() };

        Math::Vector4 leftUp = { min.GetX(), 0.0, max.GetZ() };
        Math::Vector4 leftDown = { min.GetX(), 0.0, min.GetZ() };
        Math::Vector4 rightUp = { max.GetX(), 0.0, max.GetZ() };
        Math::Vector4 rightDown = { max.GetX(), 0.0, min.GetZ() };

        //auto difLU = leftUp - pos;
        ////auto difLD = leftDown - pos;
        ////auto difRU = rightUp - pos;
        ////auto difRD = rightDown - pos;

        //////全部同じとなるため
        //auto lULength = difLU.Length_XZ();
        //auto lDLength = difLD.Length_XZ();
        //auto rULength = difRU.Length_XZ();
        //auto rDLength = difRD.Length_XZ();
        //auto norm = difLU.Normalize();

        //lULength = norm.Length_XZ();
        ////auto lULength = pos.Length();
        ////auto lDLength = pos.Length();
        ////auto rULength = pos.Length();
        ////auto rDLength = pos.Length();

        //円の方から取ってきた
        //        ////弧の左側の線
        //Math::Vector4 move = { std::cos(eRad), 0.0, std::sin(eRad) };
        //auto target = owner.GetPosition() + move * owner.GetR();

        ////索敵範囲は黄色
        //if (select) {
        //    DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 255, 0));
        //}
        //else {
        //    DrawLine3D(ToDX(pos), ToDX(target), GetColor(255, 0, 255));
        //}

        //↓ここが原因

        auto Length = 1.0;

        //先に単位円上で回転させる
        auto leftUpX = (leftUp.GetX() * move.GetX() - leftUp.GetZ() * move.GetZ()) * Length;
        auto leftUpZ = (leftUp.GetX() * move.GetZ() + leftUp.GetZ() * move.GetX()) * Length;
        auto leftDownX = (leftDown.GetX() * move.GetX() - leftDown.GetZ() * move.GetZ()) * Length;
        auto leftDownZ = (leftDown.GetX() * move.GetZ() + leftDown.GetZ() * move.GetX()) * Length;
        auto rightUpX = (rightUp.GetX() * move.GetX() - rightUp.GetZ() * move.GetZ()) * Length;
        auto rightUpZ = (rightUp.GetX() * move.GetZ() + rightUp.GetZ() * move.GetX()) * Length;
        auto rightDownX = (rightDown.GetX() * move.GetX() - rightDown.GetZ() * move.GetZ()) * Length;
        auto rightDownZ = (rightDown.GetX() * move.GetZ() + rightDown.GetZ() * move.GetX()) * Length;

        //auto leftUpX    = (leftUp.GetX()    * move.GetX() - leftUp.GetZ()    * move.GetZ()) * lULength;
        //auto leftUpZ    = (leftUp.GetX()    * move.GetZ() + leftUp.GetZ()    * move.GetX()) * lULength;
        //auto leftDownX  = (leftDown.GetX()  * move.GetX() - leftDown.GetZ()  * move.GetZ()) * lULength;
        //auto leftDownZ  = (leftDown.GetX()  * move.GetZ() + leftDown.GetZ()  * move.GetX()) * lULength;
        //auto rightUpX   = (rightUp.GetX()   * move.GetX() - rightUp.GetZ()   * move.GetZ()) * lULength;
        //auto rightUpZ   = (rightUp.GetX()   * move.GetZ() + rightUp.GetZ()   * move.GetX()) * lULength;
        //auto rightDownX = (rightDown.GetX() * move.GetX() - rightDown.GetZ() * move.GetZ()) * lULength;
        //auto rightDownZ = (rightDown.GetX() * move.GetZ() + rightDown.GetZ() * move.GetX()) * lULength;

        //並行移動させて敵の座標に合わせる
        leftUp = { leftUpX + pos.GetX() , 0.0, leftUpZ + pos.GetZ() };
        leftDown = { leftDownX + pos.GetX() , 0.0, leftDownZ + pos.GetZ() };
        rightUp = { rightUpX + pos.GetX() , 0.0, rightUpZ + pos.GetZ() };
        rightDown = { rightDownX + pos.GetX() , 0.0, rightDownZ + pos.GetZ() };


        //leftDown  = leftDown  + move * lULength;
        //rightUp   = rightUp   + move * lULength;
        //rightDown = rightDown + move * lULength;


        DrawLine3D(ToDX(leftDown), ToDX(leftUp), GetColor(255, 0, 0));
        DrawLine3D(ToDX(leftDown), ToDX(rightDown), GetColor(255, 255, 0));
        DrawLine3D(ToDX(rightUp), ToDX(leftUp), GetColor(255, 255, 0));
        DrawLine3D(ToDX(rightDown), ToDX(rightUp), GetColor(255, 255, 0));


    }

    void ModelAnimeComponent::Draw(const Actor::Actor& owner, double r, double range) {
    
        //Math::Vector4 lmax = owner.GetLMax() + owner.GetPosition();
        //Math::Vector4 lmin = owner.GetLMin() + owner.GetPosition();

        //DrawLine3D(ToDX(lmin), ToDX(lmax), GetColor(255, 0, 0));

        auto pos = owner.GetPosition();

        auto dir = owner.GetRotation();

        //atan2は、時計回りを正として実装しているため、向きが逆となるため符号をマイナスにしている
        auto rotY = -dir.GetY();

        //z軸を0度とするため
        auto nine = DX_PI / 180.0 * 90.0;



        //円の描画
        for (double i = 0.0; i < 720.0; i++)
        {
            double radian = DX_PI / 180.0 * i / 2.0;
            double x = r * std::cos(radian);
            double z = r * std::sin(radian);

            Math::Vector4 move = { x, 0.0, z };

            Math::Vector4 newpos = owner.GetPosition() + move;
            DrawPixel3D(ToDX(newpos), GetColor(0, 255, 0));

        }



            //角度
            auto angle = range;
            auto rad = DX_PI / 180.0 * angle;

            auto sRad = 0.0; auto eRad = 0.0;

            sRad = -rad + rotY + nine;
            eRad = rad + rotY + nine;

            ////弧の左側の線
            Math::Vector4 move = { std::cos(eRad), 0.0, std::sin(eRad) };

            Math::Vector4 target;
            //索敵範囲は赤色
            target = owner.GetPosition() + move * r;
            DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));


            ////弧の右側の線
            move = { std::cos(sRad), 0.0, std::sin(sRad) };
            target = owner.GetPosition() + move * r;
            //索敵範囲は赤色
            DrawLine3D(ToDX(pos), ToDX(target), GetColor(0, 0, 255));

        
    
    }

#endif

    void ModelAnimeComponent::SpecificDraw() {

        //MV1SetFrameVisible(_handle, 23, false);
        MV1SetFrameVisible(_handle, 1, false);
        MV1DrawModel(_handle);
    }

    VECTOR ModelAnimeComponent::GetHeadPos(std::string frameName) {

        auto num = MV1SearchFrame(_handle, frameName.c_str());

       return  MV1GetFramePosition(_handle, num); //!< 頭のフレーム

    }

    /// アニメーションの変更
    void ModelAnimeComponent::ChangeAnime(std::string_view key, bool repeate) {
        auto newAnimIndex = _registry[key.data()];

        if (_animIndex == newAnimIndex) {
            return;
        }
        _animIndex = newAnimIndex;

        // アニメーションをデタッチする
        MV1DetachAnim(_handle, _attachIndex);
        // 新しいアニメーションをアタッチする
        _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
        // アタッチしたアニメーションの総再生時間を取得する
        _totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);

        _playTime = 0.0f;
        _repeatedCount = 0;
        _repeate = repeate;
    }
}


