#include "EffectWind.h"
namespace MachineHuck::Effect {
    void EffectWind::LoadEffect(std::string _keyname, std::string _filepass, float expansion) {
        EffectServer::LoadEffect(_keyname, _filepass, expansion);
        keyname.push_back(_keyname);
    }

    void EffectWind::Update() {
        EffectServer::SyncCamEffekseer();
        if (GetTime() % 180 == 0) {
            EffectServer::PlayEffect3D(keyname[0]);
            SetEffect3DPos(VGet(0, 0, 0));
        }
        EffectServer::SetPositionEffect3D(GetPosition(), keyname[0]);
        VECTOR pos = VAdd(VGet(0, 0, -5), GetPosition());
        SetEffect3DPos(pos);
        PassingTime(1);
        EffectServer::UpdateEffect3D();

    }

    void EffectWind::Render() {
        EffectServer::RenderEffect3D();
    }
}