/*****************************************************************//**
 * @file   GimmickBase.cpp
 * @brief  �M�~�b�N�̊��N���X
 *
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#include "GimmickBase.h"
#include "../Actor/Actor.h"
namespace Gimmick {
	GimmickBase::GimmickBase(Game& game) : Actor(game)
	{

	}

	bool GimmickBase::IsHitPlayer(Actor& actor)
	{
		if (actor.GetTypeId() != TypeId::Gimmick)
		{
			//for (auto gimmicks : actor.GetActorServer().GetGimmicks().
			//{
			//	
			//
			//}

		}

		return false;
	}
}
