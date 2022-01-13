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
#include "../Collision/CollisionComponent.h"


namespace MachineHuck::Stage {
	namespace {

		constexpr int StageAll = 2;        //!< �ǂݍ���stagejson�̐�
		constexpr double Differ   = 500.0; //!< 1�t���A�̃T�C�Y
		constexpr double StartX   = -5.0 * Differ;
		constexpr int BoardSize = 10;

		//constexpr double HalfSize = 0.5 * Differ;
		//constexpr int StartZ = -5.0 * Differ;
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

		//for (int i = 0; i < _boardH; i++) {

		//	for (int k = 0; k < _boardW; k++) {

		//		_board[i * _boardH + k] = 0;

		//	}
		//}

		_stageFloor.clear();
		//_boardStageNum.clear();
		_allFloor.clear();
		//_floor.clear();

		//////�Ƃ肠�����A���͉�
		for (int i = 0; i < StageAll; i++) {

			//�X�e�[�W�ԍ���string�ɕϊ�
			auto no = std::to_string(i);
			//���̓���N�������json���ǂݍ��߂�
			//auto stageParameter = std::make_unique<StageParameter>();
			game.GetStageParameter().LoadStageParameter(i, "resource/json/stage" + no + ".json");
		}

		game.GetStageParameter().LoadStageTable("resource/json/stagetable.json");
		// �n�ʂ̃��f��
		//_ground = std::make_unique<ModelComponent>(*this);
		//_ground->SetModel("Ground");
		//_ground->SetScale({10.f, 10.f, 10.f});

		//const auto& stageVector = game.GetStageParameter().GetStageVector();

		//for (int i = 0; i < stageVector.size(); i++) {

		//	auto sP = stageVector[i];
		//	auto pos = sP.GetPosition();
		//	auto rot = sP.GetRotation();
		//	auto scale = sP.GetScale();


		//	auto ground = std::make_unique<Model::ModelComponent>(*this);
		//	ground->SetModel(sP.GetName(), 100);

		//	ground->SetPosition(ToDX(pos));
		//	ground->SetRotation(ToDX(rot));
		//	ground->SetScale(ToDX(scale));

		//	_floor.push_back(std::move(ground));
		//}


		//�����̂���t���A�̂ݕ`��
		_stageNo = 1;

		CreateStage(game);

		// �t�H�O�̐ݒ�
		 //SetFogEnable(TRUE);
		 //SetFogColor(247, 188, 101);
		 //SetFogStartEnd(50.0f, 15000.0f);
	}

	Stage::~Stage() {
		_allFloor.clear();
		//_floor.clear();
	}

	void Stage::Update() {

		auto pos = GetActorServer().GetPosition("Player");
		// �X�J�C�X�t�B�A���v���C���Ɠ����ʒu�ɂ���
	   //_skySphere->SetPosition(ToDX(pos));

	}

	void Stage::Draw() {
		//_skySphere->Draw();   // �X�J�C�X�t�B�A
		//_ground->Draw();      // �n��

		//�\������X�e�[�W�ԍ��̂ݕ\��
		//�L�[�̐����擾
		auto num = _allFloor.count(_stageNo);

		//if (num != 0) {


			////////////////////////�ړ����̂�2��ʕ\������悤��
			//if (IsMoving()) {
			//
			//
			//}
			//else {


					// equal_range �֐����g���āA�w�肵���L�[�̍ŏ��ƏI�[�̈ʒu�������C�e���[�^�� std::pair<> �Ŏ擾���܂��B
					auto[start, end] = _allFloor.equal_range(_stageNo);


					// �擾�����C�e���[�^�͈̔͂����[�v�ŉ񂵂܂��B(���ł�10�t���A��)
					for (auto iterator = start; iterator != end; iterator++)
					{
						//�L�[�ƒl�̃Z�b�g���擾
						auto [key, value] = *iterator;

						for (auto j = 0; j < value.size(); j++) {

							//1�u���b�N��
							value[j]->Draw();
						}
					}
				
			
			//}

		
		//}





		//for (auto j = 0; j < _allFloor.size(); j++) {
		//	_allFloor[j]->Draw();
		//}

		//_allFloor[_stageNo][0]->Draw();
		

	}

	bool Stage::CreateStage(AppFrame::Game& game) {

		auto stageTableVector = game.GetStageParameter().GetStageTableVector();
	
		auto startX = StartX;
		auto startZ = 0.0;

		auto offsetX = startX;
		auto offsetZ = startZ;

		//�t���A��
		for (auto i = 0; i < stageTableVector.size(); i++) {
		
			offsetX = startX;
			//1�񕪂̃t���A
			for (auto j = 0; j < stageTableVector[i].size(); j++) {
			
				//1�񕪂�j�Ԗڂ̐��l
				auto num = stageTableVector[i][j];

				//�c�̗񂪍Ō�̗񂾂�����
				if (i != stageTableVector.size() - 1) {
				
					AppFrame::Math::Vector2 min = { static_cast<double>(j) * Differ, static_cast<double>(i) * Differ };
					AppFrame::Math::Vector2 max = { (j + 1) * Differ, (i + 1) * Differ };

					auto stageFloor = std::make_tuple(min, max, num);

					//�e�[�u���̔z�u�ʒu���L�[�Ƃ����e�X�e�[�W�t���A��
					_stageFloor.emplace(i * BoardSize + j, stageFloor);
				}


				
				//_board[i * _boardH + j] = i * BoardSize + j;
				//_boardStageNum.push_back(num);

				if (num == 0) {
				offsetX += Differ;

				continue;
				}
				//else if (num != ) {
				//
				//}

				//�t���A�ԍ��Ə����擾
				auto stageNumMap = game.GetStageParameter().GetFloorMap();
				
				//_floor.clear();
				

				//�ǂݍ��ރt���A
				auto stageVector = stageNumMap[num-1];

				Floor floor;
				floor.clear();
				
				//�t���A�̊e�u���b�N
				for (int i = 0; i < stageVector.size(); i++) {

					auto sP = stageVector[i];
					auto pos = sP.GetPosition();
					Math::Vector4 dif = { offsetX, 0.0, offsetZ };

					//�ʒu�ɃI�t�Z�b�g�������Ă��炷
					pos = pos + dif;

					auto rot = sP.GetRotation();
					auto scale = sP.GetScale();
					auto ground = std::make_unique<Model::ModelComponent>(*this);
					ground->SetModel(sP.GetName(), 1000);

					ground->SetPosition(ToDX(pos));
					ground->SetRotation(ToDX(rot));
					ground->SetScale(ToDX(scale));

					floor.push_back(std::move(ground));

				}

				offsetX += Differ;
				_allFloor.emplace(num, std::move(floor));
				//_board[i * _boardH + j] = i * 10 + j;
				//_boardStageNum.push_back(num);
			}

			offsetZ += Differ * 2;
			

		}

		return true;
	}

	int Stage::PlayerOnStageNumber() {

		int stageNo = 0;
		std::vector<int> stageNoV;
	
		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
		
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//std::vector<int> stageNo;

				for (auto map : _stageFloor) {

					auto [floorNum, tuple] = map;
					auto [min, max, stageNum] = tuple;


					//////////////////////�����ǁA�S�ăt���A�Ƃ̔�����͂�������min��max�����ꂷ���Ă������������Ȃ��悤�ɂ�����
					//��l���Ɗe�t���A�Ƃ̓����蔻�������
					if (_collision->CircleToAABB((**i), min, max)) {

						stageNoV.push_back(stageNum);

						//if (_collision->LineToAABB(**i, min, max)) {
						//
						//}
					}


				}

			
				
			}


		}




		return stageNo;
	}

	//int Stage::GetBoard(int x, int z) {
	//	return _board[z * _boardH + x];
	//}


	//void Stage::SetBoard(int x, int z, int n) {
	//	_board[z * _boardH + x] = n;
	//}
}
