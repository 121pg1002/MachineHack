///
/// @file    Actor.cpp
/// @brief   アクター
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

//namespace Actor {
	Actor::Actor(Game& game) : _game{ game }
	{
		_collision = std::make_unique<CollisionComponent>(*this);
	}

	Actor::~Actor() {

	}

	//CollisionComponent& Actor::GetCollision() 
	//{
	//	return *_collision;
	//}

	void Actor::ComputeWorldTransform() {
		auto world = MGetScale(ToDX(_scale));
		world = MMult(world, MGetRotZ(_rotation.GetZ()));
		world = MMult(world, MGetRotX(_rotation.GetX()));
		world = MMult(world, MGetRotY(_rotation.GetY()));
		_worldTransform = MMult(world, MGetTranslate(ToDX(_position)));
	}

	ActorServer& Actor::GetActorServer() {
		return _game.GetActorServer();
	}

	void Actor::SetStateComponent(std::unique_ptr<StateComponent> state) {
		_state = std::move(state);
	}

	void Actor::SetModelComponent(std::unique_ptr</*Model::*/ModelAnimeComponent> model) {
		_model = std::move(model);
	}

	void Actor::SetCameraComponent(std::shared_ptr<CameraComponent> camera) {
		_camera = camera;
	}
//}
