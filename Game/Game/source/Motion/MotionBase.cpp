/*****************************************************************//**
 * @file   MotionBase.cpp
 * @brief  ���[�V�����̊��N���X
 *
 * @author kota Yamawaki
 * @date   January 20 2022
 *********************************************************************/
#pragma once
#include "MotionBase.h"
#include <string>
#include <DxLib.h>
#include "../Actor/Actor.h"
namespace MachineHuck::Motion {
  ///�R���X�g���N�^
  MotionBase::MotionBase(Actor::Actor& act) :_actor{ act } {

  }
  ///������
  void MotionBase::Init() {

  }
  ///�X�V
  void MotionBase::Update(Actor::Actor& act)  {

  }
  ///�`��
  void MotionBase::Render(Actor::Actor& act) {

  }
}