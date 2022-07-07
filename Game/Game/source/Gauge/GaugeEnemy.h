
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  �Q�[�W�̊��N���X
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
     * @brief �Q�[�W�̊Ǘ��N���X
     */
     //    class GaugeBase {
    class GaugeEnemy :public GaugeBase {
    public:

        /**
         * @brief �R���X�g���N�^
         * @param act �A�N�^�[�N���X�̎Q��
         */
        GaugeEnemy(AppFrame::Game& game);

        /**
         * @brief ������
         */
        void Init();
        /**
        * @brief �X�V
        */
        void Update();

        /**
         * @brief �`��
         * @param act
         */
        void Draw();

        void UpdateEnemyPosition(Math::Vector4 pos) { _gaugeEnemyPosition = pos; };
        Math::Vector4 GetGaugeEnemyPosition() { return _gaugeEnemyPosition; }
        void UpdateEnemyHp(float gauge) { _gauge = gauge; };

        int GetEnemyGauge() { return _gauge; }
    private:
        int _gaugeCount;      //!< �Q�[�W�����炷�J�E���^

        int _handleEn;          //�G�l���M�[�Q�[�W���^��
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