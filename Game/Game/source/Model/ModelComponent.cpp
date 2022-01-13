///
/// @file    ModelComponent.cpp
/// @brief   �X�^�e�B�b�N���f���p�̃R���|�[�l���g
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "ModelComponent.h"
#include "../Actor/Actor.h"
#include "AppFrame.h"


ModelComponent::ModelComponent(Actor& owner): _owner{owner} {
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
  //MV1SetPosition(_handle, _owner.GetPosition());
  //MV1SetRotationXYZ(_handle, _owner.GetRotation());
}
/// �`��
void ModelComponent::Draw() {
	SetUseLighting(_isLighting);
	MV1DrawModel(_handle);
}
/// ���f���̐ݒ�
int ModelComponent::SetModel(std::string_view key, int no) {
	auto [handle, actualNo] = _owner.GetGame().GetAssetServer().GetModel(key, no);
	_handle = handle;
	return actualNo;
}
/// ���W�̐ݒ�
void ModelComponent::SetPosition(VECTOR position) {
  MV1SetPosition(_handle, position);
}
/// ��]�p�x�̐ݒ�
void ModelComponent::SetRotation(VECTOR rotation) {
  MV1SetRotationXYZ(_handle, rotation);
}
/// �g�嗦�̐ݒ�
void ModelComponent::SetScale(VECTOR  scale) {
  MV1SetScale(_handle, scale);
}
/// ���[���h�s��̐ݒ�
void ModelComponent::SetMatrix(MATRIX& world) {
	MV1SetMatrix(_handle, world);
}

void ModelComponent::SetColor(int index, float r, float g, float b) {
	MV1SetMaterialEmiColor(_handle, index, GetColorF(r, g, b, 0.f));
}
