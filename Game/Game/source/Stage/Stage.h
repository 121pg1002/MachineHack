/*****************************************************************//**
 * @file   Stage.h
 * @brief  ステージ
 *
 * @author yamawaki kota, hikaru goto
 * @date   December 6 2021
 *********************************************************************/

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
	//using Collision = std::vector<std::pair<std::string, std::vector<std::string>>>;

	//                                       フロア番号      ハンドル名, コリジョンメッシュ名, ワープメッシュ名の配列,  フロア番号 
	using CollisionMesh = std::unordered_map<int, std::tuple<std::string, std::string, std::vector<std::string>, int>>;

	/**
	 * @class ステージクラス
	 * @brief ステージに関するクラス
	 */
	class Stage : public Actor::Actor {
	public:
		Stage(AppFrame::Game& game);
		~Stage();

		virtual void Update() override;
		void Draw() override;

#ifdef _DEBUG

		/**
		 * @brief  フロア位置を描画
		 */
		void DrawFloor();

		/**
		 * @brief  ポリゴンによるフロア作成
		 * @return true  成功
		 *         false 失敗
		 */
		bool CreateGround();
#endif 


		TypeId GetTypeId() const override { return TypeId::Stage; };

		/**
		 * @brief ステージの配置を作る
		 * @return true  成功
		 *         false 失敗
		 */
		bool CreateStage(AppFrame::Game& game);

		/**
		 * @brief  プレイヤーのいるステージ番号を返す
		 * @return ステージ番号
		 */
		int PlayerOnStageNumber();

		///**
		// * @brief  マップコリジョン情報を取得       
		// * @return _frameMapCollision
		// */
		//const int GetMapCollision() const  { return _frameMapCollision; };

		/**
		 * @brief  マップコリジョンのコンテナを取得
		 * @return _collsionFloorNameMap
		 */
		CollisionMesh GetCollMap() const { return _collisionFloorNameMap; }


		/**
		 * @brief 描画フロアを取得
		 * @return _drawFloorV
		 */
		const std::vector<int> GetDrawFloorV() { return _drawFloorV; }

	private:
		//std::unique_ptr<Model::ModelComponent> _skySphere;
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

		std::unordered_map<int, std::vector<int>>  _secretVMap; //!< 隠しているフロア配列を部屋番号で格納するマップ      
		std::vector<int>                    _secretV;           //!< 隠しているフロアの番号を格納
		CollisionMesh _collisionFloorNameMap;                   //!< コリジョンの名前フレームの配列 キー: ハンドル名 バリュー: コリジョンメッシュ名
		std::unordered_map<int, int>        _floorStageNum; //!< フロア番号でステージ番号を格納
		//std::vector<std::string> _handleV;                //ハンドル名の配列
		int _stageNo;  //!< 現在のフロア番号

#ifdef _DEBUG

		static const int _boardW = 10;             //!< ボードの幅
		static const int _boardH = 10;             //!< ボードの高さ
		int _board[_boardW * _boardH];
		std::vector<VERTEX3D> _groundVertex;
		std::vector<unsigned short> _groundIndex;

#endif
		//int _frameMapCollision; //!< マップのコリジョン情報

	};
}


