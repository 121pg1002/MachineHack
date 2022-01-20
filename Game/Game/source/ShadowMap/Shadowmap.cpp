/*****************************************************************//**
 * @file  Shadowmap.h
 * @brief  シャドウマップクラス
 *
 * @author Kyouga Tagawa
 * @date   January 17 2022
 *********************************************************************/
#include "Shadowmap.h"
#include <AppFrame.h>

namespace MachineHuck::ShadowMap {
    void Shadowmap::SetShadowMap() {
        ShadowMaphandle = MakeShadowMap(1024, 1024);
        SetShadowMapLightDirection(ShadowMaphandle, VGet(0.0f, -0.5f, 0.0f));
        SetShadowMapDrawArea(ShadowMaphandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));
    };
}