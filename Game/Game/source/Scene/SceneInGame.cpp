/*****************************************************************//**
 * @file   SceneInGame.cpp
 * @brief  インゲーム画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "AppFrame.h"
#include "SceneInGame.h"
#include "../Actor/ActorServer.h"
#include "../Actor/ActorFactory.h"
#include <numbers>
#include "../Enemy/EnemyParameter.h"
#include "../UI/UIComponent.h"

namespace MachineHuck::Scene {
    /// コンストラクタ
    SceneInGame::SceneInGame(AppFrame::Game& game)
        :Scene{ game }
    {
    }
    /// 初期化
    void SceneInGame::Init() {
        // 使用するモデル
        AppFrame::Asset::AssetServer::ModelMap usedInGame{
        {"Player",    "SDChar/SDChar.mv1"},
        {"SkySphere", "skysphere.mv1"},
        {"Ground",    "ground.mv1"},
        {"Spider",    "Spider_3.mv1"},
        {"pCube",      "pCube.mv1"},
        {"floor",     "floor.mv1"},
        {"wall",      "wall.mv1"}
        };
        // モデルの読み込み
        GetAssetServer().LoadModels(usedInGame);                                                         //追加
        // 使用するテクスチャ
        AppFrame::Asset::AssetServer::TextureMap TexUsed{
          {"BarFrame", {"BarFrame.png", 1, 1, 340, 50}}
        };
        // テクスチャの読み込み
        GetAssetServer().LoadTextures(TexUsed);
    }

    /// 入口
    void SceneInGame::Enter() {
        // ファクトリの生成とクリエイターの登録
        auto& af = GetActorFactory();
        af.Register("Player", std::make_unique<MachineHuck::Actor::PlayerCreator>());
        af.Register("TackleEnemy", std::make_unique<MachineHuck::Actor::TackleEnemyCreator>());
        // af.Register("GrabEnemy", std::make_unique<GrabEnemyCreator>());
       //  af.Register("AlartEnemy", std::make_unique<AlartEnemyCreator>());
        af.Register("Stage", std::make_unique<MachineHuck::Actor::StageCreator>());
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

        MachineHuck::Actor::ActorFactory::SpawnTable inGame{
          {0     , "TackleEnemy", { 300.f, 200.f, 300.0f}},
          {0     , "TackleEnemy", {   0.f, 220.f, 500.0f}},
          {0     , "TackleEnemy", {-300.f, 210.f, 400.0f}},

          //{60 * 5, "Enemy", { 1500.f, 2100.f, 400}},
          //{0     , "Enemy", {    0.f, 2200.f, 400}},
          //{0     , "Enemy", {-1500.f, 2000.f, 400}},

          //{60 * 10,"Enemy", { 1000.f, 2000.f, -4500}},
          //{0     , "Enemy", {    0.f, 2200.f, -4500}},
          //{0     , "Enemy", {-1000.f, 2100.f, -4500}},

          //{60 * 15,"Enemy", { 1500.f, 2000.f, -4500}},
          //{0     , "Enemy", {    0.f, 2200.f, -4500}},
          //{0     , "Enemy", {-1500.f, 2100.f, -4500}},
        };


        af.SetSpawnTable(inGame);

        //af.SetSpawnTable(EParam->GetStageEnemyParameter());

        //// アクターサーバーに登録※個別アクセス用
        auto& as = GetActorServer();
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

        // 疑似乱数
        //std::random_device seed;
        //std::mt19937 engine{seed()};
        //std::uniform_real_distribution<float> zPosition{1000, 2500};
        //std::uniform_real_distribution<float> forwardSpeed{3, 9};

        // ステージの生成と追加
        auto stage = af.Create("Stage");
        as.Add(std::move(stage));
        uiComponent().Enter();
        Update();
    }
    /// 入力処理
    void SceneInGame::Input(AppFrame::Input::InputComponent& input) {

        if (input.GetMouse().RightClick()) {
            // 右クリックでタイトルへ遷移
            //GetSceneServer().GoToScene("Title");
            GetSceneServer().GoToScene("Epilogue");
        }
        GetActorServer().Input(input);
    }
    /// 更新
    void SceneInGame::Update() {
        GetActorFactory().UpdateSpawn();
        GetActorServer().Update();
        uiComponent().Update();
    }

    /// 描画
    void SceneInGame::Render() {
        GetActorServer().Render();
        uiComponent().Render();
    }
    /// 出口
    void SceneInGame::Exit() {
        // アクターを削除
        GetActorServer().Clear();
        // デュプリケートしたモデルだけ削除
        GetAssetServer().DeleteDuplicateModels();
        // クリエイターを削除
        GetActorFactory().Clear();
    }
}
