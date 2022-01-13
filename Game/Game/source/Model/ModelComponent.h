///
/// @file    ModelComponent.h
/// @brief   �X�^�e�B�b�N���f���p�̃R���|�[�l���g
/// @date    2021/11/26
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <DxLib.h>
#include <string_view>

class Actor;

///
/// @class   ModelComponent
/// @brief   �X�^�e�B�b�N���f���p�̃R���|�[�l���g�N���X�̐錾
///
class ModelComponent {
public:
  /// �R���X�g���N�^
  /// @param[in] filename ���f���̃t�@�C����
  ModelComponent(Actor& owner);
  /// �f�X�g���N�^
  virtual ~ModelComponent();

  /// ������
	virtual void Init();

  /// �X�V
	virtual void Update();

  /// �`��
  virtual void Draw();
  
  /// ���f���̐ݒ�
  /// @param key AssetServer�ɓo�^�ς݂̃L�[
  /// @return ���ۂɓo�^���ʂ��ԍ�
  virtual int SetModel(std::string_view key, int no = 0);

  /// ���W�̐ݒ�.
  /// @param[in] position ���Wx,y,z
  virtual void SetPosition(VECTOR position);

  /// ��]�p�x�̐ݒ�.
  /// @param[in] rotation ��]�p�xx,y,z
  virtual void SetRotation(VECTOR rotation);

  /// �g�嗦�̐ݒ�.
  /// @param[in] scale �g�嗦
  virtual void SetScale(VECTOR scale);

  /// ���[���h�s��̐ݒ�
  /// @param world 
  virtual void SetMatrix(MATRIX& world);

  void SetHandle(int handle) { _handle = handle; }
  int GetHandle() { return _handle; }
  void SetColor(int index, float r, float g, float b);

protected:
  Actor& _owner;
  int _handle{-1};
  bool _isLighting{true};
};

