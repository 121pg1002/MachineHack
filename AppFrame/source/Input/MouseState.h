

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
    /// @class   MousState
    /// @brief   �}�E�X��ԃN���X�̐錾
    ///
    class MouseState {
    public:
      ///
      /// �X�V.
      ///
      void Update();
      bool LeftClick() { return _trg & MOUSE_INPUT_LEFT; }    ///< ���N���b�N����
      bool RightClick() { return _trg & MOUSE_INPUT_RIGHT; }  ///< �E�N���b�N����
      bool LeftPress() { return _fresh & MOUSE_INPUT_LEFT; }  ///< ���{�^����������
      bool RightPress() { return _fresh & MOUSE_INPUT_RIGHT; }///< �E�{�^����������
      VECTOR GetPosition() { return _position; }  ///< ���W
      VECTOR GetDelta() { return _delta; }        ///< ���W�̕ω���
    private:
      int _fresh = 0;
      int _trg = 0;
      VECTOR _position{ 0,0,0 };
      VECTOR _delta{ 0,0,0 };
    };
  }
}