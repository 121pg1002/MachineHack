///
/// @file    SceneInGame.h
/// @brief   �C���Q�[�����
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"
#include <memory>

class CameraComponent;
namespace SceneInGame {
  /// @class   SceneInGame
  /// @brief   �C���Q�[����ʃN���X�̐錾
  class SceneInGame : public Scene {
  public:
    /// �R���X�g���N�^
    /// @param[in] game Game�N���X�̎Q��
    SceneInGame(Game& game);
    /// �f�X�g���N�^
    ~SceneInGame() = default;
    /// ������
    void Init() override;
    /// ����
    void Enter() override;
    /// ����
    /// @param[in] input �C���v�b�g�R���|�[�l���g
    void Input(InputComponent& input) override;
    /// �X�V
    void Update() override;
    /// �`��
    void Render() override;
    /// �o��
    void Exit() override;
  private:
  };
}

