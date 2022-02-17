/*****************************************************************//**
 * @file  SceneServer.h
 * @brief シーンサーバー
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
*********************************************************************/

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
		void PushBack(std::string_view key, bool menuflg);
		///
		/// 
		/// シーンのポップバック
		/// リストの一番後ろ(生前面)のシーンをポップ除外する
		/// Sceneの出口処理Exitを実行する
		///
		void PopBack();
		void PopBack(bool menuflg);
		///
		/// シーンの遷移
		/// PopBackしてPushBackする
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		///
		void GoToScene(std::string_view key);

		void GoToScene(std::string_view key, bool flag);


		/// シーンの遷移
		/// PopBackしてPushBackする
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		/// @param  sceneNext 次のシーン
		/// @param  flag Enterを行うかどうか
		///
		void GoToScene(std::string_view key, std::string_view sceneNext, bool flag);
		 
		/**
		 * @brief リストの一番手前のシーンを削除する
		 */
		void PopFront();

		/// リストの一番後ろ(生前面)のシーンの真下に挿入する
		/// @param[in] key  Sceneのインスタンスに関連付けるた任意の文字列
		/// Sceneの入口処理Enterを実行する
		///
		void InsertBelowBack(std::string_view key);

		/**
		 * @brief  リストの最後部のシーンに挿入する       
		 * @param  key   Seeneのインスタンスに関連付ける任意の文字列
		 * @param  flag　Enterを通すかどうか
		 */
		void InsertBelowBack(std::string_view key, bool flag);

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

