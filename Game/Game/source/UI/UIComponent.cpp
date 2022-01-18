///
/// @file    UIComponent.cpp
/// @brief   UI�p�̃R���|�[�l���g
/// @date    2021/12/05
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#include "UIComponent.h"
#include "AppFrame.h"
#include "Sprite.h"
namespace MachineHuck::UI {

    /// �R���X�g���N�^
    UIComponent::UIComponent(AppFrame::Game& game)
        : Scene{ game } {
    }
    /// ������
    void UIComponent::Init() {
    }
    /// ����
    void UIComponent::Enter() {
        _hpGauge = std::make_unique<barGauge>(*this);

        auto& asSv = GetGame().GetAssetServer();
        _hpGauge->_handle = asSv.GetTexture("BarFrame");
        //auto info = asSv.GetTextureInfo("BarFrame");

        // �摜�̍��ォ��o�[�܂ł̃I�t�Z�b�g���W
        _hpGauge->_offset = { 7, 12, 7 + 330, 12 + 28 };//�n�_����I�_
       // _hpGauge->_offset = { 1500 , 12, 1920-7, 12+28 };

        // �o�[�̐FRGBA
        _hpGauge->_barColor = { 0x00,0xFF,0x00,0xC8 };
    }
    /// ����
    void UIComponent::Input(AppFrame::Input::InputComponent& input) {
    }
    /// �X�V
    void UIComponent::Update(/*float deltaTime*/) {
        _hpGauge->Update(_hp, _hpRange);
    }
    /// �`��
    void UIComponent::Render() {
        _hpGauge->Draw();
    }
    /// �o��
    void UIComponent::Exit() {
    }

    /// �R���X�g���N�^
    UIComponent::barGauge::barGauge(UIComponent& owner)
        : _owner{ owner } {
    }
    /// �X�V
    void UIComponent::barGauge::Update(float value, float range) {
        _value = value;
        // �o�[�̉E��x���W����`��Ԃŋ��߂�
        auto right = (_offset.right - _offset.left) * _value / range + _offset.left;
        // �o�[�̍��W(��,��),(�E,��)���X�V
        _bar.left = _x + _offset.left;
        _bar.top = _y + _offset.top;
        _bar.right = _x + right;
        _bar.bottom = _y + _offset.bottom;
    }
    /// �`��
    void UIComponent::barGauge::Draw() {
        // �o�[�̕`��
        auto [r, g, b, a] = _barColor;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
        DrawBoxAA(_bar.left, _bar.top, _bar.right, _bar.bottom, GetColor(r, g, b), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        // �t���[���摜�̕`��
        DrawGraph(_x, _y, _handle, TRUE);
    }
}
