/*****************************************************************//**
 * @file   EffectLaser.cpp
 * @brief  レーザーエフェクトクラス
 *
 * @author yamawaki kota
 * @date   December 28 2021
 *********************************************************************/
#include "EffectLaser.h"
namespace MachineHuck::Effect {
    void EffectLaser::LoadEffect(std::string _keyname, std::string _filepass, float expansion) {
        EffectServer::LoadEffect(_keyname, _filepass, expansion);
        keyname.push_back(_keyname);
    }

    void EffectLaser::Update() {
        if (GetTime() % /*90*/180 == 0) {
            EffectServer::PlayEffect2D(keyname[0]);
            //SetEffect2DPos(960,540);
            SetEffect2DPos(100, 540);
        }
        EffectServer::SetPositionEffect2D(GetPosition2D(), keyname[0]);
        //int x = GetPosition2D().first + 5;
        int x = GetPosition2D().first + 180;
        SetEffect2DPos(x, GetPosition2D().second);
        PassingTime(1);
        EffectServer::UpdateEffect2D();

    }

    void EffectLaser::Render() {
        EffectServer::RenderEffect2D();
    }
}