#include "Hole.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Gimmick {

	Hole::Hole(AppFrame::Game& game) : GimmickBase(game) {
	
		_minXZ = { -100.0, -50.0 };
		_maxXZ = { 100.0, 50.0 };
		_typeGimmick = TypeGimmick::Hole;
	}


	void Hole::Update(){
		ComputeWorldTransform();
		_model->Update();
	}

	void Hole::Draw(){
		_model->Draw();
		//_model->BrokenDraw();

#ifdef _DEBUG

		VECTOR rightDown = { _maxXZ.GetX() + _position.GetX(), 0.0, _minXZ.GetZ() + _position.GetZ() };
		VECTOR rightUp = { _maxXZ.GetX() + _position.GetX(), 0.0, _maxXZ.GetZ() + _position.GetZ() };
		VECTOR leftDown = { _minXZ.GetX() + _position.GetX(), 0.0, _minXZ.GetZ() + _position.GetZ() };
		VECTOR leftUp = { _minXZ.GetX() + _position.GetX(), 0.0, _maxXZ.GetZ() + _position.GetZ() };

		DrawLine3D(rightDown, rightUp, GetColor(255, 0, 0));
		DrawLine3D(rightUp, leftUp, GetColor(255, 0, 0));
		DrawLine3D(leftUp, leftDown, GetColor(255, 0, 0));
		DrawLine3D(leftDown, rightDown, GetColor(255, 0, 0));

#endif 
	}

}
