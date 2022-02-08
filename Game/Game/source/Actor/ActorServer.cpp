/*****************************************************************//**
 * @file   ActorServer.cpp
 * @brief  アクターサーバー
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "ActorServer.h"
#include <algorithm>
#include "Actor.h"
#include "../Model/ModelAnimComponent.h"
#include "../Model/ModelComponent.h"

namespace MachineHuck::Actor {
    /// アクターの追加
    void ActorServer::Add(std::unique_ptr<Actor> actor) {
        if (_updating) {
            // 更新中は_pendingActorsに追加する
            _pendingActors.emplace_back(std::move(actor));
        }
        else {
            _actors.emplace_back(std::move(actor));
        }
    }

    void ActorServer::Del(std::unique_ptr<Actor> actor) {
        if (_updating) {
            // 更新中は_pendingActorsに追加する
            _pendingActors.emplace_back(std::move(actor));
        }
        else {
            auto isDead = [](auto&& act) {return act->IsDead(); };
            auto it = std::remove_if(_actors.begin(), _actors.end(), isDead);
            _actors.erase(it, _actors.end());
        }

    }

    /// 入力
    void ActorServer::Input(AppFrame::Input::InputComponent& input) {
        _updating = true;
        for (auto&& actor : _actors) {
            if (actor->IsActive()) {
                // アクターに入力する
                actor->Input(input);
            }
            else if (actor->IsHucked()) {

                actor->Input(input);

            }
        }
        _updating = false;
    }
    /// 更新
    void ActorServer::Update() {
        _updating = true;
        for (auto&& actor : _actors) {
            if (!actor->IsDead()) {
                // アクターを更新する
                actor->Update();
            }
        }
        _updating = false;

        // 保留中のアクターを_actorsに移動する
        _actors.insert(_actors.end(),
            make_move_iterator(_pendingActors.begin()),
            make_move_iterator(_pendingActors.end()));

        // 保留中のアクターをクリアする
        _pendingActors.clear();

        // アクターの中に死亡状態のアクターを削除
        auto isDead = [](auto&& act) {return act->IsDead(); };
        auto it = std::remove_if(_actors.begin(), _actors.end(), isDead);

        //死亡状態か
        //if ((*it)->IsDead()) {

        //    //エネミーか
        //    if ((*it)->GetTypeId() != (*it)->IsEnemy()) {

        //        auto handle = (*it)->GetModel().GetHandle();
        //        MV1DeleteModel(handle);
        //    }
        //    else {
        //        auto handle = (*it)->GetModelAnime().GetHandle();
        //        MV1DeleteModel(handle);
        //    }
        //
        //}


        

        _actors.erase(it, _actors.end());



    }
    /// 描画
    void ActorServer::Render() {
        for (auto&& actor : _actors) {

            //if (actor->GetTypeId() != actor->IsEnemy()) {
            //
            //    if (actor->GetTypeId() != actor->IsItem()) {
            //    
            //        if (actor->GetTypeId() != actor->IsStage()) {

            //            actor->Draw();
            //        }
            //    }
            //}

            if (!actor->IsDead()) {
                actor->Draw();
            }
        }
    }
    /// 全アクターの削除
    void ActorServer::Clear() {
        _actors.clear();
        _pendingActors.clear();
    }
    /// アクターの登録
    void ActorServer::Register(std::string_view key, _pos_dir vec) {

        //キーの数が0でないなら存在する
        if (_registry.count(key.data()) != 0) {
            _registry[key.data()].first = vec.first;
            _registry[key.data()].second = vec.second;
        }
        _registry.emplace(key, vec);
    }
    /// アクターの一覧の取得
    Math::Vector4 ActorServer::GetPosition(std::string_view key) {

        if (_registry.count(key.data()) != 0) {
            return _registry[key.data()].first;
        }
        // 未登録
        return { 0, 0, 0 };
    }

    /// 登録したアクターの位置を得る
    //Math::Vector4 ActorServer::GetForward(std::string_view key) {
    //  if (_registry.contains(key.data())) {
    //    return _registry[key.data()];
    //  }
    //  // 未登録
    //  return {0, 0, 0};
    //}

    Math::Vector4 ActorServer::GetDir(std::string_view key)
    {
        if (_registry.count(key.data()) != 0) {
            return _registry[key.data()].second;
        }
        // 未登録
        return { 0, 0, 0 };

    }
}

