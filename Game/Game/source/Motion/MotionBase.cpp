/*****************************************************************//**
 * @file   MotionBase.cpp
 * @brief  モーションの基底クラス
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
  ///コンストラクタ
  MotionBase::MotionBase(Actor::Actor& act) :_actor{ act } {

  }
  ///初期化
  void MotionBase::Init() {

  }
  ///更新
  void MotionBase::Update(Actor::Actor& act)  {

  }
  ///描画
  void MotionBase::Render(Actor::Actor& act) {

  }
}