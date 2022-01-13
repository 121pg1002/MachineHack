///
/// @file    SceneTitle.h
/// @brief   タイトル画面
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}
namespace MachineHuck::Effect {
	class EffectLaser;
}
namespace MachineHuck::Scene {
	/// @class   SceneTitle
/// @brief   タイトル画面クラスの宣言
	class SceneTeam : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		SceneTeam(AppFrame::Game& game);
		/// デストラクタ
		~SceneTeam() = default;
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
		int _gameTitleHandle{ -1 };  ///< ゲームタイトル画像
		int _leftClickToStart{ -1 }; ///< Left click to Start画像
		int _teamBgHandle{ -1 };    ///< 背景画像
		int _alpha{ 0 };
		std::unique_ptr<MachineHuck::Effect::EffectLaser> laser;
	};
}


