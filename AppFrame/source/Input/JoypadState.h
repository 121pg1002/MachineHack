///
/// @file    InputComponent.h
/// @brief   ���̓R���|�[�l���g
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
   /// @brief   �W���C�p�b�h��ԃN���X�̐錾
   ///          �p�b�h���͂𓾂�ꍇ�̓����o�[��ǉ�����
   ///
    class JoypadState {
    public:
      void Update();
      /*
      *@brief  �߂�{�^��
      *@return Back�{�^��
      */
      bool Exit() { return _trg[5]; }


      /*
      *@brief  �X�^�[�g�{�^��
      *@return Start�{�^��
      */
      bool Start() { return _trg[4]; }


      /*
      *@brief  �O��
      *@return ���X�e�B�b�N & �㉺
      */
      double LVertical() { return _fresh.ThumbLY; }


      /*
      *@brief  ���E
      *@return ���X�e�B�b�N & ���E
      */
      double LHorison() { return _fresh.ThumbLX; }


      /*
      *@brief  �O��
      *@return �E�X�e�B�b�N & �㉺
      */
      double RVertical() { return _fresh.ThumbRY; }

      /*
      *@brief  ���E
      *@return �E�X�e�B�b�N & ���E
      */
      double RHorison() { return _fresh.ThumbRX; }

      /*
      *@brief  A�{�^��
      *@return �g���K & A�{�^��
      */
      bool Button_A() { return _trg[12]; }

      /*
      *@brief  B�{�^��
      *@return �g���K & B�{�^��
      */
      bool Button_B() { return _trg[13]; }

      /*
      *@brief  X�{�^��
      *@return �g���K & X�{�^��
      */
      bool Button_X() { return _trg[14]; }


      /*
      *@brief  Y�{�^��
      *@return �g���K & Y�{�^��
      */
      bool Button_Y() { return _trg[15]; }

      /*
      *@brief  LB�{�^��
      *@return �g���K & LB�{�^��
      */
      bool Button_LB() { return _trg[9]; }

      /*
      *@brief  RB�{�^��
      *@return �g���K & RB�{�^��
      */
      bool Button_RB() { return _trg[8]; }


      /*
      *@brief  LT�{�^��
      *@return LT�{�^��
      */
      bool Button_LT() { return _fresh.LeftTrigger; }

      /*
      *@brief  RT�{�^��
      *@return RT�{�^��
      */
      bool Button_RT() { return _fresh.RightTrigger; }



    private:

      XINPUT_STATE _fresh;     //!< x�C���v�b�g�̏��
      int _trg[16];            //!< �g���K
    };
  }
}
