/*****************************************************************//**
 * @file  SceneServer.cpp
 * @brief シーンサーバー
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

        PushBack(key);      // 最初のシーンをプッシュバック
        PushBack("FadeIn"); // 最初のシーンの上にプッシュバック
    }
    /// シーンの登録
    void SceneServer::Register(std::string_view key, std::shared_ptr<Scene> scene) {
        if (_registry.count(key.data()) != 0) {
            _registry.erase(key.data());
        }
        _registry.emplace(key, scene);
        scene->Init();
    }
    /// シーンのプッシュバック
    /// リストの一番後ろ(最前面)に追加
    void SceneServer::PushBack(std::string_view key) {
        if (_registry.count(key.data()) != 1) {
            return;   // キーが未登録
        }
        auto pushScene = _registry[key.data()];
        pushScene->Enter();
        _scenes.push_back(pushScene);
    }
    //Enterを呼ばずにプッシュバック
    void SceneServer::PushBack(std::string_view key,bool menuflg) {
        if (_registry.count(key.data()) != 1) {
            return;   // キーが未登録
        }
        auto pushScene = _registry[key.data()];
        _scenes.push_back(pushScene);
    }
    /// シーンのポップバック.
    /// リストの一番後ろ(最前面)を削除
    void SceneServer::PopBack() {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Exit();
        _scenes.pop_back();
    }
    //Exitを呼ばずにポップバック
    void SceneServer::PopBack(bool menuflg) {
        if (_scenes.empty()) {
            return;
        }
        _scenes.pop_back();
    }
    /// シーンの遷移
    /// ↑次のシーン
    /// ↑フェードイン
    /// ↑現在のシーン
    /// ↑フェードアウト：最前面
    void SceneServer::GoToScene(std::string_view key) {
        InsertBelowBack(key.data());  // 次のシーンを挿入
        InsertBelowBack("FadeIn");    // フェードインを挿入
        PushBack("FadeOut");          // フェードアウトをプッシュバック
    }

    void SceneServer::GoToScene(std::string_view key, bool flag) {
        InsertBelowBack(key.data(), flag);  // 次のシーンを挿入
        InsertBelowBack("FadeIn");    // フェードインを挿入
        PushBack("FadeOut");          // フェードアウトをプッシュバック
    }


    void SceneServer::GoToScene(std::string_view key, std::string_view sceneNext, bool flag) {
        
        if (key != "") {
            InsertBelowBack(key.data(), flag);  // 次のシーンを挿入
        }
        //InsertBelowBack("FadeIn", flag);    // フェードインを挿入
        if (sceneNext != "") {
            PushBack(sceneNext);          // フェードアウトをプッシュバック
        }
    }

    void SceneServer::PopFront() {
      _scenes.pop_front();
    }


    /// リストの一番後ろ(最前面)のシーンの真下に挿入
    void SceneServer::InsertBelowBack(std::string_view key) {
        if (_registry.count(key.data()) != 1) {
            return;   // キーが未登録
        }
        auto insertScene = _registry[key.data()];
        insertScene->Enter();
        _scenes.insert(std::prev(_scenes.end()), insertScene);
    }

    /// リストの一番後ろ(最前面)のシーンの真下に挿入
    void SceneServer::InsertBelowBack(std::string_view key, bool flag) {
        if (_registry.count(key.data()) != 1) {
            return;   // キーが未登録
        }
        auto insertScene = _registry[key.data()];

        if (flag) {
            insertScene->Enter();
        }
        _scenes.insert(std::prev(_scenes.end()), insertScene);
    }



    ///
    /// 入力処理.
    ///
    void SceneServer::Input(Input::InputComponent& input) {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Input(input);
    }
    ///
    /// 更新処理.
    ///
    void SceneServer::Update() {
        if (_scenes.empty()) {
            return;
        }
        _scenes.back()->Update();
    }
    ///
    /// 描画処理.
    ///
    void SceneServer::Render() const {
        for (auto&& scene : _scenes) {
            scene->Render();
        }
    }
}

