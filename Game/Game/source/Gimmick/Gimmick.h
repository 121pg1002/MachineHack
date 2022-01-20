/*****************************************************************//**
 * @file   Gimmick.h
 * @brief  ギミッククラス
 * 
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/
#pragma once

#include "AppFrame.h"
#include "GimmickBase.h"

namespace MachineHuck::Gimmick {

	class Gimmick : public GimmickBase
	{
	public:
		Gimmick(AppFrame::Game& game);
		~Gimmick()override = default;

		void Update() override;
		void Draw() override;

	};
}

