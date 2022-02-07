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
 //#include "../Enemy/EnemyParameter.h"
 //#include "../Item/ItemParameter.h"
 //#include "../Gimmick/GimmickParameter.h"

//namespace MachineHuck::Gimmick {
//	class GimmickParameter;
//}
//
//namespace MachineHuck::Enemy {
//	class EnemyParameter;
//}
//
//namespace MachineHuck::Item {
//	class ItemParameter;
//}


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
		std::unique_ptr<ShadowMap::Shadowmap> shadowmap;
		int _grHandle;
		
		
	};
}

