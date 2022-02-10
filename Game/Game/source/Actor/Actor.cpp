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
#include "../Gauge/GaugeEnemy.h"
#include "../Gauge/GaugePlayer.h"
#include "../Gimmick/GimmickBase.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Actor {

	Actor::Actor(AppFrame::Game& game) : _game{ game }
	{
		_collision = std::make_unique<Collision::CollisionComponent>(*this);
		_gaugeBase = std::make_unique<Gauge::GaugeBase>(*this);
		_gaugeEnemy = std::make_unique<Gauge::GaugeEnemy>(*this);
		_gaugePlayer = std::make_unique<Gauge::GaugePlayer>(*this);
		//_gimmickBase = std::make_unique<Gimmick::GimmickBase>(*this);

	}

	Actor::~Actor() {

	}

	void Actor::Draw() {
		DrawLine3D(ToDX(_startPos), ToDX(_endPos), GetColor(0, 255, 255));
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

	bool Actor::CollisionFloor() {

		// �ړ�������ŃR���W��������
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

						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision();
						//�n���h���̃R���W���������擾
						auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
						auto endPos = _position + under;
						// ��l���̍��ʒu���牺�����ւ̒���
						hitPoly = MV1CollCheck_Line(handle, frameMapCollision, ToDX(startPos), ToDX(endPos));



						if (hitPoly.HitFlag) {
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {

							return false;
						}
					}
				}

			}

		}


		return false;
	}

	bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos, double r) {


		// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;

		//MV1_COLL_RESULT_POLY hitPolyX;
		//MV1_COLL_RESULT_POLY hitPolyZ;
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

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
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

							//// ������Ȃ������B���̍��W�ɖ߂�
							_position = oldPos;


							return false;
						}
					}
				}

			}

		}

		return false;



	}

	bool Actor::CollisionGimmick() {

		// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Gimmick) {
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
						auto frameGimmickCollision = (*i)->GetCollision().GetGimmickCollision(handle);
						//auto frameMapCollision = (*i)->GetCollision().GetMapCollision(handle.first);

						Math::Vector4 up = { 0.0, 99.0, 0.0 };
						Math::Vector4 under = { 0.0, -99999.0, 0.0 };
						auto startPos = _position + up;
						auto endPos = _position + under;
						// ��l���̍��ʒu���牺�����ւ̒���
						hitPoly = MV1CollCheck_Line(handle, frameGimmickCollision, ToDX(startPos), ToDX(endPos));



						if (hitPoly.HitFlag) {
							_position = { _position.GetX(), hitPoly.HitPosition.y, _position.GetZ() };

							return true;
						}
						else {

							return false;
						}
					}
				}

			}

		}


		return false;
	}

	//�󂹂�ǂƓ������Ă��邩
	bool Actor::CollisionWall(Actor& gimmick, Math::Vector4 move) {

		//// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {
				//�󂹂�ǂ̃n���h��
				auto handle = gimmick.GetModel().GetHandle();

				//�󂹂�ǂ̃n���h�����擾
				//auto&&[handle, actNo] = gimmick.GetGame().GetAssetServer().GetModel("BrokenWall");
				//(*i)->GetGame().GetAssetServer().
				//�M�~�b�N�̃R���W�����t���[�����擾
				//auto gimmickFrameCollision = (*i)->GetCollision().GetGimmickCollision(handle);

				
				//auto frameGimmick = gimmick.GetActorServer().GetGimmickCollision(handle);
				auto frameGimmick = GetGame().GetActorServer().GetGimmickCollision(handle);
				//auto gimmickMap = gimmick.GetModel().GetModelGimmick();

				//auto frameGimmick = gimmickMap[handle];
				Math::Vector4 yDif = { 0.0, 10.0, 0.0 };

				auto startPos = _position + move * 100 + yDif;
				auto endPos = _position + yDif;
				// ��l���̍��ʒu����O�����ւ̒���
				hitPoly = MV1CollCheck_Line(handle, frameGimmick, ToDX(startPos), ToDX(endPos));

#ifdef _DEBUG
				_startPos = startPos;
				_endPos = endPos;
#endif 

				if (hitPoly.HitFlag) {
					//// ��������
					_judge = true;
					return true;

				}
				else {
					_judge = false;
					return false;
				}

			}
		}

		return false;
	}

	VECTOR Actor::WarpFloor(Actor& act) {

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

								//�u���b�N�ƃR���W����������
								if (frameIndex != 0 && frameIndex != 1) {

									//���[�v�O�̐G�ꂽ�t���[�������擾
									std::string name = MV1GetFrameName(handle, frameIndex);



									//�_�N�g���ǂ���
									if (name.size() > 8) {

										std::string::size_type nameParts = name.find("entry");

										//���݂���
										if (nameParts != std::string::npos) {

											//�n�b�L���O��Ԃ�
											if (act.IsHucked()) {
												return VGet(0.0f, 0.0f, 0.0f);
											}
											else {
												//�_�N�g�t���O��ݒ�
												Flag::FlagData::SetDuctWarp(true);
											}

										}


									}

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

									return pos;
								
								
								}



								//_position = { static_cast<double>(pos.x),  static_cast<double>(pos.y) , static_cast<double>(pos.z) };

								

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

								//������̐����_�N�g�̏o���T�C�Y(2����)�ł͂Ȃ���
								if (keyStr.size() > 3) {
								
									//// ��������
									return true;
								}
								else {

									if (Flag::FlagData::GetDuctWarp()) {
										return true;
									}
									continue;
								}


							}
							else {

								continue;
							}

						}

						return false;
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

	void Actor::SetModelAnimeComponent(std::unique_ptr<Model::ModelAnimeComponent> model) {
		_modelAnime = std::move(model);
	}

	void Actor::SetModelComponent(std::unique_ptr<Model::ModelComponent> model) {
		_model = std::move(model);
	}

	void Actor::SetCameraComponent(std::shared_ptr<Camera::CameraComponent> camera) {
		_camera = camera;
	}
}

