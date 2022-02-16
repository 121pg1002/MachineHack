/*****************************************************************//**
 * @file   RecoveryFloorGimmick.h
 * @brief  ダメージ床ギミッククラス
 *
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/
#pragma once

#include <memory>
#include "AppFrame.h"
#include "GimmickBase.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Gimmick {

	class RecoveryFloorGimmick : public GimmickBase
	{
	public:
		RecoveryFloorGimmick(AppFrame::Game& game);
		~RecoveryFloorGimmick() override;

		TypeId GetTypeId() const override { return TypeId::Gimmick; };

		//void Enter();
		void Update() override;
		void Draw() override;

	private:
		std::unique_ptr<Model::ModelComponent>_recoveryFloor;

	};
}

