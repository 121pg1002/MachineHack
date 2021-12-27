///
/// @file    StateComponent.h
/// @brief   �X�e�[�g�R���|�[�l���g
/// @date    2021/12/06
/// @author yamawaki kota
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class Actor;
class InputComponent;
namespace StateComponent {
  class StateBaseRoot {
  public:
    StateBaseRoot() {};
    virtual void Enter() {};
    virtual void Input(InputComponent& input) {};
    virtual void Update() {};
    virtual void Draw() {};
  };

  class StateComponent {
  public:
    /// �R���X�g���N�^
    /// @param[in] key   �ŏ��̃V�[���Ɋ֘A�t����C�ӂ̕�����
    /// @param[in] scene �ŏ��̃V�[����
    StateComponent(std::string_view key, std::shared_ptr<StateBaseRoot> state);
    /// ��Ԃ̓o�^
    /// @param[in] key   �V�[���Ɋ֘A�t����C�ӂ̕�����
    /// @param[in] scene �V�[���̃C���X�^���X
    void Register(std::string_view key, std::shared_ptr<StateBaseRoot> state);
    /// ��Ԃ̃v�b�V���o�b�N
    /// ���X�g�̈�Ԍ��(�őO��)�ɃV�[�����v�b�V���ǉ�����
    /// Scene�̓�������Enter�����s����
    /// @param[in] key �o�^�ς݂̃V�[���Ɋ֘A�t����������
    void PushBack(std::string_view key);
    /// ��Ԃ̃|�b�v�o�b�N
    /// ���X�g�̈�Ԍ��(�őO��)�̃V�[�����|�b�v���O����
    /// Scene�̏o������Exit�����s����
    void PopBack();
    /// ��Ԃ̑J��
    /// PopBack����PushBack����
    /// @param[in] key �o�^�ς݂̃V�[���Ɋ֘A�t����������
    void GoToState(std::string_view key);
    /// ����
    /// ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
    /// @param[in] input �C���v�b�g�R���|�[�l���g�̎Q��
    void Input(InputComponent& input);
    /// �X�V
    /// ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
    void Update();
    /// �`��
    /// ���X�g�̑S�V�[������������
    void Draw() const;

  private:
    /// ��Ԃ̃��W�X�g��
    std::unordered_map<std::string, std::shared_ptr<StateBaseRoot>>	_registry;
    /// ��Ԃ̃��X�g
    std::list<std::shared_ptr<StateBaseRoot>> _states;
  };
}
