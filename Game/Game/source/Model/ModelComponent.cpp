/*****************************************************************//**
 * @file   ModelComponent.cpp
 * @brief  �X�^�e�B�b�N���f���p�̃R���|�[�l���g
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

	/// �f�X�g���N�^
	ModelComponent::~ModelComponent() {
		//MV1DeleteModel(_handle);
	}
	/// ������
	void ModelComponent::Init() {

	}
	/// �X�V
	void ModelComponent::Update() {
		// ���[���h�s��X�V
		MV1SetMatrix(_handle, _owner.GetWorldTransform());

		// �s��g��Ȃ��ꍇ
		//auto pos = _owner.GetPosition();
		//auto rot = _owner.GetRotation();

		//MV1SetPosition(_handle, ToDX(pos));
		//MV1SetRotationXYZ(_handle, ToDX(rot));
	}
	/// �`��
	void ModelComponent::Draw() {
		SetUseLighting(_isLighting);
		MV1DrawModel(_handle);
	}

	void ModelComponent::BrokenDraw() {
		MV1SetFrameVisible(_handle, 1, false);
		MV1DrawModel(_handle);
	
	}

	void ModelComponent::SetModelGimmick(std::string key, std::string collisionName, int no) {
	
		auto [handle, actualNo] = _owner.GetGame().GetAssetServer().GetModel(key, no);

		//�R���W�������������Ă��Ȃ��Ƃ����Ȃ�
		auto frameGimmickCollision = MV1SearchFrame(handle, collisionName.c_str());

		MV1SetupCollInfo(handle, frameGimmickCollision, 32, 32, 32);
		//_gimmickHandle[key] = handle;
		_gimmickHandle.emplace(handle, frameGimmickCollision);
	}

	//void ModelComponent::Draw(Math::Vector4 pos, Math::Vector4 rot, Math::Vector4 scale) {
	//
	//	SetPosition(ToDX(pos));
	//	SetRotation(ToDX(rot));
	//	SetScale(ToDX(scale));
	//
	//}

	/// ���f���̐ݒ�
	int ModelComponent::SetModel(std::string_view key, int no) {
		auto&& [handle, actualNo] = _owner.GetGame().GetAssetServer().GetModel(key, no);
		_handle = handle;
		return actualNo;
	}

	//�X�e�[�W���f���̐ݒ�
	int ModelComponent::SetMap(std::string key, int no) {

		if (key.size() < 5) {
		
			return 0;
		}

		auto keyNum = key.substr(5, 1);
		int num = std::stoi(keyNum);

		auto&& [handle, actualNo] = _owner.GetGame().GetAssetServer().GetMap(num, no);
		_handle = handle;
		return actualNo;
	}


	/// ���W�̐ݒ�
	void ModelComponent::SetPosition(VECTOR position) {

		MV1SetPosition(_handle, position);

	}

	//void ModelComponent::SetPosition(VECTOR position) {

	//	auto size = MV1GetFrameNum(_handle);

	//	for (auto i = 0; i < size; i++) {
	//		MV1SetupCollInfo(_handle, i, 16, 16, 16);
	//	}

	//	MV1SetPosition(_handle, position);

	//	for (auto i = 0; i < size; i++) {
	//		MV1RefreshCollInfo(_handle, i);
	//	}

	//}



	void ModelComponent::SetPosition(VECTOR position, float diameter) {
		position.x = position.x * diameter;
		position.y = position.y * diameter;
		position.z = position.z * diameter;

		MV1SetPosition(_handle, position);
	}

	/// ��]�p�x�̐ݒ�
	void ModelComponent::SetRotation(VECTOR rotation) {

		rotation.x = 3.141592f / 180.0f * rotation.x;
		rotation.y = 3.141592f / 180.0f * rotation.y;
		rotation.z = 3.141592f / 180.0f * rotation.z;

		MV1SetRotationXYZ(_handle, rotation);
	}
	/// �g�嗦�̐ݒ�
	void ModelComponent::SetScale(VECTOR  scale) {

		scale.x = scale.x;
		scale.y = scale.y;
		scale.z = scale.z;

		//scale.x = scale.x / 70.0;
		//scale.y = scale.y / 70.0;
		//scale.z = scale.z / 70.0;

		MV1SetScale(_handle, scale);
	}



	/// ���[���h�s��̐ݒ�
	void ModelComponent::SetMatrix(MATRIX& world) {
		MV1SetMatrix(_handle, world);
	}

	void ModelComponent::SetColor(int index, float r, float g, float b) {
		MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
	}
}


