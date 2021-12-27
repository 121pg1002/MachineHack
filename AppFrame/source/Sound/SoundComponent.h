///
/// @file    SoundComponent.h
/// @brief   音入力コンポーネント
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once

#include <string>

class Game;

class SoundComponent {
public:
  SoundComponent(Game& game): _game{game} {};
  virtual ~SoundComponent();

  void Play(std::string_view key);
  void PlayLoop(std::string_view key);

  void SetVolume(std::string_view key, int volume);
  void SetMute(bool isMute) { _isMute = isMute; }
protected:
  void Play(std::string_view key, int playType);

private:
  Game& _game;
  bool _isMute{ false };
};

