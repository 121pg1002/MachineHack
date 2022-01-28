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
		SetCameraNearFar(50.0f, 10000.0f);
	}
	void CameraComponent::Input(AppFrame::Input::InputComponent& input) {
	}
	///
	/// �X�V.
	///
	void CameraComponent::Update(Math::Vector4 move) {
		//// �^�[�Q�b�g�̌�����Y�͖���
		//auto forward = _forwardOfTarget;
		//forward.y = 0.f;
		//// �^�[�Q�b�g�̌����̐^�t�ɒ�����targetDist
		//auto fromTarget = VScale(forward, -targetDist);
		//fromTarget.y = vertDist;
		// �J�����̈ʒu���v���C���[�̌���̈ʒu�ɂ���
		_position = _position + move;
		_target = _target + move;

		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));


	}


	void CameraComponent::FloorPos(Math::Vector4 pos) {
	
		_position = pos + _positionInitDif;
		_target = pos + _targetInitDif;
		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));

		Flag::FlagData::SetCameraPos(ToDX(pos));

	}

	///
	/// �`��.
	///
	void CameraComponent::Draw(bool isHit) {


		if (isHit)
		{
			DrawString(0, 0, "�������Ă���", GetColor(255, 255, 0));
		}
		else
		{
			DrawString(0, 0, "�������Ă��Ȃ�", GetColor(255, 0, 0));
		}
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


	//MATRIX GetCameraViewMatrix(VECTOR& cameraPosition, VECTOR& cameraTarget, VECTOR& cameraUp) {
	//    //SetCameraPositionAndTargetAndUpVec(camera_position, camera_target, camera_up);
	//    //MATRIX camera_matrix = GetCameraViewMatrix();
	//    // �� ��L�Ɠ��� MATRIX �̓��e���v�Z����
	//
	//    // �J�����̎p���ł� XYZ ���쐬
	//    VECTOR camera_z = VNorm(VSub(cameraTarget, cameraPosition));
	//    VECTOR camera_x = VNorm(VCross(cameraUp, camera_z));
	//    VECTOR camera_y = VCross(camera_z, camera_x);
	//
	//    MATRIX camera_matrix = MGetIdent();
	//
	//    camera_matrix.m[0][0] = camera_x.x;
	//    camera_matrix.m[0][1] = camera_y.x;
	//    camera_matrix.m[0][2] = camera_z.x;
	//
	//    camera_matrix.m[1][0] = camera_x.y;
	//    camera_matrix.m[1][1] = camera_y.y;
	//    camera_matrix.m[1][2] = camera_z.y;
	//
	//    camera_matrix.m[2][0] = camera_x.z;
	//    camera_matrix.m[2][1] = camera_y.z;
	//    camera_matrix.m[2][2] = camera_z.z;
	//    // DX ���C�u�����ɂ� VECTOR �Ƀ}�C�i�X���Z�q������@�\�͂Ȃ��̂� VScale �Ń}�C�i�X�ɂ���
	//    camera_matrix.m[3][0] = VDot(VScale(camera_x, -1.0f), cameraPosition);
	//    camera_matrix.m[3][1] = VDot(VScale(camera_y, -1.0f), cameraPosition);
	//    camera_matrix.m[3][2] = VDot(VScale(camera_z, -1.0f), cameraPosition);
	//
	//    return camera_matrix;
	//}
}

