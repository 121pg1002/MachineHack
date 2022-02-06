/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ÉQÅ[ÉWÇÃäÓíÍÉNÉâÉX
 *
 * @author hikaru Goto
 * @date   January 25 2022
 *********************************************************************/

#include "GaugePlayer.h"
#include <string>
#include <DxLib.h>
#include "../Actor/Actor.h"
namespace {
    constexpr int  _aniSpeed = 10;//ÉAÉjÉÅÅ[ÉVÉáÉìë¨ìx
    constexpr int _cgNum = 5;//âÊëúñáêî
    constexpr float _cgXPosition = 85.0 / 2;//ÉGÉlÉãÉMÅ[ÉQÅ[ÉWÇÃîzíuí≤êÆópïœêî
    constexpr float _cgYPosition = 140.0;
    constexpr float _cgXNumPosition = 23 / 2;//êîílÉQÅ[ÉWÇÃîzíu
    constexpr float _cgYNumPosition = 60;


}
namespace MachineHuck::Gauge {

    GaugePlayer::GaugePlayer(Actor::Actor& act) : GaugeBase{ act } {
        _gaugeCount = 0;
        //_handlePl = act.GetGame().GetAssetServer().GetTexture("EnergyPl6");
       // _handlePl1[] = act.GetGame().GetAssetServer().GetTexture("EnergyPl1" );
    }

    void GaugePlayer::Init(Actor::Actor& act) {
        const AppFrame::Asset::AssetServer::TextureMap texturePlayerGauge{
            /*     {"EnergyPl1", {"energy/playerEnergy1.png", 5, 1, 425, 85}},
                 {"EnergyPl2", {"energy/playerEnergy2.png", 5, 1, 425, 85}},
                 {"EnergyPl3", {"energy/playerEnergy3.png", 5, 1, 425, 85}},
                 {"EnergyPl4", {"energy/playerEnergy4.png", 5, 1, 425, 85}},
                 {"EnergyPl5", {"energy/playerEnergy5.png", 5, 1, 425, 85}},*/
                 {"Normal0", {"energy/02_Value/01_í èÌ/0.png", 1, 1, 23, 32}},
                 {"Normal1", {"energy/02_Value/01_í èÌ/1.png", 1, 1, 23, 32}},
                 {"Normal2", {"energy/02_Value/01_í èÌ/2.png", 1, 1, 23, 32}},
                 {"Normal3", {"energy/02_Value/01_í èÌ/3.png", 1, 1, 23, 32}},
                 {"Normal4", {"energy/02_Value/01_í èÌ/4.png", 1, 1, 23, 32}},
                 {"Normal5", {"energy/02_Value/01_í èÌ/5.png", 1, 1, 23, 32}},
                 {"Normal6", {"energy/02_Value/01_í èÌ/6.png", 1, 1, 23, 32}},
                 {"Normal7", {"energy/02_Value/01_í èÌ/7.png", 1, 1, 23, 32}},
                 {"Normal8", {"energy/02_Value/01_í èÌ/8.png", 1, 1, 23, 32}},
                 {"Normal9", {"energy/02_Value/01_í èÌ/9.png", 1, 1, 23, 32}},

                 {"Giri0", {"energy/02_Value/02_ïméÄ/0.png", 1, 1, 23, 32}},
                 {"Giri1", {"energy/02_Value/02_ïméÄ/1.png", 1, 1, 23, 32}},
                 {"Giri2", {"energy/02_Value/02_ïméÄ/2.png", 1, 1, 23, 32}},
                 {"Giri3", {"energy/02_Value/02_ïméÄ/3.png", 1, 1, 23, 32}},
                 {"Giri4", {"energy/02_Value/02_ïméÄ/4.png", 1, 1, 23, 32}},
                 {"Giri5", {"energy/02_Value/02_ïméÄ/5.png", 1, 1, 23, 32}},
                 {"Giri6", {"energy/02_Value/02_ïméÄ/6.png", 1, 1, 23, 32}},
                 {"Giri7", {"energy/02_Value/02_ïméÄ/7.png", 1, 1, 23, 32}},
                 {"Giri8", {"energy/02_Value/02_ïméÄ/8.png", 1, 1, 23, 32}},
                 {"Giri9", {"energy/02_Value/02_ïméÄ/9.png", 1, 1, 23, 32}},
                 {"EnergyPl6", {"energy/playerEnergy6.png", 1, 1, 85, 85}},
                 {"EnergyPl11", {"energy/kari/01.png", 1, 1, 85, 85}},
                 {"EnergyPl12", {"energy/kari/02.png", 1, 1, 85, 85}},
                 {"EnergyPl13", {"energy/kari/03.png", 1, 1, 85, 85}},
                 {"EnergyPl14", {"energy/kari/04.png", 1, 1, 85, 85}},
                 {"EnergyPl15", {"energy/kari/05.png", 1, 1, 85, 85}},
                 {"EnergyPl21", {"energy/kari/20/01.png", 1, 1, 85, 85}},
                 {"EnergyPl22", {"energy/kari/20/02.png", 1, 1, 85, 85}},
                 {"EnergyPl23", {"energy/kari/20/03.png", 1, 1, 85, 85}},
                 {"EnergyPl24", {"energy/kari/20/04.png", 1, 1, 85, 85}},
                 {"EnergyPl25", {"energy/kari/20/05.png", 1, 1, 85, 85}},
                 {"EnergyPl31", {"energy/kari/40/01.png", 1, 1, 85, 85}},
                 {"EnergyPl32", {"energy/kari/40/02.png", 1, 1, 85, 85}},
                 {"EnergyPl33", {"energy/kari/40/03.png", 1, 1, 85, 85}},
                 {"EnergyPl34", {"energy/kari/40/04.png", 1, 1, 85, 85}},
                 {"EnergyPl35", {"energy/kari/40/05.png", 1, 1, 85, 85}},
                 {"EnergyPl41", {"energy/kari/60/01.png", 1, 1, 85, 85}},
                 {"EnergyPl42", {"energy/kari/60/02.png", 1, 1, 85, 85}},
                 {"EnergyPl43", {"energy/kari/60/03.png", 1, 1, 85, 85}},
                 {"EnergyPl44", {"energy/kari/60/04.png", 1, 1, 85, 85}},
                 {"EnergyPl45", {"energy/kari/60/05.png", 1, 1, 85, 85}},
                 {"EnergyPl51", {"energy/kari/80/01.png", 1, 1, 85, 85}},
                 {"EnergyPl52", {"energy/kari/80/02.png", 1, 1, 85, 85}},
                 {"EnergyPl53", {"energy/kari/80/03.png", 1, 1, 85, 85}},
                 {"EnergyPl54", {"energy/kari/80/04.png", 1, 1, 85, 85}},
                 {"EnergyPl55", {"energy/kari/80/05.png", 1, 1, 85, 85}}
        };
        auto& as = act.GetGame().GetAssetServer();
        as.LoadTextures(texturePlayerGauge);
        _handlePl = as.GetTexture("EnergyPl6");
        //        _handlePl1[5] = as.GetTextureAni("EnergyPl1",5);
        _handlePl1[0] = as.GetTexture("EnergyPl11");
        _handlePl1[1] = as.GetTexture("EnergyPl12");
        _handlePl1[2] = as.GetTexture("EnergyPl13");
        _handlePl1[3] = as.GetTexture("EnergyPl14");
        _handlePl1[4] = as.GetTexture("EnergyPl15");
        _handlePl2[0] = as.GetTexture("EnergyPl21");
        _handlePl2[1] = as.GetTexture("EnergyPl22");
        _handlePl2[2] = as.GetTexture("EnergyPl23");
        _handlePl2[3] = as.GetTexture("EnergyPl24");
        _handlePl2[4] = as.GetTexture("EnergyPl25");
        _handlePl3[0] = as.GetTexture("EnergyPl31");
        _handlePl3[1] = as.GetTexture("EnergyPl32");
        _handlePl3[2] = as.GetTexture("EnergyPl33");
        _handlePl3[3] = as.GetTexture("EnergyPl34");
        _handlePl3[4] = as.GetTexture("EnergyPl35");
        _handlePl4[0] = as.GetTexture("EnergyPl41");
        _handlePl4[1] = as.GetTexture("EnergyPl42");
        _handlePl4[2] = as.GetTexture("EnergyPl43");
        _handlePl4[3] = as.GetTexture("EnergyPl44");
        _handlePl4[4] = as.GetTexture("EnergyPl45");
        _handlePl5[0] = as.GetTexture("EnergyPl51");
        _handlePl5[1] = as.GetTexture("EnergyPl52");
        _handlePl5[2] = as.GetTexture("EnergyPl53");
        _handlePl5[3] = as.GetTexture("EnergyPl54");
        _handlePl5[4] = as.GetTexture("EnergyPl55");
        _handlePl0 = act.GetGame().GetAssetServer().GetTexture("Energy0");
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
        _gaugeTimer = 0;
    }
    void GaugePlayer::Update() {
        if (_gauge > 100) {
            _gauge = 100;
        }
        _gaugeTimer++;
        //_gauge=(_gauge/_gaugeMAX)*100
      //  _gaugeNumber = _gauge;

        if (_gauge == _gaugeMax) {
            _gaugeNumber = _gauge / _gaugeMax * 100;
        }
        else {
            _gaugeNumber = _gauge % _gaugeMax;
        }
        _gaugeNumberHuns = _gaugeNumber / 100;
        if (_gaugeNumberHuns != 1) {
            _gaugeNumberTens = _gaugeNumber / 10;
            _gaugeNumberOnes = _gaugeNumber % 10;
        }
        else {
            _gaugeNumberTens = 0;
            _gaugeNumberOnes = 0;
        }
    }

    void GaugePlayer::Update(Actor::Actor& act) {

        if (_gaugeCount % 15 == 0) {
            _gauge--;
        }

        _gaugeCount++;
    }
    void GaugePlayer::DownGauge(const int gauge) {
        _gauge -= gauge;
    }
    void GaugePlayer::PlusGauge(const int gauge) {
        _gauge += gauge;
    }

    void GaugePlayer::Draw(Actor::Actor& act) {

        //  GaugeBase::Draw(act);
        auto gaugeStr = std::to_string(_gauge);
        auto gaugemaxStr = std::to_string(_gaugeMax);

        auto pos = act.GetPosition();
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y) - 250, gaugeStr.c_str(), GetColor(0, 255, 0));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y) - 200, gaugemaxStr.c_str(), GetColor(0, 255, 0));
        //DrawString(1000,  200, gaugeStr.c_str(), GetColor(0, 255, 0));
       // DrawGraph(static_cast<int>(v.x), static_cast<int>(v.y), _handlePl, TRUE);

        double gauge = static_cast<double>(_gauge);
        double gaugemax = static_cast<double>(_gaugeMax);

        if (_gauge < 1) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl0, TRUE);
        }
        else if (_gauge > 0 && _gauge < 21) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl1[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 20 && _gauge < 41) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl2[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 40 && _gauge < 61) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl3[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 60 && _gauge < 81) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl4[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 80 && _gauge < 100) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl5[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 99) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl, TRUE);
        }
        //100ÇÃÇ≠ÇÁÇ¢
        switch (_gaugeNumberHuns)
        {
        case 1:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition - 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[1], TRUE);
            break;
        default:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition - 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[0], TRUE);
            break;
        }
        //10ÇÃÇ≠ÇÁÇ¢
        switch (_gaugeNumberTens)
        {
        case 1:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[1], TRUE);
            break;
        case 2:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[2], TRUE);
            break;
        case 3:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[3], TRUE);
            break;
        case 4:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[4], TRUE);
            break;
        case 5:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[5], TRUE);
            break;
        case 6:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[6], TRUE);
            break;
        case 7:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[7], TRUE);
            break;
        case 8:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[8], TRUE);
            break;
        case 9:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[9], TRUE);
            break;
        default:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[0], TRUE);
            break;
        }
        //1ÇÃÇ≠ÇÁÇ¢
        switch (_gaugeNumberOnes)
        {
        case 1:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[1], TRUE);
            break;
        case 2:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[2], TRUE);
            break;
        case 3:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[3], TRUE);
            break;
        case 4:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[4], TRUE);
            break;
        case 5:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[5], TRUE);
            break;
        case 6:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[6], TRUE);
            break;
        case 7:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[7], TRUE);
            break;
        case 8:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[8], TRUE);
            break;
        case 9:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[9], TRUE);
            break;
        default:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition + 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[0], TRUE);
            break;
        }

    }
}
