/*****************************************************************//**
 * @file   InputComponent.h
 * @brief  ���̓R���|�[�l���g
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
///// @brief   �}�E�X��ԃN���X�̐錾
/////
//        class MouseState {
//        public:
//            ///
//            /// �X�V.
//            ///
//            void Update();
//            bool LeftClick() { return _trg & MOUSE_INPUT_LEFT; }    ///< ���N���b�N����
//            bool RightClick() { return _trg & MOUSE_INPUT_RIGHT; }  ///< �E�N���b�N����
//            bool LeftPress() { return _fresh & MOUSE_INPUT_LEFT; }  ///< ���{�^����������
//            bool RightPress() { return _fresh & MOUSE_INPUT_RIGHT; }///< �E�{�^����������
//            VECTOR GetPosition() { return _position; }  ///< ���W
//            VECTOR GetDelta() { return _delta; }        ///< ���W�̕ω���
//        private:
//            int _fresh = 0;
//            int _trg = 0;
//            VECTOR _position{ 0,0,0 };
//            VECTOR _delta{ 0,0,0 };
//        };
        /////
        ///// @class   JoypadState
        ///// @brief   �W���C�p�b�h��ԃN���X�̐錾
        /////          �p�b�h���͂𓾂�ꍇ�̓����o�[��ǉ�����
        /////
        //class JoypadState {
        //public:
        //    void Update();
        //    /*
        //    *@brief  �߂�{�^��
        //    *@return Back�{�^��
        //    */
        //    bool Exit() { return _trg[5]; }


        //    /*
        //    *@brief  �X�^�[�g�{�^��
        //    *@return Start�{�^��
        //    */
        //    bool Start() { return _trg[4]; }


        //    /*
        //    *@brief  �O��
        //    *@return ���X�e�B�b�N & �㉺
        //    */
        //    double LVertical() { return _fresh.ThumbLY; }


        //    /*
        //    *@brief  ���E
        //    *@return ���X�e�B�b�N & ���E
        //    */
        //    double LHorison() { return _fresh.ThumbLX; }


        //    /*
        //    *@brief  �O��
        //    *@return �E�X�e�B�b�N & �㉺
        //    */
        //    double RVertical() { return _fresh.ThumbRY; }

        //    /*
        //    *@brief  ���E
        //    *@return �E�X�e�B�b�N & ���E
        //    */
        //    double RHorison() { return _fresh.ThumbRX; }

        //    /*
        //    *@brief  A�{�^��
        //    *@return �g���K & A�{�^��
        //    */
        //    bool Button_A() { return _trg[12]; }

        //    /*
        //    *@brief  B�{�^��
        //    *@return �g���K & B�{�^��
        //    */
        //    bool Button_B() { return _trg[13]; }

        //    /*
        //    *@brief  X�{�^��
        //    *@return �g���K & X�{�^��
        //    */
        //    bool Button_X() { return _trg[14]; }


        //    /*
        //    *@brief  Y�{�^��
        //    *@return �g���K & Y�{�^��
        //    */
        //    bool Button_Y() { return _trg[15]; }

        //    /*
        //    *@brief  LB�{�^��
        //    *@return �g���K & LB�{�^��
        //    */
        //    bool Button_LB() { return _trg[9]; }

        //    /*
        //    *@brief  RB�{�^��
        //    *@return �g���K & RB�{�^��
        //    */
        //    bool Button_RB() { return _trg[8]; }


        //    /*
        //    *@brief  LT�{�^��
        //    *@return LT�{�^��
        //    */
        //    bool Button_LT() { return _fresh.LeftTrigger; }

        //    /*
        //    *@brief  RT�{�^��
        //    *@return RT�{�^��
        //    */
        //    bool Button_RT() { return _fresh.RightTrigger; }



        //private:

        //    XINPUT_STATE _fresh;     //!< x�C���v�b�g�̏��
        //    int _trg[16];            //!< �g���K
        //};

        /////
        ///// @class   KeyBoardState
        ///// @brief   �L�[�{�[�h��ԃN���X�̐錾
        /////          �L�[���͂𓾂�ꍇ�̓����o�[��ǉ�����
        ///// 
        //class KeyBoardState
        //{
        //public:

        //    ///
        //    /// �X�V
        //    ///
        //    void Update();

        //    /*
        //    *@brief  W�L�[
        //    *@return W�L�[
        //    */
        //    int Button_W() { return CheckHitKey(KEY_INPUT_W); }

        //    /*
        //    *@brief  S�L�[
        //    *@return S�L�[
        //    */
        //    int Button_S() { return CheckHitKey(KEY_INPUT_S); }

        //    /*
        //    *@brief  A�L�[
        //    *@return A�L�[
        //    */
        //    int Button_A() { return CheckHitKey(KEY_INPUT_A); }

        //    /*
        //    *@brief  D�L�[
        //    *@return D�L�[
        //    */
        //    int Button_D() { return CheckHitKey(KEY_INPUT_D); }

        //    /*
        //    *@brief  C�L�[
        //    *@return C�L�[
        //    */
        //    int Button_C() { return _trg[0]; }

        //    /*
        //    *@brief  E�L�[
        //    *@return E�L�[
        //    */
        //    int Button_E() { return _trg[1]; }

        //    /*
        //    *@brief  Q�L�[
        //    *@return Q�L�[
        //    */
        //    int Button_Q() { return _trg[2]; }

        //    /*
        //    *@brief  �X�y�[�X�L�[
        //    *@return �X�y�[�X�L�[
        //    */
        //    int Button_Space() { return  _trg[3]; }

        //    /*
        //    *@brief  Enter�L�[
        //    *@return Enter�L�[
        //    */
        //    int Button_Enter() { return _trg[4]; }

        //private:
        //    int _fresh[5]{ 0 };        //!< �L�[�̏��
        //    int _trg[5]{ 0 };          //!< �g���K�̏��
        //};


        ///
        /// @class   InputComponent
        /// @brief   ���̓R���|�[�l���g�N���X�̐錾
        ///
        class InputComponent {
        public:
            ///
            /// �X�V.
            ///
            void Update();
            ///
            /// �}�E�X��Ԃ̎擾.
            /// @return �}�E�X�̏��
            ///
            MouseState& GetMouse() { return _mouseState; }
            ///
            /// �W���C�p�b�h��Ԃ̎擾.
            /// @return �W���C�p�b�h�̏��
            ///
            JoypadState& GetJoypad() { return _joypadState; }
            ///
            /// �L�[�{�[�h��Ԃ̎擾
            /// @return �L�[�{�[�h�̏��
            KeyBoardState& GetKeyBoard() { return _keyboardState; }

        private:
           MouseState    _mouseState;      //!< �}�E�X�C���X�^���X�̐錾
           JoypadState   _joypadState;     //!< �W���C�p�b�h�C���X�^���X�̐錾
           KeyBoardState _keyboardState;   //!< �L�[�{�[�h�C���X�^���X�̐錾
        };
    
    }

}


