/*****************************************************************//**
 * @file   SceneTeam.cpp
 * @brief  チームロゴ画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "AppFrame.h"
#include "SceneTeam.h"
#include <DxLib.h>
#include"../Effect/EffectLaser.h"

namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneTeam::SceneTeam(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// 初期化
    void SceneTeam::Init() {
        // 使用する画像のテーブル
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"TeamBg",          {"title/team.png",          1, 1, 1920, 1080}},
          //{"GameTitleTeam",        {"GameTitle.png",        1, 1, 1553, 224}},
          //{"LeftClickToStartTeam", {"LeftClickToStart.png", 1, 1, 1135, 107}},
        };
        // アセットサーバーの取得
        auto& as = GetAssetServer();
        // 画像の読み込み
        as.LoadTextures(textureToUsed);


        // 画像のハンドル取得
        _teamBgHandle = as.GetTexture("TeamBg");
        //_gameTitleHandle = as.GetTexture("GameTitleTeam");
        //_leftClickToStart = as.GetTexture("LeftClickToStartTeam");

        // サウンドコンポーネントの取得
        auto& sc = GetSoundComponent();
        /*  sc.PlayLoop("bgm1");
          sc.SetVolume("bgm1", 50);*/
        //
        laser = std::make_unique<MachineHuck::Effect::EffectLaser>(VGet(0, 0, 0), 0, 0,0);
       // laser->LoadEffect("レーザー", "resource/Laser01.efkefc", 100.0f);
        laser->LoadEffect("レーザー", "resource/effect/Laser03.efkefc", 50.0f);
    }
    ///
    /// 入口処理
    /// 
    void SceneTeam::Enter() {
        _alpha = 0;
    }
    ///
    /// 入力処理.
    ///
    void SceneTeam::Input(AppFrame::Input::InputComponent& input) {
        if (input.GetMouse().LeftClick()) {
            // 左クリックでInGameへ遷移
            GetSceneServer().GoToScene("Title");
            _alpha = 255;
        }
    }
    void SceneTeam::Update() {
        //レーザーの更新
        laser->Update();
        _alpha = (_alpha + 8) % 255;
        //if (_alpha > 200) {
         if (_alpha > 250) {
            // Teamへ遷移
            GetSceneServer().GoToScene("Title");
            _alpha = 255;
        }
                                                   
    }
    ///
    /// 描画
    ///
    void SceneTeam::Render() {
        DrawGraph(0, 0, _teamBgHandle, FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        //  DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        //  DrawGraph(0, 0, _gameTeamHandle, TRUE);
        //レーザー描画
        laser->Render();
    }
}

