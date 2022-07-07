/*****************************************************************//**
 * @file   SceneEpilogue.h
 * @brief  �G�s���[�O���
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#pragma once
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}

namespace MachineHuck::Scene {
	/// @class   SceneTitle
/// @brief   �^�C�g����ʃN���X�̐錾
	class SceneEpilogue : public AppFrame::Scene::Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneEpilogue(AppFrame::Game& game);
		/// �f�X�g���N�^
		~SceneEpilogue() = default;
		/// ������
		void Init() override;
		/// 
        /// �o������
        /// 
        void Exit() override;
		/// ����
		virtual void Enter() override;
		/// ����
		void Input(AppFrame::Input::InputComponent& input) override;
		///�X�V
		void Update() override;
		/// �`��
		void Render() override;
	private:
		int _gameEpilogueHandle{ -1 };  ///< �Q�[���^�C�g���摜
		int _leftClickToStart{ -1 }; ///< Left click to Start�摜
		int _epilogueBgHandle{ -1 };    ///< �w�i�摜
		int _alpha{ 0 };
	};
}


