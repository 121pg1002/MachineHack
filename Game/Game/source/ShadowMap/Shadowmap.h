/*****************************************************************//**
 * @file  Shadowmap.h
 * @brief  シャドウマップクラス
 *
 * @author Kyouga Tagawa
 * @date   January 17 2022
 *********************************************************************/
#pragma once
#include<AppFrame.h>
#include "../Player/Player.h"
#include "../Actor/Actor.h"

namespace MachineHuck{
    namespace Player {
        class Player;
    }


}



namespace MachineHuck::ShadowMap {
    class Shadowmap {
    public:
        void SetShadowMap();
        void SetShadowMapflg(int flg) { ShadowMapflg = flg; }
        int GetShadowmap() { return ShadowMaphandle; }
        int GetShadowmapflg() { return ShadowMapflg; }
        void SetflgPlayer(std::unique_ptr<MachineHuck::Actor::Actor> player, int flg) { player->SetShadowMapflg(flg); }
    private:
        int ShadowMaphandle;
        int ShadowMapflg;
        std::unique_ptr<MachineHuck::Player::Player> _player;
    };
}