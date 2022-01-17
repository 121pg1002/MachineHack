/*****************************************************************//**
 * @file  StateComponent.cpp
 * @brief  �X�e�[�g�R���|�[�l���g
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "StateComponent.h"

namespace MachineHuck::State {
    /// �R���X�g���N�^
    StateComponent::StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        Register(key, state);
        PushBack(key);
    }
    /// ��Ԃ̓o�^
    void StateComponent::Register(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        if (_registry.contains(key.data())) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, state);
        //state->Init();
    }
    /// ��Ԃ̃v�b�V���o�b�N
    void StateComponent::PushBack(std::string_view key) {
        if (!_registry.contains(key.data())) {
            return;   // �L�[�����o�^
        }
        auto pushScene = _registry[key.data()];
        pushScene->Enter();
        _states.push_back(pushScene);
    }
    /// ��Ԃ̃|�b�v�o�b�N
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
    /// ��Ԃ̑J��
    void StateComponent::GoToState(std::string_view key) {
        PopBack();
        PushBack(key.data());
    }
    /// ����
    void StateComponent::Input(AppFrame::Input::InputComponent& input) {
        if (_states.empty()) {
            return;
        }
        _states.back()->Input(input);
    }
    /// �X�V
    void StateComponent::Update() {
        if (_states.empty()) {
            return;
        }
        _states.back()->Update();
    }
    /// �`��
    void StateComponent::Draw() const {
        if (_states.empty()) {
            return;
        }
        _states.back()->Draw();
    }
}



