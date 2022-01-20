#pragma once
///
/// @file    SceneItem.h
/// @brief   �A�C�e�����
/// @date    2021/01/19
/// @author tagawa kyoga
/// @copyright (C) Amusement Media Academy All rights Resved.

#include <AppFrame.h>


namespace MachineHuck::Scene {
    class SceneItem : public AppFrame::Scene::Scene {
	public:
		/// �R���X�g���N�^
		/// @param[in] game Game�N���X�̎Q��
		SceneItem(AppFrame::Game& game);
		/// �f�X�g���N�^
		~SceneItem() = default;
		/// ������
		void Init() override;
		/// ����
		virtual void Enter() override;
		/// ����
		void Input(AppFrame::Input::InputComponent & input) override;
		/// �X�V
		void Update() override;
		/// �`��
		void Render() override;

	private:
		int ItemHandle{ -1 };//�A�C�e����ʉ摜
		int _alpha{ 0 };

    };

	




}