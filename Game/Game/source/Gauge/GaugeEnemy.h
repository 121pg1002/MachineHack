
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  ゲージの基底クラス
 *
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
#include "../ShadowMap/Shadowmap.h"
namespace MachineHuck::Actor {
    class Actor;
}
namespace MachineHuck::Shadow {
    class ShadowMap;
}
namespace MachineHuck::Gauge {

  /**
   * @class GaugeBase
   * @brief ゲージの管理クラス
   */
   //    class GaugeBase {
  class GaugeEnemy :public GaugeBase {
  public:

    /**
     * @brief コンストラクタ
     * @param act アクタークラスの参照
     */
    GaugeEnemy(Actor::Actor& act);

    /**
     * @brief 初期化
     */
    void Init(Actor::Actor& act);
    /**
    * @brief 更新
    */
    void Update();
    /**
     * @brief 更新
     * @param act アクタークラスの参照
     */
    void Update(Actor::Actor& act);



    /**
     * @brief 描画
     * @param act
     */
    void Draw(Actor::Actor& act);




  private:

    //int _gauge{ 100 };    //!< エネルギーゲージの量
    //int _gaugeMax{ 100 }; //!< エネルギーゲージの最大値
    int _gaugeCount;      //!< ゲージを減らすカウンタ

   // Actor::Actor& _actor; //!< アクタークラスの参照
    int _handleEn;          //エネルギーゲージ満タン
    int _handleEn1[5] = { 0 };
    int _handleEn2[5] = { 0 };
    int _handleEn3[5] = { 0 };
    int _handleEn4[5] = { 0 };
    int _handleEn5[5] = { 0 };
    int _handleEn0;
    int _gaugeTimer{ 0 };
  };
}