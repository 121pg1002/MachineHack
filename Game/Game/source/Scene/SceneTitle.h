///
/// @file    SceneTitle.h
/// @brief   タイトル画面
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"
#include "../Shader/Shader.h" //田川　シェーダー描画サンプル用に追加（以下サンプル描画用に追加したコードは//tで表す）
namespace AppFrame::Input {
	class InputComponent;
}


namespace MachineHuck::Scene {
	/// @class   SceneTitle
/// @brief   タイトル画面クラスの宣言
	class SceneTitle : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		SceneTitle(AppFrame::Game& game);
		/// デストラクタ
		~SceneTitle() = default;
		/// 初期化
		void Init() override;
		/// 入口処理
		virtual void Enter() override;
		/// 入力処理
		void Input(AppFrame::Input::InputComponent& input) override;

		void Update() override;
		/// 描画処理
		void Render() override;
	private:
		int _gameTitleHandle{ -1 };  ///< ゲームタイトル画像
		int _leftClickToStart{ -1 }; ///< Left click to Start画像
		int _titleBgHandle{ -1 };    ///< 背景画像
		int _alpha{ 0 };
		Shader shader;
	};
}


