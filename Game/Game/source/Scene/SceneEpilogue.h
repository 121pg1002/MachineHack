///
/// @file    SceneEpilogue.h
/// @brief   �^�C�g�����
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
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


