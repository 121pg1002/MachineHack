/*****************************************************************//**
 * @file   DamageFloorGimmick.h
 * @brief  ダメージ床ギミッククラス
 * 
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/
#pragma once

#include "AppFrame.h"
#include "GimmickBase.h"

namespace MachineHuck::Gimmick {

	class DamageFloorGimmick : public GimmickBase
	{
	public:
		DamageFloorGimmick(AppFrame::Game& game);
		~DamageFloorGimmick() override = default;

		TypeId GetTypeId() const override { return TypeId::Gimmick; };


		//void Update() override;
		void Draw() override;

	private:
		//int _damageCount; //!< ダメージ受けるカウンタ

	};
}

