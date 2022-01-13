///
/// @file    SceneServer.h
/// @brief   シーンサーバークラスの宣言
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
#include <unordered_map>
#include <string_view>

//class Scene;
namespace AppFrame {

	namespace Input {
		class InputComponent;
	}
	namespace Scene {
		class Scene;
	}
}

namespace AppFrame::Scene {

	/// @class   SceneServer
/// @brief   シーンサーバークラスの宣言
///          シーンクラスを管理する
	class SceneServer {
	public:
		SceneServer(std::string_view key, std::shared_ptr<Scene> scene);
		///
		/// シーンの登録
		/// @param[in] key    Sceneのインスタンスに関連付ける任意の文字列
		/// @param[in] scene  Sceneのインスタンス
		///
		void Register(std::string_view key, std::shared_ptr<Scene> scene);
		///
		/// シーンのプッシュバック
		/// リストの一番後ろ(最前面)にシーンをプッシュ追加する
		/// Sceneの入口処理Enterを実行する
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		///
		void PushBack(std::string_view key);
		///
		/// シーンのポップバック
		/// リストの一番後ろ(生前面)のシーンをポップ除外する
		/// Sceneの出口処理Exitを実行する
		///
		void PopBack();
		///
		/// シーンの遷移
		/// PopBackしてPushBackする
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		///
		void GoToScene(std::string_view key);
		///
		/// リストの一番後ろ(生前面)のシーンの真下に挿入する
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		/// Sceneの入口処理Enterを実行する
		///
		void InsertBelowBack(std::string_view key);

		/// 入力
		/// リストの一番後ろ(最前面)のシーンだけ処理する
		/// @param[in] input インプットコンポーネントの参照
		void Input(Input::InputComponent& input);
		///
		/// 更新
		/// リストの一番後ろ(最前面)のシーンだけ処理する
		///
		void Update();
		///
		/// 描画
		/// リストの全シーンを処理する
		///
		void Render() const;

	private:
		/// シーンのレジストリ
		std::unordered_map<std::string, std::shared_ptr<Scene>>	_registry;
		/// シーンのリスト
		std::list<std::shared_ptr<Scene>> _scenes;

	};

}

