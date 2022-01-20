/*****************************************************************//**
 * @file   DamageFloorGimmick.cpp
 * @brief  ダメージ床ギミッククラス
 * 
 * @author hikaru Goto
 * @date   December 16 2021
 *********************************************************************/

#include "DamageFloorGimmick.h"


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

	}

	DamageFloorGimmick::~DamageFloorGimmick() {
	
		//_damageFloorV.clear();
	}

	void DamageFloorGimmick::Update()
	{
	//	_damageFloor->Update();
	}

	void DamageFloorGimmick::Draw() 
	{
		//_model->Draw();

			_damageFloor->Draw();


	}


}
