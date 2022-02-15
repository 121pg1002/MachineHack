/*****************************************************************//**
 * @file   DamageFloorGimmick.cpp
 * @brief  ダメージ床ギミッククラス
 * 
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/

#include "DamageFloorGimmick.h"
#include "../Model/ModelAnimComponent.h"
//#include "../Collision/CollisionComponent.h"
#include "../Actor/ActorServer.h"
//#include "../State/StateComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"



namespace MachineHuck::Gimmick {
	DamageFloorGimmick::DamageFloorGimmick(AppFrame::Game& game) : GimmickBase(game) {
	
		_minXZ = { -100.0, -50.0 };
		_maxXZ = { 100.0, 50.0 };
		_typeGimmick = TypeGimmick::DamageFloor;

	}

	DamageFloorGimmick::~DamageFloorGimmick() {
	
		//_damageFloorV.clear();
	}

	void DamageFloorGimmick::Update()
	{
		ComputeWorldTransform();
		_model->Update();

	//	_damageFloor->Update();
		//for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
		//	if ((*i)->GetTypeId() == TypeId::Player) {

		//		(*i)->GetGame().GetGaugePlayerUI().DownGauge(10);
		//		//	_actorState = Actor::ActorState::Dead;

		//		break;
		//	}
		//}
	}

	void DamageFloorGimmick::Draw() 
	{
		//_model->Draw();

			//_damageFloor->Draw();
		_model->Draw();

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
