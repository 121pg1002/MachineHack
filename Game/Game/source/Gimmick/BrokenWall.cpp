/*****************************************************************//**
 * @file   BrokenWall.cpp
 * @brief  ‰ó‚¹‚é•Ç‚ÌƒNƒ‰ƒX
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
