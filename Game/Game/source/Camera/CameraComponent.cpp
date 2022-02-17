/*****************************************************************//**
 * @file   CameraComponent.cpp
 * @brief  カメラコンポーネント
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
	/// コンストラクタ.
	///
	CameraComponent::CameraComponent() {
		Init();
	}
	///
	/// 初期化.
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
	/// 更新.
	///
	void CameraComponent::Update(Math::Vector4 move) {

		//Math::Vector4 cameraMove = { 0.0, 0.0, move.GetZ() };

		// カメラの位置をプレイヤーの後方の位置にする
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
	/// 描画.
	///
	void CameraComponent::Draw(bool isHit) {


		//if (isHit)
		//{
		//	DrawString(0, 0, "当たっている", GetColor(255, 255, 0));
		//}
		//else
		//{
		//	DrawString(0, 0, "当たっていない", GetColor(255, 0, 0));
		//}
		//// カメラ情報表示
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
		//////x軸, y軸, z軸の基準を示す線
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
	
		// 現在のクライアント領域のサイズを取得
		int wwid = 1920, whei = 1080;
		//GetWindowSize(&wwid, &whei);

		//// 射影行列を設定
		//MATRIX ProjectionMatrix;
		//CreatePerspectiveFovMatrix(&ProjectionMatrix, tan(DX_PI_F / 3.0 / 2.0) * whei / wwid, 0.001f, 10000.0f, (float)whei / wwid);
		//SetTransformToProjection(&ProjectionMatrix); //!< カメラ行列を射影行列に変換している
		////SetupCamera_ProjectionMatrix(ProjectionMatrix);

		//// ビューポート行列を設定
		//MATRIX ViewportMatrix;
		//CreateViewportMatrix(&ViewportMatrix, wwid / 2.0f, whei / 2.0f, (float)wwid, (float)whei);
		//SetTransformToViewport(&ViewportMatrix);//!< カメラ行列をViewPort行列に変換している

		//// 描画領域を設定
		//SetDrawArea(0, 0, wwid, whei);

		SetupCamera_Perspective(tan(DX_PI_F / 3.0 / 2.0) * whei / wwid);
	
	}

	//ワープ時のカメラ移動
	void CameraComponent::WarpMoveCamera(Math::Vector4 rot, double moveSpeed) {
		Math::Vector4 move = { 0.0, 0.0, 0.0 };
	
		if (rot.GetY() < -2.35 || 2.35 < rot.GetY()) {
		
			//上から来た(下向き)
			move = { 0.0, 0.0, moveSpeed };

		}
		else if (-2.35 <= rot.GetY() && rot.GetY() <= -0.78) {
		    //右から来た(左向き)
			move = { moveSpeed, 0.0, 0.0 };
		}
		else if (-0.78 < rot.GetY() && rot.GetY() < 0.78) {
		    //下から来た(上向き)
			move = { 0.0, 0.0, -moveSpeed };
		}
		else {
		    //左から来た(右向き)
			move = { -moveSpeed, 0.0, 0.0 };
		}

		_target = _target + move;

		SetCameraPositionAndTarget_UpVecY(ToDX(_position), ToDX(_target));
	}
}

