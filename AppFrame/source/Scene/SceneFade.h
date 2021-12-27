///
/// @file    SceneFade.h
/// @brief   �V�[���̃t�F�[�h�N���X
///          ��ʂ̍őO�ʂɃt���X�N���[���T�C�Y�̉摜���d�˂ăA���t�@�l�ɂ��t�F�[�h���s��
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "Scene.h"

  /// @class   SceneFade
  /// @brief   �V�[���t�F�[�h�N���X�̐錾
  class SceneFade : public Scene {
  public:
    /// �R���X�g���N�^
    /// @param[in] game �Q�[���N���X�̎Q��
    /// @param[in] state 
    SceneFade(Game& game);
    /// �f�X�g���N�^
    virtual ~SceneFade();
    /// ������
    virtual void Init() override;
    /// ����
    virtual void Enter() override;
    /// �X�V
    virtual void Update() override;
    /// �`��
    virtual void Render() override;
  protected:
    int _width{ 1920 };
    int _height{ 1080 };
    unsigned int _color{ 0 };
    float _alpha{ 0 };
    float _deltaAlpha{ 0 };
  };

  class SceneFadeIn : public SceneFade {
  public:
    SceneFadeIn(Game& game);
    ~SceneFadeIn();
    void Enter() override;
    void Update() override;
  };

  class SceneFadeOut : public SceneFade {
  public:
    SceneFadeOut(Game& game);
    ~SceneFadeOut();
    void Enter() override;
    void Update() override;
  };
