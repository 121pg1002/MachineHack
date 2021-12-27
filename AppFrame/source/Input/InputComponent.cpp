///
/// @file    InputComponent.cpp
/// @brief   入力コンポーネント
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "InputComponent.h"

///
/// 更新.
///
void MouseState::Update() {
  // マウスのボタン状態更新
  auto old = _fresh;
  _fresh = GetMouseInput();
  _trg = _fresh ^ old & _fresh;

  // マウス座標の取得
  int mx, my;
  GetMousePoint(&mx, &my);
  VECTOR newPos = { static_cast<float>(mx), static_cast<float>(my), 0 };

  // マウスの変化量＝今回の位置－前回の位置分
  _delta = { VSub(newPos, _position) };

  // マウス座標の更新
  _position = newPos;
}
///
/// 更新.
///
void JoypadState::Update() {

  //前フレームのパッド状態を保存
  XINPUT_STATE _old = _fresh;

  // ジョイパッド状態更新
  GetJoypadXInputState(DX_INPUT_PAD1, &_fresh);
  auto buttons_size = sizeof(_fresh.Buttons) / sizeof(_fresh.Buttons[0]);
  for (int i = 0; i < buttons_size; i++)
  {
      _trg[i] = _fresh.Buttons[i] ^ _old.Buttons[i] & _fresh.Buttons[i];
  }


}

void KeyBoardState::Update() {

    int _oldkey[5]{0};
    for (int i = 0; i < 5; i++) 
    {
        _oldkey[i] = _fresh[i];
    }

    if (CheckHitKey(KEY_INPUT_C)) 
    {
        _fresh[0] = CheckHitKey(KEY_INPUT_C);
    }
    else if (CheckHitKey(KEY_INPUT_E)) 
    {
        _fresh[1] = CheckHitKey(KEY_INPUT_E);
    }
    else if (CheckHitKey(KEY_INPUT_Q))
    {
        _fresh[2] = CheckHitKey(KEY_INPUT_Q);
    }
    else if (CheckHitKey(KEY_INPUT_SPACE))
    {
        _fresh[3] = CheckHitKey(KEY_INPUT_SPACE);
    }
    else if (CheckHitKey(KEY_INPUT_RETURN)) 
    {
        _fresh[4] = CheckHitKey(KEY_INPUT_RETURN);
    }
    else 
    {
        for (int i = 0; i < 5; i++)
        {
            _fresh[i] = 0;
        }
    }

    for (int i = 0; i < 5; i++) 
    {
        _trg[i] = (_oldkey[i] ^ _fresh[i]) & _fresh[i];
    }


}
///
/// 更新.
///
void InputComponent::Update() {
  _mouseState.Update();
  _joypadState.Update();
  _keyboardState.Update();
}