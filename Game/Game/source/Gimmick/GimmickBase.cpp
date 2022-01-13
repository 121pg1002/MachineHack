/*****************************************************************//**
 * @file   GimmickBase.cpp
 * @brief  ギミックの基底クラス
 *
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#include "GimmickBase.h"
#include "../Actor/Actor.h"

namespace MachineHuck::Gimmick {

	GimmickBase::GimmickBase(AppFrame::Game& game) : Actor::Actor(game)
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


