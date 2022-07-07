/*****************************************************************//**
 * @file  Scene.cpp
 * @brief シーンの基底クラス
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

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
MachineHuck::UI::UIComponent& Scene::Scene::GetUiComponent() {
	return _game.GetUiComponent();
}

//ゲージの取得
MachineHuck::Gauge::GaugeBase& Scene::Scene::GetGaugeBaseUI() {
	return _game.GetGaugeBaseUI();
}
MachineHuck::Gauge::GaugePlayer& Scene::Scene::GetGaugePlayerUI() {
	return _game.GetGaugePlayerUI();
}
MachineHuck::Gauge::GaugeEnemy& Scene::Scene::GetGaugeEnemyUI() {
	return _game.GetGaugeEnemyUI();
}


