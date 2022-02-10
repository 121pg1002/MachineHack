/*****************************************************************//**
 * @file   DamageFloorGimmick.h
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

	class DamageFloorGimmick : public GimmickBase
	{
	public:
		DamageFloorGimmick(AppFrame::Game& game);
		~DamageFloorGimmick() override;

		TypeId GetTypeId() const override { return TypeId::Gimmick; };
		//TypeGimmick GetTypeGimmick() const override { return TypeGimmick::DamageFloor; }

		//void Enter();
		void Update() override;
		void Draw() override;

	private:
		//int _damageCount; //!< ダメージ受けるカウンタ
		//std::vector<std::unique_ptr<Model::ModelComponent>> _damageFloorV; //!< ダメージ床の動的配列
		std::unique_ptr<Model::ModelComponent>_damageFloor;

	};
}

