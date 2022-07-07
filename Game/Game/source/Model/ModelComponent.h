/*****************************************************************//**
 * @file   ModelComponent.h
 * @brief  スタティックモデル用のコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include <string_view>
#include <unordered_map>

namespace MachineHuck::Actor {
	class Actor;
}


namespace MachineHuck::Model {
	///
/// @class   ModelComponent
/// @brief   スタティックモデル用のコンポーネントクラスの宣言
///
	class ModelComponent {
	public:
		/// コンストラクタ
		/// @param[in] filename モデルのファイル名
		ModelComponent(Actor::Actor& owner);
		/// デストラクタ
		virtual ~ModelComponent();

		/// 初期化
		virtual void Init();

		/// 更新
		virtual void Update();

		/// 描画
		virtual void Draw();

		//仮とした壊せる壁のコリジョンを描画しない
		void BrokenDraw();

		/// @param collisionName コリジョンの名前
		void SetModelGimmick(std::string key, std::string collsionName, int no);

		std::unordered_map<int, int> GetModelGimmick() const { return _gimmickHandle; }

		///**
		// * @brief 描画 
		// * @param pos
		// * @param rot
		// * @param scale
		// */
		//virtual void Draw(Math::Vector4 pos, Math::Vector4 rot, Math::Vector4 scale);

		/// モデルの設定
		/// @param key AssetServerに登録済みのキー
		/// @return 実際に登録した通し番号
		virtual int SetModel(std::string_view key, int no = 0);

		/**
		 * @brief  ステージモデルの設定       
		 * @param  key AssetServerに登録済みのキー
		 * @return 実際に登録した通し番号
		 */
		int SetMap(std::string key, int no = 0);


		/// 座標の設定.
		/// @param[in] position 座標x,y,z
		virtual void SetPosition(VECTOR position);


		void SetPosition(VECTOR position, float diameter);

		/// 回転角度の設定.
		/// @param[in] rotation 回転角度x,y,z
		virtual void SetRotation(VECTOR rotation);

		/// 拡大率の設定.
		/// @param[in] scale 拡大率
		virtual void SetScale(VECTOR scale);

		/// ワールド行列の設定
		/// @param world 
		virtual void SetMatrix(MATRIX& world);

		/**
		 * @brief  ステージ番号を取得       
		 * @return _stageNum
		 */
		int GetStageNum() { return _stageNum; }

		/**
		 * @brief  ステージ番号を設定       
		 * @param  num
		 */
		void SetStageNum(int num) { _stageNum = num; }

		void SetHandle(const int handle) { _handle = handle; }
		int GetHandle() const { return _handle; }
		void SetColor(int index, float r, float g, float b);



	protected:
		Actor::Actor& _owner;
		int _handle{ -1 };
		bool _isLighting{ true };
		int _stageNum{-1};
		std::unordered_map<int, int> _gimmickHandle; //!< キー: ハンドル バリュー: フレームコリジョン
	};
}


