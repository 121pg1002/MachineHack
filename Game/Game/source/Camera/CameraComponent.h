/*****************************************************************//**
 * @file   CameraComponent.h
 * @brief  カメラコンポーネント
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/

#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}

namespace Math = AppFrame::Math;

//ゲーム名
namespace MachineHuck {

	//フォルダ名
	namespace Camera{
	
		///
/// @class   CameraComponent
/// @brief   カメラコンポーネントクラスの宣言
///          相対マウスコントロールによるカメラ制御
///
		class CameraComponent {
		public:
			/// コンストラクタ
			CameraComponent();
			/// 初期化
			void Init();
			/// 入力処理
			void Input(AppFrame::Input::InputComponent& input);
			/// 更新
			void Update(Math::Vector4 move);

			/**
			 * @brief カメラの位置とターゲット設定       
			 * @param pos フロア位置
			 */
			void FloorPos(Math::Vector4 pos);

			/// 描画
			void Draw(bool isHit);
			/// カメラ座標(始点)の設定
			/// @param[in] position
			void SetPosition(Math::Vector4 position) { _position = position; }

			/**
			 * @brief  カメラ位置の更新         
			 * @param  position
			 */
			void SetRefleshPosition(Math::Vector4 position);

			/// 目標座標(注視点)の設定
			/// @param[in] target
			void SetTarget(Math::Vector4 target, Math::Vector4 forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }


			/**
			 * @brief  カメラ目標の更新         
			 * @param  position
			 */
			void SetRefleshTarget(Math::Vector4 position);


			/// 注視点方向のベクトルを取得
			/// @return 注視点方向の単位ベクトル
			/*VECTOR GetForward() const { return VNorm(ToDX(_target -_position)); }*/
		  //MATRIX GetCameraViewMatrix(VECTOR& cameraPosition, VECTOR& cameraTarget, VECTOR& cameraUp);

		protected:
			Math::Vector4 _position{ 0, 5.0f, 0 };
			Math::Vector4 _target{ 0, 0, 0 };
			Math::Vector4 _forwardOfTarget{ 0, 0, 0 };
			float targetDist{ 500 };
			float vertDist{ 100 };
			Math::Vector4 _positionInitDif{ 0, 1200, -1000 }; //!< 初期カメラ位置の差分座標
			//Math::Vector4 _positionInitDif{ 0, 2000, -200 }; //!< 初期カメラ位置の差分座標
			Math::Vector4 _targetInitDif{ 0, 100, 0 };       //!< 初期カメラ目標の差分座標
		};
	}

}



