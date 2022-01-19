///
/// @file    StateComponent.cpp
/// @brief   �X�e�[�g�R���|�[�l���g
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///

#include "StateComponent.h"

namespace MachineHuck::State {
    /// �R���X�g���N�^
    StateComponent::StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        Register(key, state);
        PushBack(key);
    }
    /// ��Ԃ̓o�^
    void StateComponent::Register(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
        
        //�L�[�����݂���Ȃ�폜���č\�z
        if (_registry.count(key.data()) != 0) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, state);
        //state->Init();
    }
    /// ��Ԃ̃v�b�V���o�b�N
    void StateComponent::PushBack(std::string_view key) {
        
        //�L�[�����݂��Ȃ��Ȃ�
        if (_registry.count(key.data()) != 1) {
            return;
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



