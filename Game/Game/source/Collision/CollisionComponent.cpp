///
/// @file    CollisionComponent.cpp
/// @brief   コリジョン判定
/// @date    2021/12/6
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "CollisionComponent.h"

#include "../Actor/Actor.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"
#include <cmath>
#include <numbers>


//Sphere::Sphere(const Math::Vector4& center, float radius)
//  :center(center)
//  ,radius(radius) {
//}

//bool Sphere::Contains(const Math::Vector4& point) const {
//    auto sub = center - point;
//    auto distSq = std::pow(sub.Length(), 2.0);
//  return distSq <= (radius * radius);
//}

//bool Intersect(const Sphere& a, const Sphere& b)
//{
//  auto sub = a.center - b.center;
//  auto distSq = std::pow(sub.Length(), 2.0);
//  float sumRadii = a.radius + b.radius;
//  return distSq <= (sumRadii * sumRadii);
//}


namespace MachineHuck::Collision {

    CollisionComponent::CollisionComponent(Actor::Actor& owner) : _owner{ owner } {
        /*_report = std::make_unique<Report>();*/
    }

    //void CollisionComponent::EnemyFromPlayer() {
    //    // 右手のフレーム(28番)の位置に球を設定
    //    auto handle = _owner.GetModel().GetHandle();
    //    auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
    //    auto matt = ToMath(mat);
    //    Math::Vector4 zero = { 0.0, 0.0, 0.0 };
    //    Math::Vector4 pos = matt.VectorToTransform(zero, matt);
    //    //auto playerSphere = Sphere(pos, 20);

    //    //for (auto&& actor : _owner.GetActorServer().GetActors()) {
    //    //  if (actor->GetTypeId() != Actor::TypeId::Enemy) {
    //    //    continue;
    //    //  }
    //    //  if (actor->GetCollision().GetReport().id == ReportId::HitFromPlayer) {
    //    //    continue;
    //    //  }
    //    //  // エネミー側の球を設定※こっちはフレーム関係なく適当に
    //    //  auto enemySphere = Sphere(actor->GetPosition(), 50);
    //    //  Math::Vector4 center_y = { 0.0, 40, 0.0 };
    //    //  enemySphere.center = enemySphere.center + center_y; //　足元基準なので中心を40上げる
    //    //  // 球と球の衝突判定
    //    //  if (Intersect(playerSphere, enemySphere)) {
    //    //    actor->GetCollision().SetReport({ReportId::HitFromPlayer, _owner.GetPosition()});
    //    //    break;
    //    //  }
    //    //}
    //}

    //void CollisionComponent::PlayerFromEnemy() {
    //    // 牙のフレーム(28番)の位置に球を設定
    //    auto handle = _owner.GetModel().GetHandle();
    //    auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
    //    auto matt = ToMath(mat);
    //    Math::Vector4 zero = { 0.0, 0.0, 0.0 };
    //    auto pos = matt.VectorToTransform(zero, matt);
    //    //auto enemySphere = Sphere(pos, 20);

    //    //for (auto&& actor : _owner.GetActorServer().GetActors()) {
    //    //  if (actor->GetTypeId() != Actor::TypeId::Player) {
    //    //    continue;
    //    //  }
    //    //  if (actor->GetCollision().GetReport().id == ReportId::HitFromEnemy) {
    //    //    continue;
    //    //  }
    //    //  // プレイヤー側の球を設定※こっちはフレーム関係なく適当に
    //    //  auto playerSphere = Sphere(actor->GetPosition(), 50);
    //    //  Math::Vector4 center_y = { 0.0, 40, 0.0 };
    //    //  playerSphere.center = playerSphere.center + center_y;   //　足元基準なので中心を40上げる
    //    //  // 球と球の衝突判定
    //    //  if (Intersect(enemySphere, playerSphere)) {
    //    //    actor->GetCollision().SetReport({ReportId::HitFromEnemy, _owner.GetPosition()});
    //    //    break;
    //    //  }
    //    //}




    //}

    bool CollisionComponent::CircleToCircle(const Actor::Actor& act1, const Actor::Actor& act2)
    {
        _r1 = act1.GetR(); _r2 = act2.GetR();

        auto _differ_vec = act2.GetPosition() - act1.GetPosition();

        auto _length = _differ_vec.Length_XZ();

        if (_length < _r1 + _r2)
        {
            return true;
        }
        return false;

    }

    bool CollisionComponent::AABBToAABB(const Actor::Actor& act1, const Actor::Actor& act2)
    {

        if (act1.GetMax().GetX() + act1.GetPosition().GetX() < act2.GetMin().GetX() + act2.GetPosition().GetX() ||
            act1.GetMax().GetZ() + act1.GetPosition().GetZ() < act2.GetMin().GetZ() + act2.GetPosition().GetZ() ||
            act2.GetMax().GetX() + act2.GetPosition().GetX() < act1.GetMin().GetX() + act1.GetPosition().GetX() ||
            act2.GetMax().GetZ() + act2.GetPosition().GetZ() < act1.GetMin().GetZ() + act1.GetPosition().GetZ())
        {
            return false;
        }
        return true;

    }

    bool CollisionComponent::CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2)
    {
        //主人公が球act1, 相手がAABB act2
        //double dx1 = act2.GetMin().GetX() - act1.GetMin().GetX(); //!< minが左側にある
        auto pos = act2.GetPosition();
        auto circlePos = act1.GetPosition();

        auto min = act2.GetMin();
        auto max = act2.GetMax();

        //double dx1 = act2.GetPosition().GetX() + act2.GetMin().GetX() - act1.GetPosition().GetX();
        //double dx2 = act1.GetPosition().GetX() - (act2.GetPosition().GetX() + act2.GetMax().GetX()) ;

        double dx1 = pos.GetX() + min.GetX() - circlePos.GetX();
        double dx2 = circlePos.GetX() - (pos.GetX() + max.GetX());

        dx1 = dx1 > 0.0 ? dx1 : 0.0;
        dx2 = dx1 > dx2 ? dx1 : dx2;
        //double dx2 = abs(act2.GetMin().GetX() - act1.GetMax().GetX()); //!< minが中にあるため右にずらす

        //double dz1 = act2.GetPosition().GetZ() + act2.GetMin().GetZ() - act1.GetPosition().GetZ();
        //double dz2 = act1.GetPosition().GetZ() - (act2.GetPosition().GetZ() + act2.GetMax().GetZ());
        double dz1 = pos.GetZ() + min.GetZ() - circlePos.GetZ();
        double dz2 = circlePos.GetZ() - (pos.GetZ() + max.GetZ());

        dz1 = dz1 > 0.0 ? dz1 : 0.0;
        dz2 = dz1 > dz2 ? dz1 : dz2;

        double distance = dx2 * dx2 + dz2 * dz2;
        auto length = act1.GetR() * act1.GetR();
        if (distance < length)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool CollisionComponent::CicrleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2) {

        auto dir = act2.GetRotation();

        //atan2は、時計回りを正として実装しているため、向きが逆となるため符号をマイナスにしている
        auto rotY = -dir.GetY();

        //z軸を0度とするため
        auto nine = std::numbers::pi / 180.0 * 90.0;

        auto rad = rotY + nine;

        Math::Vector4 move = { std::cos(rad), 0.0, std::sin(rad) };

        auto pos = act2.GetPosition();
        auto circlePos = act1.GetPosition();

        auto min = act2.GetMin();
        auto max = act2.GetMax();

        //Math::Vector4 leftUp = { min.GetX(), 0.0, max.GetZ()};
        //Math::Vector4 leftDown = { min.GetX(), 0.0, min.GetZ()};
        //Math::Vector4 rightUp = { max.GetX(), 0.0, max.GetZ()};
        //Math::Vector4 rightDown = { max.GetX(), 0.0, min.GetZ()};

        auto Length = 1.0;

        //先に単位円上で回転させる
        //auto leftUpX = (leftUp.GetX() * move.GetX() - leftUp.GetZ() * move.GetZ()) * Length;
        //auto leftUpZ = (leftUp.GetX() * move.GetZ() + leftUp.GetZ() * move.GetX()) * Length;
        //auto leftDownX = (leftDown.GetX() * move.GetX() - leftDown.GetZ() * move.GetZ()) * Length;
        //auto leftDownZ = (leftDown.GetX() * move.GetZ() + leftDown.GetZ() * move.GetX()) * Length;
        //auto rightUpZ = (rightUp.GetX() * move.GetZ() + rightUp.GetZ() * move.GetX()) * Length;
        //auto rightUpX = (rightUp.GetX() * move.GetX() - rightUp.GetZ() * move.GetZ()) * Length;
        //auto rightDownX = (rightDown.GetX() * move.GetX() - rightDown.GetZ() * move.GetZ()) * Length;
        //auto rightDownZ = (rightDown.GetX() * move.GetZ() + rightDown.GetZ() * move.GetX()) * Length;

        //先に単位円上で回転させる
        auto leftUpX = (min.GetX() * move.GetX() - max.GetZ() * move.GetZ()) * Length;
        auto leftUpZ = (min.GetX() * move.GetZ() + max.GetZ() * move.GetX()) * Length;
        auto leftDownX = (min.GetX() * move.GetX() - min.GetZ() * move.GetZ()) * Length;
        auto leftDownZ = (min.GetX() * move.GetZ() + min.GetZ() * move.GetX()) * Length;
        auto rightUpZ = (max.GetX() * move.GetZ() + max.GetZ() * move.GetX()) * Length;
        auto rightUpX = (max.GetX() * move.GetX() - max.GetZ() * move.GetZ()) * Length;
        auto rightDownX = (max.GetX() * move.GetX() - min.GetZ() * move.GetZ()) * Length;
        auto rightDownZ = (max.GetX() * move.GetZ() + min.GetZ() * move.GetX()) * Length;

        //回転させた点を敵座標に並行移動
        //leftUp = { leftUpX + pos.GetX() , 0.0, leftUpZ + pos.GetZ() };
        //leftDown = { leftDownX + pos.GetX() , 0.0, leftDownZ + pos.GetZ() };
        //rightUp = { rightUpX + pos.GetX() , 0.0, rightUpZ + pos.GetZ() };
        //rightDown = { rightDownX + pos.GetX() , 0.0, rightDownZ + pos.GetZ() };

        //auto leftDownToLeftUp      = leftUp - leftDown;
        //auto leftUpToRightUp       = rightUp - leftUp;
        //auto rightUpToRightDown    = rightDown - rightUp;
        //auto rightDownToLeftDown   = leftDown - rightDown;

        //auto leftDownToCirclePos  = circlePos - leftDown;
        //auto leftUpToCirclePos    = circlePos - leftUp;
        //auto rightUpToCirclePos   = circlePos - rightUp;
        //auto rightDownToCirclePos = circlePos - rightDown;

        //円の中心点
        Math::Vector2 circlePosXZ = { act1.GetPosition().GetX(), act1.GetPosition().GetZ() };

        //回転させた点を敵座標に並行移動
        Math::Vector2 leftUpXZ = { leftUpX + pos.GetX(), leftUpZ + pos.GetZ() };
        Math::Vector2 leftDownXZ = { leftDownX + pos.GetX(), leftDownZ + pos.GetZ() };
        Math::Vector2 rightUpXZ = { rightUpX + pos.GetX(), rightUpZ + pos.GetZ() };
        Math::Vector2 rightDownXZ = { rightDownX + pos.GetX(), rightDownZ + pos.GetZ() };

        auto leftDownToLeftUp = leftUpXZ - leftDownXZ;
        auto leftUpToRightUp = rightUpXZ - leftUpXZ;
        auto rightUpToRightDown = rightDownXZ - rightUpXZ;
        auto rightDownToLeftDown = leftDownXZ - rightDownXZ;

        auto leftDownToCirclePos = circlePosXZ - leftDownXZ;
        auto leftUpToCirclePos = circlePosXZ - leftUpXZ;
        auto rightUpToCirclePos = circlePosXZ - rightUpXZ;
        auto rightDownToCirclePos = circlePosXZ - rightDownXZ;

        std::pair<Math::Vector2, Math::Vector2> data[] = {
            {leftDownToLeftUp, leftDownToCirclePos},
            {leftUpToRightUp, leftUpToCirclePos},
            {rightUpToRightDown, rightUpToCirclePos},
            {rightDownToLeftDown, rightDownToCirclePos}

        };

        ////AABBのminXを出す
        //auto AABBminX = leftUpXZ.GetX() < leftDownXZ.GetX() ? leftUpXZ.GetX() : leftDownXZ.GetX();
        //AABBminX = AABBminX < rightUpXZ.GetX() ? AABBminX : rightUpXZ.GetX();
        //AABBminX = AABBminX < rightDownXZ.GetX() ? AABBminX : rightDownXZ.GetX();

        ////AABBのminZを出す
        //auto AABBminZ = leftUpXZ.GetZ() < leftDownXZ.GetZ() ? leftUpXZ.GetZ() : leftDownXZ.GetZ();
        //AABBminZ = AABBminZ < rightUpXZ.GetZ() ? AABBminX : rightUpXZ.GetZ();
        //AABBminZ = AABBminZ < rightDownXZ.GetZ() ? AABBminX : rightDownXZ.GetZ();

        ////AABBのmaxXを出す
        //auto AABBmaxX = leftUpXZ.GetX() > leftDownXZ.GetX() ? leftUpXZ.GetX() : leftDownXZ.GetX();
        //AABBmaxX = AABBmaxX > rightUpXZ.GetX() ? AABBminX : rightUpXZ.GetX();
        //AABBmaxX = AABBmaxX > rightDownXZ.GetX() ? AABBminX : rightDownXZ.GetX();

        ////AABBのmaxZを出す
        //auto AABBmaxZ = leftUpXZ.GetZ() > leftDownXZ.GetZ() ? leftUpXZ.GetZ() : leftDownXZ.GetZ();
        //AABBmaxZ = AABBmaxZ > rightUpXZ.GetZ() ? AABBminX : rightUpXZ.GetZ();
        //AABBmaxZ = AABBmaxZ > rightDownXZ.GetZ() ? AABBminX : rightDownXZ.GetZ();



        ////double dx1 = pos.GetX() + min.GetX() - circlePos.GetX();
        ////double dx2 = circlePos.GetX() - (pos.GetX() + max.GetX());

        //double dx1 = AABBminX - circlePos.GetX();
        //double dx2 = circlePos.GetX() - AABBmaxX;

        //dx1 = dx1 > 0.0 ? dx1 : 0.0;
        //dx2 = dx1 > dx2 ? dx1 : dx2;
        //
        ////dx1 = dx1 < dx2 ? dx1 : dx2;
        //
        ////double dx2 = abs(act2.GetMin().GetX() - act1.GetMax().GetX()); //!< minが中にあるため右にずらす

        ////double dz1 = act2.GetPosition().GetZ() + act2.GetMin().GetZ() - act1.GetPosition().GetZ();
        ////double dz2 = act1.GetPosition().GetZ() - (act2.GetPosition().GetZ() + act2.GetMax().GetZ());

        //double dz1 = AABBminZ - circlePos.GetZ();
        //double dz2 = circlePos.GetZ() - AABBmaxZ;

        //dz1 = dz1 > 0.0 ? dz1 : 0.0;
        //dz2 = dz1 > dz2 ? dz1 : dz2;

        //double distance = dx2 * dx2 + dz2 * dz2;
        //auto length = act1.GetR() * act1.GetR();
        //if (distance < length)
        //{
        //    return true;
        //}
        //else
        //{
        //    return false;
        //}


        for (int i = 0; i < 4; i++) {

            auto cross = data[i].first.Cross(data[i].second);

            //円の中心が中にある
            if (0 > cross) {
                return true;
            }

        }

        auto distance = circlePos - pos;
        auto length = distance.Length_XZ();

        // if(act1.GetR() + )



         //円の中心が外にある
        return false;

    }


    bool CollisionComponent::CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2)
    {
        Math::Vector4 Start = act2.GetLMin() + act2.GetPosition() - act1.GetPosition();
        Math::Vector4 End = act2.GetLMax() + act2.GetPosition() - act1.GetPosition();
        double a = End.Dot(End);
        double b = 2.0 * Start.Dot(End);
        double c = Start.Dot(Start) - act1.GetR() * act1.GetR();

        double disc = b * b - 4.0f * a * c;

        if (disc < 0.0f)
        {
            return false;
        }
        else
        {
            disc = std::sqrt(disc);

            double tMin = (-b - disc) / (2.0 * a);
            double tMax = (-b + disc) / (2.0 * a);
            if (tMin >= 0.0 && tMin <= 1.0)
            {
                //  outT = tMin;
                return true;
            }
            else if (tMax >= 0.0 && tMax <= 1.0)
            {
                //  outT = tMax;
                return true;
            }
            else
            {
                return false;
            }
        }

        return false;
    }

    bool CollisionComponent::CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2)
    {

        auto dir = act1.GetRotation();

        //y軸回転の向きが時計回りにセットされているため逆回りにする
        auto rotY = -dir.GetY();

        //範囲
        auto angle = act1.GetSearchRange();

        //0度をz軸に
        auto nine = std::numbers::pi / 180.0 * 90.0;

        //ラジアンに変換
        auto rad = std::numbers::pi / 180.0 * angle;

        //円弧の開始角度
        auto sRad = -rad + nine + rotY;
        //円弧の終了角度
        auto eRad = rad + nine + rotY;


        //主人公から敵へのベクトル
        auto dis = act2.GetPosition() - act1.GetPosition();
        auto length = dis.Length();


        Math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
        Math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

        auto cross180 = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
        auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
        auto crossEnd = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

        //円の内外判定
        if (length < act1.GetR())
        {
            //扇形の角度が180度を超えているか
            if (cross180 > 0)
            {
                //開始角に対して左にあるか//////////////////←個々の中に入っていない
                if (crossStart < 0)
                {
                    return false;
                }//終了角に対して右にあるか

                if (crossEnd > 0)
                {
                    return false;
                }

                //扇の内部にある
                return true;


            }
            else
            {   //開始角に対して左にあるか
                if (crossStart <= 0)
                {
                    return true;
                }//終了角に対して右にあるか

                if (crossEnd >= 0)
                {
                    return true;
                }

                //扇の外部にある
                return false;
            }

        }

        return false;
    }


    bool CollisionComponent::CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2, bool select)
    {
        auto range = 0.0;

        //索敵範囲かどうか
        if (select) {
            range = act1.GetR();
        }
        else {
            range = act1.GetHuckR();
        }


        auto dir = act1.GetRotation();

        //y軸回転の向きが時計回りにセットされているため逆回りにする
        auto rotY = -dir.GetY();

        //範囲
        auto angle = 0.0;

        if (select) {
            angle = act1.GetSearchRange();
        }
        else {
            angle = act1.GetHuckingRange();
        }


        //0度をz軸に
        auto nine = std::numbers::pi / 180.0 * 90.0;

        //ラジアンに変換
        auto rad = std::numbers::pi / 180.0 * angle;

        auto sRad = 0.0; auto eRad = 0.0;

        //索敵範囲かどうか
        if (select) {

            //円弧の開始角度
            sRad = -rad + nine + rotY;
            //円弧の終了角度
            eRad = rad + nine + rotY;
        }
        else {//ハッキング範囲

            //円弧の開始角度
            sRad = -rad - nine + rotY;
            //円弧の終了角度
            eRad = rad - nine + rotY;

        }



        //主人公から敵へのベクトル
        auto dis = act2.GetPosition() - act1.GetPosition();
        auto length = dis.Length();


        Math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
        Math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

        auto cross180 = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
        auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
        auto crossEnd = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

        //円の内外判定
        if (length < range)
        {
            //扇形の角度が180度を超えているか
            if (cross180 > 0)
            {
                //開始角に対して左にあるか//////////////////←個々の中に入っていない
                if (crossStart < 0)
                {
                    return false;
                }//終了角に対して右にあるか

                if (crossEnd > 0)
                {
                    return false;
                }

                //扇の内部にある
                return true;


            }
            else
            {   //開始角に対して左にあるか
                if (crossStart <= 0)
                {
                    return true;
                }//終了角に対して右にあるか

                if (crossEnd >= 0)
                {
                    return true;
                }

                //扇の外部にある
                return false;
            }

        }

        return false;
    }

    bool CollisionComponent::LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2) {

        return false;
    }

    bool CollisionComponent::TestSidePlane(const double start, double const end, double const negd) {

        return false;
    }
}

