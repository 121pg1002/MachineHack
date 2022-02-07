/*****************************************************************//**
 * @file   ActorFactory.cpp
 * @brief  アクターファクトリー
 *
 * @author yamawaki kota, hikaru Goto
 * @date   December 6 2021
 *********************************************************************/

#include "ActorFactory.h"
#include "ActorServer.h"
#include "../Player/Player.h"
#include "../Enemy/TackleEnemy.h"
#include "../Enemy/CatchEnemy.h"
#include "../Stage/Stage.h"
#include "../Model/ModelAnimComponent.h"
#include "../State/StateComponent.h"
#include "../Camera/CameraComponent.h"
#include "../Gimmick/DamageFloorGimmick.h"
#include "../Gimmick/BrokenWall.h"
#include "../Item/Item.h"
//#include "../Parameter/EStageParam.h"
//#include "../Parameter/IStageParam.h"
#include "../Parameter/GStageParam.h"


namespace Camera = MachineHuck::Camera;

namespace {

    //constexpr int StageAll = 3;        //!< 読み込むstagejsonの数
    constexpr double Differ = 3000.0; //!< 1フロアのサイズ
    constexpr double StartX = -5.0 * Differ;
    constexpr int BoardSize = 10;

    //constexpr double HalfSize = 0.5 * Differ;
    //constexpr int StartZ = -5.0 * Differ;

}

namespace MachineHuck::Actor {
    class CreatorBase;
}

namespace MachineHuck::Actor {
    /// コンストラクタ
    ActorFactory::ActorFactory(AppFrame::Game& game) : _game{ game } {

    }
    /// クリエイターの登録
    bool ActorFactory::Register(std::string_view type, std::unique_ptr<CreatorBase> creator) {

        //キーの数が0でないなら存在する
        if (_creatorMap.count(type.data()) != 0) {
            return false;
        }
        _creatorMap.emplace(type.data(), std::move(creator));
        return true;
    }

    /// アクターの生成
    std::unique_ptr<Actor> ActorFactory::Create(std::string_view type) {

        //キーの数が1でないなら存在しない
        if (_creatorMap.count(type.data()) != 1) {
            return nullptr;
        }
        auto&& creator = _creatorMap[type.data()];
        return creator->Create(_game);
    }

    void ActorFactory::Clear() {
        _creatorMap.clear();
    }

    //void ActorFactory::SetSpawnTable(SpawnTable spawnTable) {
    //    _spawnProgress = 0;
    //    _progress = 0;
    //    _spawnTable = spawnTable;
    //}

    void ActorFactory::SetSpawnTable(std::unordered_map<int, ESMV> eStageParamVMap) {
        _spawnProgress = 0;
        _progress = 0;
        _eStageParamVMap = eStageParamVMap;
    }

    void ActorFactory::SetSpawnTable(std::unordered_map<int, ISMV> vIStageParamMap) {
        _spawnProgress = 0;
        _progress = 0;
        _iStageParamVMap = vIStageParamMap;

    }

    void ActorFactory::SetSpawnTable(std::unordered_map<int, GSV> gStageParamVMap) {
        _spawnProgress = 0;
        _progress = 0;
        _gStageParamVMap = gStageParamVMap;
    
    }

    //void ActorFactory::UpdateSpawn() {
    //    while (_spawnTable.size() > _spawnProgress) {
    //        auto& spawnRecord = _spawnTable[_spawnProgress];
    //        if (spawnRecord._progress > _progress) {
    //            break;
    //        }
    //        else {
    //            auto&& actor = Create(spawnRecord._key);
    //            actor->SetPosition(spawnRecord._position);
    //            actor->SetRotation(spawnRecord._rotation);
    //            _game.GetActorServer().Add(std::move(actor));
    //            ++_spawnProgress;
    //        }
    //    }
    //    ++_progress;
    //}

    void ActorFactory::UpdateSpawn() {

        std::vector<int> num;


        //現在いる番号配列と前のステージ番号配列が異なる場合
        if (_oldStageNo != _currentStageNo) {


            //古い配列の中の新しい番号を取り出す
            for (auto old : _oldStageNo) {

                for (auto newNum : _currentStageNo) {

                    //古い番号配列に新しい番号が無かった場合
                    if (old != newNum) {

                        //古い番号配列にあるか
                        auto result = std::find(_oldStageNo.begin(), _oldStageNo.end(), newNum);

                        //無かった場合
                        if (result == _oldStageNo.end()) {

                            //新しくエネミーを生み出す番号
                            num.push_back(newNum);
                        }
                    }
                    //else {
                    //    continue;
                    //}

                }

            }

            //前のフロアのエネミーを削除する
            for (auto i = _game.GetActorServer().GetActors().begin(); i < _game.GetActorServer().GetActors().end(); i++) {

                //エネミーかどうか//ここアイテムもギミックも分ける
                if ((*i)->GetTypeId() == (*i)->IsEnemy() || (*i)->GetTypeId() == (*i)->IsItem()) {

                    //ハッキング中かどうか
                    if ((*i)->IsHucked()) {

                        continue;
                    }

                    (*i)->SetDead();

                }


            }

            ////前のステージ番号を更新
            _oldStageNo = _currentStageNo;



            ////描画するフロアのステージ番号で回す
            //for (auto&& num : _currentStageNo) {

            //空かどうか確認
            if (!num.empty()) {

                //新しい番号で回す
                for (auto no : num) {

                    auto& spawnFloor = _eStageParamVMap[no];

                    //新しい描画フロアのエネミーをリスポーンさせる
                    for (auto&& floorEnemy : spawnFloor) {

                        auto&& actor = Create(floorEnemy.GetName());

                        //auto pos = floor.GetPosition();
                        //Math::Vector4 dif = {};

                        actor->SetPosition(floorEnemy.GetPosition());
                        actor->SetRotation(floorEnemy.GetRotation());
                        actor->SetScale(floorEnemy.GetScale());

                        //actor->SetLevel(floorEnemy.GetLevel());
                        actor->SetRoutine(floorEnemy.GetRoutine());

                        _game.GetActorServer().Add(std::move(actor));

                    }

                    auto& spawnFloori = _iStageParamVMap[no];
                    //新しい描画フロアのアイテムをリスポーンさせる
                    for (auto&& floorItem : spawnFloori) {

                        auto&& actor = Create("Item");

                        actor->SetPosition(floorItem.GetPosition());
                        actor->SetRotation(floorItem.GetRotation());
                        actor->SetScale(floorItem.GetScale());

                        _game.GetActorServer().Add(std::move(actor));

                    }



                    //auto& spawnFloorGimmick = _gStageParamVMap[no];
                    //////新しい描画フロアのギミックをリスポーンさせる
                    //for (auto&& floorGimmick : spawnFloorGimmick) {

                    //    auto&& actor = Create(floorGimmick.GetName());

                    //    actor->SetPosition(floorGimmick.GetPosition());
                    //    actor->SetRotation(floorGimmick.GetRotation());
                    //    actor->SetScale(floorGimmick.GetScale());

                    //    _game.GetActorServer().Add(std::move(actor));

                    //}




                }


            }



        }

    }

    //void ActorFactory::Delete() {



    //}

    /// プレイヤーの生成
    std::unique_ptr<Actor> PlayerCreator::Create(AppFrame::Game& game) {
        // カメラの生成
        auto camera = std::make_shared<Camera::CameraComponent>();
        camera->Init();
        camera->SetPosition({ 0, 1000, -500 });
        camera->SetTarget({ 0, 100, 0 });

        // プレイヤーの生成
        auto player = std::make_unique<Player::Player>(game);
        player->SetCameraComponent(camera);
        player->SetPosition({ -Differ * 5.0 + Differ * 0.5, 0, Differ * 0.5 });
        player->SetRotation({ 0.5, 0.0, 0.0 });

        // モデルの読み込みと生成
        auto model = std::make_unique<Model::ModelAnimeComponent>(*player);
        model->SetModel("Player");
        model->Register("Attack", 0);
        model->Register("Run", 1);
        model->Register("Idle", 2);
        model->Register("Die", 3);
        //model->Register("JumpStart", 3);
        //model->Register("JumpLoop", 4);
        //model->Register("JumpEnd", 5);
        player->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Idle", std::make_shared <Player::Player::StateIdle>(*player));
        state->Register("Run", std::make_shared<Player::Player::StateRun>(*player));
        state->Register("Attack", std::make_shared<Player::Player::StateAttack>(*player));
        //state->Register("KnockBack", std::make_shared<Player::StateKnockBack>(*player));
        state->Register("Hucking", std::make_shared<Player::Player::StateHucking>(*player));
        state->Register("Hucked", std::make_shared<Player::Player::StateHucked>(*player));
        state->Register("Die", std::make_shared<Player::Player::StateDie>(*player));
        state->Register("Damage", std::make_unique<Player::Player::StateDamage>(*player));
        player->SetStateComponent(std::move(state));

        return player;
    }

    /// タックルエネミーの生成
    std::unique_ptr<Actor> TackleEnemyCreator::Create(AppFrame::Game& game) {
        // タックルエネミーの生成
        auto enemy = std::make_unique<Enemy::TackleEnemy>(game);

        //std::vector<std::string> type = { "Tackle", "Grab", "Alart" };

        // エネミーのjsonからパラメーターを読み込む

        //auto i = game.GetStageParameter().GetStageMap().find();
        //for(int i =0; i < )

        enemy->LoadJson("resource/json/tackle.json");

        //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓は、他の生成するときに同じ敵の種類のものを書く
        //enemy->LoadJson("resource/json/Grab.json");
        //enemy->LoadJson("resource/json/Alart.json");

        // 速度は3～9でランダム
        enemy->SetForwardSpeed(1.0f);

        // モデルの読み込みと生成
        auto model = std::make_unique<Model::ModelAnimeComponent>(*enemy);
        model->SetModel("Spider", 1000);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        /*No.0 idle
            No.1 walk
            No, 2 attack
            No.3 tackle
            */
        model->Register("Hucking", 3);
        model->Register("Die", 0);
        model->Register("Idle", 0);
        model->Register("Walk", 1);
        model->Register("Attack", 2);
        model->Register("Tackle", 3);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        ////model->Register("Die2", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        //model->Register("Normal", 5);
        //model->Register("RunAniBack", 6);
        model->Register("RunAniVor", 7);
        //model->Register("RunLeft", 8);
        //model->Register("RunRight", 9);
        //model->Register("WalkAniBack", 10);
        //model->Register("WalkAniBor", 11);
        //model->Register("WalkLeft", 12);
        //model->Register("WalkRight", 13);
        //model->Register("WartePose", 14);
        enemy->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Fall", std::make_shared <Enemy::TackleEnemy::StateFall>(*enemy));
        state->Register("Idle", std::make_shared<Enemy::TackleEnemy::StateIdle>(*enemy));
        state->Register("Run", std::make_shared<Enemy::TackleEnemy::StateRun>(*enemy));
        state->Register("Die", std::make_shared<Enemy::TackleEnemy::StateDie>(*enemy));
        state->Register("Tackle", std::make_shared<Enemy::TackleEnemy::StateTackle>(*enemy));
        state->Register("TackleAfter", std::make_shared<Enemy::TackleEnemy::StateTackleAfter>(*enemy));
        //state->Register("Attack", std::make_shared<Enemy::StateAttack>(*enemy));
        state->Register("IsHucking", std::make_shared<Enemy::TackleEnemy::StateHucking>(*enemy));
        state->Register("IsHucked", std::make_shared<Enemy::TackleEnemy::StateHucked>(*enemy));
        enemy->SetStateComponent(std::move(state));


        // 次の生成の為にカウントアップ
        ++_count;
        return enemy;
    }

    /// キャッチエネミーの生成
    std::unique_ptr<Actor> CatchEnemyCreator::Create(AppFrame::Game& game) {
        // タックルエネミーの生成
        auto enemy = std::make_unique<Enemy::CatchEnemy>(game);

        //std::vector<std::string> type = { "Tackle", "Grab", "Alart" };

        // エネミーのjsonからパラメーターを読み込む

        //auto i = game.GetStageParameter().GetStageMap().find();
        //for(int i =0; i < )

        enemy->LoadJson("resource/json/catch.json");

        enemy->SetForwardSpeed(1.0f);

        // モデルの読み込みと生成
        auto model = std::make_unique<Model::ModelAnimeComponent>(*enemy);
        model->SetModel("Spider", 1000);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        //model->Register("Fall", 3);
        //model->Register("Catch", 4);
        //model->Register("RunAniVor", 7);

        model->Register("Hucking", 3);
        model->Register("Die", 0);
        model->Register("Idle", 0);
        model->Register("Walk", 1);
        model->Register("Attack", 2);
        model->Register("Tackle", 3);
        //model->Register("Hucking", 0);
        //model->Register("Die", 1);
        //model->Register("Idle", 2);
        ////model->Register("Die2", 2);
        //model->Register("Fall", 3);
        //model->Register("Attack", 4);
        //model->Register("Normal", 5);
        //model->Register("RunAniBack", 6);
        model->Register("RunAniVor", 7);
        //model->Register("RunLeft", 8);
        //model->Register("RunRight", 9);
        //model->Register("WalkAniBack", 10);
        //model->Register("WalkAniBor", 11);
        //model->Register("WalkLeft", 12);
        //model->Register("WalkRight", 13);
        //model->Register("WartePose", 14);
        enemy->SetModelAnimeComponent(std::move(model));

        auto state = std::make_unique<State::StateComponent>("Fall", std::make_shared <Enemy::CatchEnemy::StateFall>(*enemy));
        state->Register("Idle", std::make_shared<Enemy::CatchEnemy::StateIdle>(*enemy));
        //state->Register("Run", std::make_shared<Enemy::CatchEnemy::StateRun>(*enemy));
        state->Register("Die", std::make_shared<Enemy::CatchEnemy::StateDie>(*enemy));
        state->Register("Catch", std::make_shared<Enemy::CatchEnemy::StateCatch>(*enemy));
        state->Register("CatchAfter", std::make_shared<Enemy::CatchEnemy::StateCatchAfter>(*enemy));
        state->Register("CatchPre", std::make_shared<Enemy::CatchEnemy::StateCatchPre>(*enemy));
        // state->Register("Attack", std::make_shared<Enemy::CatchEnemy::StateAttack>(*enemy));
        state->Register("IsHucking", std::make_shared<Enemy::CatchEnemy::StateHucking>(*enemy));
        state->Register("IsHucked", std::make_shared<Enemy::CatchEnemy::StateHucked>(*enemy));
        enemy->SetStateComponent(std::move(state));


        // 次の生成の為にカウントアップ
        ++_count;
        return enemy;
    }



    /// ステージの生成
    std::unique_ptr<Actor> StageCreator::Create(AppFrame::Game& game) {
        /// ステージの生成
        auto stage = std::make_unique<Stage::Stage>(game);
        return stage;
    }

    //ダメージ床ギミックの生成
    std::unique_ptr<Actor> DamageFloorGimmickCreator::Create(AppFrame::Game& game) {

        /// ダメージ床ギミックの生成
        auto damageFloorGimmick = std::make_unique<Gimmick::DamageFloorGimmick>(game);

        // モデルの読み込みと生成
        //auto model = std::make_unique<Model::ModelComponent>(*damageFloorGimmick);
        //model->SetModel("damagefloor", 1000);
        //damageFloorGimmick->SetModelComponent(std::move(model));
        return damageFloorGimmick;
    }

    //壊せる壁を作成
    std::unique_ptr<Actor> BrokenWallCreator::Create(AppFrame::Game& game) {
        /// 壊せる壁の生成
        auto brokenWall = std::make_unique<Gimmick::BrokenWall>(game);
        //// モデルの読み込みと生成
        auto model = std::make_unique<Model::ModelComponent>(*brokenWall);
        model->SetModel("BrokenWall", 1000);
        brokenWall->SetModelComponent(std::move(model));
        return brokenWall;
    }


    //エネルギーアイテムの作成
    std::unique_ptr<Actor> ItemCreator::Create(AppFrame::Game& game) {
        auto item = std::make_unique<Item::Item>(game);
        auto model = std::make_unique<Model::ModelComponent>(*item);
        model->SetModel("Item", 1000);
        item->SetModelComponent(std::move(model));

        return item;
    }
}


