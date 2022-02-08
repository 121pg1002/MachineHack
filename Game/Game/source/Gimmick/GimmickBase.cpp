/*****************************************************************//**
 * @file   GimmickBase.cpp
 * @brief  �M�~�b�N�̊��N���X
 *
 * @author hikaru Goto
 * @date   December 15 2021
 *********************************************************************/

#include "GimmickBase.h"
#include "../Actor/Actor.h"
#include "GimmickParameter.h"
#include "../Collision/CollisionComponent.h"



namespace MachineHuck::Gimmick {


	namespace {

		constexpr int StageAll = 1;        //!< �ǂݍ���gimmickstagejson�̐�
		//constexpr double Differ = 500.0; //!< 1�t���A�̃T�C�Y
		//constexpr double StartX = -5.0 * Differ;
		//constexpr int BoardSize = 10;

		//constexpr double HalfSize = 0.5 * Differ;
		//constexpr int StartZ = -5.0 * Differ;

	}


	GimmickBase::GimmickBase(AppFrame::Game& game) : Actor::Actor(game){



		////////�Ƃ肠�����A���͉�
		//for (int i = 0; i < StageAll; i++) {

		//	//�X�e�[�W�ԍ���string�ɕϊ�
		//	auto no = std::to_string(i);
		//	//���̓���N�������json���ǂݍ��߂�
		//	//auto stageParameter = std::make_unique<StageParameter>();
		//	if (game.GetGimmickParameter().LoadGimmickStageParameter(i, "resource/json/gimmick" + no + ".json")) {
		//	
		//	}
		//	else {
		//		printfDx("�M�~�b�N�ǂݍ��ݎ��s");
		//	}
		//}



	}



}


