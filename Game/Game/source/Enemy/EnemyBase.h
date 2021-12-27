/**
 * @file   EnemyBase.h
 * @brief  エネミーの基底クラス
 *
 * @author Hikaru Goto
 * @date   2021/12/03
 */

#pragma once
#include "../Actor/Actor.h"
namespace Enemy {
	class EnemyBase : public Actor
	{
	public:
		EnemyBase(Game& game);
		~EnemyBase();

		bool IsHucked(const EnemyBase& enemy);

		enum class Type
		{
			Base = 0,
			Tackle,
			Grab,
		};

		enum class STATUS
		{
			NONE,
			WAIT,
			WALK,
			ISHUCKING,
			ISHUCKED,
			SEARCH,
			CHASE
		};
		virtual Type GetType() const = 0;

		STATUS GetStatus() const { return _status; }
		void SetStatus(STATUS status) { _status = status; }

		virtual TypeId GetTypeId() const override = 0;

	protected:


		STATUS _status{ STATUS::WAIT };

	};
}
