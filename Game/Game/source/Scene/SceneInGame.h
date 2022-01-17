/*****************************************************************//**
 * @file   SceneInGame.h
 * @brief  �C���Q�[�����
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include <memory>

class CameraComponent;
//class UIInGame;
namespace MachineHuck::Scene {
	/// @class   SceneInGame
	/// @brief   �C���Q�[����ʃN���X�̐錾
	class SceneInGame : public AppFrame::Scene::Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneInGame(AppFrame::Game& game);
		/// �f�X�g���N�^
		~SceneInGame() = default;
		/// ������
		void Init() override;
		/// ����
		void Enter() override;
		/// ����
		/// @param[in] input �C���v�b�g�R���|�[�l���g
		void Input(AppFrame::Input::InputComponent& input) override;
		/// �X�V
		void Update() override;
		/// �`��
		void Render() override;
		/// �o��
		void Exit() override;
	private:
	};
}

