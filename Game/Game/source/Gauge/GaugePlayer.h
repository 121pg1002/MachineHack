
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  �Q�[�W�̊��N���X
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
     * @brief �Q�[�W�̊Ǘ��N���X
     */
     //    class GaugeBase {
    class GaugePlayer :public GaugeBase {
    public:

        /**
         * @brief �R���X�g���N�^
         * @param act �A�N�^�[�N���X�̎Q��
         */
        GaugePlayer(AppFrame::Game& game);

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
        /**
       * @brief  �Q�[�W�̗ʂ��擾
       * @return _gauge
       */
        int GetGauge() { return _gauge; }

        /**
         * @brief  �Q�[�W�̍ő�l���擾
         * @return _gaugeMax
         */
        int GetGaugeMax() { return _gaugeMax; }

        /**
         * @brief �Q�[�W�̗ʂ�ݒ�
         * @param gauge
         */
        void SetGauge(const int gauge) { _gauge = gauge; }

        /**
         * @brief �Q�[�W�ʂ�����
         * @param gauge
         */
        void DownGauge(const int gauge);

        /**
         * @brief �Q�[�W�ʂ����Z
         * @param gauge
         */
        void PlusGauge(const int gauge);

        /**
         * @brief  �Q�[�W�̗ʂ�0���ǂ���
         * @return true  0�ł���
         *         false 0�ł͂Ȃ�
         */
        bool IsGaugeZero(Actor::Actor& act);

        /**
         * @brief �Q�[�W�̍ő�l��ݒ�
         * @param gaugeMax
         */
        void SetGaugeMax(int gaugeMax) { _gaugeMax = gaugeMax; }

        void UpdatePlayerPosition(Math::Vector4 pos) { _gaugePlayerPosition = pos; };

        Math::Vector4 GetPlayerPos() { return _gaugePlayerPosition; }
        /// �v���C���[��HP�o�[�X�V
       /// @param[in] hp �\������q�b�g�|�C���g
       /// @param[in] hpRange �q�b�g�|�C���g�͈̔�
        void UpdatePlayerHp(float gauge) { _gauge = gauge; };
    private:

        int _gaugeCount;      //!< �Q�[�W�����炷�J�E���^
        int _gaugeTimer{ 0 };
        int _handlePl;          //�G�l���M�[�Q�[�W���^��
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


