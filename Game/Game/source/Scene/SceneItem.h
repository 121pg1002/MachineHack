#pragma once
///
/// @file    SceneItem.h
/// @brief   アイテム画面
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.

#include <AppFrame.h>


namespace MachineHuck::Scene {
    class SceneItem : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		SceneItem(AppFrame::Game& game);
		/// デストラクタ
		~SceneItem() = default;
		/// 初期化
		void Init() override;
		/// 入口
		virtual void Enter() override;
		/// 入力
		void Input(AppFrame::Input::InputComponent & input) override;
		/// 更新
		void Update() override;
		/// 描画
		void Render() override;

	private:
		int ItemHandle{ -1 };//アイテム画面画像
		int _alpha{ 0 };

    };

	




}