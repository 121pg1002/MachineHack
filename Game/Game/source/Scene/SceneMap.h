#pragma once
#include <AppFrame.h>
#include <unordered_map>

/// @file    SceneMap.h
/// @brief   アイテム画面
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.



namespace MachineHuck::Scene {
	class SceneMap : public AppFrame::Scene::Scene {
	public:
		/// コンストラクタ
		/// @param[in] game Gameクラスの参照
		SceneMap(AppFrame::Game& game);
		/// デストラクタ
		~SceneMap() = default;
		/// 初期化
		void Init() override;
		/// 入口
		virtual void Enter() override;
		/// 入力
		void Input(AppFrame::Input::InputComponent& input) override;
		/// 更新
		void Update() override;
		/// 描画
		void Render() override;

		std::vector<int> GetPlayerVector() { return _playerV; }

	private:
		int MapHandle{ -1 };  ///< マップ画像
		int _alpha{0};
		std::unordered_map<int, int> _floorMap;  //!< フロアマップの
		std::vector<int> _playerV; //!< プレイヤーのいったことのあるマップを保存するベクター
	};






}