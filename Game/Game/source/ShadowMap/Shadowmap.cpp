/*****************************************************************//**
 * @file  Shadowmap.h
 * @brief  シャドウマップクラス
 *
 * @author Kyouga Tagawa
 * @date   January 17 2022
 *********************************************************************/
#include "Shadowmap.h"
#include <AppFrame.h>
#include "../Actor/ActorServer.h"

namespace MachineHuck::ShadowMap {

    Shadowmap::Shadowmap(AppFrame::Game& game) : Actor{ game } {

    }

    void Shadowmap::SetShadowMap() {
        ShadowMaphandle = MakeShadowMap(8192, 8192);
        SetShadowMapLightDirection(ShadowMaphandle, VGet(0.01f, -0.5f, 0.0f));
        SetShadowMapDrawArea(ShadowMaphandle, VGet(-15000.0f, 0.0f, -15000.0f), VGet(3000.0f, 100.0f, 3000.0f));

    };

    void Shadowmap::SetPlayerShadowMapflg(bool flg) {
        for (auto&& actors : GetActorServer().GetActors()) {
            if (actors->GetTypeId() == TypeId::Player) {
                actors->SetShadowMapflg(flg);
                break;
            }
        }
    }
}