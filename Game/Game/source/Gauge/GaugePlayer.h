
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
        GaugePlayer(Actor::Actor& act);

        /**
         * @brief ������
         */
        void Init(Actor::Actor& act);
        /**
        * @brief �X�V
        */
        void Update();
        /**
         * @brief �X�V
         * @param act �A�N�^�[�N���X�̎Q��
         */
        void Update(Actor::Actor& act);



        /**
         * @brief �`��
         * @param act
         */
        void Draw(Actor::Actor& act);
        /**
       * @brief  �Q�[�W�̗ʂ��擾
       * @return _gauge
       */
        int GetGauge() { return _gaugePlayer; }

        /**
         * @brief  �Q�[�W�̍ő�l���擾
         * @return _gaugeMax
         */
        int GetGaugeMax() { return _gaugeMax; }

        /**
         * @brief �Q�[�W�̗ʂ�ݒ�
         * @param gauge
         */
        void SetGauge(const int gauge) { _gaugePlayer = gauge; }

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
    private:

        int _gaugePlayer{ 100 };    //!< �G�l���M�[�Q�[�W�̗�
        int _gaugeMax{ 100 }; //!< �G�l���M�[�Q�[�W�̍ő�l
        int _gaugeCount;      //!< �Q�[�W�����炷�J�E���^
        int _gaugeTimer{ 0 };
        int _handlePl;          //�G�l���M�[�Q�[�W���^��
        int _handlePl1[5] = {0};
        int _handlePl2[5] = { 0 };
        int _handlePl3[5] = { 0 };
        int _handlePl4[5] = { 0 };
        int _handlePl5[5] = { 0 };
        int _handlePl0;
       // Actor::Actor& _actor; //!< �A�N�^�[�N���X�̎Q��


    };

}


