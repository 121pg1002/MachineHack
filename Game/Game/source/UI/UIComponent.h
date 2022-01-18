///
/// @file    UIComponent.h
/// @brief   UI用のコンポーネント
/// @date    2021/12/05
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"
namespace MachineHuck::UI {
    /// @class UIComponent
    /// @brief UIコンポーネント
    class UIComponent : public AppFrame::Scene::Scene {
    public:
        /// コンストラクタ
        /// @param[in] game ゲームクラスの参照
        UIComponent(AppFrame::Game& game);
        /// デストラクタ
        virtual ~UIComponent() = default;
        /// 初期化
        void Init() override;
        /// 入口
        void Enter() override;
        /// 入力
        /// @param[in] input インプットコンポーネント
        void Input(AppFrame::Input::InputComponent& input) override;
        /// 更新
        void Update() override;
        /// 描画
        void Render() override;
        /// 出口
        void Exit() override;
        /// プレイヤーのHPバー更新
        /// @param[in] hp 表示するヒットポイント
        /// @param[in] hpRange ヒットポイントの範囲
        void UpdatePlayerHp(float hp, float hpRange) { _hp = hp; _hpRange = hpRange; };

        /// @struct RECT
        /// @brief 矩形
        struct RECT {
            float left, top, right, bottom;
        };
        /// @struct RGBA
        /// @brief 色
        struct RGBA {
            int r, g, b, a;
        };
        /// @class barGauge
        /// @brief バーゲージ
        class barGauge {
            friend UIComponent;
        public:
            /// コンストラクタ
            /// @param[in] owner UIコンポネントの参照
            barGauge(UIComponent& owner);
            /// 更新
            /// @param[in] value 表示する値
            /// @param[in] range 表示する値の範囲
            virtual void Update(float value, float range);
            /// 描画
            virtual void Draw();
        private:
            UIComponent& _owner;
            //int _x{ 1550 }, _y{ 0 };//バーゲージの座標
            int _x{ 960-165 }, _y{ 540-200 };//バーゲージの座標
            float _value{ 0 }, _range{ 0 };
            RGBA _barColor{ 0,0,0,0 };
            RECT _bar{ 0,0,0,0 };
            RECT _offset{ 0,0,0,0 };
            int _handle{ -1 };
        };
    private:
        float _hp{ 100 }, _hpRange{ 100 };
        std::unique_ptr<barGauge> _hpGauge;
    };
}
