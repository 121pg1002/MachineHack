/*****************************************************************//**
 * @file   GimmickBase.h
 * @brief  ギミックの基底クラス
 * 
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#pragma once
//#include <vector>
#include <string>
#include "AppFrame.h"
#include "../Actor/Actor.h"


namespace MachineHuck::Gimmick {
	class GimmickBase : public Actor::Actor
	{
	public:
		GimmickBase(AppFrame::Game& game);
		virtual ~GimmickBase() override = default;

		//enum class TypeGimmick {

		//	BrokenWall,
		//	Hole,
		//	DamageFloor
		//	
		//};

		//TypeGimmick IsBrokenWall() { return TypeGimmick::BrokenWall; }

		//virtual TypeGimmick GetTypeGimmick() const = 0;
		//bool IsHitPlayer(Actor& actor);
		//bool Create(std::string key, AppFrame::Math::Vector4 pos);
		//bool Delete();

	protected:

	};
}

