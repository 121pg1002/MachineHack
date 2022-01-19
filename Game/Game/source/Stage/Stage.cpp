/*****************************************************************//**
 * @file   Stage.cpp
 * @brief  �X�e�[�W
 *
 * @author yamawaki kota, hikaru goto
 * @date   December 6 2021
 *********************************************************************/


#include "Stage.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Model/ModelComponent.h"
#include "../Actor/ActorServer.h"
#include "StageParameter.h"
#include "../Collision/CollisionComponent.h"


namespace MachineHuck::Stage {

	namespace {

		constexpr int StageAll = 3;        //!< �ǂݍ���stagejson�̐�
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
		_ground = std::make_unique<Model::ModelComponent>(*this);
		_ground->SetModel("Dungeon");
		//_ground->SetScale({1.f, 1.f, 1.f});

		//for (int i = 0; i < _boardH; i++) {

		//	for (int k = 0; k < _boardW; k++) {

		//		_board[i * _boardH + k] = 0;

		//	}
		//}
#ifdef _DEBUG

		_groundVertex.clear();
		_groundIndex.clear();


#endif

		_stageFloor.clear();
		//_boardStageNum.clear();
		//_allFloor.clear();
		_allFloorMap.clear();
		_secretV.clear();
		_secretVMap.clear();
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
		
		//�t���A�̖��O������
		auto handle = game.GetAssetServer().GetModel("Dungeon");

		//�i�r���b�V���̃R���W��������ݒ�
		GetCollision().SetMapCollision(handle.first);


		CreateGround();

		//�����̂���t���A�̂ݕ`��
		//_stageNo = 1;

		CreateStage(game);

		// �t�H�O�̐ݒ�
		 //SetFogEnable(TRUE);
		 //SetFogColor(247, 188, 101);
		 //SetFogStartEnd(50.0f, 15000.0f);
	}

	Stage::~Stage() {
		//_allFloor.clear();
		_allFloorMap.clear();
		//_floor.clear();
	}

	void Stage::Update() {

		//auto pos = GetActorServer().GetPosition("Player");
		// �X�J�C�X�t�B�A���v���C���Ɠ����ʒu�ɂ���
	   //_skySphere->SetPosition(ToDX(pos));

		_stageNo = PlayerOnStageNumber();

	}

	void Stage::Draw() {
		//_skySphere->Draw();   // �X�J�C�X�t�B�A
		_ground->Draw();      // �n��

		//�\������X�e�[�W�ԍ��̂ݕ\��
		//�L�[�̐����擾
		//auto num = _allFloor.count(_stageNo);

		//if (num != 0) {


			////////////////////////�ړ����̂�2��ʕ\������悤��
			//if (IsMoving()) {
			//
			//
			//}
			//else {
		//_stageNo = 1;

					// equal_range �֐����g���āA�w�肵���L�[�̍ŏ��ƏI�[�̈ʒu�������C�e���[�^�� std::pair<> �Ŏ擾���܂��B
					//auto[start, end] = _allFloor.equal_range(_stageNo);


					//// �擾�����C�e���[�^�͈̔͂����[�v�ŉ񂵂܂��B(���ł�10�t���A��)
					//for (auto iterator = start; iterator != end; iterator++)
					//{
					//	//�L�[�ƒl�̃Z�b�g���擾
					//	auto [key, value] = *iterator;

					//	for (auto j = 0; j < value.size(); j++) {

					//		//1�u���b�N��
					//		value[j]->Draw();
					//	}
					//}

					//�`�悷��t���A�ԍ��ŉ�
					for (auto&& no : _drawFloorV) {

						if (no != 0 && no != 3) {



							//��l���̐G��Ă���t���A�ԍ��ƈ�v�����ꍇ
		//					if (no == _stageNo) {

							auto value = _allFloorMap[no];
							//auto secret = _secretVMap[no];

							////�t���A���̃u���b�N��`��
							for (auto&& floor : value) {

								floor->Draw();
							}
						}

							//�B�����p�̋@�\(����)
							//for (auto i = 0; i != value.size(); i++) {
							//
							//	for (auto&& match : secret) {
							//	
							//		if (i != match) {

							//			value[i]->Draw();
							//		}
							//		
							//	}
							//	
							//}

						//}
						//else {
						//
						//}

						
					}
				
#ifdef _DEBUG


					auto stageNo = std::to_string(_stageNo);
					DrawFloor();
					DrawString(0, 50,stageNo.c_str(), GetColor(255, 0, 0));


#endif 
			//}

		
		//}





		//for (auto j = 0; j < _allFloor.size(); j++) {
		//	_allFloor[j]->Draw();
		//}

		//_allFloor[_stageNo][0]->Draw();
		

	}

#ifdef _DEBUG

	bool Stage::CreateGround() {
		// �n�ʑS�̂̒��S�����_�ɂ���I�t�Z�b�g
		constexpr auto groundPolygonSize = Differ;
		constexpr auto groundStartX = -groundPolygonSize * static_cast<float>(BoardSize) * 0.5;
		constexpr auto groundStartZ = 0.0;
		// ���_�p�̌Œ���
		constexpr VECTOR groundNormal = { 0.0f, 1.0f, 0.0f };
		constexpr COLOR_U8 groundDiffuse0 = { 0, 0, 0, 255 };
		constexpr COLOR_U8 groundDiffuse1 = { 255, 0, 0, 255 };
		constexpr COLOR_U8 groundDiffuse2 = { 0, 255, 0, 255 };
		constexpr COLOR_U8 groundDiffuse3 = { 0, 0, 255, 255 };
		constexpr std::array<COLOR_U8, 4> groundColorList = {
		groundDiffuse0, groundDiffuse1, groundDiffuse2, groundDiffuse3
		};
		constexpr COLOR_U8 groundSpecular = { 0, 0, 0, 0 };
		// �n�ʂ̊�{�̐����`�p�e�[�u��
		constexpr VECTOR groundPosition0 = { 0.0f, 0.0f, 0.0f };
		constexpr VECTOR groundPosition1 = { 0.0f, 0.0f, Differ };
		constexpr VECTOR groundPosition2 = { Differ, 0.0f, 0.0f };
		constexpr VECTOR groundPosition3 = { Differ, 0.0f, Differ };
		constexpr std::array<VECTOR, 4> groundPositionlist = {
			groundPosition0,groundPosition1, groundPosition2, groundPosition3
		};
		// uv �̃e�[�u��
		constexpr std::array<float, 4> uList = { 0.0f, 0.0f, 1.0f, 1.0f };
		constexpr std::array<float, 4> vList = { 0.0f, 1.0f, 0.0f, 1.0f };

		auto offsetX = groundStartX;
		auto offsetZ = groundStartZ;
		auto offsetIndex = 0;

		for (auto z = 0; z < BoardSize; ++z)
		{
			offsetX = groundStartX;

			for (auto x = 0; x < BoardSize; ++x)
			{
				// �����`���`������
				for (auto i = 0; i < 4; ++i)
				{
					VERTEX3D vertex;

					VECTOR base = groundPositionlist[i];

					base.x += static_cast<float>(offsetX);
					base.z += static_cast<float>(offsetZ);

					vertex.pos = base;
					vertex.norm = groundNormal;

					vertex.dif = groundColorList[i];


					vertex.spc = groundSpecular;
					vertex.u = uList[i];
					vertex.v = vList[i];

					_groundVertex.emplace_back(std::move(vertex));
				}

				auto index = offsetIndex;

				_groundIndex.emplace_back(index);
				_groundIndex.emplace_back(index + 1);
				_groundIndex.emplace_back(index + 2);

				_groundIndex.emplace_back(index + 2);
				_groundIndex.emplace_back(index + 1);
				_groundIndex.emplace_back(index + 3);

				offsetIndex += 4;

				offsetX += Differ;
			}

			offsetZ += Differ;
		}

		return true;
	}

	void Stage::DrawFloor() {
	

		auto vertexNum = static_cast<int>(_groundVertex.size());
		auto indexNum = static_cast<int>(_groundIndex.size());
		auto polygonNum = indexNum / 3;

		DrawPolygonIndexed3D(_groundVertex.data(), vertexNum, _groundIndex.data(), polygonNum, DX_NONE_GRAPH, FALSE);
	}

#endif 

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

				//�Ō�̈�ԏ�̗񂾂�����
				if (i != stageTableVector.size() - 1) {
				
					AppFrame::Math::Vector4 min = { static_cast<double>(j) * Differ + startX, 0.0, static_cast<double>(i) * Differ};
					AppFrame::Math::Vector4 max = { (j + 1) * Differ + startX, 0.0, (i + 1) * Differ };

					auto stageFloor = std::make_tuple(min, max, num);

					//�e�[�u���̔z�u�ʒu���L�[�Ƃ����e�X�e�[�W�t���A��min�����max
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
				for (int k = 0; k < stageVector.size(); k++) {

					auto sP = stageVector[k];
					auto pos = sP.GetPosition();
					Math::Vector4 dif = { offsetX, 0.0, offsetZ };

					//�ʒu�ɃI�t�Z�b�g�������Ă��炷
					pos = pos + dif;

					auto rot   = sP.GetRotation();
					auto scale = sP.GetScale();
					auto ground = std::make_unique<Model::ModelComponent>(*this);
					ground->SetModel(sP.GetName(), 1000000);

					//�Ƃ肠�����A���ŉB���̕ǂ���у^�C�����B���悤�̃x�N�^�[�ɓo�^
					if (sP.GetName() == "secretwall" || sP.GetName() == "secretfloor") {
						_secretV.push_back(k);
					}
					

					ground->SetPosition(ToDX(pos));
					ground->SetRotation(ToDX(rot));
					ground->SetScale(ToDX(scale));

					floor.push_back(std::move(ground));

				}

				//�Ƃ肠�����A���ŉB���̕ǂ���у^�C�����B���悤�̃X�e�[�W�ԍ��ɓo�^
				_secretVMap.emplace(num, _secretV);

				offsetX += Differ;

				//��́A�X�e�[�W�ԍ��Ŋi�[
				//_allFloor.emplace(num, std::move(floor));

				//���́A�t���A�ԍ��Ŋi�[
				_allFloorMap.emplace(i * BoardSize + j, std::move(floor));
				//_board[i * _boardH + j] = i * 10 + j;
				//_boardStageNum.push_back(num);
			}

			offsetZ += Differ;
			

		}

		return true;
	}

	int Stage::PlayerOnStageNumber() {

		_drawFloorV.clear();
		int stageNo = 0;
		std::vector<int> stageNoV;
	
		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {
		
			if ((*i)->GetTypeId() != TypeId::Player) {
				continue;
			}
			else {

				//std::vector<int> stageNo;

				for (auto&& map : _stageFloor) {

					auto [floorNum, tuple] = map;
					auto [min, max, stageNum] = tuple;



					//////////////////////�����ǁA�S�ăt���A�Ƃ̔�����͂�������min��max�����ꂷ���Ă������������Ȃ��悤�ɂ�����
					//��l���Ɗe�t���A�Ƃ̓����蔻�������
					if (_collision->CircleToAABB(**i, min, max)) {

						stageNoV.push_back(floorNum);

						AppFrame::Math::Vector4 leftUp    = { min.GetX(), 0.0, max.GetZ() };
						AppFrame::Math::Vector4 rightDown = { max.GetX(), 0.0, min.GetZ() };

						auto player = GetActorServer().GetPosition("Player");

						//�~�̒��S���l�p�`�̒��ɂ���ꍇ
						auto leftTriangle = AppFrame::Math::Utility::InsideTrianglePoint(min, leftUp, rightDown, player);
						auto rightTriangle = AppFrame::Math::Utility::InsideTrianglePoint(rightDown, leftUp, max, player);

						
						if (leftTriangle || rightTriangle) {
							stageNo = floorNum;
						}

					}


				}

			
				
			}


		}



		_drawFloorV = stageNoV;
		return stageNo;
	}

	//int Stage::GetBoard(int x, int z) {
	//	return _board[z * _boardH + x];
	//}


	//void Stage::SetBoard(int x, int z, int n) {
	//	_board[z * _boardH + x] = n;
	//}
}
