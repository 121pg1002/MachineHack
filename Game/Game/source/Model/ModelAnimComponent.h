/*****************************************************************//**
 * @file   ModelAnimComponent.h
 * @brief  アニメーションモデル用のコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include "ModelComponent.h"
#include <string_view>
#include <unordered_map> 
#include "AppFrame.h"
namespace Math = AppFrame::Math;


namespace MachineHuck::Model {
	///
/// @class   ModelAnimComponent
/// @brief   アニメーションモデル用のコンポーネントクラスの宣言
///
	class ModelAnimeComponent : public ModelComponent {
	public:
		///
		/// コンストラクタ.
		///
		ModelAnimeComponent(Actor::Actor& owner);
		/// デストラクタ
		virtual ~ModelAnimeComponent() override;

		/// 初期化
		void Init() override;

		/// アニメーションの登録
		/// @param[in] key 任意の文字列キー
		/// @param[in] animIndex 関連付けるアニメインデックス
		void Register(std::string_view key, int animIndex);

		/// 更新
		void Update() override;

		/// 描画
		void Draw() override;

		/// 描画扇型判定用
		void Draw(const Actor::Actor& owner, bool isHit, double range, bool select);

		//AABB用
		void Draw(const Actor::Actor& owner, Math::Vector4 position);

		///
		/// アニメーションの変更.
		/// @param[in] newAnimIndex アニメインデックス
		///
		void ChangeAnime(std::string_view key, bool repeate = false);

		/// アニメーションを繰り返した回数の取得
		/// @return 繰り返した回数
		///
		int GetRepeatedCount() const { return _repeatedCount; }
		///
		/// アニメーションの総時間を取得.
		/// @return 総時間
		///
		float GetPlayTime() const { return _playTime; }
		/// アニメーションの総時間を取得
		/// @return 総時間
		float GetPlayProgress() const { return _playTime / _totalTime; }

		/// 再生時間の掛率設定
		/// @param[in] timeRate 再生時間の掛率
		void SetTimeRate(float timeRate) { _timeRate = timeRate; }
		float GetTimeRate() { return _timeRate; }


	private:
		std::unordered_map<std::string, int> _registry;
		int _animIndex{ -1 };
		int _attachIndex{ -1 };
		float _playTime{ 0 };
		float _totalTime{ 0 };
		float _timeRate{ 1.f };
		int _repeatedCount{ 0 };
		bool _repeate{ false };
	};
}


