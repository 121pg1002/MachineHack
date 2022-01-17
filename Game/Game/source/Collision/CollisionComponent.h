
/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  衝突判定クラス
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include <memory>
#include <DxLib.h>
#include "AppFrame.h"

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



		CollisionComponent(Actor::Actor& owner);

		//void EnemyFromPlayer();
		//void PlayerFromEnemy();

		//void SetReport(Report report) { *_report = report; }
		//Report& GetReport() const { return *_report; }

		/**
		 * @brief  円と円の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		bool CircleToCircle(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  矩形と矩形の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		bool AABBToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  円と矩形の当たり判定を行う
		 * @param  act1 自分(円)
		 * @param  act2 相手(矩形)
		 * @return 成否
		 */
		bool CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);


		/**
		 * @brief  円と回転した矩形の当たり判定を行う
		 * @param  act1 自分(円)
		 * @param  act2 相手(回転した矩形)
		 * @return
		 */
		bool CicrleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  円と線分の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		bool CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2);

		/*
		*@brief 円と扇形の当たり判定を行う
		*/
		bool CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  円と扇形の当たり判定を行う
		 * @param  act1  自分
		 * @param  act2  相手
		 * @param  select trueは索敵範囲 falseはハッキング範囲の判定
		 * @return 成否
		 */
		bool CircleToFan(const Actor::Actor& act1, const Actor::Actor& act2, bool select);

		/**
		 * @brief  線分とAABBの当たり判定を行う
		 * @param  act1
		 * @param  act2
		 * @return 成否
		 */
		bool LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  平面との交差テスト
		 * @param  start
		 * @param  end
		 * @param  negd
		 * @return 成否
		 */
		bool TestSidePlane(const double start, double const end, double const negd);


	private:
		Actor::Actor& _owner;
		/*std::unique_ptr<Report> _report;*/
		double _r1{ 0.0 }, _r2{ 0.0 }; //!< 円の半径
	};
}

