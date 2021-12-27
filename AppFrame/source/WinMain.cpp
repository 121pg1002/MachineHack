//!
//! @file WinMain.cpp
//!
//! @brief �G���g���[�|�C���g
//!
#include "Game.h"
#include <windows.h>
#include <memory>

// Windows�A�v���P�[�V������WinMain�֐�����n�܂�
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

  // Game�N���X�̃C���X�^���X�𐶐����ă��j�[�N�|�C���^������������
  auto game = std::make_unique<Game>();
  auto success = game->Initialize();


  if (success) {
    // �Q�[�������s���遦�������ɐ���
    game->Run();
  }

  // �Q�[�����~�I������
  game->Shutdown();
  return 0;
}
