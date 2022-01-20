/*****************************************************************//**
 * @file   MotionBase.h
 * @brief  ���[�V�����̊��N���X
 *
 * @author kota Yamawaki
 * @date   January 20 2022
 *********************************************************************/
#pragma once

namespace MachineHuck::Actor {
  class Actor;
}
namespace MachineHuck::Motion {
  /**
     * @class MotionBase
     * @brief �Q�[�W�̊Ǘ��N���X
     */
  class MotionBase {
  public:
    /**
     * @brief �R���X�g���N�^
     * @param act �A�N�^�[�N���X�̎Q��
     */
    MotionBase(Actor::Actor& act);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~MotionBase()= default;
    /**
     * @brief ������
     */
    void Init();

    /**
     * @brief �X�V
     * @param act �A�N�^�[�N���X�̎Q��
     */
    void Update(Actor::Actor& act);

    /**
     * @brief �`��
     * @param act �A�N�^�[�N���X�̎Q��
     */
    void Render(Actor::Actor& act);
  private:
    Actor::Actor& _actor; //!< �A�N�^�[�N���X�̎Q��
      };
}
