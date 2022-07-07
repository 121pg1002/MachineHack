/*****************************************************************//**
 * @file   CameraComponent.cpp
 * @brief  �J�����R���|�[�l���g
 *
 * @author yamawaki kota
 * @date   December 19 2021
 *********************************************************************/

#include "CameraComponent.h"
#include "AppFrame.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>
#include "../Flag/FlagData.h"
//#include <numbers>

namespace MachineHuck::Camera {

	///
	/// �R���X�g���N�^.
	///
	CameraComponent::CameraComponent() {
		Init();
	}
	///
	/// ������.
	///
	void CameraComponent::Init() {
		SetCameraNearFar(50.0f, 50000.0f);
	}
	void CameraComponent::Input(AppFrame::Input::InputComponent& input) {

		//if(input.GetJoypad().)

		//_lx = 0.0, _ly = 0.0;

		//if (input.GetJoypad().LHorison() != 0.0) {
		//	_lx = input.GetJoypad().LHorison() / 1000.0;
		//}



		//if (input.GetJoypad().LVertical() != 0.0) {
		//	_ly = input.GetJoypad().LVertical() / 1000.0;
		//}

	}
	///
	/// �X�V.
	///
	void CameraComponent::Update(Math::Vector4 move) {

		//Math::Vector4 cameraMove = { 0.0, 0.0, move.GetZ() };

		// �J�����̈ʒu���v���C���[�̌���̈ʒu�ɂ���
		_position = _position + move / 4;

		//Math::Vector4 cameraMove = { 0.0, 0.0, move.GetZ() };

			_target = _target + move / 2;

		

		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));

	}


	void CameraComponent::FloorPos(Math::Vector4 pos) {
	
		_position = pos + _positionInitDif;
		_target = pos + _targetInitDif;

		//_target = pos;

		
		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));
		SetCameraMatrix();
		//Flag::FlagData::SetCameraPos(ToDX(pos));

	}

	///
	/// �`��.
	///
	void CameraComponent::Draw(bool isHit) {


		//if (isHit)
		//{
		//	DrawString(0, 0, "�������Ă���", GetColor(255, 255, 0));
		//}
		//else
		//{
		//	DrawString(0, 0, "�������Ă��Ȃ�", GetColor(255, 0, 0));
		//}
		//// �J�������\��
		//
		//	int x = 0, y = 0, size = 16;
		//	//VECTOR v = { x, y };
		//	SetFontSize(size);
		//	DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		//	DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _target.GetX(), _target.GetY(), _target.GetZ()); y += size;
		//	DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _position.GetX(), _position.GetY(), _position.GetZ()); y += size;
		//	float sx = _position.GetX() - _target.GetX();
		//	float sz = _position.GetZ() - _target.GetZ();
		//	float length = sqrt(sz * sz + sx * sx);
		//	float rad = atan2(sz, sx);
		//	float deg = 180.0f /std::numbers::pi * rad;
		//	DrawFormatString(x, y, GetColor(255, 0, 255), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
		//
		//////x��, y��, z���̊��������
		//float linelength = 1000.0f;
		//VECTOR v = { 0, 0, 0 };
		//DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		//DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));

	}

	void CameraComponent::SetRefleshPosition(Math::Vector4 position) {
	
		_position = position + _positionInitDif;
	}

	void CameraComponent::SetRefleshTarget(Math::Vector4 position) {

		_target = position + _targetInitDif;
	}

	void CameraComponent::SetCameraMatrix() {
	
		// ���݂̃N���C�A���g�̈�̃T�C�Y���擾
		int wwid = 1920, whei = 1080;
		//GetWindowSize(&wwid, &whei);

		//// �ˉe�s���ݒ�
		//MATRIX ProjectionMatrix;
		//CreatePerspectiveFovMatrix(&ProjectionMatrix, tan(DX_PI_F / 3.0 / 2.0) * whei / wwid, 0.001f, 10000.0f, (float)whei / wwid);
		//SetTransformToProjection(&ProjectionMatrix); //!< �J�����s����ˉe�s��ɕϊ����Ă���
		////SetupCamera_ProjectionMatrix(ProjectionMatrix);

		//// �r���[�|�[�g�s���ݒ�
		//MATRIX ViewportMatrix;
		//CreateViewportMatrix(&ViewportMatrix, wwid / 2.0f, whei / 2.0f, (float)wwid, (float)whei);
		//SetTransformToViewport(&ViewportMatrix);//!< �J�����s���ViewPort�s��ɕϊ����Ă���

		//// �`��̈��ݒ�
		//SetDrawArea(0, 0, wwid, whei);

		SetupCamera_Perspective(tan(DX_PI_F / 3.0 / 2.0) * whei / wwid);
	
	}

	//���[�v���̃J�����ړ�
	void CameraComponent::WarpMoveCamera(Math::Vector4 rot, double moveSpeed) {
		Math::Vector4 move = { 0.0, 0.0, 0.0 };
	
		if (rot.GetY() < -2.35 || 2.35 < rot.GetY()) {
		
			//�ォ�痈��(������)
			move = { 0.0, 0.0, moveSpeed };

		}
		else if (-2.35 <= rot.GetY() && rot.GetY() <= -0.78) {
		    //�E���痈��(������)
			move = { moveSpeed, 0.0, 0.0 };
		}
		else if (-0.78 < rot.GetY() && rot.GetY() < 0.78) {
		    //�����痈��(�����)
			move = { 0.0, 0.0, -moveSpeed };
		}
		else {
		    //�����痈��(�E����)
			move = { -moveSpeed, 0.0, 0.0 };
		}

		_target = _target + move;

		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));
	}
}

