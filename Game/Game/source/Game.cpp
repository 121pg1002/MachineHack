///
/// @file    Game.cpp
/// @brief   �Q�[���N���X�̒�`
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "../source/Scene/SceneInGame.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/SceneTitle.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/SceneAMG.h"
#include "../source/Actor/ActorServer.h"
#include "../source/Actor/ActorFactory.h"
#include "../source/Stage/StageParameter.h"
#include <DxLib.h>

AppFrame::Game::Game() {
}

AppFrame::Game::~Game() {
}
/// ������
bool AppFrame::Game::Initialize() {
  // ��ʃ��[�h�̂�ݒ�
  SetGraphMode(1920, 1080, 32);
  // �E�B���h�E���[�h�Ɏw�肷��
  ChangeWindowMode(true);
  // Dx���C�u����������
  if (DxLib_Init() == -1) {
    return false;
  }
                                                   //�ǉ�

  // ��ʂ̔w�i�F��ɐݒ肷��
  SetBackgroundColor(100, 0, 255);
  // �`����ʂ𗠂ɂ���
  SetDrawScreen(DX_SCREEN_BACK);

  // �y�o�b�t�@��L���ɂ���
  SetUseZBuffer3D(TRUE);

  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(TRUE);

  // �}�e���A���̎��Ȕ����F���Â��F�ɂ���
#ifdef _DEBUG
  MATERIALPARAM material;
  material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
  material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
  material.Power = 20.0f;
  SetMaterialParam(material);
#endif


  // �C���v�b�g�R���|�[�l���g�̐���
  _input = std::make_unique<AppFrame::Input::InputComponent>();

  // �T�E���h�R���|�[�l���g�̐���
  _sound = std::make_unique<AppFrame::Sound::SoundComponent>(*this);

  // �A�N�^�[�T�[�o�[�̐���
  _actorServer = std::make_unique<MachineHuck::Actor::ActorServer>();

  // �A�N�^�[�t�@�N�g���[�̐���
  _actorFactory = std::make_unique<MachineHuck::Actor::ActorFactory>(*this);


  // �A�Z�b�g�T�[�o�[�̐���
  _assetServer = std::make_unique<AppFrame::Asset::AssetServer>(*this);

  // �A�Z�b�g�T�[�o�[�̎擾
  auto& as = GetAssetServer();
  // �A�Z�b�g�̃J�����g�t�H���_�ݒ�
  as.ChangeCurrentPath("resource");

  // �g�p���鉹�̃e�[�u��
  const AppFrame::Asset::AssetServer::SoundMap soundToUsed{
    {"damage", {"damage.wav", true}},
    {"bgm1", {"sublight.wav", false}},
    {"bgm2", {"stage1.mid", false}},
  };
  // ���̓ǂݍ���
  as.LoadSounds(soundToUsed);
  // �T�E���h�R���|�[�l���g�̎擾
  auto& sc = GetSoundComponent();
  sc.SetVolume("damage", 128);
#ifdef _DEBUG
  sc.SetMute(false);
#else
  sc.SetMute(false);
#endif

  // �V�[���T�[�o�[�𐶐����^�C�g���𐶐����čŏ��̃V�[���Ƃ��ēo�^
  _sceneServer = std::make_unique<AppFrame::Scene::SceneServer>("AMG", std::make_shared<MachineHuck::Scene::SceneAMG>(*this));
  
 
  _sceneServer->Register("Team", std::make_shared<MachineHuck::Scene::SceneTeam>(*this));
  _sceneServer->Register("Title", std::make_shared<MachineHuck::Scene::SceneTitle>(*this));

  // �C���Q�[���𐶐����ăV�[���Ƃ��ēo�^
  _sceneServer->Register("InGame", std::make_shared<MachineHuck::Scene::SceneInGame>(*this));

  _stageParam = std::make_unique<MachineHuck::Stage::StageParameter>();

  return true;
}
/// ���s
void AppFrame::Game::Run() {
  // ���C�����[�v
  while (_state != State::Quit) {
    Input(*_input);  // ����
    Update(); // �X�V
    Render(); // �`��
  }
}
/// ��~
void AppFrame::Game::Shutdown() {                                                     //�ǉ�
  // Dx���C�u�����I��
  DxLib_End();
}
/// ����
void AppFrame::Game::Input(AppFrame::Input::InputComponent& input) {
  // Windows ���L�̖ʓ|�ȏ��������C�u�����ɂ�点��
  if (ProcessMessage() == -1) {
    _state = State::Quit;  // -1 ���Ԃ��Ă����̂ŃQ�[�����I������
  }
  // ���͏�Ԃ̍X�V
  _input->Update();
  if (_input->GetJoypad().Exit()) {
    _state = State::Quit;  // ESC�����ꂽ�̂ŃQ�[�����I������
  }
  _sceneServer->Input(*_input);    // �V�[���T�[�o�[�̓��͏��������s
}
/// �X�V
void AppFrame::Game::Update() {
  _sceneServer->Update(); // �V�[���T�[�o�[�̍X�V���������s
}
/// �`��
void AppFrame::Game::Render() {
  ClearDrawScreen();      // ��ʂ��N���A����
  _sceneServer->Render(); // �V�[���T�[�o�[�̕`�揈�������s
  ScreenFlip();           // ����ʂ�\������
}
/// �A�N�^�[�T�[�o�[�̎擾
//ActorServer& Game::GetActorServer() const {
//  return _sceneServer->GetScene().GetActorServer();
//}
