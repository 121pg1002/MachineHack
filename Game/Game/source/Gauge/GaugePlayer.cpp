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
#include "../Actor/Actor.h"
namespace {
  constexpr int  _aniSpeed= 10;//アニメーション速度
  constexpr int _cgNum = 5;//画像枚数
  constexpr float _cgXPosition = 85.0/2;//エネルギーゲージの配置調整用変数
  constexpr float _cgYPosition = 140.0;
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
        _gaugePlayer = 100;
        _gaugeCount = 0;
        _gaugeTimer = 0;
    }
    void GaugePlayer::Update() {
        if (_gaugePlayer > 100) {
            _gaugePlayer = 100;
       }
      _gaugeTimer++;
    }

    void GaugePlayer::Update(Actor::Actor& act) {

        if (_gaugeCount % 15 == 0) {
            _gaugePlayer--;
        }

        _gaugeCount++;
    }
    void GaugePlayer::DownGauge(const int gauge) {
        _gaugePlayer -= gauge;
    }
    void GaugePlayer::PlusGauge(const int gauge) {
        _gaugePlayer += gauge;
    }

    void GaugePlayer::Draw(Actor::Actor& act) {
   
        //  GaugeBase::Draw(act);
        auto gaugeStr = std::to_string(_gaugePlayer);
        auto pos = act.GetPosition();
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
        DrawString(static_cast<int>(v.x), static_cast<int>(v.y) - 250, gaugeStr.c_str(), GetColor(0, 255, 0));
        //DrawString(1000,  200, gaugeStr.c_str(), GetColor(0, 255, 0));
       // DrawGraph(static_cast<int>(v.x), static_cast<int>(v.y), _handlePl, TRUE);

        if (_gaugePlayer < 1) {
        DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl0, TRUE);
        }
        else if (_gaugePlayer > 0 && _gaugePlayer < 21) {
        DrawGraph(static_cast<int>(v.x)-_cgXPosition, static_cast<int>(v.y) - _cgYPosition, _handlePl1[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugePlayer > 20 && _gaugePlayer < 41) {
          DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl2[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugePlayer > 40 && _gaugePlayer < 61) {
          DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl3[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugePlayer > 60 && _gaugePlayer < 81) {
          DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl4[(_gaugeTimer / _aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugePlayer > 80 && _gaugePlayer < 100) {
          DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl5[(_gaugeTimer /_aniSpeed) % _cgNum], TRUE);
        }
        else if (_gaugePlayer > 99) {
            DrawGraph(static_cast<int>(v.x) - _cgXPosition , static_cast<int>(v.y) - _cgYPosition, _handlePl, TRUE);
        }
    }
}
