/*****************************************************************//**
 * @file   SceneSlideIn.cpp
 * @brief  スライドインクラス
 * 
 * @author Kota Yamawaki, hikaru Goto
 * @date   February 2022
 *********************************************************************/
#include "SceneSlideIn.h"
#include "../Flag/FlagData.h"
namespace MachineHuck::Scene {

    SceneSlideIn::SceneSlideIn(AppFrame::Game& game)
        :Scene{ game } {

    }
    void SceneSlideIn::Init() {
        const AppFrame::Asset::AssetServer::TextureMap texSceneSlideIn{
          {"XSlideIn",{"title/XSlideIn.png",1,1,3840,1080}},
          {"YSlideIn",{"title/YSlideIn.png",1,1,1920,2160}}
        };
        auto& as = GetAssetServer();
        as.LoadTextures(texSceneSlideIn);
        _cgXSlideIn = as.GetTexture("XSlideIn");
        _cgYSlideIn = as.GetTexture("YSlideIn");
    }

    void SceneSlideIn::Enter() {
        _xSlideIn = 0;
    }


    void SceneSlideIn::Update() {
        _xSlideIn -= 60;

        if (_xSlideIn < -120) {
            MachineHuck::Flag::FlagData::SetBlackOutFlag(false);
        }
       

        if (_xSlideIn < -3840) {
            GetSceneServer().PopBack();
        }
    }
    void SceneSlideIn::Render() {
        DrawGraph(_xSlideIn, _ySlideIn, _cgXSlideIn, TRUE);
    }


}
