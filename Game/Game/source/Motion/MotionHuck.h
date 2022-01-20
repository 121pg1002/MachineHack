/*****************************************************************//**
 * @file   MotionHuck.h
 * @brief  ハッキングモーションクラス
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
    * @brief コンストラクタ
    * @param act アクタークラスの参照
     */
    MotionHuck(Actor::Actor& act);
    /**
    * @brief デストラクタ
    */
    ~MotionHuck()override = default;
    /**
     * @brief 更新
     * @param act アクタークラスの参照
     */
    void Update(Actor::Actor& act);

    /**
     * @brief 描画
     * @param act アクタークラスの参照
     */
    void Render(Actor::Actor& act);
  private:
  };
}
