/*****************************************************************//**
 * @file   ScenePrologue.cpp
 * @brief  プロローグ画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "AppFrame.h"
#include "ScenePrologue.h"
#include <DxLib.h>

namespace MachineHuck::Scene {
    /// コンストラクタ
    ScenePrologue::ScenePrologue(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// 初期化
    void ScenePrologue::Init() {
        // 使用する画像のテーブル
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"PrologueBg",          {"title/team.png",          1, 1, 1920, 1080}},
          //{"GameTitleTeam",        {"GameTitle.png",        1, 1, 1553, 224}},
          //{"LeftClickToStartTeam", {"LeftClickToStart.png", 1, 1, 1135, 107}},
        };
        // アセットサーバーの取得
        auto& as = GetAssetServer();
        // 画像の読み込み
        as.LoadTextures(textureToUsed);


        // 画像のハンドル取得
        _epilogueBgHandle = as.GetTexture("PrologueBg");
        //_gameTitleHandle = as.GetTexture("GameTitleTeam");
        //_leftClickToStart = as.GetTexture("LeftClickToStartTeam");

        // サウンドコンポーネントの取得
        auto& sc = GetSoundComponent();
        sc.PlayLoop("bgm1");
        sc.SetVolume("bgm1", 50);

    }
    ///
    /// 入口処理
    /// 
    void ScenePrologue::Enter() {
        _alpha = 0;
    }
    ///
    /// 入力処理.
    ///
    void ScenePrologue::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // 左クリックでInGameへ遷移
            GetSceneServer().GoToScene("InGame");
            _alpha = 255;
        }
    }
    void ScenePrologue::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Teamへ遷移
            GetSceneServer().GoToScene("InGame");
            _alpha = 255;
        }
    }
    ///
    /// 描画
    ///
    void ScenePrologue::Render() {
        DrawGraph(0, 0, _epilogueBgHandle, FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        //  DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        //  DrawGraph(0, 0, _gameTeamHandle, TRUE);
    }
}