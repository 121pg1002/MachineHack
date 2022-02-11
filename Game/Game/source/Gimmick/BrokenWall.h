/*****************************************************************//**
 * @file   BrokenWall.h
 * @brief  ‰ó‚¹‚é•Ç‚ÌƒNƒ‰ƒX
 * 
 * @author hikaru Goto
 * @date   Feburuary 6 2022
 *********************************************************************/
#pragma once
#include <memory>
#include "AppFrame.h"
#include "GimmickBase.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Gimmick{

	class BrokenWall : public GimmickBase {
    public:

	    BrokenWall(AppFrame::Game& game);
	    ~BrokenWall() override;

		TypeId GetTypeId() const override { return TypeId::Gimmick; }
		//TypeGimmick GetTypeGimmick() const override { return TypeGimmick::BrokenWall; }

	    void Update();
	    void Draw();
	private:
		//std::unique_ptr<Model::ModelComponent> _wall;
    };
}


