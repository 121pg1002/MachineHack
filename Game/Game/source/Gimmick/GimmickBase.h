/*****************************************************************//**
 * @file   GimmickBase.h
 * @brief  ギミックの基底クラス
 * 
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#pragma once
#include "AppFrame.h"
#include "../Actor/Actor.h"
//#include <vector>
#include <string>
namespace Gimmick {
	class GimmickBase : public Actor
	{
	public:
		GimmickBase(Game& game);
		virtual ~GimmickBase() override = default;

		bool IsHitPlayer(Actor& actor);
		//bool Create(std::string key, math::Vector4 pos);
		//bool Delete();

	protected:

	};
}