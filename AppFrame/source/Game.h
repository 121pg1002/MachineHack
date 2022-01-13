///
/// @file    Game.h
/// @brief   �Q�[���N���X�̐錾
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>
class ActorFactory;
class ActorServer;
class AssetServer;
class SceneServer;
class InputComponent;
class SoundComponent;

/// @class   Game
/// @brief   �Q�[���S�̂̃t���[�����[�N
class Game {
public:
  ///�Q�[���̏��
	enum class State {
		Play,    ///< ���s��
		Paused,  ///< �ꎞ��~
		Quit     ///< �I��
	};
  Game();
  virtual ~Game();
  /// ������
  /// DxLib�̏��������s��
  /// @return ������(true:����, false:���s).
  virtual bool Initialize();
  /// ���s
  /// ���C�����[�v�����s����
	virtual void Run();
  /// ��~
  /// DxLib���I������
	virtual void Shutdown();
  /// ����
  /// ���C�����[�v���Ŏ��s����
	virtual void Input();
  /// �X�V
  /// ���C�����[�v���Ŏ��s����
	virtual void Update();
  /// �`��
  /// ���C�����[�v���Ŏ��s����
  virtual void Render();
  /// �A�Z�b�g�T�[�o�[�̎擾
  /// @return �A�Z�b�g�T�[�o�[�̎Q��
  /*Asset::*/AssetServer& GetAssetServer() const { return *_assetServer; }
  /// �V�[���T�[�o�[�̎擾
  /// @return �V�[���T�[�o�[�̎Q��
  SceneServer& GetSceneServer() const { return *_sceneServer; }
  /// �A�N�^�[�T�[�o�[�̎擾
  /// @return �A�N�^�[�T�[�o�[�̎Q��
  ActorServer& GetActorServer() const { return *_actorServer; };
  /// �A�N�^�[�T�[�o�[�̎擾
  /// @return �A�N�^�[�T�[�o�[�̎Q��
  ActorFactory& GetActorFactory() const { return *_actorFactory; };
  /// �T�E���h�R���|�[�l���g�̎擾
  /// @return �T�E���h�R���|�[�l���g�̎Q��
  SoundComponent& GetSoundComponent() const { return *_sound; };


private:
  /// ���
	State _state{State::Play};

  std::unique_ptr<ActorServer> _actorServer;

  /// �A�N�^�[�t�@�N�g���̃��j�[�N�|�C���^
  std::unique_ptr<ActorFactory> _actorFactory;

  /// �A�Z�b�g�T�[�o�[�̃��j�[�N�|�C���^
  std::unique_ptr</*Asset::*/AssetServer> _assetServer;
  /// �V�[���T�[�o�[�̃��j�[�N�|�C���^
  std::unique_ptr<SceneServer> _sceneServer;
  /// �C���v�b�g�R���|�[�l���g�̃��j�[�N�|�C���^
  std::unique_ptr<InputComponent> _input;
  /// �T�E���h�R���|�[�l���g�̃��j�[�N�|�C���^
  std::unique_ptr<SoundComponent> _sound;
};
