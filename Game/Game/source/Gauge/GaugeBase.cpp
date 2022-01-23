/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ゲージの基底クラス
 * 
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/

#include "GaugeBase.h"
#include <string>
#include <DxLib.h>
#include "../Actor/Actor.h"

namespace MachineHuck::Gauge {

    GaugeBase::GaugeBase(Actor::Actor& act) : _actor{ act } {
        _gaugeCount = 0;
    }

    void GaugeBase::Init() {
        _gauge = 100;
        _gaugeCount = 0;
    }

    void GaugeBase::Update(Actor::Actor& act) {

        if (_gaugeCount % 15 == 0) {
            _gauge--;
        }
        _gaugeCount++;
    }

    void GaugeBase::DownGauge(const int gauge) {
        _gauge -= gauge;
    }

    void GaugeBase::PlusGauge(const int gauge) {
    
        _gauge += gauge;

        //最大値を超えたか
        if (_gauge > _gaugeMax) {
        
            _gauge = _gaugeMax;
        }
    
    }

#ifdef _DEBUG
    void GaugeBase::Draw() {

        auto gaugeStr = std::to_string(_gauge);
        DrawString(10, 100, gaugeStr.c_str(), GetColor(255, 0, 0));
       // DrawStringToZBuffer(10, 50, gaugeStr.c_str(), DX_ZWRITE_MASK);
    }

    void GaugeBase::Draw(Actor::Actor& act) {
    
        auto gaugeStr = std::to_string(_gauge);
        auto pos = act.GetPosition();
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y), gaugeStr.c_str(), GetColor(255, 0, 0));

    }

#endif

    bool GaugeBase::IsGaugeZero(Actor::Actor& act) {

        //死亡状態かどうか
        if (!act.IsDead()) {

            //ゲージの量が0以下か
            if (act.GetGaugeBase().GetGauge() <= 0) {
                return true;
            }
            else {
                return false;
            }
        
        }
        return false;
    }
}


