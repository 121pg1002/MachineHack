
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  �Q�[�W�̊��N���X
 *
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
namespace MachineHuck::Actor {
    class Actor;
}
//namespace AppFrame::Scene {
//    class Scene;
//}

namespace MachineHuck::Gauge {

    /**
     * @class GaugeBase
     * @brief �Q�[�W�̊Ǘ��N���X
     */
    class GaugeBase : public AppFrame::Scene::Scene {

    public:

        /**
         * @brief �R���X�g���N�^
         * @param act �A�N�^�[�N���X�̎Q��
         */
        GaugeBase(AppFrame::Game& game);

        /**
         * @brief ������
         */
        void Init();

        /**
         * @brief �X�V
         * @param act �A�N�^�[�N���X�̎Q��
         */
        void Update();

#ifdef _DEBUG
        /**
         * @brief �`��
         */
        void Draw();

        ///**
        // * @brief �`��
        // * @param act
        // */
        //void Draw();
#endif

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

        void SetGaugeFlag(bool flag) { _gaugeFlag = flag; };
        bool GetGaygeFlag() { return _gaugeFlag; }
    protected:
        int _gaugeNumberOnes;//��̈ʂ̐���
        int _gaugeNumberTens;//�\�̈ʂ̐���
        int _gaugeNumberHuns;//�S�̈ʂ̐���
        int _gaugeNumber;//�Q�[�W�̐��l
        float _gauge{ 100.0f };    //!< �G�l���M�[�Q�[�W�̗�
        float _gaugeMax{ 100.0f }; //!< �G�l���M�[�Q�[�W�̍ő�l
        int _gaugeCount;      //!< �Q�[�W�����炷�J�E���^
        bool _gaugeFlag;  //�v���C���[�Q�[�W�A�G�l�~�[�Q�[�W�̐؂�ւ��t���O

        int _handleNormalNumber[10] = { 0 };//���l  
        int _handleGiri[10] = { 0 };

        double lx{ 0.0 }, ly{ 0.0 };                    //!< ���A�i���O�X�e�B�b�N�̌X��

    };

}


