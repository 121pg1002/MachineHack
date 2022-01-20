/*****************************************************************//**
 * @file   BrokenWall.cpp
 * @brief  �󂹂�ǂ̃N���X
 *      
 * @author hikaru Goto
 * @date   January 20 2022
 *********************************************************************/
#include "BrokenWall.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Gimmick {

	BrokenWall::BrokenWall(AppFrame::Game& game) : GimmickBase(game) {

		_wall = std::make_unique<Model::ModelComponent>(*this);
		_wall->SetModel("BrokenWall");

	}

	BrokenWall::~BrokenWall() {

	}

	void BrokenWall::Update()
	{
	}

	void BrokenWall::Draw()
	{
		_wall->Draw();
	}


}
