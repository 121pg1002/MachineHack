/*****************************************************************//**
 * @file   CollisionComponent.cpp
 * @brief  �Փ˔���N���X
 *
 * @author yamawaki kota, hikaru goto
 * @date   December 19 2021
 *********************************************************************/

#include "CollisionComponent.h"
#include <cmath>
//#include <numbers>
#include <DxLib.h>
#include "../Actor/Actor.h"
#include "../Actor/ActorServer.h"
#include "../Model/ModelAnimComponent.h"



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
        _frameMapCollision = 0;
        _frameGimmickCollision = 0;
        _frameMap.clear();
        _frameGimmick.clear();
        _warpNameMap.clear();
        _warpMap.clear();
        _floorNums.push_back(0);

        // _frameMapCollisions.clear();

        /*_report = std::make_unique<Report>();*/
    }

    CollisionComponent::~CollisionComponent() {
        _frameMap.clear();
        _frameGimmick.clear();
        _warpNameMap.clear();
        _warpMap.clear();
    }

    //void CollisionComponent::EnemyFromPlayer() {
    //    // �E��̃t���[��(28��)�̈ʒu�ɋ���ݒ�
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
    //    //  // �G�l�~�[���̋���ݒ聦�������̓t���[���֌W�Ȃ��K����
    //    //  auto enemySphere = Sphere(actor->GetPosition(), 50);
    //    //  Math::Vector4 center_y = { 0.0, 40, 0.0 };
    //    //  enemySphere.center = enemySphere.center + center_y; //�@������Ȃ̂Œ��S��40�グ��
    //    //  // ���Ƌ��̏Փ˔���
    //    //  if (Intersect(playerSphere, enemySphere)) {
    //    //    actor->GetCollision().SetReport({ReportId::HitFromPlayer, _owner.GetPosition()});
    //    //    break;
    //    //  }
    //    //}
    //}

    //void CollisionComponent::PlayerFromEnemy() {
    //    // ��̃t���[��(28��)�̈ʒu�ɋ���ݒ�
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
    //    //  // �v���C���[���̋���ݒ聦�������̓t���[���֌W�Ȃ��K����
    //    //  auto playerSphere = Sphere(actor->GetPosition(), 50);
    //    //  Math::Vector4 center_y = { 0.0, 40, 0.0 };
    //    //  playerSphere.center = playerSphere.center + center_y;   //�@������Ȃ̂Œ��S��40�グ��
    //    //  // ���Ƌ��̏Փ˔���
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



    //std::pair<Math::Vector2, Math::Vector2> CollisionComponent::GetOrientedRectangleEdge(Math::Vector4 center, Math::Vector2 halfExtends, double rot, int point) {
    //
    //    Math::Vector2 startPos = {0.0, 0.0};
    //    Math::Vector2 endPos   = {0.0, 0.0};

    //    std::pair<Math::Vector2, Math::Vector2> edge = std::make_pair(startPos, endPos);
    //    auto vecA = halfExtends;
    //    auto vecB = halfExtends;

    //    // �E���Ŏ擾����
    //    // 0,2
    //    // 1,3�͑Εӂ�\��
    //    switch (point % 4) {
    //    case 0:
    //        vecA.SetX(-vecA.GetX());
    //        break;
    //    case 1:
    //        vecB.SetZ(-vecB.GetZ());
    //        break;
    //    case 2:
    //        vecA.SetZ(-vecA.GetZ());
    //        vecB = GetNeGateVector(vecB);
    //            break;
    //    case 3:
    //        vecA = GetNeGateVector(vecA);
    //        vecB.SetX(-vecB.GetX());
    //        break;
    //    }

    //    vecA = GetRotateVector(vecA, rot);
    //    vecA = GetAddVector(vecA, center);

    //    vecB = GetRotateVector(vecB, rot);
    //    vecB = getAddVector(vecB, center);

    //    edge.point1 = vecA;
    //    edge.point2 = vecB;
    //    return edge;

    //}

    //�t�x�N�g����Ԃ�
    //Math::Vector2 CollisionComponent::GetNeGateVector(Math::Vector2 vec) {
    //
    //    vec.SetX(-vec.GetX());
    //    vec.SetZ(-vec.GetZ());

    //    return vec;
    //}

    //Math::Vector2 CollisionComponent::GetRotateVector(Math::Vector2 vec, double radian) {
    //
    //    var sin = std::sin(radian);
    //    var cos = std::cos(radian);

    //    var r = new Vector2D();
    //    r.x = vec.x * cos - vec.y * sin;
    //    r.y = vec.x * sin + vec.y * cos;

    //    return r;
    //
    //}


    bool CollisionComponent::CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2)
    {
        //��l������act1, ���肪AABB act2
        //double dx1 = act2.GetMin().GetX() - act1.GetMin().GetX(); //!< min�������ɂ���
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
        //double dx2 = abs(act2.GetMin().GetX() - act1.GetMax().GetX()); //!< min�����ɂ��邽�߉E�ɂ��炷

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


    bool CollisionComponent::CircleToAABB(const Actor::Actor& act, const AppFrame::Math::Vector4 min, const AppFrame::Math::Vector4 max)
    {
        //��l������act1, ���肪AABB act2
        //double dx1 = act2.GetMin().GetX() - act1.GetMin().GetX(); //!< min�������ɂ���
        //auto pos = (max + min) / 2;
       const auto& circlePos = act.GetPosition();

        //auto min = act2.GetMin();
        //auto max = act2.GetMax();

        //double dx1 = act2.GetPosition().GetX() + act2.GetMin().GetX() - act1.GetPosition().GetX();
        //double dx2 = act1.GetPosition().GetX() - (act2.GetPosition().GetX() + act2.GetMax().GetX());

        double dx1 = min.GetX() - circlePos.GetX();
        double dx2 = circlePos.GetX() - max.GetX();

        dx1 = dx1 > 0.0 ? dx1 : 0.0;
        dx2 = dx1 > dx2 ? dx1 : dx2;
        //double dx2 = abs(act2.GetMin().GetX() - act1.GetMax().GetX()); //!< min�����ɂ��邽�߉E�ɂ��炷

        //double dz1 = act2.GetPosition().GetZ() + act2.GetMin().GetZ() - act1.GetPosition().GetZ();
        //double dz2 = act1.GetPosition().GetZ() - (act2.GetPosition().GetZ() + act2.GetMax().GetZ());
        double dz1 = min.GetZ() - circlePos.GetZ();
        double dz2 = circlePos.GetZ() - max.GetZ();

        dz1 = dz1 > 0.0 ? dz1 : 0.0;
        dz2 = dz1 > dz2 ? dz1 : dz2;

        double distance = dx2 * dx2 + dz2 * dz2;
        auto length = act.GetR() * act.GetR();
        if (distance < length)
        {
            return true;
        }
        else
        {
            return false;
        }
    }




    bool CollisionComponent::CircleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2) {

        //��`�̉�]�p�x
        auto dir = act2.GetRotation();

        //atan2�́A���v���𐳂Ƃ��Ď������Ă��邽�߁A�������t�ƂȂ邽�ߕ������}�C�i�X�ɂ��Ă���
        auto rotY = -dir.GetY();

        //z����0�x�Ƃ��邽��
        auto nine = DX_PI / 180.0 * 90.0;
        auto rad = rotY + nine;

        //��]�ɂ��ړ���
        Math::Vector4 move = { std::cos(rad), 0.0, std::sin(rad) };

        //��`�̈ʒu
        auto pos = act2.GetPosition();
        //�~�̈ʒu
        auto circlePos = act1.GetPosition();

        //��`�̍ŏ��_
        auto min = act2.GetMin();

        //��`�̍ő�_
        auto max = act2.GetMax();

        //��ɒP�ʉ~��ŉ�]������
        auto leftUpX    = min.GetX() * move.GetX() - max.GetZ() * move.GetZ();
        auto leftUpZ    = min.GetX() * move.GetZ() + max.GetZ() * move.GetX();
        auto leftDownX  = min.GetX() * move.GetX() - min.GetZ() * move.GetZ();
        auto leftDownZ  = min.GetX() * move.GetZ() + min.GetZ() * move.GetX();
        auto rightUpZ   = max.GetX() * move.GetZ() + max.GetZ() * move.GetX();
        auto rightUpX   = max.GetX() * move.GetX() - max.GetZ() * move.GetZ();
        auto rightDownX = max.GetX() * move.GetX() - min.GetZ() * move.GetZ();
        auto rightDownZ = max.GetX() * move.GetZ() + min.GetZ() * move.GetX();

        //�~�̒��S�_
        //Math::Vector2 circlePosXZ = { act1.GetPosition().GetX(), act1.GetPosition().GetZ() };

        //��]�������_��G���W�ɕ��s�ړ�
        Math::Vector4 leftUp =    { leftUpX    + pos.GetX(), pos.GetY(), leftUpZ    + pos.GetZ() };
        Math::Vector4 leftDown =  { leftDownX  + pos.GetX(), pos.GetY(), leftDownZ  + pos.GetZ() };
        Math::Vector4 rightUp =   { rightUpX   + pos.GetX(), pos.GetY(), rightUpZ   + pos.GetZ() };
        Math::Vector4 rightDown = { rightDownX + pos.GetX(), pos.GetY(), rightDownZ + pos.GetZ() };

        //�~�̒��S���l�p�`�̒��ɂ���ꍇ
        auto first = AppFrame::Math::Utility::InsideTrianglePoint(leftDown, leftUp, rightDown, circlePos);
        auto second = AppFrame::Math::Utility::InsideTrianglePoint(rightDown, leftUp, rightUp, circlePos);

        if (first || second) {
                return true;
        }

        //�~�̒��S���l�p�`�̊O�ɂ���ꍇ
        if (CircleToLine(act1, leftDown, leftUp)) {
            return true;
        }

        if (CircleToLine(act1, leftUp, rightUp)) {
            return true;
        }

        if (CircleToLine(act1, rightUp, rightDown)) {
            return true;
        }

        if (CircleToLine(act1, rightDown, leftDown)) {
            return true;
        }
        
           //�������Ă��Ȃ�
            return false;
        

    }

    bool CollisionComponent::AABBToOrientedAABB(const Actor::Actor& own, const Actor::Actor& target) {

        //��`�̉�]�p�x
        auto dir = target.GetRotation();

        
        auto rotY = dir.GetY();

        //z����0�x�Ƃ��邽��
        auto nine = DX_PI / 180.0 * 90.0;
        auto rad = rotY + nine;

        //��]�ɂ��ړ���
        Math::Vector4 move = { std::cos(rad), 0.0, std::sin(rad) };

        //��]��`�̈ʒu
        auto pos = target.GetPosition();
        //AABB�̒��S�ʒu
        //auto center = target.GetPosition();

        //��`�̍ŏ��_
        auto min = target.GetMin();

        //��`�̍ő�_
        auto max = target.GetMax();

        //��ɒP�ʉ~��ŉ�]������
        auto leftUpX = min.GetX() * move.GetX() - max.GetZ() * move.GetZ();
        auto leftUpZ = min.GetX() * move.GetZ() + max.GetZ() * move.GetX();
        auto leftDownX = min.GetX() * move.GetX() - min.GetZ() * move.GetZ();
        auto leftDownZ = min.GetX() * move.GetZ() + min.GetZ() * move.GetX();
        auto rightUpZ = max.GetX() * move.GetZ() + max.GetZ() * move.GetX();
        auto rightUpX = max.GetX() * move.GetX() - max.GetZ() * move.GetZ();
        auto rightDownX = max.GetX() * move.GetX() - min.GetZ() * move.GetZ();
        auto rightDownZ = max.GetX() * move.GetZ() + min.GetZ() * move.GetX();

        //AABB�̒��S�_
        Math::Vector2 AABBCenterXZ = { own.GetPosition().GetX(), own.GetPosition().GetZ() };

        ////��]�������_��G���W�ɕ��s�ړ�
        //Math::Vector4 leftUp = { leftUpX + pos.GetX(), pos.GetY(), leftUpZ + pos.GetZ() };
        //Math::Vector4 leftDown = { leftDownX + pos.GetX(), pos.GetY(), leftDownZ + pos.GetZ() };
        //Math::Vector4 rightUp = { rightUpX + pos.GetX(), pos.GetY(), rightUpZ + pos.GetZ() };
        //Math::Vector4 rightDown = { rightDownX + pos.GetX(), pos.GetY(), rightDownZ + pos.GetZ() };


        //Math::Vector4 leftUp = { leftUpX + pos.GetX(), pos.GetY(), leftUpZ + pos.GetZ() };
        //Math::Vector4 leftDown = { leftDownX + pos.GetX(), pos.GetY(), leftDownZ + pos.GetZ() };
        //Math::Vector4 rightUp = { rightUpX + pos.GetX(), pos.GetY(), rightUpZ + pos.GetZ() };
        //Math::Vector4 rightDown = { rightDownX + pos.GetX(), pos.GetY(), rightDownZ + pos.GetZ() };


        //��]�������_�𕽍s�ړ�
        Math::Vector2 leftUpXZ =    { leftUpX + pos.GetX(),    leftUpZ + pos.GetZ() };
        Math::Vector2 leftDownXZ =  { leftDownX + pos.GetX(),  leftDownZ + pos.GetZ() };
        Math::Vector2 rightUpXZ =   { rightUpX + pos.GetX(),   rightUpZ + pos.GetZ() };
        Math::Vector2 rightDownXZ = { rightDownX + pos.GetX(), rightDownZ + pos.GetZ() };

        //AABB�̒��S���l�p�`�̒��ɂ���ꍇ
        auto first = AppFrame::Math::Utility::InsideTrianglePoint(leftDownXZ, leftUpXZ, rightDownXZ, AABBCenterXZ);
        auto second = AppFrame::Math::Utility::InsideTrianglePoint(rightDownXZ, leftUpXZ, rightUpXZ, AABBCenterXZ);

        if (first || second) {
            return true;
        }


        //AABB�̒��S���l�p�`�̊O�ɂ���ꍇ
        if (LineToAABB(leftUpXZ, leftDownXZ, own)) {
            return true;
        }

        if (LineToAABB(leftDownXZ, rightDownXZ, own)) {
            return true;
        }

        if (LineToAABB(rightDownXZ, rightUpXZ, own)) {
            return true;
        }

        if (LineToAABB(rightUpXZ, leftUpXZ, own)) {
            return true;
        }



        //�������Ă��Ȃ�
        return false;

    }


    //bool CollisionComponent::CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2)
    //{
    //    Math::Vector4 start = act2.GetLMin() + act2.GetPosition() - act1.GetPosition();
    //    Math::Vector4 end = act2.GetLMax() + act2.GetPosition() - act1.GetPosition();
    //    double a = end.Dot(end);
    //    double b = 2.0 * start.Dot(end);
    //    double c = start.Dot(start) - act1.GetR() * act1.GetR();

    //    double disc = b * b - 4.0f * a * c;

    //    if (disc < 0.0f)
    //    {
    //        return false;
    //    }
    //    else
    //    {
    //        disc = std::sqrt(disc);

    //        double tMin = (-b - disc) / (2.0 * a);
    //        double tMax = (-b + disc) / (2.0 * a);
    //        if (tMin >= 0.0 && tMin <= 1.0)
    //        {
    //           
    //            return true;
    //        }
    //        else if (tMax >= 0.0 && tMax <= 1.0)
    //        {
    //           
    //            return true;
    //        }
    //        else
    //        {
    //            return false;
    //        }
    //    }

    //    return false;
    //}

    bool CollisionComponent::CircleToLine(const Actor::Actor& act, const Math::Vector4 start, const Math::Vector4 end)
    {

        Math::Vector4 X = start - act.GetPosition();
        Math::Vector4 Y = end - start;

        double a = Y.Dot(Y);
        double b = 2.0 * X.Dot(Y);
        double c = X.Dot(X) - act.GetR() * act.GetR();


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

    bool CollisionComponent::FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2)
    {

        auto dir = act1.GetRotation();

        //y����]�̌��������v���ɃZ�b�g����Ă��邽�ߋt���ɂ���
        auto rotY = -dir.GetY();

        //�͈�
        auto angle = act1.GetSearchRange();

        //0�x��z����
        auto nine = DX_PI / 180.0 * 90.0;

        //���W�A���ɕϊ�
        auto rad = DX_PI / 180.0 * angle;

        //�~�ʂ̊J�n�p�x
        auto sRad = -rad + nine + rotY;
        //�~�ʂ̏I���p�x
        auto eRad = rad + nine + rotY;

        Math::Vector2 act2XZ = { act2.GetPosition().GetX(), act2.GetPosition().GetZ() };
        Math::Vector2 act1XZ = { act1.GetPosition().GetX(), act1.GetPosition().GetZ() };

        //��l������G�ւ̃x�N�g��
        auto dis = act2XZ - act1XZ;
        auto length = dis.Length();

        ////��l������G�ւ̃x�N�g��
        //auto dis = act2.GetPosition() - act1.GetPosition();
        //auto length = dis.Length();


        Math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
        Math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

        auto cross180 = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
        auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
        auto crossEnd = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

        //�~�̓��O����
        if (length < act1.GetR())
        {
            //��`�̊p�x��180�x�𒴂��Ă��邩
            if (cross180 > 0)
            {
                //�J�n�p�ɑ΂��č��ɂ��邩//////////////////���X�̒��ɓ����Ă��Ȃ�
                if (crossStart < 0)
                {
                    return false;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd > 0)
                {
                    return false;
                }

                //��̓����ɂ���
                return true;


            }
            else
            {   //�J�n�p�ɑ΂��č��ɂ��邩
                if (crossStart <= 0)
                {
                    return true;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd >= 0)
                {
                    return true;
                }

                //��̊O���ɂ���
                return false;
            }

        }

        return false;
    }


    bool CollisionComponent::FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, bool select)
    {
        auto range = 0.0;

        //���G�͈͂��ǂ���
        if (select) {
            range = act1.GetR();
        }
        else {
            range = act1.GetHuckR();
        }



        auto dir = act1.GetRotation();

        //y����]�̌��������v���ɃZ�b�g����Ă��邽�ߋt���ɂ���
        auto rotY = -dir.GetY();

        //�͈�
        auto angle = 0.0;

        if (select) {
            angle = act1.GetSearchRange();
        }
        else {
            angle = act1.GetHuckingRange();
        }


        //0�x��z����
        auto nine = DX_PI / 180.0 * 90.0;

        //���W�A���ɕϊ�
        auto rad = DX_PI / 180.0 * angle;

        auto sRad = 0.0; auto eRad = 0.0;

        //���G�͈͂��ǂ���
        if (select) {

            //�~�ʂ̊J�n�p�x
            sRad = -rad + nine + rotY;
            //�~�ʂ̏I���p�x
            eRad = rad + nine + rotY;
        }
        else {//�n�b�L���O�͈�

            //�~�ʂ̊J�n�p�x
            sRad = -rad - nine + rotY;
            //�~�ʂ̏I���p�x
            eRad = rad - nine + rotY;

        }


        Math::Vector2 act2XZ = { act2.GetPosition().GetX(), act2.GetPosition().GetZ() };
        Math::Vector2 act1XZ = { act1.GetPosition().GetX(), act1.GetPosition().GetZ() };

        //��l������G�ւ̃x�N�g��
        auto dis = act2XZ - act1XZ;
        auto length = dis.Length();


        Math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
        Math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

        auto cross180 = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
        auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
        auto crossEnd = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

        //�~�̓��O����
        if (length < range)
        {
            //��`�̊p�x��180�x�𒴂��Ă��邩
            if (cross180 > 0)
            {
                //�J�n�p�ɑ΂��č��ɂ��邩//////////////////���X�̒��ɓ����Ă��Ȃ�
                if (crossStart < 0)
                {
                    return false;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd > 0)
                {
                    return false;
                }

                //��̓����ɂ���
                return true;


            }
            else
            {   //�J�n�p�ɑ΂��č��ɂ��邩
                if (crossStart <= 0)
                {
                    return true;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd >= 0)
                {
                    return true;
                }

                //��̊O���ɂ���
                return false;
            }

        }

        return false;
    }

    bool CollisionComponent::FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, double r, double range) {
    
        auto dir = act1.GetRotation();

        //y����]�̌��������v���ɃZ�b�g����Ă��邽�ߋt���ɂ���
        auto rotY = -dir.GetY();

        //�͈�
        auto angle = range;

        //0�x��z����
        auto nine = DX_PI / 180.0 * 90.0;

        //���W�A���ɕϊ�
        auto rad = DX_PI / 180.0 * angle;

        //�~�ʂ̊J�n�p�x
        auto sRad = -rad + nine + rotY;
        //�~�ʂ̏I���p�x
        auto eRad = rad + nine + rotY;


        Math::Vector2 act2XZ = { act2.GetPosition().GetX(), act2.GetPosition().GetZ() };
        Math::Vector2 act1XZ = { act1.GetPosition().GetX(), act1.GetPosition().GetZ() };

        //���肩�玩���ւ̃x�N�g��
        auto dis = act2XZ - act1XZ;
        auto length = dis.Length();

        ////���肩�玩���ւ̃x�N�g��
        //auto dis = act2.GetPosition() - act1.GetPosition();
        //auto length = dis.Length();


        Math::Vector4 startPos = { std::cos(sRad) , 0.0,std::sin(sRad) };
        Math::Vector4 endPos = { std::cos(eRad) , 0.0,std::sin(eRad) };

        auto cross180 = startPos.GetX() * endPos.GetZ() - endPos.GetX() * startPos.GetZ();
        auto crossStart = startPos.GetX() * dis.GetZ() - dis.GetX() * startPos.GetZ();
        auto crossEnd = endPos.GetX() * dis.GetZ() - dis.GetX() * endPos.GetZ();

        //�~�̓��O����
        if (length < r)
        {
            //��`�̊p�x��180�x�𒴂��Ă��邩
            if (cross180 > 0)
            {
                //�J�n�p�ɑ΂��č��ɂ��邩//////////////////���X�̒��ɓ����Ă��Ȃ�
                if (crossStart < 0)
                {
                    return false;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd > 0)
                {
                    return false;
                }

                //��̓����ɂ���
                return true;


            }
            else
            {   //�J�n�p�ɑ΂��č��ɂ��邩
                if (crossStart <= 0)
                {
                    return true;
                }//�I���p�ɑ΂��ĉE�ɂ��邩

                if (crossEnd >= 0)
                {
                    return true;
                }

                //��̊O���ɂ���
                return false;
            }

        }

        return false;
    
    }

    bool CollisionComponent::LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2, const AABB box) {


        std::vector<double> tValues;

        auto [minX, minZ, maxX, maxZ] = box;
       
        auto lMin = act1.GetPosition();
        auto lMax = act2.GetPosition();

        //x���ʂ̃e�X�g
        TestSidePlane(lMin.GetX(), lMax.GetX(), minX, tValues);
        TestSidePlane(lMin.GetX(), lMax.GetX(), maxX, tValues);

        //z���ʂ̃e�X�g
        TestSidePlane(lMin.GetZ(), lMax.GetZ(), minZ, tValues);
        TestSidePlane(lMin.GetZ(), lMax.GetZ(), maxZ, tValues);

        Math::Vector4 point;
        for (auto&& t : tValues) {
        
           // _interSection = PointOnSegment(lMin, lMax, t);
            return true;
        }
        
        return false;
    }

    bool CollisionComponent::LineToAABB(Math::Vector2 startPos, Math::Vector2 endPos, const Actor::Actor& target) {


        std::vector<double> tValues;

        Math::Vector2 posXZ = { target.GetPosition().GetX(), target.GetPosition().GetZ() };
    

        auto boxMin = target.GetMin() + posXZ;
        auto boxMax = target.GetMax() + posXZ;

        auto lMin = startPos;
        auto lMax = endPos;

        //x���ʂ̃e�X�g
        TestSidePlane(lMin.GetX(), lMax.GetX(), boxMin.GetX(), tValues);
        TestSidePlane(lMin.GetX(), lMax.GetX(), boxMax.GetX(), tValues);

        //z���ʂ̃e�X�g
        TestSidePlane(lMin.GetZ(), lMax.GetZ(), boxMin.GetZ(), tValues);
        TestSidePlane(lMin.GetZ(), lMax.GetZ(), boxMax.GetZ(), tValues);

        Math::Vector4 point;
        for (auto&& t : tValues) {
            auto point = PointOnSegment(startPos, endPos, t);

            Math::Vector2 AABBLeftDownXZ  = { boxMin.GetX(), boxMin.GetZ() };
            Math::Vector2 AABBLeftUpXZ    = { boxMin.GetX(), boxMax.GetZ() };
            Math::Vector2 AABBRightDownXZ = { boxMax.GetX(), boxMin.GetZ() };
            Math::Vector2 AABBRightUpXZ   = { boxMax.GetX(), boxMax.GetZ() };

            //���W��AABB�̒��ɂ���ꍇ
            auto first = AppFrame::Math::Utility::InsideTrianglePoint(AABBLeftDownXZ, AABBLeftUpXZ, AABBRightDownXZ, point);
            auto second = AppFrame::Math::Utility::InsideTrianglePoint(AABBRightDownXZ, AABBLeftUpXZ, AABBRightUpXZ, point);

            if (first || second) {
                return true;
            }
           
        }

        return false;
    }

    //bool CollisionComponent::CollisionFloor(const Actor::Actor& act) {


    //    // �ړ�������ŃR���W��������
    //    MV1_COLL_RESULT_POLY hitPoly;

    //    auto handle = act.GetAssetServer().GetModel("Dungeon");

    //    for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

    //        if ((*i)->GetTypeId() != TypeId::Stage) {
    //            continue;
    //        }
    //        else {

    //            auto frameMapCollision = (*i)->GetCollision().GetMapCollision();

    //            Math::Vector4 dif = { 0.0, 40.0, 0.0 };
    //            Math::Vector4 under = { 0.0, -99999.0, 0.0 };
    //            auto startPos = _position + dif;
    //            auto endPos = _position + under;
    //            // ��l���̍��ʒu���牺�����ւ̒���
    //            hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision, ToDX(startPos), ToDX(endPos));

    //            if (hitPoly.HitFlag) {
    //                // ��������
    //                // ��������Y�ʒu���L�������W�ɂ���
    //                _position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };
    //                return true;
    //            }
    //            else {
    //                // ������Ȃ������B���̍��W�ɖ߂�
    //                _position = oldPos;

    //                return false;
    //            }

    //        }

    //    }

    //    return false;

    //
    //}


    //bool CollisionComponent::LineToAABB(const Actor::Actor& act, const Math::Vector2 min, const Math::Vector2 max) {


    //    std::vector<double> tValues;

    //   // auto [minX, minZ, maxX, maxZ] = box;

    //    Math::Vector4 lMin = { act.GetPosition().GetX(), 150.0, act.GetPosition().GetZ() };
    //    Math::Vector4 lMax = {act.GetPosition().GetX(), -9999.0, act.GetPosition().GetZ()};
    //   // auto boxMin = act2.GetMin();


    //    //x���ʂ̃e�X�g
    //    TestSidePlane(lMin.GetX(), lMax.GetX(), min.GetX(), tValues);
    //    TestSidePlane(lMin.GetX(), lMax.GetX(), max.GetX(), tValues);

    //    //z���ʂ̃e�X�g
    //    TestSidePlane(lMin.GetZ(), lMax.GetZ(), min.GetZ(), tValues);
    //    TestSidePlane(lMin.GetZ(), lMax.GetZ(), max.GetZ(), tValues);

    //    Math::Vector4 point;
    //    for (auto t : tValues) {

    //        // _interSection = PointOnSegment(lMin, lMax, t);
    //        return true;
    //    }

    //    return false;
    //}

    bool CollisionComponent::TestSidePlane(const double start, const double end, const double negd, std::vector<double>& out) {

        auto denom = end - start;
        if (-0.001 < denom && denom < 0.001) {
            return false;
        }
        else {
        
            auto numer = -start + negd;
            auto t = numer / denom;

            //t���͈͓��ɂ��邩�ǂ���
            if (t >= 0.0 && t <= 1.0) {
                out.emplace_back(t);
                return true;
            }
            else {
                return false;
            }
        }

    }

    const Math::Vector4 CollisionComponent::PointOnSegment(const Math::Vector4 start, const Math::Vector4 end, const double t) {
    
        return start + (end - start) * t;
    }

    const Math::Vector2 CollisionComponent::PointOnSegment(const Math::Vector2 start, const Math::Vector2 end, const double t) {

        return start + (end - start) * t;
    }


    //�}�b�v�̃R���W���������\�z
    void CollisionComponent::SetMapCollision(int handle, std::string key) {

        auto frameMapCollision = MV1SearchFrame(handle, key.c_str());

        //MV1SetPosition(handle, VGet(-500, 0, 500));
        //�����Ɋe�X�e�[�W�̔z�u�ꏊ�����Ă݂�
        //auto zero = MV1GetPosition(handle);

        MV1SetupCollInfo(handle, frameMapCollision, 32, 32, 32);

        //auto zero = MV1GetPosition(handle);
        //MV1RefreshCollInfo(handle, frameMapCollision);
        _frameMap.emplace(handle, frameMapCollision);

    }


    //�}�b�v�̃R���W��������S�\�z
    void CollisionComponent::SetMapCollision(int handle) {

        // auto frameMapCollision = MV1SearchFrame(handle, key.c_str());

         //MV1SetPosition(handle, VGet(-500, 0, 500));
         //�����Ɋe�X�e�[�W�̔z�u�ꏊ�����Ă݂�
         //auto zero = MV1GetPosition(handle);

        MV1SetupCollInfo(handle, -1, 32, 32, 32);

        auto zero = MV1GetPosition(handle);
        //MV1RefreshCollInfo(handle, frameMapCollision);
        _frameMap.emplace(handle, -1);

    }

    //�M�~�b�N�̃R���W���������\�z
    //void CollisionComponent::SetGimmickCollision(int handle, std::string key) {
    //    auto frameGimmickCollision = MV1SearchFrame(handle, key.c_str());

    //    MV1SetupCollInfo(handle, frameGimmickCollision, 32, 32, 32);

    //    if (frameGimmickCollision == -2) {
    //    
    //        printfDx("is not gimmickCollision");
    //        return;
    //    }

    //    _frameGimmick.emplace(handle, frameGimmickCollision);
    //
    //}

    //���[�v���b�V�����Ō���
    const std::pair<std::pair<int, int>, int> CollisionComponent::GetWarpCollision(std::string key, int handle) {

        auto collisionFrame = _warpMap[key];
        return collisionFrame;

    }

    //�n���h���ƃ��[�v���b�V�����ō\�z
    void CollisionComponent::SetWarpCollision(int handle, std::string key) {


        if (key.size() < 8) {
        
            return;
        }

        //�Ή����郏�[�v���b�V���̖��O
        auto name = key.substr(0, 2);

        //���[�v���b�V�����ɂ���n�C�t�����΂�������
        auto x = key.substr(3, 2);

        auto xStr = x;
        xStr.substr(0, 1);

        if (xStr != "0") {
            x = x.substr(1, 1);
        }

        int xNum = std::atoi(x.c_str());

        //���[�v���b�V�����ɂ���n�C�t�����΂�������
        auto y = key.substr(6, 2);
        auto yStr = y;
        yStr.substr(0, 1);


        if (yStr != "0") {
            y = y.substr(1, 1);
        }

        int yNum = std::atoi(y.c_str());


        //�X�e�[�W�e�[�u���̃��[�v��̍��W�ʒu
        auto pos = std::make_pair(xNum, yNum);

        //�i�r���b�V���̖��O
        auto warpMapCollision = MV1SearchFrame(handle, key.c_str());
        MV1SetupCollInfo(handle, warpMapCollision, 32, 32, 32);

        //VECTOR position = { 0.0, 0.0, 500 };
        //MV1SetPosition(handle, position);
        //auto size = MV1GetFrameNum(handle);

        //for (auto i = 0; i < size; i++) {
        MV1RefreshCollInfo(handle, warpMapCollision);
        //}

        //���[�v�̈ʒu�ƃR���W�������
        auto warpPosCol = std::make_pair(pos, warpMapCollision);
        _warpMap.emplace(key, warpPosCol);

    }

    const std::vector<std::string> CollisionComponent::GetWarpName(int handle) {
        auto vecStr = _warpNameMap[handle];
        return vecStr;
    }

    void CollisionComponent::SetWarpName(int handle, std::vector<std::string> keyV) {
        _warpNameMap.emplace(handle, keyV);
    }

    //���[�v��̖��O���擾
    const std::string CollisionComponent::GetWarpNameFloor(int floorNum, std::string warpKey) {

        //�����o�����[�̃L�[�Ɨv�f�̃y�A���擾
        auto range = _warpNameFloor.equal_range(floorNum);

        //������2����
        auto key = warpKey.substr(0, 2);

        std::string str;

        for (auto i = range.first; i != range.second; i++) {

            auto secondRange = i->second.equal_range(key);

            for (auto k = secondRange.first; k != secondRange.second; k++) {

                //���������ɂ��郏�[�v�ʒu�̏����̂��߈قȂ镶��������
                if (k->second != warpKey) {

                    str = k->second;
                    return str;
                }

            }

        }


        return str;
    }

    void CollisionComponent::SetWarpNameFloor(int num, std::vector<std::string> keys) {

        std::unordered_multimap<std::string, std::string> warps;
        //  std::unordered_multimap<int, std::unordered_multimap<std::string, std::string>> warpFloors;

        for (auto key : keys) {

            //�Ή����郏�[�v���b�V���̖��O
            auto name = key.substr(0, 2);

            //���[�v���b�V�����ɂ���n�C�t�����΂�������
            //auto x = key.substr(3, 2);

            //auto xStr = x;
            //xStr.substr(0, 1);

            //if (xStr != "0") {
            //    x = x.substr(1, 1);
            //}

            //int xNum = std::atoi(x.c_str());

            ////���[�v���b�V�����ɂ���n�C�t�����΂�������
            //auto y = key.substr(6, 2);
            //auto yStr = y;
            //yStr.substr(0, 1);


            //if (yStr != "0") {
            //    y = y.substr(1, 1);
            //}

            //int yNum = std::atoi(y.c_str());


            ////�t���A�ԍ��v�Z
            //auto floorNum = yNum * 10 + xNum;

            warps.emplace(name, key);


        }

        //�����ɂ͂����10�ł͂Ȃ�0�łȂ��Ƃ���
        _warpNameFloor.emplace(num, warps);



        //_warpNameFloor.emplace(warpFloors);
    }


}

