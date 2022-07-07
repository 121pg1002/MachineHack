///
/// @file    UIComponent.h
/// @brief   UI�p�̃R���|�[�l���g
/// @date    2021/12/05
/// @copyright (C) Amusement Media Academy All rights Resved.
///
#pragma once
#include "AppFrame.h"
namespace MachineHuck::UI {
    /// @class UIComponent
    /// @brief UI�R���|�[�l���g
    class UIComponent : public AppFrame::Scene::Scene {
    public:
        /// �R���X�g���N�^
        /// @param[in] game �Q�[���N���X�̎Q��
        UIComponent(AppFrame::Game& game);
        /// �f�X�g���N�^
        virtual ~UIComponent() = default;
        /// ������
        void Init() override;
        /// ����
        void Enter() override;
        /// ����
        /// @param[in] input �C���v�b�g�R���|�[�l���g
        void Input(AppFrame::Input::InputComponent& input) override;
        /// �X�V
        void Update() override;
        /// �`��
        void Render() override;
        /// �o��
        void Exit() override;
        /// �v���C���[��HP�o�[�X�V
        /// @param[in] hp �\������q�b�g�|�C���g
        /// @param[in] hpRange �q�b�g�|�C���g�͈̔�
        void UpdatePlayerHp(float hp, float hpRange) { _hp = hp; _hpRange = hpRange; };

        /// @struct RECT
        /// @brief ��`
        struct RECT {
            float left, top, right, bottom;
        };
        /// @struct RGBA
        /// @brief �F
        struct RGBA {
            int r, g, b, a;
        };
        /// @class barGauge
        /// @brief �o�[�Q�[�W
        class barGauge {
            friend UIComponent;
        public:
            /// �R���X�g���N�^
            /// @param[in] owner UI�R���|�l���g�̎Q��
            barGauge(UIComponent& owner);
            /// �X�V
            /// @param[in] value �\������l
            /// @param[in] range �\������l�͈̔�
            virtual void Update(float value, float range);
            /// �`��
            virtual void Draw();
        private:
            UIComponent& _owner;
            //int _x{ 1550 }, _y{ 0 };//�o�[�Q�[�W�̍��W
            int _x{ 960-165 }, _y{ 540-200 };//�o�[�Q�[�W�̍��W
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
