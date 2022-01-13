///
/// @file    Stage.h
/// @brief   ステージ
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include "../Actor/Actor.h"

namespace MachineHuck::Model {
	class ModelComponent;
}

namespace MachineHuck::Stage {

	using Floor = std::vector<std::shared_ptr<Model::ModelComponent>>;
	using StageFloor = std::unordered_map<int, std::tuple<AppFrame::Math::Vector4, AppFrame::Math::Vector4, int>>;
	

	class Stage : public Actor::Actor {
	public:
		Stage(AppFrame::Game& game);
		~Stage();

		virtual void Update() override;
		void Draw() override;

#ifdef _DEBUG

		void DrawFloor();

		bool CreateGround();
#endif 


		TypeId GetTypeId() const override { return TypeId::Stage; };

		/**
		 * @brief ステージの配置を作る
		 * @return 成功or失敗
		 */
		bool CreateStage(AppFrame::Game& game);

		/**
		 * @brief  プレイヤーのいるステージ番号を返す         
		 * @return ステージ番号
		 */
		int PlayerOnStageNumber();
		/** 
		 * @biref フロアの位置番号を取得
		 * @param x
		 * @param z
		 * @return フロアの位置番号
		 */
		//int GetBoard(int x, int z);

		///**
		// * @brief ボードにフロアの位置番号を書き込む
		// * @param x
		// * @param z
		// * @param n 番号
		// */
		//void SetBoard(int x, int z, int n);
	private:
		std::unique_ptr<Model::ModelComponent> _skySphere;
		std::unique_ptr<Model::ModelComponent> _ground;
		//static const int _boardW = 10;     //!< ボードの幅
		//static const int _boardH = 10;     //!< ボードの高さ
		//int _board[_boardW * _boardH];     //!< ボード
		//std::vector<int> _boardStageNum;   //!< キーがフロア番号、バリューがステージ番号


		StageFloor _stageFloor;                        //!< 各ステージフロア番号をキーとしたminおよびmaxの座標およびステージ番号を格納
		//Floor _floor;                                //!< 1フロア情報格納体
		//std::unordered_multimap<int, Floor> _allFloor; //!< 全フロアの情報
		std::unordered_map<int, Floor>      _allFloorMap;//!< 全フロアの情報
		std::vector<int>                    _drawFloorV; //!< 描画するフロア番号を格納

		int _stageNo;  //!< 現在のフロア番号

#ifdef _DEBUG

		static const int _boardW = 10;             //!< ボードの幅
		static const int _boardH = 10;             //!< ボードの高さ
		int _board[_boardW * _boardH];
		std::vector<VERTEX3D> _groundVertex;
		std::vector<unsigned short> _groundIndex;

#endif

		
	};
}


