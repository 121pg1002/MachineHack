/**
 * @file   EnemyBase.h
 * @brief  エネミーの基底クラス
 *
 * @author Hikaru Goto
 * @date   2021/12/03
 */

#include "EnemyBase.h"
namespace Enemy {
	EnemyBase::EnemyBase(Game& game) : Actor{ game } {

	}
	EnemyBase::~EnemyBase() {}
	bool IsHucked(const EnemyBase& enemy)
	{
		if (enemy.GetTypeId() != Actor::TypeId::Enemy)
		{
			return false;
		}
		else
		{
			if (enemy.isDead())
			{
				return false;
			}
			else
			{
				if (enemy.GetStatus() != EnemyBase::STATUS::ISHUCKED)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
}
