///
/// @file    SceneTitle.h
/// @brief   �^�C�g�����
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"

class InputComponent;
namespace SceneTitle {
  /// @class   SceneTitle
  /// @brief   �^�C�g����ʃN���X�̐錾
  class SceneTitle : public Scene {
  public:
    /// �R���X�g���N�^
    /// @param[in] game Game�N���X�̎Q��
    SceneTitle(Game& game);
    /// �f�X�g���N�^
    ~SceneTitle() = default;
    /// ������
    void Init() override;
    /// ��������
    virtual void Enter() override;
    /// ���͏���
    void Input(InputComponent& input) override;

    void Update() override;
    /// �`�揈��
    void Render() override;
  private:
    int _gameTitleHandle{ -1 };  ///< �Q�[���^�C�g���摜
    int _leftClickToStart{ -1 }; ///< Left click to Start�摜
    int _titleBgHandle{ -1 };    ///< �w�i�摜
    int _alpha{ 0 };
  };
}

