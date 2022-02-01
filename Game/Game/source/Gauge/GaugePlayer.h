
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
    class GaugePlayer :public GaugeBase {
    public:

        /**
         * @brief コンストラクタ
         * @param act アクタークラスの参照
         */
        GaugePlayer(Actor::Actor& act);

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
        /**
       * @brief  ゲージの量を取得
       * @return _gauge
       */
        int GetGauge() { return _gaugePlayer; }

        /**
         * @brief  ゲージの最大値を取得
         * @return _gaugeMax
         */
        int GetGaugeMax() { return _gaugeMax; }

        /**
         * @brief ゲージの量を設定
         * @param gauge
         */
        void SetGauge(const int gauge) { _gaugePlayer = gauge; }

        /**
         * @brief ゲージ量を減少
         * @param gauge
         */
        void DownGauge(const int gauge);

        /**
         * @brief ゲージ量を加算
         * @param gauge
         */
        void PlusGauge(const int gauge);

        /**
         * @brief  ゲージの量が0かどうか
         * @return true  0である
         *         false 0ではない
         */
        bool IsGaugeZero(Actor::Actor& act);

        /**
         * @brief ゲージの最大値を設定
         * @param gaugeMax
         */
        void SetGaugeMax(int gaugeMax) { _gaugeMax = gaugeMax; }
    private:

        int _gaugePlayer{ 100 };    //!< エネルギーゲージの量
        int _gaugeMax{ 100 }; //!< エネルギーゲージの最大値
        int _gaugeCount;      //!< ゲージを減らすカウンタ
        int _gaugeTimer{ 0 };
        int _handlePl;          //エネルギーゲージ満タン
        int _handlePl1[5] = {0};
        int _handlePl2[5] = { 0 };
        int _handlePl3[5] = { 0 };
        int _handlePl4[5] = { 0 };
        int _handlePl5[5] = { 0 };
        int _handlePl0;
       // Actor::Actor& _actor; //!< アクタークラスの参照


    };

}


