/*****************************************************************//**
 * @file   ModelComponent.cpp
 * @brief  スタティックモデル用のコンポーネント
 *
 * @author yamawaki kota
 * @date   December 6 2021
 *********************************************************************/

#include "ModelComponent.h"
#include "../Actor/Actor.h"
#include "AppFrame.h"


namespace MachineHuck::Model {
	ModelComponent::ModelComponent(Actor::Actor& owner) : _owner{ owner } {
	}

	/// デストラクタ
	ModelComponent::~ModelComponent() {
		//MV1DeleteModel(_handle);
	}
	/// 初期化
	void ModelComponent::Init() {

	}
	/// 更新
	void ModelComponent::Update() {
		// ワールド行列更新
		MV1SetMatrix(_handle, _owner.GetWorldTransform());

		// 行列使わない場合

		//auto pos = _owner.GetPosition();
		//auto rot = _owner.GetRotation();

		//MV1SetPosition(_handle, ToDX(pos));
		//MV1SetRotationXYZ(_handle, ToDX(rot));
	}
	/// 描画
	void ModelComponent::Draw() {
		SetUseLighting(_isLighting);
		MV1DrawModel(_handle);
	}



	//void ModelComponent::Draw(Math::Vector4 pos, Math::Vector4 rot, Math::Vector4 scale) {
	//
	//	SetPosition(ToDX(pos));
	//	SetRotation(ToDX(rot));
	//	SetScale(ToDX(scale));
	//
	//}

	/// モデルの設定
	int ModelComponent::SetModel(std::string_view key, int no) {
		auto [handle, actualNo] = _owner.GetGame().GetAssetServer().GetModel(key, no);
		_handle = handle;
		return actualNo;
	}
	/// 座標の設定
	void ModelComponent::SetPosition(VECTOR position) {
		MV1SetPosition(_handle, position);
	}

	void ModelComponent::SetPosition(VECTOR position, float diameter) {
		position.x = position.x * diameter;
		position.y = position.y * diameter;
		position.z = position.z * diameter;

		MV1SetPosition(_handle, position);
	}

	/// 回転角度の設定
	void ModelComponent::SetRotation(VECTOR rotation) {

		rotation.x = 3.141592f / 180.0f * rotation.x;
		rotation.y = 3.141592f / 180.0f * rotation.y;
		rotation.z = 3.141592f / 180.0f * rotation.z;

		MV1SetRotationXYZ(_handle, rotation);
	}
	/// 拡大率の設定
	void ModelComponent::SetScale(VECTOR  scale) {

		scale.x = scale.x * 75.0f;
		scale.y = scale.y * 75.0f;
		scale.z = scale.z * 75.0f;

		//scale.x = scale.x / 70.0;
		//scale.y = scale.y / 70.0;
		//scale.z = scale.z / 70.0;

		MV1SetScale(_handle, scale);
	}



	/// ワールド行列の設定
	void ModelComponent::SetMatrix(MATRIX& world) {
		MV1SetMatrix(_handle, world);
	}

	void ModelComponent::SetColor(int index, float r, float g, float b) {
		MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
	}
}


