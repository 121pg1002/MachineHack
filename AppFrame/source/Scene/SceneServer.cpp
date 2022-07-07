/*****************************************************************//**
 * @file  SceneServer.cpp
 * @brief �V�[���T�[�o�[
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

#include "SceneServer.h"
#include "Scene.h"
#include "SceneFade.h"

namespace AppFrame::Scene {
    SceneServer::SceneServer(std::string_view key, std::shared_ptr<Scene> scene) {
        Register("FadeIn", std::make_shared<SceneFadeIn>(scene->GetGame()));
        Register("FadeOut", std::make_shared<SceneFadeOut>(scene->GetGame()));
        Register(key, scene);

        PushBack(key);      // �ŏ��̃V�[�����v�b�V���o�b�N
        PushBack("FadeIn"); // �ŏ��̃V�[���̏�Ƀv�b�V���o�b�N
    }
    /// �V�[���̓o�^
    void SceneServer::Register(std::string_view key, std::shared_ptr<Scene> scene) {
        if (_registry.count(key.data()) != 0) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, scene);
        scene->Init();
    }
    /// �V�[���̃v�b�V���o�b�N
    /// ���X�g�̈�Ԍ��(�őO��)�ɒǉ�
    void SceneServer::PushBack(std::string_view key) {
        if (_registry.count(key.data()) != 1) {
            return;   // �L�[�����o�^
        }
        auto pushScene = _registry[key.data()];
        pushScene->Enter();
        _scenes.push_back(pushScene);
    }
    //Enter���Ă΂��Ƀv�b�V���o�b�N
    void SceneServer::PushBack(std::string_view key,bool menuflg) {
        if (_registry.count(key.data()) != 1) {
            return;   // �L�[�����o�^
        }
        auto pushScene = _registry[key.data()];
        _scenes.push_back(pushScene);
    }
    /// �V�[���̃|�b�v�o�b�N.
    /// ���X�g�̈�Ԍ��(�őO��)���폜
    void SceneServer::PopBack() {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Exit();
        _scenes.pop_back();
    }
    //Exit���Ă΂��Ƀ|�b�v�o�b�N
    void SceneServer::PopBack(bool menuflg) {
        if (_scenes.empty()) {
            return;
        }
        _scenes.pop_back();
    }
    /// �V�[���̑J��
    /// �����̃V�[��
    /// ���t�F�[�h�C��
    /// �����݂̃V�[��
    /// ���t�F�[�h�A�E�g�F�őO��
    void SceneServer::GoToScene(std::string_view key) {
        InsertBelowBack(key.data());  // ���̃V�[����}��
        InsertBelowBack("FadeIn");    // �t�F�[�h�C����}��
        PushBack("FadeOut");          // �t�F�[�h�A�E�g���v�b�V���o�b�N
    }

    void SceneServer::GoToScene(std::string_view key, bool flag) {
        InsertBelowBack(key.data(), flag);  // ���̃V�[����}��
        InsertBelowBack("FadeIn");    // �t�F�[�h�C����}��
        PushBack("FadeOut");          // �t�F�[�h�A�E�g���v�b�V���o�b�N
    }


    void SceneServer::GoToScene(std::string_view key, std::string_view sceneNext, bool flag) {
        
        if (key != "") {
            InsertBelowBack(key.data(), flag);  // ���̃V�[����}��
        }
        //InsertBelowBack("FadeIn", flag);    // �t�F�[�h�C����}��
        if (sceneNext != "") {
            PushBack(sceneNext);          // �t�F�[�h�A�E�g���v�b�V���o�b�N
        }
    }

    void SceneServer::PopFront() {
      _scenes.pop_front();
    }


    /// ���X�g�̈�Ԍ��(�őO��)�̃V�[���̐^���ɑ}��
    void SceneServer::InsertBelowBack(std::string_view key) {
        if (_registry.count(key.data()) != 1) {
            return;   // �L�[�����o�^
        }
        auto insertScene = _registry[key.data()];
        insertScene->Enter();
        _scenes.insert(std::prev(_scenes.end()), insertScene);
    }

    /// ���X�g�̈�Ԍ��(�őO��)�̃V�[���̐^���ɑ}��
    void SceneServer::InsertBelowBack(std::string_view key, bool flag) {
        if (_registry.count(key.data()) != 1) {
            return;   // �L�[�����o�^
        }
        auto insertScene = _registry[key.data()];

        if (flag) {
            insertScene->Enter();
        }
        _scenes.insert(std::prev(_scenes.end()), insertScene);
    }



    ///
    /// ���͏���.
    ///
    void SceneServer::Input(Input::InputComponent& input) {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Input(input);
    }
    ///
    /// �X�V����.
    ///
    void SceneServer::Update() {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Update();
    }
    ///
    /// �`�揈��.
    ///
    void SceneServer::Render() const {
        for (auto&& scene : _scenes) {
            scene->Render();
        }
    }
}

