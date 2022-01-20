///
/// @file    SceneMap.cpp
/// @brief   マップ画面
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "SceneMap.h"


namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneMap::SceneMap(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// 初期化
    void  SceneMap::Init() {
        // 使用する画像のテーブル
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"MapBg",    {"Texture/cloth_00146.png",          1, 1, 1920, 1080}},
          /*    {"GameTitleAMG",        {"GameTitle.png",        1, 1, 1553, 224}},
              {"LeftClickToStartAMG", {"LeftClickToStart.png", 1, 1, 1135, 107}},*/
        };
        // アセットサーバーの取得
        auto& as = GetAssetServer();
        // 画像の読み込み
        as.LoadTextures(textureToUsed);

        // 画像のハンドル取得
        MapHandle = as.GetTexture("MapBg");
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
    void  SceneMap::Enter() {
        _alpha = 0;
    }
    ///
    /// 入力
    ///
    void  SceneMap::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // 左クリックでInGameへ遷移
            GetSceneServer().GoToScene("Team");
            _alpha = 255;
        }
        if (input.GetJoypad().Button_X()) {
            GetSceneServer().PopBack(1);
            GetSceneServer().PushBack("InGame",1);
            _alpha = 255;
        }

    }
    /// 更新
    void  SceneMap::Update() {
        _alpha = (_alpha + 8) % 255;
       
    }
    ///
    /// 描画
    ///
    void  SceneMap::Render() {
        DrawGraph(0, 0, MapHandle, false);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        // DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // DrawGraph(0, 0, _gameAMGHandle, true);
    }
}
