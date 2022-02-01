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
#include "../Actor/Actor.h"
namespace {
  constexpr int  _aniSpeed = 10;//アニメーション速度
  constexpr int _cgNum = 5;//画像枚数
  constexpr float _cgXPosition = 85.0;//エネルギーゲージの配置調整用変数
  constexpr float _cgYPosition = 140.0;
}
namespace MachineHuck::Gauge {

    GaugeEnemy::GaugeEnemy(Actor::Actor& act) : GaugeBase{ act } {
        _gaugeCount = 0;
    }

    void GaugeEnemy::Init(Actor::Actor& act) {
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
        auto& as = act.GetGame().GetAssetServer();
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
        _handleEn0 = act.GetGame().GetAssetServer().GetTexture("Energy0");
        _gaugeTimer = 0;
    }
    ///　更新
    void GaugeEnemy::Update() {

      _gaugeTimer++;
    }
    ///  更新
    void GaugeEnemy::Update(Actor::Actor& act) {

        if (_gaugeCount % 15 == 0) {
            _gauge--;
        }
        _gaugeCount++;
    }

    void GaugeEnemy::Draw(Actor::Actor& act) {
      //  GaugeBase::Draw(act);
        auto gaugeStr = std::to_string(_gauge);
        auto pos = act.GetPosition();
        auto v = ConvWorldPosToScreenPos(ToDX(pos));
       DrawString(static_cast<int>(v.x)+200, static_cast<int>(v.y), gaugeStr.c_str(), GetColor(255, 0, 0));
        //DrawString(1000,  200, gaugeStr.c_str(), GetColor(0, 255, 0));
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
    }
}
