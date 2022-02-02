
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
  class GaugeEnemy :public GaugeBase {
  public:

    /**
     * @brief �R���X�g���N�^
     * @param act �A�N�^�[�N���X�̎Q��
     */
    GaugeEnemy(Actor::Actor& act);

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




  private:

    //int _gauge{ 100 };    //!< �G�l���M�[�Q�[�W�̗�
    //int _gaugeMax{ 100 }; //!< �G�l���M�[�Q�[�W�̍ő�l
    int _gaugeCount;      //!< �Q�[�W�����炷�J�E���^

   // Actor::Actor& _actor; //!< �A�N�^�[�N���X�̎Q��
    int _handleEn;          //�G�l���M�[�Q�[�W���^��
    int _handleEn1[5] = { 0 };
    int _handleEn2[5] = { 0 };
    int _handleEn3[5] = { 0 };
    int _handleEn4[5] = { 0 };
    int _handleEn5[5] = { 0 };
    int _handleEn0;
    int _gaugeTimer{ 0 };
  };
}