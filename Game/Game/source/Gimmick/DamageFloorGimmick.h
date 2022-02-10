/*****************************************************************//**
 * @file   DamageFloorGimmick.h
 * @brief  �_���[�W���M�~�b�N�N���X
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
		//int _damageCount; //!< �_���[�W�󂯂�J�E���^
		//std::vector<std::unique_ptr<Model::ModelComponent>> _damageFloorV; //!< �_���[�W���̓��I�z��
		std::unique_ptr<Model::ModelComponent>_damageFloor;

	};
}

