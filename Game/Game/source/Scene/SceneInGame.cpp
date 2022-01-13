///
/// @file    SceneInGame.cpp
/// @brief   �C���Q�[�����
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "SceneInGame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include <numbers>
//using namespace Asset;
namespace SceneInGame {
  /// �R���X�g���N�^
  SceneInGame::SceneInGame(Game& game)
    :Scene{ game }
  {
  }
  /// ������
  void SceneInGame::Init() {
    // �g�p���郂�f��

    /*Asset::*/AssetServer::ModelMap usedInGame{
      {"Player",    "SDChar/SDChar.mv1"},
      {"SkySphere", "skysphere.mv1"},
      {"Ground",    "ground.mv1"},
      {"Spider",    "Spider_3.mv1"},
    };

    // ���f���̓ǂݍ���
    GetAssetServer().LoadModels(usedInGame);                                                         //�ǉ�
  }
  /// ����
  void SceneInGame::Enter() {
    // �t�@�N�g���̐����ƃN���G�C�^�[�̓o�^
    auto& af = GetActorFactory();
    af.Register("Player", std::make_unique<PlayerCreator>());
    af.Register("TackleEnemy", std::make_unique<EnemyCreator>());
    af.Register("Stage", std::make_unique<StageCreator>());

    ActorFactory::SpawnTable inGame{
      {0     , "TackleEnemy", { 300.f, 200.f, 300.0f}},
      {0     , "TackleEnemy", {   0.f, 220.f, 500.0f}},
      {0     , "TackleEnemy", {-300.f, 210.f, 400.0f}},

      //{60 * 5, "Enemy", { 1500.f, 2100.f, 400}},
      //{0     , "Enemy", {    0.f, 2200.f, 400}},
      //{0     , "Enemy", {-1500.f, 2000.f, 400}},

      //{60 * 10,"Enemy", { 1000.f, 2000.f, -4500}},
      //{0     , "Enemy", {    0.f, 2200.f, -4500}},
      //{0     , "Enemy", {-1000.f, 2100.f, -4500}},

      //{60 * 15,"Enemy", { 1500.f, 2000.f, -4500}},
      //{0     , "Enemy", {    0.f, 2200.f, -4500}},
      //{0     , "Enemy", {-1500.f, 2100.f, -4500}},
    };

    af.SetSpawnTable(inGame);

    //// �A�N�^�[�T�[�o�[�ɓo�^���ʃA�N�Z�X�p
    auto& as = GetActorServer();
    //for (int i = 0; i < 3; i++) 
    //{
    //    auto spawnTable = inGame[i];
    //    std::string u = static_cast<std::string>(i);
    //    auto enemy = af.Create(spawnTable._key);
    //    std::pair<math::Vector4, math::Vector4> pos_dir = { spawnTable._position, spawnTable._rotation };
    //    as.Register("Enemy" + u, pos_dir);
    //    as.Add(std::move(enemy));
    //}

    // �v���C���[�̐����ƒǉ�
    auto player = af.Create("Player");
    std::pair<math::Vector4, math::Vector4> pos_dir = { player->GetPosition(), player->GetRotation() };
    as.Register("Player", pos_dir);
    as.Add(std::move(player));

    // �^������
    //std::random_device seed;
    //std::mt19937 engine{seed()};
    //std::uniform_real_distribution<float> zPosition{1000, 2500};
    //std::uniform_real_distribution<float> forwardSpeed{3, 9};

    // �X�e�[�W�̐����ƒǉ�
    auto stage = af.Create("Stage");
    as.Add(std::move(stage));
    Update();
  }
  /// ���͏���
  void SceneInGame::Input(InputComponent& input) {

    if (input.GetMouse().RightClick()) {
      // �E�N���b�N�Ń^�C�g���֑J��
      GetSceneServer().GoToScene("Title");
    }
    GetActorServer().Input(input);
  }
  /// �X�V
  void SceneInGame::Update() {
    GetActorFactory().UpdateSpawn();
    GetActorServer().Update();
  }

  /// �`��
  void SceneInGame::Render() {
    GetActorServer().Render();
  }
  /// �o��
  void SceneInGame::Exit() {
    // �A�N�^�[���폜
    GetActorServer().Clear();
    // �f���v���P�[�g�������f�������폜
    GetAssetServer().DeleteDuplicateModels();
    // �N���G�C�^�[���폜
    GetActorFactory().Clear();
  }
}