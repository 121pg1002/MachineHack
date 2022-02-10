
/*****************************************************************//**
 * @file   CollisionComponent.h
 * @brief  衝突判定クラス
 * 
 * @author hikaru Goto
 * @date   December 19 2021
 *********************************************************************/

#include <memory>
#include <tuple>
#include <DxLib.h>
#include "AppFrame.h"


namespace Math = AppFrame::Math;


//struct Sphere {
//  Sphere(const Math::Vector4& center, float radius);
//  bool Contains(const Math::Vector4& point) const;
//
//  Math::Vector4 center;
//  float radius;
//};

//bool Intersect(const Sphere& a, const Sphere& b);
namespace MachineHuck::Actor {
	class Actor;
}

namespace MachineHuck::Model {
	class ModelComponent;
}

namespace MachineHuck::Collision {
	class CollisionComponent {
	public:
		//enum class ReportId {
		//  None,
		//  HitFromPlayer,
		//  HitFromEnemy,
		//  HuckedFromPlayer,
		//};

		//struct Report {
		//  ReportId id{ReportId::None};
		//  Math::Vector4 position{0, 0, 0};
		//};
		using AABB = std::tuple<double, double, double, double>;
		using WarpMap = std::unordered_map<std::string, std::pair<std::pair<int, int>, int>>;
		using WarpName = std::unordered_multimap<int, std::unordered_multimap<std::string, std::string>>;
		using Floor = std::vector<std::shared_ptr<Model::ModelComponent>>;


		CollisionComponent(Actor::Actor& owner);
		~CollisionComponent();

		//void EnemyFromPlayer();
		//void PlayerFromEnemy();

		//void SetReport(Report report) { *_report = report; }
		//Report& GetReport() const { return *_report; }

		/**
		 * @brief  円と円の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		bool CircleToCircle(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  矩形と矩形の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		bool AABBToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief 辺の四角形の辺の一辺を得る 
		 * @param center
		 * @param halfExtends
		 * @param rot
		 * @param point
		 * @return 始点と終点のペア型
		 */
		//std::pair<Math::Vector2, Math::Vector2 > GetOrientedRectangleEdge(Math::Vector4 center, Math::Vector2 halfExtends, double rot, int point);

		///**
		// * @brief 逆ベクトルを返す
		// * @param vec
		// * @return 引数の逆ベクトル
		// */
		//Math::Vector2 GetNeGateVector(Math::Vector2 vec);

		///**
		// * @brief ベクトルを回転させる
		// * @param vec    xzベクトル
		// * @param radian ラジアン
		// * @return 回転したベクトル
		// */
		//Math::Vector2 GetRotateVector(Math::Vector2 vec, double radian);
		



		/**
		 * @brief  円と矩形の当たり判定を行う
		 * @param  act1 自分(円)
		 * @param  act2 相手(矩形)
		 * @return 成否
		 */
		bool CircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);


		///**
		// * @brief  円と矩形の当たり判定を行う
		// * @param  act1 自分(円)
		// * @param  act2 相手(矩形)
		// * @return 成否
		// */
		//bool CollisionCircleToAABB(const Actor::Actor& act1, const Actor::Actor& act2);

	
		/**
		 * @brief  円と矩形の当たり判定を行う       
		 * @param  act  プレイヤー
		 * @param  min  最小座標
		 * @param  max  最大座標
		 * @return 成否
		 */
		bool CircleToAABB(const Actor::Actor& act, const AppFrame::Math::Vector4 min, const AppFrame::Math::Vector4 max);


		/**
		 * @brief  円と回転した矩形の当たり判定を行う
		 * @param  act1 自分(円)
		 * @param  act2 相手(回転した矩形)
		 * @return
		 */
		bool CircleToOrientedAABB(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief 矩形と回転した矩形の当たり判定を行う 
		 * @param own (矩形)
		 * @param target(回転した矩形)
		 * @return true  当たった
		 *         false 当たっていない
		 */
		bool AABBToOrientedAABB(const Actor::Actor& own, const Actor::Actor& target);

		/**
		 * @brief  円と線分の当たり判定を行う
		 * @param  act1 自分
		 * @param  act2 相手
		 * @return 成否
		 */
		//bool CircleToLine(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  円と線分の当たり判定を行う
		 * @param  act1 自分
		 * @param  start 始点
		 * @param  end 終点 
		 * @return 成否
		 */
		bool CircleToLine(const Actor::Actor& act1, const Math::Vector4 start, const Math::Vector4 end);




		/*
		*@brief 円と扇形の当たり判定を行う
		*/
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2);

		/**
		 * @brief  円と扇形の当たり判定を行う
		 * @param  act1  自分
		 * @param  act2  相手
		 * @param  select trueは索敵範囲 falseはハッキング範囲の判定
		 * @return 成否
		 */
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, bool select);


		
		/**
		 * 
		 * @brief  キャッチエネミー用の当たり判定         
		 * @param  act1         自分
		 * @param  act2　　　　 相手
		 * @param  catchR       半径
		 * @param  catchRange   範囲角度
		 * @return true  当たった
		 *         false 当たっていない
		 */
		bool FanToPoint(const Actor::Actor& act1, const Actor::Actor& act2, double r, double range);


		

		/**
		 * @brief  線分とAABBの当たり判定を行う
		 * @param  act1
		 * @param  act2
		 * @return 成否
		 */
		bool LineToAABB(const Actor::Actor& act1, const Actor::Actor& act2, const AABB box);

		/**
		 * @brief 線分とAABBの当たり判定を行う
		 * @param startPos
		 * @param endPos
		 * @param target
		 * @return 成否
		 */
		bool LineToAABB(Math::Vector2 startPos, Math::Vector2 endPos, const Actor::Actor& target);
		///**
		// * @brief  線分とAABBの当たり判定を行う
		// * @param  act
		// * @param  min
		// * @param  max
		// * @return 成否
		// */
		//bool LineToAABB(const Actor::Actor& act1, const Math::Vector2 min, const Math::Vector2 max);

		/**
		 * @brief 床のナビメッシュとの当たり判定
		 * @param act
		 * @return true  当たっている
		 *         false 当たっていない
		 */
		//bool CollisionFloor(const Actor::Actor& act);

		/**
		 * @brief  平面との交差テスト
		 * @param  start
		 * @param  end
		 * @param  negd
		 * @param  out
		 * @return 成否
		 */
		bool TestSidePlane(const double start, const double end, const double negd, std::vector<double>& out);

		/** 
		 * @brief  線分上の座標を計算  
		 * @param  start
		 * @param  end     
		 * @param  t
		 * @return 座標
		 */
		const Math::Vector4 PointOnSegment(const Math::Vector4 start, const Math::Vector4 end, const double t);

		/** 
		 * @brief  線分上の座標を計算  
		 * @param  start
		 * @param  end     
		 * @param  t
		 * @return 座標
		 */
		const Math::Vector2 PointOnSegment(const Math::Vector2 start, const Math::Vector2 end, const double t);

		/**
		 * @brief  壊せる壁と当たっているか       
		 * @param  own
		 * @return 成否
		 */
		bool CollisionBrokenWall(const Actor::Actor& own);

		///**
		// * @brief  マップコリジョン情報を取得       
		// * @return _frameMapCollision
		// */
		//const int GetMapCollision() const  { return _frameMapCollision; };

		/**
		 * @brief  マップのコリジョン情報配列を取得
		 * @return _frameMapCollisions
		 */
		//const std::vector<int> GetMapCollision() const { return _frameMapCollisions; }

		/**
		 * @brief  マップコリジョン情報を取得       
		 * @return _frameMapCollision
		 */
		const int GetMapCollision(int handle) { return _frameMap[handle]; };

		/**
		 * @brief  ギミックのコリジョン情報を取得       
		 * @param  handle
		 * @return _frameGimmickCollision
		 */
		const int GetGimmickCollision(int handle) { return _frameGimmick[handle]; };


		/**
		 * @brief  マップのナビメッシュ情報の構築
		 * @param  handle
		 * @param  key
		 */
		void SetMapCollision(int handle, std::string key);

		/**
		 * @brief  マップのナビメッシュ情報の全フレーム構築
		 * @param  handle
		 */
		void SetMapCollision(int handle);

		/**
		 * @brief  ギミックのナビメッシュ情報の構築       
		 * @param  handle
		 * @param  key
		 */
		void SetGimmickCollision(int handle, std::string key);


		/**
		 * @brief  ワープ位置情報を取得
		 * @param  handle ハンドル
		 * @return _frameMapCollision
		 */
		const std::pair<std::pair<int, int>, int> GetWarpCollision(std::string key, int handle);

		/**
		 * @brief  マップのワープ位置情報の設定
		 * @param  handle
		 * @param  key
		 */
		void SetWarpCollision(int handle, std::string key);

		/**
		 * @brief  ワープ位置の名前配列を取得
		 * @param  handle ハンドル
		 * @return _warpName
		 */
		const std::vector<std::string> GetWarpName(int handle);

		/**
		 * @brief  ワープ位置の名前配列を設定
		 * @param  handle ハンドル
		 * @param  keyV   キーの配列
		 */
		void SetWarpName(int handle, std::vector<std::string> keyV);

		/**
		 * @brief  ワープ先の名前を取得
		 * @param  floorNum フロア番号
		 * @param  warpKey  ワープ前のフレーム名
		 * @return ワープ先の名前
		 */
		const std::string GetWarpNameFloor(int floorNum, std::string warpKey);

		///**
		// * @brief  ワープ位置の名前配列を設定      
		// * @param  num         配置するフロア番号
		// * @param  keys        ワープ位置の名前配列
		// */
		void SetWarpNameFloor(int num, std::vector<std::string> keys);

		/**
		 * @brief  主人公の触れているステージ番号配列を取得
		 * @return _stageNums
		 */
		std::vector<int> GetCollStageNum() { return _stageNums; }

		/**
		 * @brief  主人公の触れているステージ番号配列を設定
		 * @param  stageNums
		 */
		void SetCollStageNum(std::vector<int> stageNums) { _stageNums = stageNums; }

		/**
		 * @brief  主人公の触れているフロア番号配列を取得
		 * @return _floorNums
		 */
		std::vector<int> GetFloorNum() { return _floorNums; }

		/**
		 * @brief  カメラに送るためのフロア番号によるステージの位置を取得
		 * @param  floorNum
		 * @return ステージ座標
		 */
		Math::Vector4 GetFloorPos(int floorNum) { return _floorPoses[floorNum]; }

		/**
		 * @brief  フロア番号によるステージ位置の設定
		 * @param  floorPoses
		 */
		void SetFloorPos(std::unordered_map<int, Math::Vector4> floorPoses) { _floorPoses = floorPoses; }


		/**
		 * @brief  主人公の触れているフロア番号配列を設定
		 * @param  floorNums
		 */
		void SetFloorNum(std::vector<int> floorNums) { _floorNums = floorNums; }

		/**
		 * @brief  フロア番号をキーとしてステージ番号を取得
		 * @param  floorNum フロア番号
		 * @return ステージ番号
		 */
		int GetFloorStageNum(int floorNum) { return _floorStageNum[floorNum]; }

		/**
		 * @brief  フロア番号をキーとして、要素をステージ番号とした連想配列を設定
		 * @param  floorStage キー :　フロア番号,  要素 : ステージ番号
		 */
		void SetFloorStageNum(std::unordered_map<int, int> floorStage) { _floorStageNum = floorStage; }

		std::unordered_map<int, Floor> GetAllFloorMap() { return _allFloorMap; }

		void SetAllFloorMap(std::unordered_map<int, Floor> allFloorMap) { _allFloorMap = allFloorMap; }
	private:
		Actor::Actor& _owner;
		/*std::unique_ptr<Report> _report;*/
		double _r1{ 0.0 }, _r2{ 0.0 }; //!< 円の半径

		Math::Vector4 _interSection;          //!< 線分と回転した四角形との交点
		int _frameMapCollision;               //!< マップのコリジョン情報
		int _frameGimmickCollision;           //!< ギミックのコリジョン情報
		//std::vector<int> _frameMapCollisions; //!< マップのコリジョン情報のベクター
		std::unordered_map<int, int> _frameMap; //!< ハンドルをキーとしたコリジョン情報
		std::unordered_map<int, int> _frameGimmick; //!< ハンドルをキーとしたギミックのコリジョン情報
		std::unordered_map<int, std::vector<std::string>> _warpNameMap;   //!< ハンドルをキーとしたワープの名前配列
		WarpMap _warpMap;                                                 //!< キーはワープコリジョンフレーム名で バリューは、ワープ先の位置情報とコリジョン情報
		WarpName _warpNameFloor; //!< フロア番号頭をキーとした連想配列は、ワープ位置の頭文字2文字をキーとした ワープ名の名前をバリューとしてもつ
		std::vector<int> _stageNums; //!< 主人公が触れているステージ番号配列
		std::unordered_map<int, int> _floorStageNum; //フロア番号をキーとしてステージ番号を取得する連想配列
		//std::unordered_map<int, int> _stageFloorNum; //ステージ番号をキーとしてフロア番号を取得する連想配列
		std::vector<int> _floorNums;  // フロア番号配列
		std::unordered_map<int, Floor> _allFloorMap; //全フロアマップの連想配列

		std::unordered_map<int, Math::Vector4> _floorPoses; //!< フロア番号をキーとしたステージ位置座標
	};
}

