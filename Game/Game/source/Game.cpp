///
/// @file    Game.cpp
/// @brief   ゲームクラスの定義
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "../source/Scene/SceneInGame.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/SceneTitle.h"
#include "../source/Scene/SceneTeam.h"
#include "../source/Scene/ScenePrologue.h"
#include "../source/Scene/SceneEpilogue.h"
#include "../source/Scene/SceneAMG.h"
#include "../source/Scene/SceneMap.h"
#include "../source/Scene/SceneItem.h"
#include "../source/Actor/ActorServer.h"
#include "../source/Actor/ActorFactory.h"
#include "../source/Stage/StageParameter.h"
#include "../source/Gimmick/GimmickParameter.h"
#include "../source/Effect/EffectServer.h"
#include "../source/UI/UIComponent.h"
#include "../source/UI/SpriteServer.h"
#include <DxLib.h>

AppFrame::Game::Game() {
}

AppFrame::Game::~Game() {
}
/// 初期化
bool AppFrame::Game::Initialize() {
  // 画面モードのを設定
  SetGraphMode(1920, 1080, 32);
  // ウィンドウモードに指定する
  ChangeWindowMode(true);

  // Dxライブラリ初期化
  if (DxLib_Init() == -1) {
    return false;
  }
                                                   //追加
  
  // 画面の背景色を青に設定する
  SetBackgroundColor(10, 10, 10);
  // 描画先画面を裏にする
  SetDrawScreen(DX_SCREEN_BACK);

  //Effekseerの初期化
  MachineHuck::Effect::EffectServer::EffekseerInit();                     //追加

  // Ｚバッファを有効にする
  SetUseZBuffer3D(TRUE);

  // Ｚバッファへの書き込みを有効にする
  SetWriteZBuffer3D(TRUE);

  // マテリアルの自己発光色を暗い青色にする
#ifdef _DEBUG
  MATERIALPARAM material;
  material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
  material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
  material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
  material.Power = 20.0f;
  SetMaterialParam(material);
#endif



  // インプットコンポーネントの生成
  _input = std::make_unique<AppFrame::Input::InputComponent>();

  // サウンドコンポーネントの生成
  _sound = std::make_unique<AppFrame::Sound::SoundComponent>(*this);

  // アクターサーバーの生成
  _actorServer = std::make_unique<MachineHuck::Actor::ActorServer>();

  // アクターファクトリーの生成
  _actorFactory = std::make_unique<MachineHuck::Actor::ActorFactory>(*this);

  // スプライトサーバーの生成
  _spriteServer = std::make_unique<MachineHuck::UI::SpriteServer>();

  // UIコンポーネントの生成
  _ui = std::make_unique<MachineHuck::UI::UIComponent>(*this);


  // アセットサーバーの生成
  _assetServer = std::make_unique<AppFrame::Asset::AssetServer>(*this);

  // アセットサーバーの取得
  auto& as = GetAssetServer();
  // アセットのカレントフォルダ設定
  as.ChangeCurrentPath("resource");

  // 使用する音のテーブル
  const AppFrame::Asset::AssetServer::SoundMap soundToUsed{
    {"damage", {"damage.wav", true}},
    {"charging", {"se/ビーム砲チャージ.mp3", true}},
    {"push", {"se/決定、ボタン押下33.mp3", true}},
    {"bgm1", {"se/energy.mp3", false}},

    // {"bgm2", {"stage1.mid", false}},
  };
  // 音の読み込み
  as.LoadSounds(soundToUsed);
  // サウンドコンポーネントの取得
  auto& sc = GetSoundComponent();
  sc.SetVolume("damage", 128);
  sc.SetVolume("push", 128);
#ifdef _DEBUG
  sc.SetMute(false);
#else
  sc.SetMute(false);
#endif

  // シーンサーバーを生成＆タイトルを生成して最初のシーンとして登録
  _sceneServer = std::make_unique<AppFrame::Scene::SceneServer>("AMG", std::make_shared<MachineHuck::Scene::SceneAMG>(*this));
  
 
  _sceneServer->Register("Team", std::make_shared<MachineHuck::Scene::SceneTeam>(*this));
  _sceneServer->Register("Title", std::make_shared<MachineHuck::Scene::SceneTitle>(*this));
  _sceneServer->Register("Prologue", std::make_shared<MachineHuck::Scene::ScenePrologue>(*this));
  _sceneServer->Register("Epilogue", std::make_shared<MachineHuck::Scene::SceneEpilogue>(*this));
  _sceneServer->Register("Map", std::make_shared<MachineHuck::Scene::SceneMap>(*this));
  _sceneServer->Register("Item", std::make_shared<MachineHuck::Scene::SceneItem>(*this));

  // インゲームを生成してシーンとして登録
  _sceneServer->Register("InGame", std::make_shared<MachineHuck::Scene::SceneInGame>(*this));

  _stageParam = std::make_unique<MachineHuck::Stage::StageParameter>();
  _gParam = std::make_unique<MachineHuck::Gimmick::GimmickParameter>();

  return true;
}
/// 実行
void AppFrame::Game::Run() {
  // メインループ
  while (_state != State::Quit) {
    Input(*_input);  // 入力
    Update(); // 更新
    Render(); // 描画
  }
}
/// 停止
void AppFrame::Game::Shutdown() {                                                     //追加
    //Effekseer終了処理
    MachineHuck::Effect::EffectServer::EndEffekseer();            //追加
                                                                                      // Dxライブラリ終了
  DxLib_End();
}
/// 入力
void AppFrame::Game::Input(AppFrame::Input::InputComponent& input) {
  // Windows 特有の面倒な処理をライブラリにやらせる
  if (ProcessMessage() == -1) {
    _state = State::Quit;  // -1 が返ってきたのでゲームを終了する
  }
  // 入力状態の更新
  _input->Update();
  if (_input->GetJoypad().Exit()) {
    _state = State::Quit;  // ESC押されたのでゲームを終了する
  }
  _sceneServer->Input(*_input);    // シーンサーバーの入力処理を実行
}
/// 更新
void AppFrame::Game::Update() {
  _sceneServer->Update(); // シーンサーバーの更新処理を実行
}
/// 描画
void AppFrame::Game::Render() {
  ClearDrawScreen();      // 画面をクリアする
  _sceneServer->Render(); // シーンサーバーの描画処理を実行
  ScreenFlip();           // 裏画面を表示する
}
/// アクターサーバーの取得
//ActorServer& Game::GetActorServer() const {
//  return _sceneServer->GetScene().GetActorServer();
//}
