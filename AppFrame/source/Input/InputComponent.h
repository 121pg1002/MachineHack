/*****************************************************************//**
 * @file   InputComponent.h
 * @brief  入力コンポーネント
 *
 * @author Kota Yamawaki
 * @date   November 26 2021
 *********************************************************************/

#pragma once
#include "JoypadState.h"
#include "KeyBoardState.h"
#include "MouseState.h"
#include <DxLib.h>
#include <utility>

namespace AppFrame {

    namespace Input {
      class MouseState;
      class JoypadState;
      class KeyBoardState;
//        ///
///// @class   MousState
///// @brief   マウス状態クラスの宣言
/////
//        class MouseState {
//        public:
//            ///
//            /// 更新.
//            ///
//            void Update();
//            bool LeftClick() { return _trg & MOUSE_INPUT_LEFT; }    ///< 左クリック判定
//            bool RightClick() { return _trg & MOUSE_INPUT_RIGHT; }  ///< 右クリック判定
//            bool LeftPress() { return _fresh & MOUSE_INPUT_LEFT; }  ///< 左ボタン押下判定
//            bool RightPress() { return _fresh & MOUSE_INPUT_RIGHT; }///< 右ボタン押下判定
//            VECTOR GetPosition() { return _position; }  ///< 座標
//            VECTOR GetDelta() { return _delta; }        ///< 座標の変化量
//        private:
//            int _fresh = 0;
//            int _trg = 0;
//            VECTOR _position{ 0,0,0 };
//            VECTOR _delta{ 0,0,0 };
//        };
        /////
        ///// @class   JoypadState
        ///// @brief   ジョイパッド状態クラスの宣言
        /////          パッド入力を得る場合はメンバーを追加する
        /////
        //class JoypadState {
        //public:
        //    void Update();
        //    /*
        //    *@brief  戻るボタン
        //    *@return Backボタン
        //    */
        //    bool Exit() { return _trg[5]; }


        //    /*
        //    *@brief  スタートボタン
        //    *@return Startボタン
        //    */
        //    bool Start() { return _trg[4]; }


        //    /*
        //    *@brief  前後
        //    *@return 左スティック & 上下
        //    */
        //    double LVertical() { return _fresh.ThumbLY; }


        //    /*
        //    *@brief  左右
        //    *@return 左スティック & 左右
        //    */
        //    double LHorison() { return _fresh.ThumbLX; }


        //    /*
        //    *@brief  前後
        //    *@return 右スティック & 上下
        //    */
        //    double RVertical() { return _fresh.ThumbRY; }

        //    /*
        //    *@brief  左右
        //    *@return 右スティック & 左右
        //    */
        //    double RHorison() { return _fresh.ThumbRX; }

        //    /*
        //    *@brief  Aボタン
        //    *@return トリガ & Aボタン
        //    */
        //    bool Button_A() { return _trg[12]; }

        //    /*
        //    *@brief  Bボタン
        //    *@return トリガ & Bボタン
        //    */
        //    bool Button_B() { return _trg[13]; }

        //    /*
        //    *@brief  Xボタン
        //    *@return トリガ & Xボタン
        //    */
        //    bool Button_X() { return _trg[14]; }


        //    /*
        //    *@brief  Yボタン
        //    *@return トリガ & Yボタン
        //    */
        //    bool Button_Y() { return _trg[15]; }

        //    /*
        //    *@brief  LBボタン
        //    *@return トリガ & LBボタン
        //    */
        //    bool Button_LB() { return _trg[9]; }

        //    /*
        //    *@brief  RBボタン
        //    *@return トリガ & RBボタン
        //    */
        //    bool Button_RB() { return _trg[8]; }


        //    /*
        //    *@brief  LTボタン
        //    *@return LTボタン
        //    */
        //    bool Button_LT() { return _fresh.LeftTrigger; }

        //    /*
        //    *@brief  RTボタン
        //    *@return RTボタン
        //    */
        //    bool Button_RT() { return _fresh.RightTrigger; }



        //private:

        //    XINPUT_STATE _fresh;     //!< xインプットの状態
        //    int _trg[16];            //!< トリガ
        //};

        /////
        ///// @class   KeyBoardState
        ///// @brief   キーボード状態クラスの宣言
        /////          キー入力を得る場合はメンバーを追加する
        ///// 
        //class KeyBoardState
        //{
        //public:

        //    ///
        //    /// 更新
        //    ///
        //    void Update();

        //    /*
        //    *@brief  Wキー
        //    *@return Wキー
        //    */
        //    int Button_W() { return CheckHitKey(KEY_INPUT_W); }

        //    /*
        //    *@brief  Sキー
        //    *@return Sキー
        //    */
        //    int Button_S() { return CheckHitKey(KEY_INPUT_S); }

        //    /*
        //    *@brief  Aキー
        //    *@return Aキー
        //    */
        //    int Button_A() { return CheckHitKey(KEY_INPUT_A); }

        //    /*
        //    *@brief  Dキー
        //    *@return Dキー
        //    */
        //    int Button_D() { return CheckHitKey(KEY_INPUT_D); }

        //    /*
        //    *@brief  Cキー
        //    *@return Cキー
        //    */
        //    int Button_C() { return _trg[0]; }

        //    /*
        //    *@brief  Eキー
        //    *@return Eキー
        //    */
        //    int Button_E() { return _trg[1]; }

        //    /*
        //    *@brief  Qキー
        //    *@return Qキー
        //    */
        //    int Button_Q() { return _trg[2]; }

        //    /*
        //    *@brief  スペースキー
        //    *@return スペースキー
        //    */
        //    int Button_Space() { return  _trg[3]; }

        //    /*
        //    *@brief  Enterキー
        //    *@return Enterキー
        //    */
        //    int Button_Enter() { return _trg[4]; }

        //private:
        //    int _fresh[5]{ 0 };        //!< キーの状態
        //    int _trg[5]{ 0 };          //!< トリガの状態
        //};


        ///
        /// @class   InputComponent
        /// @brief   入力コンポーネントクラスの宣言
        ///
        class InputComponent {
        public:
            ///
            /// 更新.
            ///
            void Update();
            ///
            /// マウス状態の取得.
            /// @return マウスの状態
            ///
            MouseState& GetMouse() { return _mouseState; }
            ///
            /// ジョイパッド状態の取得.
            /// @return ジョイパッドの状態
            ///
            JoypadState& GetJoypad() { return _joypadState; }
            ///
            /// キーボード状態の取得
            /// @return キーボードの状態
            KeyBoardState& GetKeyBoard() { return _keyboardState; }

        private:
           MouseState    _mouseState;      //!< マウスインスタンスの宣言
           JoypadState   _joypadState;     //!< ジョイパッドインスタンスの宣言
           KeyBoardState _keyboardState;   //!< キーボードインスタンスの宣言
        };
    
    }

}


