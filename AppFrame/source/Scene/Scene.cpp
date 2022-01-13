///
/// @file    Scene.cpp
/// @brief   �V�[���̊��N���X
///          �e�V�[���͂��̃N���X���p������
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "Scene.h"
#include "../Game.h"

//namespace Scene {
	/// �R���X�g���N�^
	Scene::Scene(Game& game) : _game{ game } {
	}
	/// �f�X�g���N�^
	Scene::~Scene() {
	}
	ActorServer& Scene::GetActorServer() {
		return _game.GetActorServer();
	}
	ActorFactory& Scene::GetActorFactory() {
		return _game.GetActorFactory();
	}

	/// �A�Z�b�g�T�[�o�[�̎擾
	AssetServer& Scene::GetAssetServer() {
		return _game.GetAssetServer();
	}
	/// �V�[���T�[�o�[�̎擾
	SceneServer& Scene::GetSceneServer() {
		return _game.GetSceneServer();
	}

	SoundComponent& Scene::GetSoundComponent() {
		return _game.GetSoundComponent();
	}


