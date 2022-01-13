///
/// @file    SceneTitle.h
/// @brief   �^�C�g�����
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"

class InputComponent;
namespace SceneAMG {
	/// @class   SceneTitle
	/// @brief   �^�C�g����ʃN���X�̐錾
	class SceneAMG : public Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneAMG(Game& game);
		/// �f�X�g���N�^
		~SceneAMG() = default;
		/// ������
		void Init() override;
		/// ����
		virtual void Enter() override;
		/// ����
		void Input(InputComponent& input) override;
		/// �X�V
		void Update() override;
		/// �`��
		void Render() override;
	private:
		int _gameTitleHandle{ -1 };  ///< �Q�[���^�C�g���摜
		int _leftClickToStart{ -1 }; ///< Left click to Start�摜
		int _amgBgHandle{ -1 };    ///< �w�i�摜
		int _alpha{ 0 };
	};
}
