/*****************************************************************//**
 * @file   SceneInGame.cpp
 * @brief  インゲーム画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/


#include "SceneInGame.h"
//#include <numbers>
#include "AppFrame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include "../Enemy/EnemyParameter.h"
#include "../UI/UIComponent.h"
#include "../Flag/FlagData.h"

namespace {

    constexpr int StageAll = 1; //!< 読み込むjsonの最大数

}

namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneInGame::SceneInGame(AppFrame::Game& game)
        :Scene{ game }
    {
        shadowmap = std::make_unique<ShadowMap::Shadowmap>(game);
    }
    /// 初期化
    void SceneInGame::Init() {
        // 使用するモデル
        AppFrame::Asset::AssetServer::ModelMap usedInGame{
        //{"Player",    "SDChar/SDChar.mv1"},
        {"Player",    "Player/player.mv1"},
        {"SkySphere", "model/skysphere.mv1"},
        {"Ground",    "model/ground.mv1"},
        {"Spider",    "tackle/takcle.mv1"},
        {"pCube",      "model/pCube.mv1"},
        {"floor",     "model/floor.mv1"},
        {"wall",      "model/wall.mv1"},
        {"Dungeon",   "model/Dungeon.mv1"},
        {"breakwall",  "model/breakwall.mv1"},
        {"enemy",      "model/enemy.mv1"},
        {"gate",       "model/gate.mv1"},
        {"normalfloor",  "model/normalfloor.mv1"},
        {"normalwall",  "model/normalwall.mv1"},
        {"secretfloor", "model/secretfloor.mv1"},
        {"secretwall", "model/secretwall.mv1"},
        //  {"damagefloor",  "target.mv1"},
          {"entrypoint", "entrypoint.mv1"},
          {"test", "test.mv1"},
          // {"Dungeon",   "Dungeon.mv1"},
          // {"stage0",    "stage0.mv1"}

        };

        AppFrame::Asset::AssetServer::StageMap stageHandles{
            //{"Dunge0",   "Dungeon.mv1"}
            {"stage0",    "StageFloor/stage0.mv1"},
            {"stage1",    "StageFloor/stage1.mv1"},
            {"Dunge2",   "StageFloor/Dunge2.mv1"}
            //    {"Stage3",    "Stage3.mv1"}
        };


        // モデルの読み込み
        GetAssetServer().LoadModels(usedInGame);                                                         //追加

        //ステージ用のモデル読み込み
        GetAssetServer().LoadMaps(stageHandles);
        //追加
        //シャドウマップの読み込み
        shadowmap->SetShadowMap();
        // 使用するテクスチャ
        AppFrame::Asset::AssetServer::TextureMap TexUsed{
          {"BarFrame", {"BarFrame.png", 1, 1, 340, 50}},
          {"black", {"BlackColor.png", 1, 1, 1920, 1080}},
          {"Energy0", {"energy/Energy0.png", 1, 1, 85, 85}}
        };
        // テクスチャの読み込み
        GetAssetServer().LoadTextures(TexUsed);

        _grHandle = GetAssetServer().GetTexture("black");

    }
    /// 入口
    void SceneInGame::Enter() {
        // ファクトリの生成とクリエイターの登録
        auto& af = GetActorFactory();
        af.Register("Player", std::make_unique<Actor::PlayerCreator>());
        af.Register("TackleEnemy", std::make_unique<Actor::TackleEnemyCreator>());
        // af.Register("GrabEnemy", std::make_unique<GrabEnemyCreator>());
       //  af.Register("AlartEnemy", std::make_unique<AlartEnemyCreator>());
        af.Register("Stage", std::make_unique<Actor::StageCreator>());
        af.Register("DamageFloor", std::make_unique<Actor::DamageFloorGimmickCreator>());
        af.Register("BrokenWall", std::make_unique<Actor::BrokenWallCreator>());


        //for (int i = 0; i < StageAll; i++) {



        
        //    //ステージ番号をstringに変換
        //    auto no = std::to_string(i);
        //    //下の二つを起動すればjsonが読み込める
        //    //auto stageParameter = std::make_unique<StageParameter>();
        //    game.GetStageParameter().LoadStageParameter("resource/json/sample" + no + ".json");

        //}


        //auto EParam = std::make_unique<EnemyParameter>();

        //for (int i = 0; i < 10; i++) {

        //    //ステージ番号をstringに変換
        //    auto no = std::to_string(i);
        //    //下の二つを起動すればjsonが読み込める
        //    EParam->LoadStageEnemyParam("resource/json/stageenemy" + no + ".json");

        //}

        //エネミーのステージ配置を一括で読み込む
        for (int i = 0; i < StageAll; i++) {

            //ステージ番号をstringに変換
            auto no = std::to_string(i);
            //下の二つを起動すればjsonが読み込める
            //auto stageParameter = std::make_unique<StageParameter>();
            GetGame().GetEnemyParameter().LoadStageEnemyParam(i, "resource/json/stageenemy" + no + ".json");
        }


        //読み込んだエネミーのステージ配置をテーブルに入れる
        auto inGame = GetGame().GetEnemyParameter().GetFloorEnemyMap();

        //エネミーのスポーンテーブルの読み込み

        af.SetSpawnTable(inGame);

        //af.SetSpawnTable(EParam->GetStageEnemyParameter());

        //// アクターサーバーに登録※個別アクセス用
        auto& as = GetActorServer();

        // ステージの生成と追加
        auto stage = af.Create("Stage");
        as.Add(std::move(stage));
        
        ////ダメージ床ギミックの生成と追加
        //auto damageFloorGimmick = af.Create("DamageFloor");
        //as.Add(std::move(damageFloorGimmick));


        //for (int i = 0; i < 3; i++) 
        //{
        //    auto spawnTable = inGame[i];
        //    std::string u = static_cast<std::string>(i);
        //    auto enemy = af.Create(spawnTable._key);
        //    std::pair<Math::Vector4, Math::Vector4> pos_dir = { spawnTable._position, spawnTable._rotation };
        //    as.Register("Enemy" + u, pos_dir);
        //    as.Add(std::move(enemy));
        //}

        // プレイヤーの生成と追加
        auto player = af.Create("Player");
        std::pair<Math::Vector4, Math::Vector4> pos_dir = { player->GetPosition(), player->GetRotation() };
        as.Register("Player", pos_dir);
        as.Add(std::move(player));

        GetUiComponent().Enter();

        // 疑似乱数
        //std::random_device seed;
        //std::mt19937 engine{seed()};
        //std::uniform_real_distribution<float> zPosition{1000, 2500};
        //std::uniform_real_distribution<float> forwardSpeed{3, 9};
        Update();
    }
    /// 入力処理
    void SceneInGame::Input(AppFrame::Input::InputComponent& input) {

        if (input.GetMouse().RightClick()) {
            // 右クリックでタイトルへ遷移
            //GetSceneServer().GoToScene("Title");
            GetSceneServer().GoToScene("Epilogue");
        }
        if (input.GetJoypad().Button_X()) {
            // Xボタンでマップ画面へ
            GetSceneServer().PopBack(true);
            GetSceneServer().PushBack("Map",true);
        }
        if (input.GetJoypad().Button_Y()) {
            // Yボタンでアイテム画面へ
            GetSceneServer().PopBack(true);
            GetSceneServer().PushBack("Item", true);
        }
        GetActorServer().Input(input);
    }
    /// 更新
    void SceneInGame::Update() {
        GetActorFactory().UpdateSpawn();
        GetActorServer().Update();
        GetUiComponent().Update();


        if (Flag::FlagData::GetFadeOutFlag()) {
            //GetSceneServer().PopBack(true);
            //GetSceneServer().PushBack("FadeOut");
            GetSceneServer().GoToScene("Loading", "FadeOut", false);

            //Flag::FlagData::SetFadeOutFlag(false);
            //フェードアウトの方でPopBackしていないのだと思う
        }

        if (Flag::FlagData::GetFadeInFlag()) {
            GetSceneServer().GoToScene("Loading", "FadeIn", false);

            Flag::FlagData::SetFadeInFlag(false);
        }

    }

    /// 描画
    void SceneInGame::Render() {


        //シャドウマップへの描画のフラグをオンにする
        shadowmap->SetPlayerShadowMapflg(TRUE);
        //シャドウマップへの描画の準備を行う
        ShadowMap_DrawSetup(shadowmap->GetShadowmap());
        //シャドウマップに描画したい3Dモデルの描画
        GetActorServer().Render();
        //シャドウマップへの描画を終了する
        ShadowMap_DrawEnd();
        //シャドウマップへの描画のフラグをオフにする。
        shadowmap->SetPlayerShadowMapflg(FALSE);
        //	描画で使用するシャドウマップを変更する
        SetUseShadowMap(0, shadowmap->GetShadowmap());
        //3Dモデルの描画
        GetActorServer().Render();
        //３Dモデルの描画で使用したシャドウマップの設定を解除する
        SetUseShadowMap(0, -1);
        //UIの描画
        GetUiComponent().Render();

        if (Flag::FlagData::GetBlackOutFlag()) {
            DrawGraph(0, 0, _grHandle, true);
            //Flag::FlagData::SetBlackOutFlag(false);
        }
    }
    /// 出口
    void SceneInGame::Exit() {
        // アクターを削除
        GetActorServer().Clear();
        // デュプリケートしたモデルだけ削除
        GetAssetServer().DeleteDuplicateModels();

        // デュプリケートしたモデルだけ削除
        GetAssetServer().DeleteDuplicateMaps();

        // クリエイターを削除
        GetActorFactory().Clear();
        //シャドウマップの削除
        DeleteShadowMap(shadowmap->GetShadowmap());

    }
}
