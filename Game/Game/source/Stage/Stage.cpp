///
/// @file    Stage.cpp
/// @brief   ステージ
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "AppFrame.h"
#include "Stage.h"
#include "../Model/ModelComponent.h"
#include "../Actor/ActorServer.h"

namespace Stage {
  Stage::Stage(Game& game) : Actor{ game } {
    // スカイスフィアのモデル
    _skySphere = std::make_unique<ModelComponent>(*this);
    _skySphere->SetModel("SkySphere");
    _skySphere->SetScale({ 80.f,  80.f, 80.f });
    // 地面のモデル
    _ground = std::make_unique<ModelComponent>(*this);
    _ground->SetModel("Ground");
    _ground->SetScale({ 10.f, 10.f, 10.f });

    // フォグの設定
    SetFogEnable(TRUE);
    SetFogColor(247, 188, 101);
    SetFogStartEnd(50.0f, 15000.0f);
  }

  void Stage::Update() {

    auto pos = GetActorServer().GetPosition("Player");
    // スカイスフィアをプレイヤと同じ位置にする
    _skySphere->SetPosition(ToDX(pos));

  }

  void Stage::Draw() {
    //_skySphere->Draw();   // スカイスフィア
    _ground->Draw();  // 地面
  }
}