/*****************************************************************//**
 * @file   SceneInGame.h
 * @brief  インゲーム画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once

#include <memory>
#include "AppFrame.h"
#include "../ShadowMap/Shadowmap.h"

class CameraComponent;

class Player;

namespace MachineHuck::Scene {
	/// @class   SceneInGame
	/// @brief   インゲーム画面クラスの宣言
	class SceneInGame : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		SceneInGame(AppFrame::Game& game);
		/// デストラクタ
		~SceneInGame() = default;
		/// 初期化
		void Init() override;
		/// 入口
		void Enter() override;
		/// 入力
		/// @param[in] input インプットコンポーネント
		void Input(AppFrame::Input::InputComponent& input) override;
		/// 更新
		void Update() override;
		/// 描画
		void Render() override;
		/// 出口
		void Exit() override;
	private:
		MachineHuck::ShadowMap::Shadowmap shadowmap;
		
		
	};
}

