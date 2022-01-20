/*****************************************************************//**
 * @file  Shadowmap.h
 * @brief  シャドウマップクラス
 *
 * @author Kyouga Tagawa
 * @date   January 17 2022
 *********************************************************************/
#pragma once
namespace MachineHuck::ShadowMap {
    class Shadowmap {
    public:
        void SetShadowMap();
        int GetShadowmap() { return ShadowMaphandle; }
    private:
        int ShadowMaphandle;
    };
}