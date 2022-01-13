

///
/// @file    InputComponent.h
/// @brief   入力コンポーネント
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <DxLib.h>
#include <utility>

namespace AppFrame {

  namespace Input {

    ///
    /// @class   MousState
    /// @brief   マウス状態クラスの宣言
    ///
    class MouseState {
    public:
      ///
      /// 更新.
      ///
      void Update();
      bool LeftClick() { return _trg & MOUSE_INPUT_LEFT; }    ///< 左クリック判定
      bool RightClick() { return _trg & MOUSE_INPUT_RIGHT; }  ///< 右クリック判定
      bool LeftPress() { return _fresh & MOUSE_INPUT_LEFT; }  ///< 左ボタン押下判定
      bool RightPress() { return _fresh & MOUSE_INPUT_RIGHT; }///< 右ボタン押下判定
      VECTOR GetPosition() { return _position; }  ///< 座標
      VECTOR GetDelta() { return _delta; }        ///< 座標の変化量
    private:
      int _fresh = 0;
      int _trg = 0;
      VECTOR _position{ 0,0,0 };
      VECTOR _delta{ 0,0,0 };
    };
  }
}