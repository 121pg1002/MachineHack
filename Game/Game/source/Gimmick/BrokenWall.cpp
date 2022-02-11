/*****************************************************************//**
 * @file   BrokenWall.cpp
 * @brief  ‰ó‚¹‚é•Ç‚ÌƒNƒ‰ƒX
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
		_minXZ = { -100.0, -50.0 };
		_maxXZ = { 100.0, 50.0 };
		_typeGimmick = TypeGimmick::BrokenWall;
	}

	BrokenWall::~BrokenWall() {

	}

	void BrokenWall::Update() {
		ComputeWorldTransform();
		_model->Update();
	}

	void BrokenWall::Draw() {
		//_model->Draw();
		_model->BrokenDraw();

#ifdef _DEBUG

		VECTOR rightDown = {_maxXZ.GetX() + _position.GetX(), 0.0, _minXZ.GetZ() + _position.GetZ() };
		VECTOR rightUp =   {_maxXZ.GetX() + _position.GetX(), 0.0, _maxXZ.GetZ() + _position.GetZ() };
		VECTOR leftDown =  {_minXZ.GetX() + _position.GetX(), 0.0, _minXZ.GetZ() + _position.GetZ() };
		VECTOR leftUp =    {_minXZ.GetX() + _position.GetX(), 0.0, _maxXZ.GetZ() + _position.GetZ() };

		DrawLine3D(rightDown, rightUp, GetColor(255, 0, 0));
		DrawLine3D(rightUp, leftUp, GetColor(255, 0, 0));
		DrawLine3D(leftUp, leftDown, GetColor(255, 0, 0));
		DrawLine3D(leftDown, rightDown, GetColor(255, 0, 0));

#endif 
	}


}
