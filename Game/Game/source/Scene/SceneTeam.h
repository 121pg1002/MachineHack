/*****************************************************************//**
 * @file   SceneTeam.h
 * @brief  �`�[�����S���
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}
namespace MachineHuck::Effect {
	class EffectLaser;
}
namespace MachineHuck::Scene {
	/// @class   SceneTitle
/// @brief   �^�C�g����ʃN���X�̐錾
	class SceneTeam : public AppFrame::Scene::Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneTeam(AppFrame::Game& game);
		/// �f�X�g���N�^
		~SceneTeam() = default;
		/// ������
		void Init() override;
		/// ����
		virtual void Enter() override;
		/// ����
		void Input(AppFrame::Input::InputComponent& input) override;
		///�X�V
		void Update() override;
		/// �`��
		void Render() override;
	private:
		int _gameTitleHandle{ -1 };  ///< �Q�[���^�C�g���摜
		int _leftClickToStart{ -1 }; ///< Left click to Start�摜
		int _teamBgHandle{ -1 };    ///< �w�i�摜
		int _alpha{ 0 };
		std::unique_ptr<MachineHuck::Effect::EffectLaser> laser;
	};
}


