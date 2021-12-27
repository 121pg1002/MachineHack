///
/// @file    ActorFactory.cpp
/// @brief   アクターファクトリー
/// @date    2021/12/6
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "ActorFactory.h"
#include "ActorServer.h"
#include "../Player/Player.h"
#include "../Enemy/TackleEnemy.h"
#include "../Stage/Stage.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"
#include "../Camera/CameraComponent.h"
using namespace StateComponent;
/// コンストラクタ
ActorFactory::ActorFactory(Game& game): _game{game} {
}
/// クリエイターの登録
bool ActorFactory::Register(std::string_view type, std::unique_ptr<CreatorBase> creator) {
  if (_creatorMap.contains(type.data())) {
    return false;
  }
  _creatorMap.emplace(type.data(), std::move(creator));
  return true;
}
/// アクターの生成
std::unique_ptr<Actor> ActorFactory::Create(std::string_view type) {
  if (!_creatorMap.contains(type.data())) {
    return nullptr;
  }
  auto&& creator = _creatorMap[type.data()];
  return creator->Create(_game);
}

void ActorFactory::Clear() {
  _creatorMap.clear();
}

void ActorFactory::SetSpawnTable(SpawnTable spawnTable) {
  _spawnProgress = 0;
  _progress = 0;
  _spawnTable = spawnTable;
}

void ActorFactory::UpdateSpawn() {
  while (_spawnTable.size() > _spawnProgress) {
    auto& spawnRecord = _spawnTable[_spawnProgress];
    if (spawnRecord._progress > _progress) {
      break;
    }else{
      auto&& actor = Create(spawnRecord._key);
      actor->SetPosition(spawnRecord._position);
      actor->SetRotation(spawnRecord._rotation);
      _game.GetActorServer().Add(std::move(actor));
      ++_spawnProgress;
    }
  }
  ++_progress;
}

/// プレイヤーの生成
std::unique_ptr<Actor> PlayerCreator::Create(Game& game) {
  // カメラの生成
  auto camera = std::make_shared</*Camera::*/CameraComponent>();
  camera->Init();
  camera->SetPosition({0, 50, -200});
  camera->SetTarget({0, 50, 0});

  // プレイヤーの生成
  auto player = std::make_unique <Player::Player> (game);
  player->SetCameraComponent(camera);

  // モデルの読み込みと生成
  auto model = std::make_unique</*Model::*/ModelAnimeComponent>(*player);
  model->SetModel("Player");
  model->Register("Idle",      0);
  model->Register("Run",       1);
  model->Register("Attack",    2);
  model->Register("JumpStart", 3);
  model->Register("JumpLoop",  4);
  model->Register("JumpEnd",   5);
  player->SetModelComponent(std::move(model));

  auto state = std::make_unique<StateComponent::StateComponent>("Idle", std::make_shared <Player::Player::StateIdle>(*player));
  state->Register("Run", std::make_shared<Player::Player::StateRun>(*player));
  state->Register("Attack", std::make_shared<Player::Player::StateAttack>(*player));
  //state->Register("KnockBack", std::make_shared<Player::StateKnockBack>(*player));
  state->Register("Hucking", std::make_shared<Player::Player::StateHucking>(*player));
  state->Register("Hucked", std::make_shared<Player::Player::StateHucked>(*player));
  player->SetStateComponent(std::move(state));

  return player;
}

/// エネミーの生成
std::unique_ptr<Actor> EnemyCreator::Create(Game& game) {
  // エネミーの生成
  auto enemy = std::make_unique<Enemy::TackleEnemy>(game);
  
  // エネミーのjsonからパラメーターを読み込む
  //enemy->LoadJson("resource/test.json");

  // 速度は3〜9でランダム
  enemy->SetForwardSpeed(1.0f);

  // モデルの読み込みと生成
  auto model = std::make_unique < /*Model::*/ ModelAnimeComponent > (*enemy);
  model->SetModel("Spider", 1000);
  model->Register("Attack",     0);
  model->Register("Die",        1);
  model->Register("Die2",       2);
  model->Register("Fall",       3);
  model->Register("Jump",       4);
  model->Register("Normal",     5);
  model->Register("RunAniBack", 6);
  model->Register("RunAniVor",  7);
  model->Register("RunLeft",    8);
  model->Register("RunRight",   9);
  model->Register("WalkAniBack",10);
  model->Register("WalkAniBor", 11);
  model->Register("WalkLeft",   12);
  model->Register("WalkRight",  13);
  model->Register("WartePose",  14);
  enemy->SetModelComponent(std::move(model));

  auto state = std::make_unique</*State::*/StateComponent>("Fall", std::make_shared <Enemy::TackleEnemy::StateFall>(*enemy));
  state->Register("Idle", std::make_shared<Enemy::TackleEnemy::StateIdle>(*enemy));
  state->Register("Run", std::make_shared<Enemy::TackleEnemy::StateRun>(*enemy));
  state->Register("Die", std::make_shared<Enemy::TackleEnemy::StateDie>(*enemy));
  //state->Register("Attack", std::make_shared<Enemy::StateAttack>(*enemy));
  state->Register("IsHucking", std::make_shared<Enemy::TackleEnemy::StateHucking>(*enemy));
  state->Register("IsHucked", std::make_shared<Enemy::TackleEnemy::StateHucked>(*enemy));
  enemy->SetStateComponent(std::move(state));


  // 次の生成の為にカウントアップ
  ++_count;
  return enemy;
}

/// ステージの生成
std::unique_ptr<Actor> StageCreator::Create(Game& game) {
  /// ステージの生成
  auto stage = std::make_unique<Stage::Stage>(game);
  return stage;
}

