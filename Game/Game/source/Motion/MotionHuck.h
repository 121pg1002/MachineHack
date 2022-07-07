/*****************************************************************//**
 * @file   MotionHuck.h
 * @brief  �n�b�L���O���[�V�����N���X
 *
 * @author kota Yamawaki
 * @date   January 20 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include "MotionBase.h"
namespace MachineHuck::Motion {
  class MotionHuck :public MotionBase {
  public:
    /**
    * @brief �R���X�g���N�^
    * @param act �A�N�^�[�N���X�̎Q��
     */
    MotionHuck(Actor::Actor& act);
    /**
    * @brief �f�X�g���N�^
    */
    ~MotionHuck()override = default;
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
  };
}
