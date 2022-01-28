/*****************************************************************//**
 * @file   BrokenWall.h
 * @brief  �󂹂�ǂ̃N���X
 * 
 * @author hikaru Goto
 * @date   January 20 2022
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

		TypeId GetTypeId() const override { return TypeId::Gimmick; };

	    void Update();
	    void Draw();
	private:
		std::unique_ptr<Model::ModelComponent> _wall;
    };
}

