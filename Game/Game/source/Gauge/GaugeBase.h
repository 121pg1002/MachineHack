
/*****************************************************************//**
 * @file   GaugeBase.h
 * @brief  ゲージの基底クラス
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
     * @brief  ゲージの量を取得 
     * @return 
     */
    int GetGauge() { return _gauge; }


private:

    int _gauge{100};

};
