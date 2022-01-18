///
/// @file    Actor.cpp
/// @brief   �A�N�^�[
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
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

	bool Actor::CollisionFloor(AppFrame::Math::Vector4 oldPos) {

		//Actor�̕��Ɉړ��������������ǂ݂̂��S�����肷�邩��

		// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY hitPoly;

		auto handle = GetGame().GetAssetServer().GetModel("Dungeon");

		for (auto i = GetActorServer().GetActors().begin(); i != GetActorServer().GetActors().end(); i++) {

			if ((*i)->GetTypeId() != TypeId::Stage) {
				continue;
			}
			else {

				auto frameMapCollision = (*i)->GetCollision().GetMapCollision();

				Math::Vector4 dif = { 0.0, 40.0, 0.0 };
				Math::Vector4 under = { 0.0, -99999.0, 0.0 };
				auto startPos = _position + dif;
				auto endPos = _position + under;
				// ��l���̍��ʒu���牺�����ւ̒���
				hitPoly = MV1CollCheck_Line(handle.first, frameMapCollision, ToDX(startPos), ToDX(endPos));

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

