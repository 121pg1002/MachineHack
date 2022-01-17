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

namespace MachineHuck::Actor {
	class ActorServer;
	class ActorFactory;
}

namespace AppFrame {
	class Game;
	namespace Input {
		class InputComponent;
	}

	namespace Asset{
		class AssetServer;
	}

	namespace Scene {
		class SceneServer;
	}
	namespace Sound {
		class SoundComponent;
	}
}

namespace AppFrame::Scene {
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
		virtual void Input(Input::InputComponent& input) {};
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
		MachineHuck::Actor::ActorServer& GetActorServer();
		/// �A�N�^�[�t�@�N�g���[�̎擾
		/// @return �A�N�^�[�t�@�N�g���[�̎Q��
		MachineHuck::Actor::ActorFactory& GetActorFactory();
		/// �A�Z�b�g�T�[�o�[�̎擾
		/// @return �A�Z�b�g�T�[�o�[�̎Q��
		Asset::AssetServer& GetAssetServer();
		/// �V�[���T�[�o�[�̎擾
		/// @return �V�[���T�[�o�[�̎Q��
		SceneServer& GetSceneServer();
		/// �T�E���h�R���|�[�l���g�̎擾
		/// @return �T�E���h�R���|�[�l���g�̎Q��
		Sound::SoundComponent& GetSoundComponent();
	private:
		/// �Q�[���N���X�̎Q��
		Game& _game;
	};
}


