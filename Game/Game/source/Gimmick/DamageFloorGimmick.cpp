/*****************************************************************//**
 * @file   DamageFloorGimmick.cpp
 * @brief  ダメージ床ギミッククラス
 * 
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/

#include "DamageFloorGimmick.h"
#include "../Model/ModelAnimComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Actor/ActorServer.h"
#include "../State/StateComponent.h"
#include "../Gauge/GaugeBase.h"
#include "../Gauge/GaugePlayer.h"



namespace MachineHuck::Gimmick {
	DamageFloorGimmick::DamageFloorGimmick(AppFrame::Game& game) : GimmickBase(game) {
	
		//_damagefloorV.clear();
	
		_damageFloor = std::make_unique<Model::ModelComponent>(*this);
		_damageFloor->SetModel("DamageFloor", 5);
	//	_damageFloor->SetPosition();

		//{0, "DamageFloor", { 200.f, 200.f, 0.0f }},
		//{ 0     , "DamageFloor", {  0.f,  200.f, 0.0f} },
		//{ 0     , "DamageFloor", {-200.f, 200.f, 0.0f} },
		//_damageFloorV.push_back(std::move(damageFloor));
		_r = 20.0;
		_typeGimmick = TypeGimmick::DamageFloor;

	}

	DamageFloorGimmick::~DamageFloorGimmick() {
	
		//_damageFloorV.clear();
	}

	void DamageFloorGimmick::Update()
	{
	//	_damageFloor->Update();
		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
			if ((*i)->GetTypeId() == TypeId::Player) {
				(*i)->GetGame().GetGaugePlayerUI().DownGauge(10);
				//	_actorState = Actor::ActorState::Dead;

				break;
			}
		}
	}

	void DamageFloorGimmick::Draw() 
	{
		//_model->Draw();

			_damageFloor->Draw();


	}


}
