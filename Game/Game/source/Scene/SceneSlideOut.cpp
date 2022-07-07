
/*****************************************************************//**
 * @file   SceneSlideOut.cpp
 * @brief  スライドアウトクラス
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#include "SceneSlideOut.h"
#include "../Flag/FlagData.h"

namespace MachineHuck::Scene {

    SceneSlideOut::SceneSlideOut(AppFrame::Game& game)
        :Scene{ game } {
    }
    void SceneSlideOut::Init() {
        const AppFrame::Asset::AssetServer::TextureMap texSlideOut{
          {"XSlideOut",{"title/XSlideOut.png",1,1,3840,1080}},
          {"YSlideOut",{"title/YSlideOut.png",1,1,1920,2160}}
        };
        auto& as = GetAssetServer();
        as.LoadTextures(texSlideOut);
        _cgXSlideOut = as.GetTexture("XSlideOut");
        _cgYSlideOut = as.GetTexture("YSlideOut");
        // _ySlideOut = 0;
    }

    void SceneSlideOut::Enter() {
        _xSlideOut = 1920;
    }

    void SceneSlideOut::Update() {
        _xSlideOut -= 60;

        if (_xSlideOut < -960) {

            GetSceneServer().PopBack(false);
            MachineHuck::Flag::FlagData::SetSlideOut(false);
            MachineHuck::Flag::FlagData::SetBlackOutFlag(true);

        }
    }
    void SceneSlideOut::Render() {
        DrawGraph(_xSlideOut, _ySlideOut, _cgXSlideOut, TRUE);
    }

}
