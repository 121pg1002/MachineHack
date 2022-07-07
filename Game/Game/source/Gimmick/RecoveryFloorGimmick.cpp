/*****************************************************************//**
 * @file  RecoveryFloorGimmick.cpp
 * @brief  回復床（セーブポイント）ギミッククラス
 *
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/

#include "RecoveryFloorGimmick.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Actor/ActorServer.h"
#include "../State/StateComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"

namespace MachineHuck::Gimmick {
	RecoveryFloorGimmick::RecoveryFloorGimmick(AppFrame::Game& game) : GimmickBase(game) {

		//_damagefloorV.clear();

		//_recoveryFloor = std::make_unique<Model::ModelComponent>(*this);
		//_recoveryFloor->SetModel("RecoveryFloor", 5);
		//	_damageFloor->SetPosition();

			//{0, "DamageFloor", { 200.f, 200.f, 0.0f }},
			//{ 0     , "DamageFloor", {  0.f,  200.f, 0.0f} },
			//{ 0     , "DamageFloor", {-200.f, 200.f, 0.0f} },
			//_damageFloorV.push_back(std::move(damageFloor));
		_collisionR = 50.0;
		_typeGimmick = TypeGimmick::RecoveryFloor;

	}

	RecoveryFloorGimmick::~RecoveryFloorGimmick() {

		//_damageFloorV.clear();
	}

	void RecoveryFloorGimmick::Update()
	{
		//	_damageFloor->Update();
		ComputeWorldTransform();
		_model->Update();
		//for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
		//	if ((*i)->GetTypeId() == TypeId::Player) {
		//		(*i)->GetGame().GetGaugePlayerUI().PlusGauge(1000);
		//	//	_actorState = Actor::ActorState::Dead;

		//		break;
		//	}
		//}
	}

	void RecoveryFloorGimmick::Draw()
	{
		_model->Draw();
#ifdef _DEBUG
		//円の描画
		for (double i = 0.0; i < 720.0; i++)
		{
			double radian = DX_PI / 180.0 * i / 2.0;
			double x = _collisionR * std::cos(radian);
			double z = _collisionR * std::sin(radian);

			Math::Vector4 move = { x, 0.0, z };

			Math::Vector4 newpos = _position + move;
			DrawPixel3D(ToDX(newpos), GetColor(0, 255, 0));

		}
		//_recoveryFloor->Draw();

#endif 


	}


}
