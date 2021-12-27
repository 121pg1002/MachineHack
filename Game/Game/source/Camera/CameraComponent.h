///
/// @file    CameraComponent.h
/// @brief   カメラコンポーネント
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>
#include "AppFrame.h"

class InputComponent;
//namespace Camera {
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
    void Input(InputComponent& input);
    /// 更新
    void Update(math::Vector4 move);
    /// 描画
    void Draw(bool isHit);
    /// カメラ座標(始点)の設定
    /// @param[in] position
    void SetPosition(math::Vector4 position) { _position = position; }
    /// 目標座標(注視点)の設定
    /// @param[in] target
    void SetTarget(math::Vector4 target, math::Vector4 forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
    /// 注視点方向のベクトルを取得
    /// @return 注視点方向の単位ベクトル
    /*VECTOR GetForward() const { return VNorm(ToDX(_target -_position)); }*/
    //MATRIX GetCameraViewMatrix(VECTOR& cameraPosition, VECTOR& cameraTarget, VECTOR& cameraUp);

  protected:
    math::Vector4 _position{ 0, 5.0f, 0 };
    math::Vector4 _target{ 0, 0, 0 };
    math::Vector4 _forwardOfTarget{ 0, 0, 0 };
    float targetDist{ 500 };
    float vertDist{ 100 };
  };
//}
