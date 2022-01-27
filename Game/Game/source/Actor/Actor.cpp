/*****************************************************************//**
 * @file   Actor.cpp
 * @brief  �A�N�^�[�N���X
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/

#include "AppFrame.h"
#include "Actor.h"
#include "ActorServer.h"
#include "../Camera/CameraComponent.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"
#include "../Collision/CollisionComponent.h"
#include "../Gauge/GaugeBase.h"

namespace MachineHuck::Actor {

	Actor::Actor(AppFrame::Game& game) : _game{ game }
	{
		_collision = std::make_unique<Collision::CollisionComponent>(*this);
		_gaugeBase = std::make_unique<Gauge::GaugeBase>(*this);
	}

	Actor::~Actor() {

	}

	//CollisionComponent& Actor::GetCollision() 
	//{
	//	return *_collision;
	//}

	void Actor::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(static_cast<float>(_rotation.GetZ())));
		world = MMult(world, MGetRotX(static_cast<float>(_rotation.GetX())));
		world = MMult(world, MGetRotY(static_cast<float>(_rotation.GetY())));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	//bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos, int num) {


	//	// �ړ�������ŃR���W��������
	//	MV1_COLL_RESULT_POLY hitPoly;

	//	//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

	//	//AssetServer�̕��ɐ����Ńn���h�����擾�ł���悤�ɂ���
	//	//�����̃n���h�����X�e�[�W�̂ݔԍ��Ŏ擾�ł���悤�ɂ���
	//	auto handle = GetGame().GetAssetServer().GetMap(num);
	//	//���������������������������������������������������ɏ���

	//	//auto handle = GetGame().GetAssetServer().GetModel(handleName);

	//	for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

	//		if ((*i)->GetTypeId() != TypeId::Stage) {
	//			continue;
	//		}
	//		else {

	//			

	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
	//			//�n���h���̃R���W���������擾
	//			auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);
	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

	//			Math::Vector4 dif = { 0.0, 50.0, 0.0 };
	//			Math::Vector4 under = { 0.0, -99999.0, 0.0 };
	//			auto startPos = _position + dif;
	//			auto endPos = _position + under;
	//			// ��l���̍��ʒu���牺�����ւ̒���
	//			
	//			hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision, ToDX(startPos), ToDX(endPos));

	//			if (hitPoly.HitFlag) {
	//				// ��������
	//				// ��������Y�ʒu���L�������W�ɂ���
	//				_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

	//				return true;
	//			}
	//			else {
	//				// ������Ȃ������B���̍��W�ɖ߂�
	//				_position = oldPos;


	//				return false;
	//			}

	//		}

	//	}

	//	return false;

	//}

	//bool Actor::WarpFloor(int num) {

	//	//// �ړ�������ŃR���W��������
	//	MV1_COLL_RESULT_POLY hitPoly;

	//	//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

	//	//AssetServer�̕��ɐ����Ńn���h�����擾�ł���悤�ɂ���
	//	//�����̃n���h�����X�e�[�W�̂ݔԍ��Ŏ擾�ł���悤�ɂ���
	//	auto handle = GetGame().GetAssetServer().GetMap(num);
	//	//���������������������������������������������������ɏ���

	//	//auto handle = GetGame().GetAssetServer().GetModel(handleName);

	//	for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

	//		if ((*i)->GetTypeId() != TypeId::Stage) {
	//			continue;
	//		}
	//		else {

	//			auto keys = (*i)->GetCollision().GetWarpName(handle.first);

	//			//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
	//			for (auto keyStr : keys){
	//			
	//				//�n���h���̃R���W���������擾
	//				auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle.first);
	//				//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

	//				Math::Vector4 dif = { 0.0, 50.0, 0.0 };
	//				Math::Vector4 under = { 0.0, -99999.0, 0.0 };
	//				auto startPos = _position + dif;
	//				auto endPos = _position + under;
	//				// ��l���̍��ʒu���牺�����ւ̒���
	//				hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

	//				if (hitPoly.HitFlag) {
	//					//// ��������
	//					//// ��������Y�ʒu���L�������W�ɂ���
	//					//_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

	//					//���������t���[���C���f�b�N�X
	//					auto frameIndex = hitPoly.FrameIndex;

	//					//���[�v�O�̐G�ꂽ�t���[�������擾
	//					std::string name = MV1GetFrameName(handle.first, frameIndex);


	//	                //���[�v���b�V�����ɂ���n�C�t�����΂�������
	//					auto x = name.substr(3, 2);

	//					auto xStr = x;
	//					xStr.substr(0, 1);

	//					if (xStr != "0") {
	//						x = x.substr(1, 1);
	//					}

	//					int xNum = std::atoi(x.c_str());

	//					//���[�v���b�V�����ɂ���n�C�t�����΂�������
	//					auto y = name.substr(5, 2);
	//					auto yStr = y;
	//					yStr.substr(0, 1);


	//					if (yStr != "0") {
	//						y = y.substr(1, 1);
	//					}

	//					int yNum = std::atoi(y.c_str());

	//					//�t���A�ԍ��v�Z
	//					auto floorNum = yNum * 10 + xNum;

	//					//���[�v��̃t���[����
	//					auto toWarpName  = (*i)->GetCollision().GetWarpNameFloor(floorNum, name);

	//					//���[�v��̃X�e�[�W�ԍ�
	//					auto warpStageNum = (*i)->GetCollision().GetFloorStageNum(floorNum);
	//					
	//					//���[�v��̃n���h��
	//					auto toWarpHandle = GetGame().GetAssetServer().GetMap(warpStageNum);

	//					//���[�v��̃t���[���C���f�b�N�X
	//					int toWarpFrameIndex = MV1SearchFrame(toWarpHandle.first, toWarpName.c_str());
	//					
	//					//���[�v��̈ʒu���擾
	//					auto pos = MV1GetFramePosition(toWarpHandle.first, toWarpFrameIndex);

	//					//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };
	//					_position = {0.0, 0.0, 0.0};

	//					return true;
	//				}
	//				else {

	//					return false;
	//				}
	//			
	//			}

	//		}

	//	}


	//	return false;
	//}

	bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos) {


		// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;

		//auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

		//AssetServer�̕��ɐ����Ńn���h�����擾�ł���悤�ɂ���
		//�����̃n���h�����X�e�[�W�̂ݔԍ��Ŏ擾�ł���悤�ɂ���
		//auto handle = GetGame().GetAssetServer().GetMap(num);




		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//�S�t���A�}�b�v���擾
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//�G��Ă���t���A�ԍ����擾
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();



						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						//�n���h���̃R���W���������擾
						auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 dif = { 0.0, 50.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + dif;
						auto endPos = _position + under;
						// ��l���̍��ʒu���牺�����ւ̒���

						hitPoly = MV1CollCheck_Line(handle, frameMapCollision, ToDX(startPos), ToDX(endPos));

						if (hitPoly.HitFlag) {
							// ��������
							// ��������Y�ʒu���L�������W�ɂ���
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {
							// ������Ȃ������B���̍��W�ɖ߂�
							_position = oldPos;


							return false;
						}
					}
				}

			}

		}

		return false;



	}

	VECTOR Actor::WarpFloor() {

		//// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;


		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//�S�t���A�}�b�v���擾
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//�G��Ă���t���A�ԍ����擾
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();

						auto keys = (*i)->GetCollision().GetWarpName(handle);

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						for (auto keyStr : keys) {

							//�n���h���̃R���W���������擾
							auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle);
							//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

							Math::Vector4 dif = { 0.0, 50.0, 0.0 };
							Math::Vector4 under = { 0.0, -99999.0, 0.0 };
							auto startPos = _position + dif;
							auto endPos = _position + under;
							// ��l���̍��ʒu���牺�����ւ̒���
							hitPoly = MV1CollCheck_Line(handle, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

							if (hitPoly.HitFlag) {
								//// ��������
								//// ��������Y�ʒu���L�������W�ɂ���
								//_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };


									//���������t���[���C���f�b�N�X
								auto frameIndex = hitPoly.FrameIndex;

								//���[�v�O�̐G�ꂽ�t���[�������擾
								std::string name = MV1GetFrameName(handle, frameIndex);


								//���[�v���b�V�����ɂ���n�C�t�����΂�������
								auto x = name.substr(3, 2);

								auto xStr = x;
								xStr.substr(0, 1);

								if (xStr != "0") {
									x = x.substr(1, 1);
								}

								int xNum = std::atoi(x.c_str());

								//���[�v���b�V�����ɂ���n�C�t�����΂�������
								auto y = name.substr(6, 2);
								auto yStr = y;
								yStr.substr(0, 1);


								if (yStr != "0") {
									y = y.substr(1, 1);
								}

								int yNum = std::atoi(y.c_str());

								//�t���A�ԍ��v�Z
								auto floorNum = yNum * 10 + xNum;

								//���[�v��̃t���[����
								auto toWarpName = (*i)->GetCollision().GetWarpNameFloor(floorNum, name);

								////���[�v���b�V�����ɂ���n�C�t�����΂�������
								//x = toWarpName.substr(3, 2);

								//xStr = x;
								//xStr.substr(0, 1);

								//if (xStr != "0") {
								//	x = x.substr(1, 1);
								//}

								//xNum = std::atoi(x.c_str());

								////���[�v���b�V�����ɂ���n�C�t�����΂�������
								//y = toWarpName.substr(6, 2);
								//yStr = y;
								//yStr.substr(0, 1);


								//if (yStr != "0") {
								//	y = y.substr(1, 1);
								//}

								//yNum = std::atoi(y.c_str());

								////�t���A�ԍ��v�Z
								//auto warpFloorNum = yNum * 10 + xNum;


								////���[�v��̃X�e�[�W�ԍ�
								//auto warpStageNum = (*i)->GetCollision().GetFloorStageNum(floorNum);

								////���[�v��̃n���h��
								//auto toWarpHandle = GetGame().GetAssetServer().GetMap(warpStageNum);

								//���[�v��̃t���A�ԍ��̃|�C���^�z����擾
								auto warpFloor = allFloorMap[floorNum];


								if (warpFloor.empty()) {

									printfDx("���[�v�t���A�|�C���^�����݂��Ȃ�");
									return VGet(0.0f, 0.0f, 0.0f);

								}

								//���[�v��̃|�C���^���擾
								auto warp = warpFloor[0];

								//���[�v��̃n���h�����擾
								auto warpHandle = warp->GetHandle();

								//���[�v��̃t���[���C���f�b�N�X
								int toWarpFrameIndex = MV1SearchFrame(warpHandle, toWarpName.c_str());


								//���[�v��̈ʒu���擾
								auto pos = MV1GetFramePosition(warpHandle, toWarpFrameIndex);

								//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };

								return pos;

							}

						}

						return VGet(0.0f, 0.0f, 0.0f);
					}
				}


			}

		}


		return VGet(0.0f, 0.0f, 0.0f);
	}

	//���[�v���̓����蔻��
	bool Actor::WarpingFloor() {

		//// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;


		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				//�S�t���A�}�b�v���擾
				auto allFloorMap = (*i)->GetCollision().GetAllFloorMap();

				//�G��Ă���t���A�ԍ����擾
				auto floorNums = (*i)->GetCollision().GetFloorNum();


				for (auto&& floorNum : floorNums) {



					for (auto&& floor : allFloorMap[floorNum]) {

						auto&& handle = floor->GetHandle();

						auto keys = (*i)->GetCollision().GetWarpName(handle);

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						for (auto keyStr : keys) {

							//�n���h���̃R���W���������擾
							auto frameMapCollision = (*i)->GetCollision().GetWarpCollision(keyStr, handle);
							//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

							Math::Vector4 dif = { 0.0, 50.0, 0.0 };
							Math::Vector4 under = { 0.0, -99999.0, 0.0 };
							auto startPos = _position + dif;
							auto endPos = _position + under;
							// ��l���̍��ʒu���牺�����ւ̒���
							hitPoly = MV1CollCheck_Line(handle, frameMapCollision.second, ToDX(startPos), ToDX(endPos));

							if (hitPoly.HitFlag) {
								//// ��������
								return true;

							}
							else {

								return false;
							}

						}
					}
				}


			}

		}


		return false;
	}

	ActorServer& Actor::GetActorServer() {
		return _game.GetActorServer();
	}

	void Actor::SetStateComponent(std::unique_ptr<State::StateComponent> state) {
		_state = std::move(state);
	}

	void Actor::SetModelComponent(std::unique_ptr<Model::ModelAnimeComponent> model) {
		_model = std::move(model);
	}

	void Actor::SetCameraComponent(std::shared_ptr<Camera::CameraComponent> camera) {
		_camera = camera;
	}
}

