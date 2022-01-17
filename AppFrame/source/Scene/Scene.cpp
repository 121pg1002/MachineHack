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

namespace Asset = AppFrame::Asset;
namespace Scene = AppFrame::Scene;
namespace Sound = AppFrame::Sound;
/// コンストラクタ
Scene::Scene::Scene(Game& game): _game{game} {
}
/// デストラクタ
Scene::Scene::~Scene() {
}
MachineHuck::Actor::ActorServer& Scene::Scene::GetActorServer() {
	return _game.GetActorServer();
}
MachineHuck::Actor::ActorFactory& Scene::Scene::GetActorFactory() {
	return _game.GetActorFactory();
}

/// アセットサーバーの取得
Asset::AssetServer& Scene::Scene::GetAssetServer() {
  return _game.GetAssetServer();
}
/// シーンサーバーの取得
Scene::SceneServer& Scene::Scene::GetSceneServer() {
  return _game.GetSceneServer();
}

Sound::SoundComponent& Scene::Scene::GetSoundComponent() {
	return _game.GetSoundComponent();
}


/// UIコンポーネントの取得
MachineHuck::UI::UIComponent& Scene::Scene::uiComponent() {
	return _game.uiComponent();
}