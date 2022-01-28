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
        ShadowMaphandle = MakeShadowMap(1024, 1024);
        SetShadowMapLightDirection(ShadowMaphandle, VGet(0.0f, -0.5f, 0.0f));
        SetShadowMapDrawArea(ShadowMaphandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

    };

    void Shadowmap::SetPlayerShadowMapflg(bool flg) {
        for (auto&& actors : GetActorServer().GetActors()) {
            if (actors->GetTypeId() == TypeId::Player) {
                actors->SetShadowMapflg(true);
                break;
            }
        }
    }
}