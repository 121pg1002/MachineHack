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

			/**
			 * @brief �J�����̈ʒu�ƃ^�[�Q�b�g�ݒ�       
			 * @param pos �t���A�ʒu
			 */
			void FloorPos(Math::Vector4 pos);

			/// �`��
			void Draw(bool isHit);
			/// �J�������W(�n�_)�̐ݒ�
			/// @param[in] position
			void SetPosition(Math::Vector4 position) { _position = position; }

			/**
			 * @brief  �J�����ʒu�̍X�V         
			 * @param  position
			 */
			void SetRefleshPosition(Math::Vector4 position);

			/// �ڕW���W(�����_)�̐ݒ�
			/// @param[in] target
			void SetTarget(Math::Vector4 target, Math::Vector4 forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }


			/**
			 * @brief  �J�����ڕW�̍X�V         
			 * @param  position
			 */
			void SetRefleshTarget(Math::Vector4 position);


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
			Math::Vector4 _positionInitDif{ 0, 1200, -1000 }; //!< �����J�����ʒu�̍������W
			//Math::Vector4 _positionInitDif{ 0, 2000, -200 }; //!< �����J�����ʒu�̍������W
			Math::Vector4 _targetInitDif{ 0, 100, 0 };       //!< �����J�����ڕW�̍������W
		};
	}

}



