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
      /// @class   KeyBoardState
      /// @brief   キーボード状態クラスの宣言
      ///          キー入力を得る場合はメンバーを追加する
      /// 
    class KeyBoardState
    {
    public:

      ///
      /// 更新
      ///
      void Update();

      /*
      *@brief  Wキー
      *@return Wキー
      */
      int Button_W() { return CheckHitKey(KEY_INPUT_W); }

      /*
      *@brief  Sキー
      *@return Sキー
      */
      int Button_S() { return CheckHitKey(KEY_INPUT_S); }

      /*
      *@brief  Aキー
      *@return Aキー
      */
      int Button_A() { return CheckHitKey(KEY_INPUT_A); }

      /*
      *@brief  Dキー
      *@return Dキー
      */
      int Button_D() { return CheckHitKey(KEY_INPUT_D); }

      /*
      *@brief  Cキー
      *@return Cキー
      */
      int Button_C() { return _trg[0]; }

      /*
      *@brief  Eキー
      *@return Eキー
      */
      int Button_E() { return _trg[1]; }

      /*
      *@brief  Qキー
      *@return Qキー
      */
      int Button_Q() { return _trg[2]; }

      /*
      *@brief  スペースキー
      *@return スペースキー
      */
      int Button_Space() { return  _trg[3]; }

      /*
      *@brief  Enterキー
      *@return Enterキー
      */
      int Button_Enter() { return _trg[4]; }

    private:
      int _fresh[5]{ 0 };        //!< キーの状態
      int _trg[5]{ 0 };          //!< トリガの状態
    };
  }
}
