///
/// @file    Stage.cpp
/// @brief   �X�e�[�W
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "Stage.h"
#include "AppFrame.h"
#include "../Model/ModelComponent.h"
#include "../Actor/ActorServer.h"
#include "StageParameter.h"


namespace MachineHuck::Stage {
	namespace {

		constexpr int StageAll = 1;
	}

	Stage::Stage(AppFrame::Game& game) : Actor::Actor{ game } {
		// �X�J�C�X�t�B�A�̃��f��
		//_skySphere = std::make_unique<ModelComponent>(*this);
		//_skySphere->SetModel("SkySphere");
		//_skySphere->SetScale({ 80.f,  80.f, 80.f });
		//// �n�ʂ̃��f��
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});


		//////�Ƃ肠�����A���͉�
		for (int i = 0; i < StageAll; i++) {

			//�X�e�[�W�ԍ���string�ɕϊ�
			auto no = std::to_string(i);
			//���̓���N�������json���ǂݍ��߂�
			//auto stageParameter = std::make_unique<StageParameter>();
			game.GetStageParameter().LoadStageParameter("resource/json/stage" + no + ".json");
		}

		// �n�ʂ̃��f��
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});

		const auto& stageVector = game.GetStageParameter().GetStageVector();

		for (int i = 0; i < stageVector.size(); i++) {

			auto sP = stageVector[i];
			auto pos = sP.GetPosition();
			auto rot = sP.GetRotation();
			auto scale = sP.GetScale();


			auto ground = std::make_unique<Model::ModelComponent>(*this);
			ground->SetModel(sP.GetName(), 100);

			ground->SetPosition(ToDX(pos));
			ground->SetRotation(ToDX(rot));
			ground->SetScale(ToDX(scale));

			_grounds.push_back(std::move(ground));
		}

		// �t�H�O�̐ݒ�
		 //SetFogEnable(TRUE);
		 //SetFogColor(247, 188, 101);
		 //SetFogStartEnd(50.0f, 15000.0f);
	}

	void Stage::Update() {

		auto pos = GetActorServer().GetPosition("Player");
		// �X�J�C�X�t�B�A���v���C���Ɠ����ʒu�ɂ���
	   //_skySphere->SetPosition(ToDX(pos));

	}

	void Stage::Draw() {
		//_skySphere->Draw();   // �X�J�C�X�t�B�A
		//_ground->Draw();  // �n��

		for (auto i = 0; i < _grounds.size(); i++) {

			_grounds[i]->Draw();

		}

	}
}
