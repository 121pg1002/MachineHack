///
/// @file    Game.h
/// @brief   �Q�[���N���X�̐錾
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <memory>

namespace AppFrame {

	namespace Asset {
		class AssetServer;
	}

	namespace Scene {
		class SceneServer;
	}

	namespace Input {
		class InputComponent;
	}

	namespace Sound {
		class SoundComponent;
	}

}

namespace MachineHuck::Actor {
	class ActorFactory;
	class ActorServer;
}

namespace MachineHuck::UI {
	class UIComponent;
	class SpriteServer;
}

namespace MachineHuck::Stage {
	class StageParameter;
}

namespace AppFrame {
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
		virtual void Input(Input::InputComponent& input);
		/// �X�V
		/// ���C�����[�v���Ŏ��s����
		virtual void Update();
		/// �`��
		/// ���C�����[�v���Ŏ��s����
		virtual void Render();
		/// �A�Z�b�g�T�[�o�[�̎擾
		/// @return �A�Z�b�g�T�[�o�[�̎Q��
		Asset::AssetServer& GetAssetServer() const { return *_assetServer; }
		/// �V�[���T�[�o�[�̎擾
		/// @return �V�[���T�[�o�[�̎Q��
		Scene::SceneServer& GetSceneServer() const { return *_sceneServer; }
		/// �A�N�^�[�T�[�o�[�̎擾
		/// @return �A�N�^�[�T�[�o�[�̎Q��
		MachineHuck::Actor::ActorServer& GetActorServer() const { return *_actorServer; };
		/// �A�N�^�[�T�[�o�[�̎擾
		/// @return �A�N�^�[�T�[�o�[�̎Q��
		MachineHuck::Actor::ActorFactory& GetActorFactory() const { return *_actorFactory; };
		/// �T�E���h�R���|�[�l���g�̎擾
		/// @return �T�E���h�R���|�[�l���g�̎Q��
		Sound::SoundComponent& GetSoundComponent() const { return *_sound; };
		/// �X�v���C�g�T�[�o�[�̎擾
        /// @return �X�v���C�g�T�[�o�[�̎Q��
		MachineHuck::UI::SpriteServer& spriteServer() const { return *_spriteServer; }
		/// UI�R���|�[�l���g�̎擾
        /// @return UI�R���|�[�l���g�̎Q��
		MachineHuck::UI::UIComponent& GetUiComponent() const { return *_ui; }

		/**
		 * @brief �X�e�[�W�p�����[�^�[�̎擾
		 * @return �X�e�[�W�p�����[�^�[�̎Q��
		 */
		MachineHuck::Stage::StageParameter& GetStageParameter() const { return *_stageParam; };


	private:
		/// ���
		State _state{ State::Play };

		std::unique_ptr<MachineHuck::Actor::ActorServer> _actorServer;

		/// �A�N�^�[�t�@�N�g���̃��j�[�N�|�C���^
		std::unique_ptr<MachineHuck::Actor::ActorFactory> _actorFactory;

		/// �A�Z�b�g�T�[�o�[�̃��j�[�N�|�C���^
		std::unique_ptr<Asset::AssetServer> _assetServer;
		/// �V�[���T�[�o�[�̃��j�[�N�|�C���^
		std::unique_ptr<Scene::SceneServer> _sceneServer;
		/// �C���v�b�g�R���|�[�l���g�̃��j�[�N�|�C���^
		std::unique_ptr<Input::InputComponent> _input;
		/// �T�E���h�R���|�[�l���g�̃��j�[�N�|�C���^
		std::unique_ptr<Sound::SoundComponent> _sound;
		/// �X�v���C�g�T�[�o�[�̎擾
		/// �X�v���C�g�T�[�o�[�̃��j�[�N�|�C���^
		std::unique_ptr<MachineHuck::UI::SpriteServer> _spriteServer;
		/// UI�R���|�[�l���g�̃��j�[�N�|�C���^
		std::unique_ptr<MachineHuck::UI::UIComponent> _ui;
		std::unique_ptr<MachineHuck::Stage::StageParameter> _stageParam;//!< 

	};
}


