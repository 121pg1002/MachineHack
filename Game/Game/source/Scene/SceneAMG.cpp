///
/// @file    SceneTitle.cpp
/// @brief   タイトル画面
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "AppFrame.h"
#include "SceneAMG.h"
#include <DxLib.h>
//using namespace Asset;
namespace SceneAMG {
  /// コンストラクタ
  SceneAMG::SceneAMG(Game& game)
    :Scene{ game }
  {
  }
  /// 初期化
  void SceneAMG::Init() {
    // 使用する画像のテーブル
    const /*Asset::*/AssetServer::TextureMap textureToUsed{
      {"AMGBg",          {"title/AMG.png",          1, 1, 1920, 1080}},
      /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
          {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
    };
    // アセットサーバーの取得
    auto& as = GetAssetServer();
    // 画像の読み込み
    as.LoadTextures(textureToUsed);

    // 画像のハンドル取得
    _amgBgHandle = as.GetTexture("AMGBg");
    /*  _gameTitleHandle = as.GetTexture("GameTitle");
      _leftClickToStart = as.GetTexture("LeftClickToStart");*/

      // サウンドコンポーネントの取得
    auto& sc = GetSoundComponent();
    sc.PlayLoop("bgm1");
    sc.SetVolume("bgm1", 50);
  }
  ///
  /// 入口
  /// 
  void SceneAMG::Enter() {
    _alpha = 0;
  }
  ///
  /// 入力
  ///
  void SceneAMG::Input(InputComponent& input) {
    if (input.GetMouse().LeftClick()) {
      // 左クリックでInGameへ遷移
      GetSceneServer().GoToScene("Team");
      _alpha = 255;
    }
  }
  /// 更新
  void SceneAMG::Update() {
    _alpha = (_alpha + 8) % 255;
    if (_alpha > 200) {
      // Teamへ遷移
      GetSceneServer().GoToScene("Team");
      _alpha = 255;
    }
  }
  ///
  /// 描画
  ///
  void SceneAMG::Render() {
    DrawGraph(0, 0, _amgBgHandle, false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    // DrawGraph(0, 0, _gameAMGHandle, true);
  }
}
