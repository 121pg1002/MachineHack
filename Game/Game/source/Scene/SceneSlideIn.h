/*****************************************************************//**
 * @file   SceneSlideIn.h
 * @brief  �X���C�h�C���N���X
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace MachineHuck::Scene {

	//�X���C�h�C���N���X
	class SceneSlideIn : public AppFrame::Scene::Scene {
	public:
        /// @brief �R���X�g���N�^
        /// @param game �Q�[���N���X�Q��
        SceneSlideIn(AppFrame::Game& game);

        virtual ~SceneSlideIn() = default;

        //����
        void Enter() override;

        /// ������
        void Init() override;

        /// �X�V
        void Update() override;
        /// �`��
        void Render() override;

        //int GetYSlideIn() { return _ySlideIn; }
    private:
        int _cgXSlideIn{ 0 };  //!< x�̉摜�n���h��
        int _cgYSlideIn{ 0 };  //!< ���̉摜�n���h��
        int _xSlideIn{ 1920 }; //!< x�����̈ړ���
        int _ySlideIn{ 0 };    //!< y�����̈ړ���


	};

}
