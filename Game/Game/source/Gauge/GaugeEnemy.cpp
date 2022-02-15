/*****************************************************************//**
 * @file   GaugeBase.cpp
 * @brief  ゲージの基底クラス
 *
 * @author hikaru Goto
 * @date   January 17 2022
 *********************************************************************/

#include "GaugeEnemy.h"
#include <string>
#include <DxLib.h>
#include "AppFrame.h"
#include "../Actor/Actor.h"
namespace {
    constexpr int  _aniSpeed = 10;//アニメーション速度
    constexpr int _cgNum = 5;//画像枚数
    constexpr float _cgXPosition = 85.0 / 2;//エネルギーゲージの配置調整用変数
    constexpr float _cgYPosition = 140.0;
    constexpr float _cgXNumPosition = 23 / 2;//数値ゲージの配置
    constexpr float _cgYNumPosition = 60;
}
namespace MachineHuck::Gauge {

    GaugeEnemy::GaugeEnemy(AppFrame::Game& game) : GaugeBase{ game } {
        _gaugeCount = 0;
    }

    void GaugeEnemy::Init() {
        _gauge = 100;
        _gaugeCount = 0;
        const AppFrame::Asset::AssetServer::TextureMap textureTackleEnemyGauge{
          {"EnergyEn11", {"energy/kari/e1/01.png", 1, 1, 85, 85}},
          {"EnergyEn12", {"energy/kari/e1/02.png", 1, 1, 85, 85}},
          {"EnergyEn13", {"energy/kari/e1/03.png", 1, 1, 85, 85}},
          {"EnergyEn14", {"energy/kari/e1/04.png", 1, 1, 85, 85}},
          {"EnergyEn15", {"energy/kari/e1/05.png", 1, 1, 85, 85}},
          {"EnergyEn21", {"energy/kari/e20/01.png", 1, 1, 85, 85}},
          {"EnergyEn22", {"energy/kari/e20/02.png", 1, 1, 85, 85}},
          {"EnergyEn23", {"energy/kari/e20/03.png", 1, 1, 85, 85}},
          {"EnergyEn24", {"energy/kari/e20/04.png", 1, 1, 85, 85}},
          {"EnergyEn25", {"energy/kari/e20/05.png", 1, 1, 85, 85}},
          {"EnergyEn31", {"energy/kari/e40/01.png", 1, 1, 85, 85}},
          {"EnergyEn32", {"energy/kari/e40/02.png", 1, 1, 85, 85}},
          {"EnergyEn33", {"energy/kari/e40/03.png", 1, 1, 85, 85}},
          {"EnergyEn34", {"energy/kari/e40/04.png", 1, 1, 85, 85}},
          {"EnergyEn35", {"energy/kari/e40/05.png", 1, 1, 85, 85}},
          {"EnergyEn41", {"energy/kari/e60/01.png", 1, 1, 85, 85}},
          {"EnergyEn42", {"energy/kari/e60/02.png", 1, 1, 85, 85}},
          {"EnergyEn43", {"energy/kari/e60/03.png", 1, 1, 85, 85}},
          {"EnergyEn44", {"energy/kari/e60/04.png", 1, 1, 85, 85}},
          {"EnergyEn45", {"energy/kari/e60/05.png", 1, 1, 85, 85}},
          {"EnergyEn51", {"energy/kari/e80/01.png", 1, 1, 85, 85}},
          {"EnergyEn52", {"energy/kari/e80/02.png", 1, 1, 85, 85}},
          {"EnergyEn53", {"energy/kari/e80/03.png", 1, 1, 85, 85}},
          {"EnergyEn54", {"energy/kari/e80/04.png", 1, 1, 85, 85}},
          {"EnergyEn55", {"energy/kari/e80/05.png", 1, 1, 85, 85}},
          {"EnergyEn6", {"energy/enemyEnergy6.png", 1, 1, 85, 85}}
        };
        auto& as = GetGame().GetAssetServer();
        as.LoadTextures(textureTackleEnemyGauge);
        _handleEn = as.GetTexture("EnergyEn6");
        _handleEn1[0] = as.GetTexture("EnergyEn11");
        _handleEn1[1] = as.GetTexture("EnergyEn12");
        _handleEn1[2] = as.GetTexture("EnergyEn13");
        _handleEn1[3] = as.GetTexture("EnergyEn14");
        _handleEn1[4] = as.GetTexture("EnergyEn15");
        _handleEn2[0] = as.GetTexture("EnergyEn21");
        _handleEn2[1] = as.GetTexture("EnergyEn22");
        _handleEn2[2] = as.GetTexture("EnergyEn23");
        _handleEn2[3] = as.GetTexture("EnergyEn24");
        _handleEn2[4] = as.GetTexture("EnergyEn25");
        _handleEn3[0] = as.GetTexture("EnergyEn31");
        _handleEn3[1] = as.GetTexture("EnergyEn32");
        _handleEn3[2] = as.GetTexture("EnergyEn33");
        _handleEn3[3] = as.GetTexture("EnergyEn34");
        _handleEn3[4] = as.GetTexture("EnergyEn35");
        _handleEn4[0] = as.GetTexture("EnergyEn41");
        _handleEn4[1] = as.GetTexture("EnergyEn42");
        _handleEn4[2] = as.GetTexture("EnergyEn43");
        _handleEn4[3] = as.GetTexture("EnergyEn44");
        _handleEn4[4] = as.GetTexture("EnergyEn45");
        _handleEn5[0] = as.GetTexture("EnergyEn51");
        _handleEn5[1] = as.GetTexture("EnergyEn52");
        _handleEn5[2] = as.GetTexture("EnergyEn53");
        _handleEn5[3] = as.GetTexture("EnergyEn54");
        _handleEn5[4] = as.GetTexture("EnergyEn55");
        _handleEn0 = GetGame().GetAssetServer().GetTexture("Energy0");

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
        _gaugeTimer = 0;
    }
    ///　更新
    void GaugeEnemy::Update() {

        _gaugeTimer++;
        _gaugeEnemyPosition = GetGaugeEnemyPosition();

        _gaugeNumber = _gauge / _gaugeMax * 100;
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

    void GaugeEnemy::Draw() {
        auto gaugeStr = std::to_string(_gauge);
        auto pos = _gaugeEnemyPosition;
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
        DrawString(static_cast<int>(v.x) + 200, static_cast<int>(v.y), gaugeStr.c_str(), GetColor(255, 0, 0));
        DrawString(1000, 200, gaugeStr.c_str(), GetColor(255, 0, 0));
        auto x = static_cast<int>(v.x) - _cgXPosition;
        auto y = static_cast<int>(v.y) - _cgYPosition;
        if (_gauge < 1) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn0, TRUE);
        }
        else if (_gauge > 0 && _gauge < 21) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn1[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 20 && _gauge < 41) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn2[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 40 && _gauge < 61) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn3[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 60 && _gauge < 81) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn4[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 80 && _gauge < 100) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn5[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gauge > 99) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handleEn, TRUE);
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
