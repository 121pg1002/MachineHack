
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
#include "AppFrame.h"
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
        GaugePlayer(AppFrame::Game& game);

        /**
         * @brief 初期化
         */
        void Init();

        /**
        * @brief 更新
        */
        void Update();



        /**
         * @brief 描画
         * @param act
         */
        void Draw();
        /**
       * @brief  ゲージの量を取得
       * @return _gauge
       */
        int GetGauge() { return _gauge; }

        /**
         * @brief  ゲージの最大値を取得
         * @return _gaugeMax
         */
        int GetGaugeMax() { return _gaugeMax; }

        /**
         * @brief ゲージの量を設定
         * @param gauge
         */
        void SetGauge(const int gauge) { _gauge = gauge; }

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

        void UpdatePlayerPosition(Math::Vector4 pos) { _gaugePlayerPosition = pos; };

        Math::Vector4 GetPlayerPos() { return _gaugePlayerPosition; }
        /// プレイヤーのHPバー更新
       /// @param[in] hp 表示するヒットポイント
       /// @param[in] hpRange ヒットポイントの範囲
        void UpdatePlayerHp(float gauge) { _gauge = gauge; };
    private:

        int _gaugeCount;      //!< ゲージを減らすカウンタ
        int _gaugeTimer{ 0 };
        int _handlePl;          //エネルギーゲージ満タン
        int _handlePl1[5] = { 0 };
        int _handlePl2[5] = { 0 };
        int _handlePl3[5] = { 0 };
        int _handlePl4[5] = { 0 };
        int _handlePl5[5] = { 0 };
        int _handlePl0;
        Math::Vector4 _oldPlayerPosition = { 0,0,0 };
        Math::Vector4 _gaugePlayerPosition = { 0,0,0 };
    };

}


