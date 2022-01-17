
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  �Q�[�W�̊��N���X
 * 
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/
#pragma once

class GaugeBase {

public:
    void Init();
    void Update();
    void Draw();

    /**
     * @brief  �Q�[�W�̗ʂ��擾 
     * @return 
     */
    int GetGauge() { return _gauge; }


private:

    int _gauge{100};

};
