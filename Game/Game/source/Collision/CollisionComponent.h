
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
#include <tuple>

namespace Math = AppFrame::Math;


//struct Sphere {
//  Sphere(const Math::Vector4& center, float radius);
//  bool Contains(const Math::Vector4& point) const;
//
//  Math::Vector4 center;
//  float radius;
//};

//bool Intersect(const Sphere& a, const Sphere& b);
namespace MachineHuck::Actor {
	class Actor;
}

namespace MachineHuck::Collision {
	class CollisionComponent {
	public:
		//enum class ReportId {
		//  None,
		//  HitFromPlayer,
		//  HitFromEnemy,
		//  HuckedFromPlayer,
		//};

		//struct Report {
		//  ReportId id{ReportId::None};
		//  Math::Vector4 position{0, 0, 0};
		//};
		using AABB = std::tuple<double, double, double, double>;


		CollisionComponent(Actor::Actor& owner);

		//void EnemyFromPlayer();
		//void PlayerFromEnemy();

		//void SetReport(Report report) { *_report = report; }
		//Report& GetReport() const { return *_report; }

		/**
		 * @brief  �~�Ɖ~�̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		bool CircleToCircle(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  ��`�Ƌ�`�̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		bool AABBToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ƌ�`�̓����蔻����s��
		 * @param  act1 ����(�~)
		 * @param  act2 ����(��`)
		 * @return ����
		 */
		bool CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

	
		/**
		 * @brief  �~�Ƌ�`�̓����蔻����s��       
		 * @param  act  �v���C���[
		 * @param  min  �ŏ����W
		 * @param  max  �ő���W
		 * @return ����
		 */
		bool CircleToAABB(const Actor::Actor& act, const AppFrame::Math::Vector2 min, const AppFrame::Math::Vector2 max);


		/**
		 * @brief  �~�Ɖ�]������`�̓����蔻����s��
		 * @param  act1 ����(�~)
		 * @param  act2 ����(��]������`)
		 * @return
		 */
		bool CicrleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ɛ����̓����蔻����s��
		 * @param  act1 ����
		 * @param  act2 ����
		 * @return ����
		 */
		bool CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ɛ����̓����蔻����s��
		 * @param  act1 ����
		 * @param  start �n�_
		 * @param  end �I�_ 
		 * @return ����
		 */
		bool CircleToLine(const Actor::Actor& act1, const Math::Vector4 start, const Math::Vector4 end);

		/*
		*@brief �~�Ɛ�`�̓����蔻����s��
		*/
		bool CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  �~�Ɛ�`�̓����蔻����s��
		 * @param  act1  ����
		 * @param  act2  ����
		 * @param  select true�͍��G�͈� false�̓n�b�L���O�͈͂̔���
		 * @return ����
		 */
		bool CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2, bool select);

		/**
		 * @brief  ������AABB�̓����蔻����s��
		 * @param  act1
		 * @param  act2
		 * @return ����
		 */
		bool LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2, const AABB box);

		/**
		 * @brief  ���ʂƂ̌����e�X�g
		 * @param  start
		 * @param  end
		 * @param  negd
		 * @param  out
		 * @return ����
		 */
		bool TestSidePlane(const double start, const double end, const double negd, std::vector<double>& out);

		/** 
		 * @brief  ������̍��W���v�Z  
		 * @param  start
		 * @param  end     
		 * @param  t
		 * @return ���W
		 */
		const Math::Vector4 PointOnSegment(const Math::Vector4 start, const Math::Vector4 end, const double t);


	private:
		Actor::Actor& _owner;
		/*std::unique_ptr<Report> _report;*/
		double _r1{ 0.0 }, _r2{ 0.0 }; //!< �~�̔��a

		Math::Vector4 _interSection;//!< �����Ɖ�]�����l�p�`�Ƃ̌�_
	};
}

