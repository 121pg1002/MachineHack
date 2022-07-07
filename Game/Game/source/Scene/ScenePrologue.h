/*****************************************************************//**
 * @file   ScenePrologue.h
 * @brief  プロローグ画面
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#pragma once
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}

namespace MachineHuck::Scene {
	/// @class   SceneTitle
/// @brief   プロローグ画面クラスの宣言
	class ScenePrologue : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		ScenePrologue(AppFrame::Game& game);
		/// デストラクタ
		~ScenePrologue() = default;
		/// 初期化
		void Init() override;
		/// 入口
		virtual void Enter() override;
		/// 入力
		void Input(AppFrame::Input::InputComponent& input) override;
		///更新
		void Update() override;
		/// 描画
		void Render() override;
	private:
		int _gameEpilogueHandle{ -1 };  ///< ゲームタイトル画像
		int _leftClickToStart{ -1 }; ///< Left click to Start画像
		int _epilogueBgHandle{ -1 };    ///< 背景画像
		int _alpha{ 0 };
	};
}


