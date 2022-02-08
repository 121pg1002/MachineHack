/*****************************************************************//**
 * @file   ActorServer.cpp
 * @brief  �A�N�^�[�T�[�o�[
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

    void ActorServer::Del(std::unique_ptr<Actor> actor) {
        if (_updating) {
            // �X�V����_pendingActors�ɒǉ�����
            _pendingActors.emplace_back(std::move(actor));
        }
        else {
            auto isDead = [](auto&& act) {return act->IsDead(); };
            auto it = std::remove_if(_actors.begin(), _actors.end(), isDead);
            _actors.erase(it, _actors.end());
        }

    }

    /// ����
    void ActorServer::Input(AppFrame::Input::InputComponent& input) {
        _updating = true;
        for (auto&& actor : _actors) {
            if (actor->IsActive()) {
                // �A�N�^�[�ɓ��͂���
                actor->Input(input);
            }
            else if (actor->IsHucked()) {

                actor->Input(input);

            }
        }
        _updating = false;
    }
    /// �X�V
    void ActorServer::Update() {
        _updating = true;
        for (auto&& actor : _actors) {
            if (!actor->IsDead()) {
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

        // �A�N�^�[�̒��Ɏ��S��Ԃ̃A�N�^�[���폜
        auto isDead = [](auto&& act) {return act->IsDead(); };
        auto it = std::remove_if(_actors.begin(), _actors.end(), isDead);

        //���S��Ԃ�
        //if ((*it)->IsDead()) {

        //    //�G�l�~�[��
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
    /// �`��
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
    /// �S�A�N�^�[�̍폜
    void ActorServer::Clear() {
        _actors.clear();
        _pendingActors.clear();
    }
    /// �A�N�^�[�̓o�^
    void ActorServer::Register(std::string_view key, _pos_dir vec) {

        //�L�[�̐���0�łȂ��Ȃ瑶�݂���
        if (_registry.count(key.data()) != 0) {
            _registry[key.data()].first = vec.first;
            _registry[key.data()].second = vec.second;
        }
        _registry.emplace(key, vec);
    }
    /// �A�N�^�[�̈ꗗ�̎擾
    Math::Vector4 ActorServer::GetPosition(std::string_view key) {

        if (_registry.count(key.data()) != 0) {
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
        if (_registry.count(key.data()) != 0) {
            return _registry[key.data()].second;
        }
        // ���o�^
        return { 0, 0, 0 };

    }
}

