/*****************************************************************//**
 * @file   SceneSlideOut.h
 * @brief  �X���C�h�A�E�g�N���X
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace MachineHuck::Scene {

	class SceneSlideOut :public AppFrame::Scene::Scene {
	public:
        /// @brief �R���X�g���N�^
        /// @param game �Q�[���N���X�Q��
        SceneSlideOut(AppFrame::Game& game);

        virtual ~SceneSlideOut() = default;
        /// ������
        void Init() override;

        //����
        void Enter() override;
        /// �X�V
        void Update() override;
        /// �`��
        void Render() override;



        //int GetYSlideOut() { return _ySlideOut; }
    private:
        int _cgXSlideOut{ 0 };  //!< x�̉摜�n���h��
        int _cgYSlideOut{ 0 };  //!< ���̉摜�n���h��
        int _xSlideOut{ 1920 }; //!< x�����̈ړ���
        int _ySlideOut{ 0 };    //!< y�����̈ړ���


	};

}

