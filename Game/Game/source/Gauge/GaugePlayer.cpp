/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ゲージの基底クラス
 *
 * @author hikaru Goto
 * @date   January 25 2022
 *********************************************************************/

#include "GaugePlayer.h"
#include <string>
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/Actor.h"
#include "../Gauge/GaugeEnemy.h"
#include "../Player/Player.h"
namespace {
    constexpr int  _aniSpeed = 10;//アニメーション速度
    constexpr int _cgNum = 5;//画像枚数
    constexpr float _cgXPosition = 85.0 / 2;//エネルギーゲージの配置調整用変数
    constexpr float _cgYPosition = 140.0;
    constexpr float _cgXNumPosition = 23 / 2;//数値ゲージの配置
    constexpr float _cgYNumPosition = 60;
    constexpr double _analogMin = 0.3;

}
namespace MachineHuck::Gauge {

    GaugePlayer::GaugePlayer(AppFrame::Game& game) : GaugeBase{ game } {
        _gaugeCount = 0;
    }

    void GaugePlayer::Init() {
        const AppFrame::Asset::AssetServer::TextureMap texturePlayerGauge{
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
        auto& as = GetGame().GetAssetServer();
        as.LoadTextures(texturePlayerGauge);
        _handlePl = as.GetTexture("EnergyPl6");
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
        _handlePl0 = GetGame().GetAssetServer().GetTexture("Energy0");
        auto& asn = GetGame().GetAssetServer();

        _handleNormalNumber[0] = asn.GetTexture("Normal0");
        _handleNormalNumber[1] = asn.GetTexture("Normal1");
        _handleNormalNumber[2] = asn.GetTexture("Normal2");
        _handleNormalNumber[3] = asn.GetTexture("Normal3");
        _handleNormalNumber[4] = asn.GetTexture("Normal4");
        _handleNormalNumber[5] = asn.GetTexture("Normal5");
        _handleNormalNumber[6] = asn.GetTexture("Normal6");
        _handleNormalNumber[7] = asn.GetTexture("Normal7");
        _handleNormalNumber[8] = asn.GetTexture("Normal8");
        _handleNormalNumber[9] = asn.GetTexture("Normal9");

        _handleGiri[0] = asn.GetTexture("Giri0");
        _handleGiri[1] = asn.GetTexture("Giri1");
        _handleGiri[2] = asn.GetTexture("Giri2");
        _handleGiri[3] = asn.GetTexture("Giri3");
        _handleGiri[4] = asn.GetTexture("Giri4");
        _handleGiri[5] = asn.GetTexture("Giri5");
        _handleGiri[6] = asn.GetTexture("Giri6");
        _handleGiri[7] = asn.GetTexture("Giri7");
        _handleGiri[8] = asn.GetTexture("Giri8");
        _handleGiri[9] = asn.GetTexture("Giri9");

        _gauge = 100;
        _gaugeTimer = 0;
    }

    void GaugePlayer::Update() {
        if (_gauge > _gaugeMax) {
            _gauge = _gaugeMax;
        }
        _gaugeTimer++;
        _gaugeNumber = _gauge / _gaugeMax * 100;
        _gaugeNumberHuns = _gauge / _gaugeMax;
        if (_gaugeNumberHuns != 1) {
            _gaugeNumberTens = _gaugeNumber / 10;
            _gaugeNumberOnes = _gaugeNumber % 10;
        }
        else {
            _gaugeNumberTens = 0;
            _gaugeNumberOnes = 0;
        }
        if (_gaugeTimer > 1) {
            if ((_oldPlayerPosition.GetX() != _gaugePlayerPosition.GetX() || _oldPlayerPosition.GetZ() != _gaugePlayerPosition.GetZ()) && _gaugePlayerPosition.GetY() == 0) {
                if (_gaugeCount % 15 == 0) {
                    _gauge--;
                }
                _oldPlayerPosition = _gaugePlayerPosition;
            }
        }
        _gaugeCount++;
    }
    void GaugePlayer::DownGauge(const int gauge) {
        _gauge -= gauge;
    }
    void GaugePlayer::PlusGauge(const int gauge) {
        _gauge += gauge;
    }

    void GaugePlayer::Draw() {
        auto gaugeStr = std::to_string(_gauge);
        auto gaugemaxStr = std::to_string(_gaugeMax);

        auto pos = _gaugePlayerPosition;
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y) - 250, gaugeStr.c_str(), GetColor(0, 255, 0));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y) - 200, gaugemaxStr.c_str(), GetColor(0, 255, 0));

        if (_gaugeNumber < 1) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl0, TRUE);
        }
        else if (_gaugeNumber > 0 && _gaugeNumber < 21) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl1[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugeNumber > 20 && _gaugeNumber < 41) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl2[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugeNumber > 40 && _gaugeNumber < 61) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl3[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugeNumber > 60 && _gaugeNumber < 81) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl4[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugeNumber > 80 && _gaugeNumber < 100) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl5[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugeNumber > 99) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl, TRUE);
        }
        //100のくらい
        switch (_gaugeNumberHuns)
        {
        case 1:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition - 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[1], TRUE);
            break;
        default:
            DrawGraph(static_cast<int>(v.x) - _cgXNumPosition - 23, static_cast<int>(v.y) - _cgYNumPosition, _handleNormalNumber[0], TRUE);
            break;
        }
        //10のくらい
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
        //1のくらい
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