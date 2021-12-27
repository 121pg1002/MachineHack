///
/// @file    Scene.cpp
/// @brief   シーンの基底クラス
///          各シーンはこのクラスを継承する
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "Scene.h"
#include "../Game.h"

//namespace Scene {
	/// コンストラクタ
	Scene::Scene(Game& game) : _game{ game } {
	}
	/// デストラクタ
	Scene::~Scene() {
	}
	ActorServer& Scene::GetActorServer() {
		return _game.GetActorServer();
	}
	ActorFactory& Scene::GetActorFactory() {
		return _game.GetActorFactory();
	}

	/// アセットサーバーの取得
	AssetServer& Scene::GetAssetServer() {
		return _game.GetAssetServer();
	}
	/// シーンサーバーの取得
	SceneServer& Scene::GetSceneServer() {
		return _game.GetSceneServer();
	}

	SoundComponent& Scene::GetSoundComponent() {
		return _game.GetSoundComponent();
	}


