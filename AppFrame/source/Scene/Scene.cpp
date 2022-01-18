/*****************************************************************//**
 * @file  Scene.cpp
 * @brief �V�[���̊��N���X
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

#include "Scene.h"
#include "../Game.h"

namespace Asset = AppFrame::Asset;
namespace Scene = AppFrame::Scene;
namespace Sound = AppFrame::Sound;
/// �R���X�g���N�^
Scene::Scene::Scene(Game& game): _game{game} {
}
/// �f�X�g���N�^
Scene::Scene::~Scene() {
}
MachineHuck::Actor::ActorServer& Scene::Scene::GetActorServer() {
	return _game.GetActorServer();
}
MachineHuck::Actor::ActorFactory& Scene::Scene::GetActorFactory() {
	return _game.GetActorFactory();
}

/// �A�Z�b�g�T�[�o�[�̎擾
Asset::AssetServer& Scene::Scene::GetAssetServer() {
  return _game.GetAssetServer();
}
/// �V�[���T�[�o�[�̎擾
Scene::SceneServer& Scene::Scene::GetSceneServer() {
  return _game.GetSceneServer();
}

Sound::SoundComponent& Scene::Scene::GetSoundComponent() {
	return _game.GetSoundComponent();
}

/// UI�R���|�[�l���g�̎擾
MachineHuck::UI::UIComponent& Scene::Scene::GetUiComponent() {
	return _game.GetUiComponent();
}


