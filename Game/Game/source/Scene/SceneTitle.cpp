///
/// @file    SceneTitle.cpp
/// @brief   タイトル画面
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "SceneTitle.h"
#include <DxLib.h>
//using namespace Asset;
namespace SceneTitle {
  /// コンストラクタ
  SceneTitle::SceneTitle(Game& game)
    :Scene{ game }
  {
  }
  /// 初期化
  void SceneTitle::Init() {
    // 使用する画像のテーブル
    const /*Asset::*/AssetServer::TextureMap textureToUsed{
      {"TitleBg",          {"TitleBg.png",          1, 1, 1920, 1080}},
      {"GameTitle",        {"GameTitle.png",        1, 1, 1553, 224}},
      {"LeftClickToStart", {"LeftClickToStart.png", 1, 1, 1135, 107}},
    };
    // アセットサーバーの取得
    auto& as =GetAssetServer();
    // 画像の読み込み
    as.LoadTextures(textureToUsed);


    // 画像のハンドル取得
    _titleBgHandle = as.GetTexture("TitleBg");
    _gameTitleHandle = as.GetTexture("GameTitle");
    _leftClickToStart = as.GetTexture("LeftClickToStart");

    // サウンドコンポーネントの取得
    auto& sc = GetSoundComponent();
    sc.PlayLoop("bgm1");
    sc.SetVolume("bgm1", 50);
  }
  ///
  /// 入口
  /// 
  void SceneTitle::Enter() {
    _alpha = 0;
  }
  ///
  /// 入力
  ///
  void SceneTitle::Input(InputComponent& input) {
    if (input.GetMouse().LeftClick()) {
      // 左クリックでInGameへ遷移
      GetSceneServer().GoToScene("InGame");
      _alpha = 255;
    }
  }

  //更新
  void SceneTitle::Update() {
    _alpha = (_alpha + 8) % 255;
  }
  ///
  /// 描画
  ///
  void SceneTitle::Render() {
    DrawGraph(0, 0, _titleBgHandle, FALSE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawGraph(0, 0, _gameTitleHandle, TRUE);
  }
}
