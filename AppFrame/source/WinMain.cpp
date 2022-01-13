//!
//! @file WinMain.cpp
//!
//! @brief エントリーポイント
//!
#include "Game.h"
#include <windows.h>
#include <memory>

// WindowsアプリケーションはWinMain関数から始まる
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

  // Gameクラスのインスタンスを生成してユニークポインタを初期化する
  auto game = std::make_unique<Game>();
  auto success = game->Initialize();


  if (success) {
    // ゲームを実行する※初期化に成功
    game->Run();
  }

  // ゲームを停止終了する
  game->Shutdown();
  return 0;
}
