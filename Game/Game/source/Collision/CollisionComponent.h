
/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  �Փ˔���N���X
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include <memory>
#include <DxLib.h>
#include "AppFrame.h"
//namespace  Collision {
  struct Sphere {
    Sphere(const math::Vector4& center, float radius);
    bool Contains(const math::Vector4& point) const;

    math::Vector4 center;
    float radius;
  };

  bool Intersect(const Sphere& a, const Sphere& b);

  class Actor;

  class CollisionComponent {
  public:
    enum class ReportId {
      None,
      HitFromPlayer,
      HitFromEnemy,
      HuckedFromPlayer,
    };

    struct Report {
      ReportId id{ ReportId::None };
      math::Vector4 position{ 0, 0, 0 };
    };



    CollisionComponent(Actor& owner);

    void EnemyFromPlayer();
    void PlayerFromEnemy();

    void SetReport(Report report) { *_report = report; }
    Report& GetReport() const { return *_report; }

    /*
    *@brief �~�Ɖ~�̓����蔻����s��
    */
    bool CircleToCircle(const Actor& act1, const Actor& act2);

    /*
    *@brief ��`�Ƌ�`�̓����蔻����s��
    */
    bool AABBToAABB(const Actor& act1, const Actor& act2);

    /*
    *@brief �~��AABB�̓����蔻����s��
    */
    bool CircleToAABB(const Actor& act1, const Actor& act2);

    /*
    *@brief �~�Ɛ����̓����蔻����s��
    */
    bool CircleToLine(const Actor& act1, const Actor& act2);

    /*
    *@brief �~�Ɛ�`�̓����蔻����s��
    */
    bool CircleToFan(const Actor& act1, const Actor& act2);

  private:
    Actor& _owner;
    std::unique_ptr<Report> _report;
    double _r1{ 0.0 }, _r2{ 0.0 }; //!< �~�̔��a
  };
//}