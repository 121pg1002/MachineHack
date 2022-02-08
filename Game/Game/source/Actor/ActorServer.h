/*****************************************************************//**
 * @file   ActorServer.h
 * @brief  アクターサーバー
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include "AppFrame.h"
#include "Actor.h"

class Actor;
namespace Input {
	class InputComponent;
}

namespace Math = AppFrame::Math;
using _pos_dir = std::pair<Math::Vector4, Math::Vector4>;


namespace MachineHuck::Actor {
	/// @class ActorServer
/// @brief アクターを一元管理する
	class ActorServer {
	public:
		/// アクターの追加
		/// @param actor 
		void Add(std::unique_ptr<Actor> actor);
		/**
		 * @brief アクターの削除
		 * @param actor
		 */
		void Del(std::unique_ptr<Actor> actor);

		/// 
		/// 		/// 入力
		/// @param[in] input インプットコンポーネント
		void Input(AppFrame::Input::InputComponent& input);
		/// 更新
		void Update();
		/// 描画
		void Render();
		/// 全アクターの削除
		void Clear();
		/// アクターの登録
		/// 登録するとアクターから情報を得ることができる
		/// @param[in] key 任意の文字列キー
		/// @param[in] pos 登録する位置
		void Register(std::string_view key, _pos_dir vec);
		/// アクターの一覧の取得
		/// @return アクターの一覧への参照
		std::vector<std::unique_ptr<Actor>>& GetActors() { return _actors; };


		/// 登録したアクターの位置を得る
		/// @param[in] key 登録済みのキー
		/// @return 登録したアクターの位置
		Math::Vector4 GetPosition(std::string_view key);
		/// 登録したアクターの前進方向を得る
		/// @param[in] key 登録済みのキー
		/// @return 登録したアクターの前進方向単位ベクトル
		//Math::Vector4 GetForward(std::string_view key);

		Math::Vector4 GetDir(std::string_view key);


		int GetGimmickCollision(const int handle)   { return _gimmicksCollision[handle]; }

		void SetGimmickCollision(const std::unordered_map<int, int> gimmicks) { _gimmicksCollision = gimmicks; }
		//Math::Vector4 GetMove(std::string_view key);

	private:
		bool 	_updating{ false };
		std::vector<std::unique_ptr<Actor>> _actors;
		std::vector<std::unique_ptr<Actor>> _pendingActors;
		std::unordered_map<std::string, _pos_dir> _registry;
		std::unordered_map<int, int> _gimmicksCollision;

	};
}

