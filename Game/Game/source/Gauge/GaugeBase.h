
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  ゲージの基底クラス
 * 
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/
#pragma once

namespace MachineHuck::Actor {
    class Actor;
}

namespace MachineHuck::Gauge{

    /**
     * @class GaugeBase
     * @brief ゲージの管理クラス
     */
    class GaugeBase{

    public:

        /**
         * @brief コンストラクタ
         * @param act アクタークラスの参照
         */
        GaugeBase(Actor::Actor& act);

        /**
         * @brief 初期化
         */
        void Init();

        /**
         * @brief 更新
         * @param act アクタークラスの参照
         */
        void Update(Actor::Actor& act);

#ifdef _DEBUG
        /**
         * @brief 描画
         */
        void Draw();

        /**
         * @brief 描画
         * @param act
         */
        void Draw(Actor::Actor& act);
#endif

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

    protected:

        int _gaugeNumberOnes;//一の位の数字
        int _gaugeNumberTens;//十の位の数字
        int _gaugeNumberHuns;//百の位の数字
        int _gaugeNumber;//ゲージの数値
    //private:


        int _gauge{ 100 };    //!< エネルギーゲージの量
        int _gaugeMax{ 100 }; //!< エネルギーゲージの最大値
        int _gaugeCount;      //!< ゲージを減らすカウンタ

        Actor::Actor& _actor; //!< アクタークラスの参照


    };

}


