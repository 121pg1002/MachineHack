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
      /// @class   KeyBoardState
      /// @brief   �L�[�{�[�h��ԃN���X�̐錾
      ///          �L�[���͂𓾂�ꍇ�̓����o�[��ǉ�����
      /// 
    class KeyBoardState
    {
    public:

      ///
      /// �X�V
      ///
      void Update();

      /*
      *@brief  W�L�[
      *@return W�L�[
      */
      int Button_W() { return CheckHitKey(KEY_INPUT_W); }

      /*
      *@brief  S�L�[
      *@return S�L�[
      */
      int Button_S() { return CheckHitKey(KEY_INPUT_S); }

      /*
      *@brief  A�L�[
      *@return A�L�[
      */
      int Button_A() { return CheckHitKey(KEY_INPUT_A); }

      /*
      *@brief  D�L�[
      *@return D�L�[
      */
      int Button_D() { return CheckHitKey(KEY_INPUT_D); }

      /*
      *@brief  C�L�[
      *@return C�L�[
      */
      int Button_C() { return _trg[0]; }

      /*
      *@brief  E�L�[
      *@return E�L�[
      */
      int Button_E() { return _trg[1]; }

      /*
      *@brief  Q�L�[
      *@return Q�L�[
      */
      int Button_Q() { return _trg[2]; }

      /*
      *@brief  �X�y�[�X�L�[
      *@return �X�y�[�X�L�[
      */
      int Button_Space() { return  _trg[3]; }

      /*
      *@brief  Enter�L�[
      *@return Enter�L�[
      */
      int Button_Enter() { return _trg[4]; }

    private:
      int _fresh[5]{ 0 };        //!< �L�[�̏��
      int _trg[5]{ 0 };          //!< �g���K�̏��
    };
  }
}
