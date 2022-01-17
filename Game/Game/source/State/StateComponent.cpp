/*****************************************************************//**
 * @file  StateComponent.cpp
 * @brief  ステートコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "StateComponent.h"

namespace MachineHuck::State {
    /// コンストラクタ
    StateComponent::StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        Register(key, state);
        PushBack(key);
    }
    /// 状態の登録
    void StateComponent::Register(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        if (_registry.contains(key.data())) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, state);
        //state->Init();
    }
    /// 状態のプッシュバック
    void StateComponent::PushBack(std::string_view key) {
        if (!_registry.contains(key.data())) {
            return;   // キーが未登録
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



