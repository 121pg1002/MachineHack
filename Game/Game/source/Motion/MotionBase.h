/*****************************************************************//**
 * @file   MotionBase.h
 * @brief  モーションの基底クラス
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
     * @brief ゲージの管理クラス
     */
  class MotionBase {
  public:
    /**
     * @brief コンストラクタ
     * @param act アクタークラスの参照
     */
    MotionBase(Actor::Actor& act);
    /**
    * @brief デストラクタ
    */
    virtual ~MotionBase()= default;
    /**
     * @brief 初期化
     */
    void Init();

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
    Actor::Actor& _actor; //!< アクタークラスの参照
      };
}
