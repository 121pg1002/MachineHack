/*****************************************************************//**
 * @file  Shadowmap.h
 * @brief  シャドウマップクラス
 *
 * @author Kyouga Tagawa
 * @date   January 17 2022
 *********************************************************************/
#pragma once
#include "../Actor/Actor.h"
namespace MachineHuck::ShadowMap {
    class Shadowmap :public Actor::Actor {
    public:
        Shadowmap(AppFrame::Game& _game);
        virtual ~Shadowmap() override = default;

        void SetShadowMap();
        int GetShadowmap() { return ShadowMaphandle; }
        void SetPlayerShadowMapflg(bool flg);
        TypeId GetTypeId()const override { return TypeId::ShadowMap; };
    private:
        int ShadowMaphandle;
    };
}