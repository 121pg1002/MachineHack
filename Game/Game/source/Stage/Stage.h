///
/// @file    Stage.h
/// @brief   ステージ
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
#include <vector>
#include "../Actor/Actor.h"

namespace MachineHuck::Model {
	class ModelComponent;
}

namespace MachineHuck::Stage {
	class Stage : public Actor::Actor {
	public:
		Stage(AppFrame::Game& game);
		virtual void Update() override;
		void Draw() override;
		TypeId GetTypeId() const override { return TypeId::Stage; };
	private:
		std::unique_ptr<Model::ModelComponent> _skySphere;
		std::unique_ptr<Model::ModelComponent> _ground;

		std::vector<std::unique_ptr<Model::ModelComponent>> _grounds;
	};
}


