
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  ゲージの基底クラス
 *
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/
#pragma once
#include "GaugeBase.h"
#include "AppFrame.h"
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
        GaugeEnemy(AppFrame::Game& game);

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

        void UpdateEnemyPosition(Math::Vector4 pos) { _gaugeEnemyPosition = pos; };
        Math::Vector4 GetGaugeEnemyPosition() { return _gaugeEnemyPosition; }
        void UpdateEnemyHp(float gauge) { _gauge = gauge; };

        int GetEnemyGauge() { return _gauge; }
    private:
        int _gaugeCount;      //!< ゲージを減らすカウンタ

        int _handleEn;          //エネルギーゲージ満タン
        int _handleEn1[5] = { 0 };
        int _handleEn2[5] = { 0 };
        int _handleEn3[5] = { 0 };
        int _handleEn4[5] = { 0 };
        int _handleEn5[5] = { 0 };
        int _handleEn0;
        int _gaugeTimer{ 0 };
        Math::Vector4  _gaugeEnemyPosition = { 0, 0, 0 };
    };
}