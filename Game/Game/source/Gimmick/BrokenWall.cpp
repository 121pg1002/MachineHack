/*****************************************************************//**
 * @file   BrokenWall.cpp
 * @brief  壊せる壁のクラス
 *      
 * @author hikaru Goto
 * @date   Feburuary 6 2022
 *********************************************************************/
#include "BrokenWall.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Gimmick {

	BrokenWall::BrokenWall(AppFrame::Game& game) : GimmickBase(game) {

		//_wall = std::make_unique<Model::ModelComponent>(*this);
		//_wall->SetModel("BrokenWall");

	}

	BrokenWall::~BrokenWall() {

	}

	void BrokenWall::Update()
	{
		ComputeWorldTransform();
		_model->Update();
	}

	void BrokenWall::Draw()
	{
		_model->Draw();
	}


}
