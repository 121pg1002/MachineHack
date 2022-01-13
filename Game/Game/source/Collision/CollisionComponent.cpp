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

Sphere::Sphere(const math::Vector4& center, float radius)
  :center(center)
  ,radius(radius) {
}

bool Sphere::Contains(const math::Vector4& point) const {
    auto sub = center - point;
    auto distSq = std::pow(sub.Length(), 2.0);
  return distSq <= (radius * radius);
}

bool Intersect(const Sphere& a, const Sphere& b)
{
  auto sub = a.center - b.center;
  auto distSq = std::pow(sub.Length(), 2.0);
  float sumRadii = a.radius + b.radius;
  return distSq <= (sumRadii * sumRadii);
}

CollisionComponent::CollisionComponent(Actor& owner): _owner{owner} {
  _report = std::make_unique<Report>();
}

void CollisionComponent::EnemyFromPlayer() {
   // 右手のフレーム(28番)の位置に球を設定
  auto handle = _owner.GetModel().GetHandle();
  auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
  auto matt   = ToMath(mat);
  math::Vector4 zero = { 0.0, 0.0, 0.0 };
  math::Vector4 pos = matt.VectorToTransform(zero, matt);
  auto playerSphere = Sphere(pos, 20);

  //for (auto&& actor : _owner.GetActorServer().GetActors()) {
  //  if (actor->GetTypeId() != Actor::TypeId::Enemy) {
  //    continue;
  //  }
  //  if (actor->GetCollision().GetReport().id == ReportId::HitFromPlayer) {
  //    continue;
  //  }
  //  // エネミー側の球を設定※こっちはフレーム関係なく適当に
  //  auto enemySphere = Sphere(actor->GetPosition(), 50);
  //  math::Vector4 center_y = { 0.0, 40, 0.0 };
  //  enemySphere.center = enemySphere.center + center_y; //　足元基準なので中心を40上げる
  //  // 球と球の衝突判定
  //  if (Intersect(playerSphere, enemySphere)) {
  //    actor->GetCollision().SetReport({ReportId::HitFromPlayer, _owner.GetPosition()});
  //    break;
  //  }
  //}
}

void CollisionComponent::PlayerFromEnemy() {
  // 牙のフレーム(28番)の位置に球を設定
  auto handle = _owner.GetModel().GetHandle();
  auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
  auto matt = ToMath(mat);
  math::Vector4 zero = { 0.0, 0.0, 0.0 };
  auto pos = matt.VectorToTransform(zero, matt);
  auto enemySphere = Sphere(pos, 20);

  //for (auto&& actor : _owner.GetActorServer().GetActors()) {
  //  if (actor->GetTypeId() != Actor::TypeId::Player) {
  //    continue;
  //  }
  //  if (actor->GetCollision().GetReport().id == ReportId::HitFromEnemy) {
  //    continue;
  //  }
  //  // プレイヤー側の球を設定※こっちはフレーム関係なく適当に
  //  auto playerSphere = Sphere(actor->GetPosition(), 50);
  //  math::Vector4 center_y = { 0.0, 40, 0.0 };
  //  playerSphere.center = playerSphere.center + center_y;   //　足元基準なので中心を40上げる
  //  // 球と球の衝突判定
  //  if (Intersect(enemySphere, playerSphere)) {
  //    actor->GetCollision().SetReport({ReportId::HitFromEnemy, _owner.GetPosition()});
  //    break;
  //  }
  //}




}

bool CollisionComponent::CircleToCircle(const Actor& act1, const Actor& act2)
{
    _r1 = act1.Get_r(); _r2 = act2.Get_r();

    auto _differ_vec = act2.GetPosition() - act1.GetPosition();

    auto _length = _differ_vec.Length_XZ();

    if (_length < _r1 + _r2)
    {
        return true;
    }
    return false;

}

bool CollisionComponent::AABBToAABB(const Actor& act1, const Actor& act2)
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

bool CollisionComponent::CircleToAABB(const Actor& act1, const Actor& act2)
{
    //主人公が球act1, 相手がAABB act2
    //double dx1 = act2.GetMin().GetX() - act1.GetMin().GetX(); //!< minが左側にある
    double dx1 = act2.GetPosition().GetX() + act2.GetMin().GetX() - act1.GetPosition().GetX();
    double dx2 = act1.GetPosition().GetX() - (act2.GetPosition().GetX() + act2.GetMax().GetX()) ;
    dx1 = dx1 > 0.0 ? dx1 : 0.0;
    dx2 = dx1 > dx2 ? dx1 : dx2;
    //double dx2 = abs(act2.GetMin().GetX() - act1.GetMax().GetX()); //!< minが中にあるため右にずらす
    
    double dz1 = act2.GetPosition().GetZ() + act2.GetMin().GetZ() - act1.GetPosition().GetZ();
    double dz2 = act1.GetPosition().GetZ() - (act2.GetPosition().GetZ() + act2.GetMax().GetZ());
    dz1 = dz1 > 0.0 ? dz1 : 0.0;
    dz2 = dz1 > dz2 ? dz1 : dz2;

    double distance = dx2 * dx2 + dz2 * dz2;
    if (distance < act1.Get_r()) 
    {
     return true;
    }
    else
    {
    return false;
    }
}

bool CollisionComponent::CircleToLine(const Actor& act1, const Actor& act2) 
{
    math::Vector4 Start = act2.GetLMin() + act2.GetPosition() - act1.GetPosition();
    math::Vector4 End = act2.GetLMax() + act2.GetPosition() - act1.GetPosition();
    double a = End.Dot(End);
    double b = 2.0 * Start.Dot(End);
    double c = Start.Dot(Start) - act1.Get_r() * act1.Get_r();

    double disc = b * b - 4.0f * a * c;

    if(disc < 0.0f)
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

bool CollisionComponent::CircleToFan(const Actor& act1, const Actor& act2)
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


    math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
    math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

    auto cross180   = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
    auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
    auto crossEnd   = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

    //円の内外判定
    if (length < act1.Get_r())
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
