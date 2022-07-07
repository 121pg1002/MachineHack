/*****************************************************************//**
 * @file   SceneEpilogue.cpp
 * @brief  エピローグ画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "SceneEpilogue.h"
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include "../ShadowMap/Shadowmap.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneEpilogue::SceneEpilogue(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// 初期化
    void SceneEpilogue::Init() {
        // 使用する画像のテーブル
        const AppFrame::Asset::AssetServer::TextureMap textureToUsed{
          {"EpilogueBg",          {"title/team.png",          1, 1, 1920, 1080}},
          //{"GameTitleTeam",        {"GameTitle.png",        1, 1, 1553, 224}},
          //{"LeftClickToStartTeam", {"LeftClickToStart.png", 1, 1, 1135, 107}},
        };
        // アセットサーバーの取得
        auto& as = GetAssetServer();
        // 画像の読み込み
        as.LoadTextures(textureToUsed);


        // 画像のハンドル取得
        _epilogueBgHandle = as.GetTexture("EpilogueBg");
        //_gameTitleHandle = as.GetTexture("GameTitleTeam");
        //_leftClickToStart = as.GetTexture("LeftClickToStartTeam");

        // サウンドコンポーネントの取得
        auto& sc = GetSoundComponent();
        sc.PlayLoop("bgm1");
        sc.SetVolume("bgm1", 50);
    }
    ///
    /// 出口処理
    /// 
    void SceneEpilogue::Exit() {
        // アクターを削除
        GetActorServer().Clear();
        // デュプリケートしたモデルだけ削除
        GetAssetServer().DeleteDuplicateModels();
        // デュプリケートしたモデルだけ削除
        GetAssetServer().DeleteDuplicateMaps();

        // クリエイターを削除
        GetActorFactory().Clear();
        //シャドウマップの削除
       // DeleteShadowMap(shadowmap.GetShadowmap());
    }
    ///
    /// 入口処理
    /// 
    void SceneEpilogue::Enter() {
        _alpha = 0;
    }
    ///
    /// 入力処理.
    ///
    void SceneEpilogue::Input(AppFrame::Input::InputComponent& input) {
        //if (input.GetMouse().LeftClick()) {
        //    // 左クリックでInGameへ遷移
        //    GetSceneServer().GoToScene("Title");
        //    _alpha = 255;
        //}
    }
    void SceneEpilogue::Update() {
        _alpha = (_alpha + 8) % 255;
        if (_alpha > 200) {
            // Teamへ遷移
            GetSceneServer().GoToScene("Title");
           // Flag::FlagData::SetBlackOutFlag(true);
            _alpha = 255;
        }
    }
    ///
    /// 描画
    ///
    void SceneEpilogue::Render() {
        DrawGraph(0, 0, _epilogueBgHandle, FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
        //  DrawGraph(1920 / 2 - 1135 / 2, 700 - 107 / 2, _leftClickToStart, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        //  DrawGraph(0, 0, _gameTeamHandle, TRUE);
    }
}