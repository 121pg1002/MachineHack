/*****************************************************************//**
 * @file   RestrictionGate.cpp
 * @brief  �����Q�[�g�̃N���X
 *
 * @author kyoga tagawa
 * @date   February 20 2022
 *********************************************************************/
#include "RestrictionGate.h"
#include "../Model/ModelComponent.h"
#include "../Flag/FlagData.h"
#include "../Actor/ActorFactory.h"
#include "../State/StateBaseRoot.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"

namespace MachineHuck::Gimmick {

	RestrictionGate::RestrictionGate(AppFrame::Game& game) : GimmickBase(game) {
		//_state->GoToState("Close");
		 //�Q�[�g�C�x���g���I���ɂ���B
		//Flag::FlagData::SetGateflg(true);
		//�Q�[�g�����
		Flag::FlagData::SetOpenGate(false);
		
	}

	RestrictionGate::~RestrictionGate() {

	}

	void RestrictionGate::Update()
	{
		//�G�̐���0�Ȃ�Q�[�g���J����
		if (Flag::FlagData::GetEnemyNum() == 0) {
			Flag::FlagData::SetOpenGate(true);
		}

		
		if (Flag::FlagData::GetOpenGate()) {
			//_state->GoToState("Open");

		}
		
		ComputeWorldTransform();
		_model->Update();
	}

	void RestrictionGate::Draw()
	{
		//_state->Draw();
		_model->Draw();
	}


	void StateBase::Draw() {
		_owner.GetModelAnime().Draw();
	}


	void StateClose::Enter(){
		_owner.GetModelAnime().ChangeAnime("Close");
	}

	void StateClose::Input(AppFrame::Input::InputComponent& input){}

	void StateClose::Update(){}




	void StateOpen::Enter() { _owner.GetModelAnime().ChangeAnime("Open"); }

	void StateOpen::Input(AppFrame::Input::InputComponent& input) {}

	void StateOpen::Update() {}
}
