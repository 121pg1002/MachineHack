///
/// @file    StateComponent.cpp
/// @brief   ステートコンポーネント
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "StateComponent.h"

namespace MachineHuck::State {
    /// コンストラクタ
    StateComponent::StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        Register(key, state);
        PushBack(key);
    }
    /// 状態の登録
    void StateComponent::Register(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        
        //キーが存在するなら削除して構築
        if (_registry.count(key.data()) != 0) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, state);
        //state->Init();
    }
    /// 状態のプッシュバック
    void StateComponent::PushBack(std::string_view key) {
        
        //キーが存在しないなら
        if (_registry.count(key.data()) != 1) {
            return;
        }
        auto pushScene = _registry[key.data()];
        pushScene->Enter();
        _states.push_back(pushScene);
    }
    /// 状態のポップバック
    void StateComponent::PopBack() {
        if (_states.empty()) {
            return;
        }
        //_states.back()->Exit();
        _states.pop_back();
        if (_states.empty()) {
            return;
        }
        _states.back()->Enter();
    }
    /// 状態の遷移
    void StateComponent::GoToState(std::string_view key) {
        PopBack();
        PushBack(key.data());
    }
    /// 入力
    void StateComponent::Input(AppFrame::Input::InputComponent& input) {
        if (_states.empty()) {
            return;
        }
        _states.back()->Input(input);
    }
    /// 更新
    void StateComponent::Update() {
        if (_states.empty()) {
            return;
        }
        _states.back()->Update();
    }
    /// 描画
    void StateComponent::Draw() const {
        if (_states.empty()) {
            return;
        }
        _states.back()->Draw();
    }
}



