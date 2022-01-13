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
   /// @class   JoypadState
   /// @brief   ジョイパッド状態クラスの宣言
   ///          パッド入力を得る場合はメンバーを追加する
   ///
    class JoypadState {
    public:
      void Update();
      /*
      *@brief  戻るボタン
      *@return Backボタン
      */
      bool Exit() { return _trg[5]; }


      /*
      *@brief  スタートボタン
      *@return Startボタン
      */
      bool Start() { return _trg[4]; }


      /*
      *@brief  前後
      *@return 左スティック & 上下
      */
      double LVertical() { return _fresh.ThumbLY; }


      /*
      *@brief  左右
      *@return 左スティック & 左右
      */
      double LHorison() { return _fresh.ThumbLX; }


      /*
      *@brief  前後
      *@return 右スティック & 上下
      */
      double RVertical() { return _fresh.ThumbRY; }

      /*
      *@brief  左右
      *@return 右スティック & 左右
      */
      double RHorison() { return _fresh.ThumbRX; }

      /*
      *@brief  Aボタン
      *@return トリガ & Aボタン
      */
      bool Button_A() { return _trg[12]; }

      /*
      *@brief  Bボタン
      *@return トリガ & Bボタン
      */
      bool Button_B() { return _trg[13]; }

      /*
      *@brief  Xボタン
      *@return トリガ & Xボタン
      */
      bool Button_X() { return _trg[14]; }


      /*
      *@brief  Yボタン
      *@return トリガ & Yボタン
      */
      bool Button_Y() { return _trg[15]; }

      /*
      *@brief  LBボタン
      *@return トリガ & LBボタン
      */
      bool Button_LB() { return _trg[9]; }

      /*
      *@brief  RBボタン
      *@return トリガ & RBボタン
      */
      bool Button_RB() { return _trg[8]; }


      /*
      *@brief  LTボタン
      *@return LTボタン
      */
      bool Button_LT() { return _fresh.LeftTrigger; }

      /*
      *@brief  RTボタン
      *@return RTボタン
      */
      bool Button_RT() { return _fresh.RightTrigger; }



    private:

      XINPUT_STATE _fresh;     //!< xインプットの状態
      int _trg[16];            //!< トリガ
    };
  }
}
