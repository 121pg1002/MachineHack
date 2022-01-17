/*****************************************************************//**
 * @file   ActorServer.cpp
 * @brief  アクターサーバー
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "ActorServer.h"
#include "Actor.h"

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
    /// 入力
    void ActorServer::Input(AppFrame::Input::InputComponent& input) {
        _updating = true;
        for (auto&& actor : _actors) {
            if (actor->isActive()) {
                // アクターに入力する
                actor->Input(input);
            }
        }
        _updating = false;
    }
    /// 更新
    void ActorServer::Update() {
        _updating = true;
        for (auto&& actor : _actors) {
            if (!actor->isDead()) {
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

        // 死んだアクターを削除する
        erase_if(_actors, [](auto&& act) { return act->isDead(); });
    }
    /// 描画
    void ActorServer::Render() {
        for (auto&& actor : _actors) {
            if (!actor->isDead()) {
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
        if (_registry.contains(key.data())) {
            _registry[key.data()].first = vec.first;
            _registry[key.data()].second = vec.second;
        }
        _registry.emplace(key, vec);
    }
    /// アクターの一覧の取得
    Math::Vector4 ActorServer::GetPosition(std::string_view key) {
        if (_registry.contains(key.data())) {
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
        if (_registry.contains(key.data())) {
            return _registry[key.data()].second;
        }
        // 未登録
        return { 0, 0, 0 };

    }
}

