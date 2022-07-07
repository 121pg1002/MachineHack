/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ƒQ[ƒW‚ÌŠî’êƒNƒ‰ƒX
 *
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/

#include "GaugeBase.h"
#include <string>
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/Actor.h"

namespace MachineHuck::Gauge {

    GaugeBase::GaugeBase(AppFrame::Game& game)
        : Scene{ game } {
        _gaugeCount = 0;
    }

    void GaugeBase::Init() {
        const AppFrame::Asset::AssetServer::TextureMap textureNumber{
            {"Normal0", {"energy/02_Value/01_’Êí/0.png", 1, 1, 23, 32}},
            {"Normal1", {"energy/02_Value/01_’Êí/1.png", 1, 1, 23, 32}},
            {"Normal2", {"energy/02_Value/01_’Êí/2.png", 1, 1, 23, 32}},
            {"Normal3", {"energy/02_Value/01_’Êí/3.png", 1, 1, 23, 32}},
            {"Normal4", {"energy/02_Value/01_’Êí/4.png", 1, 1, 23, 32}},
            {"Normal5", {"energy/02_Value/01_’Êí/5.png", 1, 1, 23, 32}},
            {"Normal6", {"energy/02_Value/01_’Êí/6.png", 1, 1, 23, 32}},
            {"Normal7", {"energy/02_Value/01_’Êí/7.png", 1, 1, 23, 32}},
            {"Normal8", {"energy/02_Value/01_’Êí/8.png", 1, 1, 23, 32}},
            {"Normal9", {"energy/02_Value/01_’Êí/9.png", 1, 1, 23, 32}},

            {"Giri0", {"energy/02_Value/02_•m€/0.png", 1, 1, 23, 32}},
            {"Giri1", {"energy/02_Value/02_•m€/1.png", 1, 1, 23, 32}},
            {"Giri2", {"energy/02_Value/02_•m€/2.png", 1, 1, 23, 32}},
            {"Giri3", {"energy/02_Value/02_•m€/3.png", 1, 1, 23, 32}},
            {"Giri4", {"energy/02_Value/02_•m€/4.png", 1, 1, 23, 32}},
            {"Giri5", {"energy/02_Value/02_•m€/5.png", 1, 1, 23, 32}},
            {"Giri6", {"energy/02_Value/02_•m€/6.png", 1, 1, 23, 32}},
            {"Giri7", {"energy/02_Value/02_•m€/7.png", 1, 1, 23, 32}},
            {"Giri8", {"energy/02_Value/02_•m€/8.png", 1, 1, 23, 32}},
            {"Giri9", {"energy/02_Value/02_•m€/9.png", 1, 1, 23, 32}},
        };
        auto& as = GetGame().GetAssetServer();
        as.LoadTextures(textureNumber);
        _handleNormalNumber[0] = as.GetTexture("Normal0");
        _handleNormalNumber[1] = as.GetTexture("Normal1");
        _handleNormalNumber[2] = as.GetTexture("Normal2");
        _handleNormalNumber[3] = as.GetTexture("Normal3");
        _handleNormalNumber[4] = as.GetTexture("Normal4");
        _handleNormalNumber[5] = as.GetTexture("Normal5");
        _handleNormalNumber[6] = as.GetTexture("Normal6");
        _handleNormalNumber[7] = as.GetTexture("Normal7");
        _handleNormalNumber[8] = as.GetTexture("Normal8");
        _handleNormalNumber[9] = as.GetTexture("Normal9");

        _handleGiri[0] = as.GetTexture("Giri0");
        _handleGiri[1] = as.GetTexture("Giri1");
        _handleGiri[2] = as.GetTexture("Giri2");
        _handleGiri[3] = as.GetTexture("Giri3");
        _handleGiri[4] = as.GetTexture("Giri4");
        _handleGiri[5] = as.GetTexture("Giri5");
        _handleGiri[6] = as.GetTexture("Giri6");
        _handleGiri[7] = as.GetTexture("Giri7");
        _handleGiri[8] = as.GetTexture("Giri8");
        _handleGiri[9] = as.GetTexture("Giri9");
        _gauge = 100;
        _gaugeCount = 0;
        lx = 0.0, ly = 0.0;
        _gaugeFlag = true;
    }


    void GaugeBase::Update() {

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

        //Å‘å’l‚ğ’´‚¦‚½‚©
        if (_gauge > _gaugeMax) {

            _gauge = _gaugeMax;
        }

    }

#ifdef _DEBUG
    void GaugeBase::Draw() {

        auto gaugeStr = std::to_string(_gauge);
        DrawString(10, 100, gaugeStr.c_str(), GetColor(255, 0, 0));
    }


#endif

    bool GaugeBase::IsGaugeZero(Actor::Actor& act) {

        //€–Só‘Ô‚©‚Ç‚¤‚©
        if (!act.IsDead()) {

        }
        return false;
    }
}

