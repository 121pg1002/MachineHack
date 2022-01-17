/*****************************************************************//**
 * @file  StateComponent.h
 * @brief  ステートコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "StateBaseRoot.h"

//class Actor;



namespace AppFrame::Input {
	class InputComponent;
}

namespace MachineHuck::State {
	//class StateBaseRoot {
	//public:
	//	StateBaseRoot() {};
	//	virtual void Enter() {};
	//	virtual void Input(AppFrame::Input::InputComponent& input) {};
	//	virtual void Update() {};
	//	virtual void Draw() {};
	//};

	class StateComponent {
	public:
		/// コンストラクタ
		/// @param[in] key   最初のシーンに関連付ける任意の文字列
		/// @param[in] scene 最初のシーンの
		StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state);
		/// 状態の登録
		/// @param[in] key   シーンに関連付ける任意の文字列
		/// @param[in] scene シーンのインスタンス
		void Register(std::string_view key, std::shared_ptr<StateBaseRoot> state);
		/// 状態のプッシュバック
		/// リストの一番後ろ(最前面)にシーンをプッシュ追加する
		/// Sceneの入口処理Enterを実行する
		/// @param[in] key 登録済みのシーンに関連付けた文字列
		void PushBack(std::string_view key);
		/// 状態のポップバック
		/// リストの一番後ろ(最前面)のシーンをポップ除外する
		/// Sceneの出口処理Exitを実行する
		void PopBack();
		/// 状態の遷移
		/// PopBackしてPushBackする
		/// @param[in] key 登録済みのシーンに関連付けた文字列
		void GoToState(std::string_view key);
		/// 入力
		/// リストの一番後ろ(最前面)のシーンだけ処理する
		/// @param[in] input インプットコンポーネントの参照
		void Input(AppFrame::Input::InputComponent& input);
		/// 更新
		/// リストの一番後ろ(最前面)のシーンだけ処理する
		void Update();
		/// 描画
		/// リストの全シーンを処理する
		void Draw() const;

	private:
		/// 状態のレジストリ
		std::unordered_map<std::string, std::shared_ptr<StateBaseRoot>>	_registry;
		/// 状態のリスト
		std::list<std::shared_ptr<StateBaseRoot>> _states;
	};
}


