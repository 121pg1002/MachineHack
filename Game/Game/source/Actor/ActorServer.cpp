/*****************************************************************//**
 * @file   ActorServer.cpp
 * @brief  �A�N�^�[�T�[�o�[
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#include "ActorServer.h"
#include "Actor.h"

namespace MachineHuck::Actor {
    /// �A�N�^�[�̒ǉ�
    void ActorServer::Add(std::unique_ptr<Actor> actor) {
        if (_updating) {
            // �X�V����_pendingActors�ɒǉ�����
            _pendingActors.emplace_back(std::move(actor));
        }
        else {
            _actors.emplace_back(std::move(actor));
        }
    }
    /// ����
    void ActorServer::Input(AppFrame::Input::InputComponent& input) {
        _updating = true;
        for (auto&& actor : _actors) {
            if (actor->isActive()) {
                // �A�N�^�[�ɓ��͂���
                actor->Input(input);
            }
        }
        _updating = false;
    }
    /// �X�V
    void ActorServer::Update() {
        _updating = true;
        for (auto&& actor : _actors) {
            if (!actor->isDead()) {
                // �A�N�^�[���X�V����
                actor->Update();
            }
        }
        _updating = false;

        // �ۗ����̃A�N�^�[��_actors�Ɉړ�����
        _actors.insert(_actors.end(),
            make_move_iterator(_pendingActors.begin()),
            make_move_iterator(_pendingActors.end()));

        // �ۗ����̃A�N�^�[���N���A����
        _pendingActors.clear();

        // ���񂾃A�N�^�[���폜����
        erase_if(_actors, [](auto&& act) { return act->isDead(); });
    }
    /// �`��
    void ActorServer::Render() {
        for (auto&& actor : _actors) {
            if (!actor->isDead()) {
                actor->Draw();
            }
        }
    }
    /// �S�A�N�^�[�̍폜
    void ActorServer::Clear() {
        _actors.clear();
        _pendingActors.clear();
    }
    /// �A�N�^�[�̓o�^
    void ActorServer::Register(std::string_view key, _pos_dir vec) {
        if (_registry.contains(key.data())) {
            _registry[key.data()].first = vec.first;
            _registry[key.data()].second = vec.second;
        }
        _registry.emplace(key, vec);
    }
    /// �A�N�^�[�̈ꗗ�̎擾
    Math::Vector4 ActorServer::GetPosition(std::string_view key) {
        if (_registry.contains(key.data())) {
            return _registry[key.data()].first;
        }
        // ���o�^
        return { 0, 0, 0 };
    }
    /// �o�^�����A�N�^�[�̈ʒu�𓾂�
    //Math::Vector4 ActorServer::GetForward(std::string_view key) {
    //  if (_registry.contains(key.data())) {
    //    return _registry[key.data()];
    //  }
    //  // ���o�^
    //  return {0, 0, 0};
    //}

    Math::Vector4 ActorServer::GetDir(std::string_view key)
    {
        if (_registry.contains(key.data())) {
            return _registry[key.data()].second;
        }
        // ���o�^
        return { 0, 0, 0 };

    }
}

