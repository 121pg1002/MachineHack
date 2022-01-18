///
/// @file    UIComponent.cpp
/// @brief   UI用のコンポーネント
/// @date    2021/12/05
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "UIComponent.h"
#include "AppFrame.h"
#include "Sprite.h"
namespace MachineHuck::UI {

    /// コンストラクタ
    UIComponent::UIComponent(AppFrame::Game& game)
        : Scene{ game } {
    }
    /// 初期化
    void UIComponent::Init() {
    }
    /// 入口
    void UIComponent::Enter() {
        _hpGauge = std::make_unique<barGauge>(*this);

        auto& asSv = GetGame().GetAssetServer();
        _hpGauge->_handle = asSv.GetTexture("BarFrame");
        //auto info = asSv.GetTextureInfo("BarFrame");

        // 画像の左上からバーまでのオフセット座標
        _hpGauge->_offset = { 7, 12, 7 + 330, 12 + 28 };//始点から終点
       // _hpGauge->_offset = { 1500 , 12, 1920-7, 12+28 };

        // バーの色RGBA
        _hpGauge->_barColor = { 0x00,0xFF,0x00,0xC8 };
    }
    /// 入力
    void UIComponent::Input(AppFrame::Input::InputComponent& input) {
    }
    /// 更新
    void UIComponent::Update(/*float deltaTime*/) {
        _hpGauge->Update(_hp, _hpRange);
    }
    /// 描画
    void UIComponent::Render() {
        _hpGauge->Draw();
    }
    /// 出口
    void UIComponent::Exit() {
    }

    /// コンストラクタ
    UIComponent::barGauge::barGauge(UIComponent& owner)
        : _owner{ owner } {
    }
    /// 更新
    void UIComponent::barGauge::Update(float value, float range) {
        _value = value;
        // バーの右側x座標を線形補間で求める
        auto right = (_offset.right - _offset.left) * _value / range + _offset.left;
        // バーの座標(左,上),(右,下)を更新
        _bar.left = _x + _offset.left;
        _bar.top = _y + _offset.top;
        _bar.right = _x + right;
        _bar.bottom = _y + _offset.bottom;
    }
    /// 描画
    void UIComponent::barGauge::Draw() {
        // バーの描画
        auto [r, g, b, a] = _barColor;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
        DrawBoxAA(_bar.left, _bar.top, _bar.right, _bar.bottom, GetColor(r, g, b), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // フレーム画像の描画
        DrawGraph(_x, _y, _handle, TRUE);
    }
}
