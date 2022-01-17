/*****************************************************************//**
 * @file   CameraComponent.h
 * @brief  �J�����R���|�[�l���g
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/
#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>
#include "AppFrame.h"

namespace AppFrame::Input {
	class InputComponent;
}

namespace Math = AppFrame::Math;

//�Q�[����
namespace MachineHuck {

	//�t�H���_��
	namespace Camera{
	
		///
/// @class   CameraComponent
/// @brief   �J�����R���|�[�l���g�N���X�̐錾
///          ���΃}�E�X�R���g���[���ɂ��J��������
///
		class CameraComponent {
		public:
			/// �R���X�g���N�^
			CameraComponent();
			/// ������
			void Init();
			/// ���͏���
			void Input(AppFrame::Input::InputComponent& input);
			/// �X�V
			void Update(Math::Vector4 move);
			/// �`��
			void Draw(bool isHit);
			/// �J�������W(�n�_)�̐ݒ�
			/// @param[in] position
			void SetPosition(Math::Vector4 position) { _position = position; }
			/// �ڕW���W(�����_)�̐ݒ�
			/// @param[in] target
			void SetTarget(Math::Vector4 target, Math::Vector4 forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
			/// �����_�����̃x�N�g�����擾
			/// @return �����_�����̒P�ʃx�N�g��
			/*VECTOR GetForward() const { return VNorm(ToDX(_target -_position)); }*/
		  //MATRIX GetCameraViewMatrix(VECTOR& cameraPosition, VECTOR& cameraTarget, VECTOR& cameraUp);

		protected:
			Math::Vector4 _position{ 0, 5.0f, 0 };
			Math::Vector4 _target{ 0, 0, 0 };
			Math::Vector4 _forwardOfTarget{ 0, 0, 0 };
			float targetDist{ 500 };
			float vertDist{ 100 };
		};
	}

}



