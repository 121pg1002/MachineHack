///
/// @file    Scene.h
/// @brief   �V�[���̊��N���X
///          �e�V�[���͂��̃N���X���p������
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
class Game;
class InputComponent;
class ActorServer;
class ActorFactory;
class AssetServer;
class SceneServer;
class SoundComponent;

  /// @class   Scene
  /// @brief   �V�[���̃t���[�����[�N
  class Scene {
  public:
    /// �R���X�g���N�^
    /// @param[in] game �Q�[���N���X�̎Q��
    Scene(Game& game);
    /// �f�X�g���N�^
    virtual ~Scene();
    /// ������
    /// SceneServer::Register�o�^���Ɏ��s����
    virtual void Init() = 0;
    /// ��������
    /// SceneServer::PushBack���Ɏ��s����
    virtual void Enter() {};
    /// ���͏���
    /// SceneServer::Input������s����
    virtual void Input(InputComponent& input) {};
    /// �X�V����
    /// SceneServer::Update������s����
    virtual void Update() {};
    /// �`�揈��
    /// SceneServer::Render������s����
    virtual void Render() {};
    /// �o������
    /// SceneServer::PopBack������s����
    virtual void Exit() {};
    /// �Q�[���̎擾
    /// @return �Q�[���N���X�̎Q��
    Game& GetGame() const { return _game; };
    /// �A�N�^�[�T�[�o�[�̎擾
    /// @return �A�N�^�[�T�[�o�[�̎Q��
    ActorServer& GetActorServer();
    /// �A�N�^�[�t�@�N�g���[�̎擾
    /// @return �A�N�^�[�t�@�N�g���[�̎Q��
    ActorFactory& GetActorFactory();
    /// �A�Z�b�g�T�[�o�[�̎擾
    /// @return �A�Z�b�g�T�[�o�[�̎Q��
    AssetServer& GetAssetServer();
    /// �V�[���T�[�o�[�̎擾
    /// @return �V�[���T�[�o�[�̎Q��
    SceneServer& GetSceneServer();
    /// �T�E���h�R���|�[�l���g�̎擾
    /// @return �T�E���h�R���|�[�l���g�̎Q��
    SoundComponent& GetSoundComponent();
  private:
    /// �Q�[���N���X�̎Q��
    Game& _game;
  };


